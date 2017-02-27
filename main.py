#!/usr/bin/env python3
import pymysql
import ctypes
import threading
import getopt
import sys

# 首先配置数据库
config = dict(
    host='localhost',
    user='username',
    passwd='yourpassword',
    db='yourdatabasename',
    charset='utf8mb4'
)


class Book(ctypes.Structure):
    pass


class Main:
    help = '   -a 新增图书\n   -d 删除已经废弃不用的图书\n   -s 搜索图书的信息\n   -b 借书\n   -r 还书\n\n'

    def __init__(self):
        try:
            self.so = ctypes.cdll.LoadLibrary('libbook.so')
        except OSError as e:
            print(e)
        self.so.deletbook.restype = ctypes.c_int
        self.so.creatdata.restype = ctypes.POINTER(Book)
        self.so.loadbook.restype = ctypes.c_int
        self.so.repay.restype = ctypes.c_int
        print(self.help)
        self.sql = Sql()
        self.bo = self.so.creatdate(None)

    def main(self):
        opts, args = getopt.getopt(sys.argv[1:], 'ha:d:s:b:r:')
        for op, values in opts:
            if op == '-h':
                print(self.help)
                break

            elif op == '-a':
                index = input('序列号:')
                name = input('书名:')
                author = input('作者:')
                description = input('描述:')
                if self.bo is not None:
                    self.bo = self.so.addbook(self.bo, ctypes.c_ulong(index), ctypes.c_char_p(name),
                                              ctypes.c_char_p(author), ctypes.c_char_p(description))
                self.sql.adddata(index, name, author, description)

            elif op == '-d':
                index = input('序列号:')
                name = input('书名:')
                if self.bo is not None:
                    self.so.deletbook(self.bo, ctypes.c_ulong(index), ctypes.c_char_p(name))
                self.sql.deletdata(index)

            elif op == '-s':
                name = input('书名:')
                if self.bo is not None:
                    self.so.searchbook(self.bo, ctypes.c_char_p(name))
                else:
                    res = self.sql.search(name)
                    sum = 0
                    for i in res:
                        for j in i:
                            if j[4] == 1:
                                sum += 1
                    print('作者:', res[0][1], '共:', len(res), '其中', sum, '可以借阅')

            elif op == '-b':
                index = input('序列号:')
                if self.bo is not None:
                    self.so.loadbook(self.bo, ctypes.c_char_p(name))
                self.sql.writedata('b', index)

            elif op == '-r':
                index = input('序列号:')
                if self.bo is not None:
                    self.so.repay(self.bo, ctypes.c_ulong(index), ctypes.c_char_p(name))
                self.sql.writedata('r', index)


class Sql:
    sql_init = 'CREATE TABLE book (id INTEGER NOT NULL, bookname VARCHAR(100) NOT NULL, author VARCHAR(50) NOT NULL, ' \
               'description TEXT, flag TINYINT NOT NULL, PRIMARY KEY(id))character set utf8mb4;'
    sql_insert = 'INSERT INTO book (id, bookname, author, description, flag) VALUES({}, "{}", "{}", "{}", {});'
    sql_update = 'UPDATE book SET {} = {} WHERE id = {};'
    sql_search = 'SELECT * FROM book WHERE bookname = "{}";'
    sql_del = 'DELETE FROM book WHERE id = {};'

    def __init__(self):
        try:
            self.connect = pymysql.connect(**config)
        except pymysql.err.OperationalError as e:
            print(e, '检查是否配置正确...')
        try:
            with self.connect.cursor() as cu:
                cu.execute(self.sql_init)
            self.connect.commit()
        except pymysql.err.InternalError:
            pass

    def writedata(self, *args, **kwargs):
        if args[0] == 'b':
            with self.connect.cursor() as cu:
                cu.execute(self.sql_update.format('flag', '0', args[1]))
                self.connect.commit()
        else:
            with self.connect.cursor() as cu:
                cu.execute(self.sql_update.format('flag', '1', args[1]))
                self.connect.commit()

    def deletdata(self, index):
        with self.connect.cursor() as cu:
            if cu.execute(self.sql_del.format(index)):
                self.connect.commit()
                return True
            return False

    def search(self, name):
        with self.connect.cursor() as cu:
            cu.execute(self.sql_search.format(name))
        return cu.fetchall()

    def adddata(self, index, name, author, description):
        with self.connect.cursor() as cu:
            try:
                cu.execute(self.sql_insert.format(index, name, author, description, '1'))
                self.connect.commit()
            except pymysql.err.OperationalError as e:
                print(e)

    def __del__(self):
        self.connect.close()


class Synchronization(threading.Thread):
    """using to update the original data that was stored in linked list"""
    def __init__(self, origin_data, sql_data):
        super(Synchronization, self).__init__()
        self.origin = origin_data
        self.sql = sql_data
        global lock

    def run(self):
        # wait a moment
        pass

    def __del__(self):
        super(Synchronization, self).__del__()


if __name__ == '__main__':

    Book._fields_ = [
        ('index', ctypes.c_ulong),
        ('prior', ctypes.POINTER(Book)),
        ('next', ctypes.POINTER(Book)),
        ('name', ctypes.c_char_p),
        ('author', ctypes.c_char_p),
        ('flag', ctypes.c_int),
        ('description', ctypes.c_char_p)
    ]

    m = Main()
    m.main()
