#!/usr/bin/env python3
import pymysql
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


class Main:
    help = '   -a 新增图书\n   -d 删除已经废弃不用的图书\n   -s 搜索图书的信息\n   -b 借书\n   -r 还书\n\n'

    def __init__(self):
        print(self.help)
        self.sql = Sql()
        try:
            self.sql.adddata(1, 'ifininit', 'ifitinit', 'ifitinit')
            print('建立数据..序列为0时结束..')
            while True:
                index = input('序列:')
                name = input('名字:')
                author = input('作者')
                des = input('描述')
                if index == 0:
                    break
                self.sql.adddata(index, name, author, des)
        except pymysql.err.OperationalError:
            pass

    def main(self):
        opts, args = getopt.getopt(sys.argv[1:], 'ha:d:s:b:r:')
        if opts is None or args is None:
            while True:
                print(self.help.join("q 退出\n"))
                i = input("(liberamanager)")
                if i is 'q' or i is 'quit':
                    break
                elif i is 'a':
                    self.__add()
                elif i is 'd':
                    self.__dele()
                elif i is 's':
                    self.__search()
                elif i is 'b':
                    self.__bow()
                elif i is 'r':
                    self.__replt()
        for op, values in opts:
            if op == '-h':
                print(self.help)
                break
            elif op == '-a':
                self.__add()
            elif op == '-d':
                self.__dele()
            elif op == '-s':
                self.__search()
            elif op == '-b':
                self.__bow()
            elif op == '-r':
                self.__reply()

    def __add(self):
        index = input('序列号:')
        name = input('书名:')
        author = input('作者:')
        description = input('描述:')
        self.sql.adddata(index, name, author, description)

    def __dele(self):
        index = input('序列号:')
        self.sql.deletdata(index)

    def __search(self):
        name = input('书名:')
        res = self.sql.search(name)
        sum = 0
        for i in res:
            for j in i:
                if j[4] == 1:
                    sum += 1
        print('作者:', res[0][1], '共:', len(res), '其中', sum, '可以借阅')

    def __bow(self):
        index = input('序列号:')
        self.sql.writedata('b', index)

    def __reply(self):
        index = input('序列号:')
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
            cu.execute(self.sql_insert.format(index, name, author, description, '1'))
            self.connect.commit()

    def __del__(self):
        self.connect.close()


if __name__ == '__main__':
    m = Main()
    m.main()
