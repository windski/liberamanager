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
    db='yourdatabasename'
)


class Book(ctypes.Structure):
    pass

Book._fields_ = [
    ('index', ctypes.c_ulong),
    ('prior', ctypes.POINTER(Book)),
    ('next', ctypes.POINTER(Book)),
    ('name', ctypes.c_char_p),
    ('author', ctypes.c_char_p),
    ('flag', ctypes.c_int),
    ('description', ctypes.c_char_p)
]


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
                    self.bo = self.so.addbook(self.bo, ctypes.c_ulong(index), ctypes.c_char_p(name), ctypes.c_char_p(author), ctypes.c_char_p(description))
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
                    self.sql.search(name)
                    # 未完,标记一下
            elif op == '-b':
                name = input('书名:')
                if self.bo is not None:
                    self.so.loadbook(self.bo, ctypes.c_char_p(name))
                self.sql.writedata(name)
            elif op == '-r':
                index = input('序列号:')
                name = input('书名:')
                if self.bo is not None:
                    self.so.repay(self.bo, ctypes.c_ulong(index), ctypes.c_char_p(name))
                self.sql.writedata(index, name)


class Sql:
    sql_init = 'CREATE TABLE book (id INTEGER NOT NULL, bookname VARCHAR(100) NOT NULL, author VARCHAR(50) NOT NULL, ' \
               'description TEXT, flag TINYINT NOT NULL, PRIMARY KEY(id));'
    sql_insert = 'INSERT INTO book (id, bookname, author, description, flag) VALUES(%s, %s, %s, %s, %s)'
    sql_update = 'UPDATE book SET {} = {} WHERE id = {}'

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

    def writedata(self, *kwargs):
        pass

    def deletdata(self, index):
        pass

    def search(self, name):
        pass

    def adddata(self, index, name, author, description):
        pass

    def updating(self):
        pass

    def __del__(self):
        self.connect.close()
