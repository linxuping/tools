# -*- coding: utf-8 -*-
# vim:sw=4 ts=4 si et

import os
import traceback
from cStringIO import StringIO

import sys
from os.path import abspath, dirname

base_dir = dirname(dirname(abspath(__file__)))
if base_dir not in sys.path:
    sys.path.insert(0, base_dir)

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "settings")

#from django.db.models import Q, Count
#from django.utils import timezone

from django.conf import settings

class AlterDB(object):
    """初始化salmon数据库"""

    CREATE_DB = """DROP DATABASE IF EXISTS `%s`; CREATE DATABASE %s CHARACTER SET = "UTF8"; USE %s;"""

    def __init__(self):
        self.base = "4.0"
        self.start = -1
        self.end = -1
        self.isCreateDB = True
        self.isAlterTable = True

    def init(self, base, start, end):
        try:
            if base:
                self.base = base
            if start:
                self.start = int(start)
            elif not base:
                try:
                    if os.path.isfile(".curVersion"):
                        fd = open(".curVersion", "rb")
                        start_str = fd.readline()
                        fd.close()
                        start_str = start_str.strip()
                        self.start = int(start_str) + 1
                except:
                    stream = StringIO()
                    traceback.print_exc(file=stream)
                    print stream.getvalue()
            if end:
                self.end = int(end)
            if not base and (start or end):
                self.isCreateDB = False
            if base and (not start):
                self.isAlterTable = False
        except:
            stream = StringIO()
            traceback.print_exc(file=stream)
            print stream.getvalue()
            # 出错时恢复默认配置
            self.__init__()

    def process_base(self, base_version):
        if not base_version:
            return 0

        try:
            file_name = "salmon-%s.sql" %(base_version)
            if not os.path.isfile(file_name):
                return -2

            db_dict = settings.DATABASES["default"]
            db_name = db_dict["NAME"]
            sql_cmd = AlterDB.CREATE_DB %(db_name, db_name, db_name)
            shell_cmd = """mysql -u %s -h %s -P %s --password=%s -e '%s;source %s;'""" %(
                db_dict["USER"], db_dict["HOST"], db_dict["PORT"], db_dict["PASSWORD"],
                sql_cmd, file_name)
            ret = os.system(shell_cmd)
            if ret:
                print "fail to execute shell cmd [%s]" %shell_cmd
                return -3
            if not self.isAlterTable and os.path.isfile(".curVersion"):
                os.remove(".curVersion")
            return 0
        except:
            stream = StringIO()
            traceback.print_exc(file=stream)
            print stream.getvalue()
            return -1

    def process_normal(self, start_version, end_version):
        file_dict = self.get_sql_file(start_version, end_version)
        print file_dict, start_version, end_version#cys
        version_list = file_dict.keys()
        version_list.sort()

        db_dict = settings.DATABASES["default"]
        pre_cmd = """mysql -u %s -h %s -P %s --password=%s -D %s""" %(
            db_dict["USER"], db_dict["HOST"], db_dict["PORT"],
            db_dict["PASSWORD"], db_dict["NAME"])

        for version in version_list:
            cmd = "%s -e 'source %s;'" %(pre_cmd, file_dict[version])
            if os.system(cmd):
                return -1

        if len(version_list):
            try:
                fd = open(".curVersion", "w")
                fd.write("%s" %(version_list[-1]))
                fd.close()
            except:
                stream = StringIO()
                traceback.print_exc(file=stream)
                print stream.getvalue()
                return -2

        return 0

    def get_sql_file(self, start=-1, end=-1):
        file_dict = {}
        file_list = os.listdir(".")
        for file_name in file_list:
            if not file_name.startswith("salmon_alter_v") \
                or not file_name.endswith(".sql"):
                continue
            num_str = file_name[14:-4]
            if not num_str.isdigit():
                continue
            num = int(num_str)
            if start > 0 and num < start:
                continue
            if end > 0 and num > end:
                continue
            file_dict[num] = file_name
        return file_dict

    def backup(self, file_name):
        try:
            print "try to backup database"
            db_dict = settings.DATABASES["default"]
            cmd = "mysqldump -u %s -h %s -P %s --password=%s %s > %s" %(
                db_dict["USER"], db_dict["HOST"], db_dict["PORT"],
                db_dict["PASSWORD"], db_dict["NAME"], file_name)
            if os.system(cmd):
                print "back up error!"
                return False
        except:
            stream = StringIO()
            traceback.print_exc(file=stream)
            print stream.getvalue()
            print "back up error!"
            return False

        print "succeed to back up data to salmon_db_back.sql"
        return True
    
    def rollback(self, file_name):
        try:
            print "try to roll back"
            db_dict = settings.DATABASES["default"]
            db_name = db_dict["NAME"]
            sql_cmd = AlterDB.CREATE_DB %(db_name, db_name, db_name)
            shell_cmd = """mysql -u %s -h %s -P %s --password=%s -e '%s;source %s;'""" %(
                db_dict["USER"], db_dict["HOST"], db_dict["PORT"], db_dict["PASSWORD"],
                sql_cmd, file_name)
            if os.system(shell_cmd):
                print "roll back error!"
                return False
        except:
            stream = StringIO()
            traceback.print_exc(file=stream)
            print stream.getvalue()
            print "roll back error!"
            return False

        print "succeed to roll back!"
        return True

    def run(self):
        try:
            file_name = "salmon_db_back.sql"
            hasBackup = self.backup(file_name)
            if not hasBackup:
                print "fail to backup database!give up any operation!"
            else:
                print "try to update database ..."
                if self.isCreateDB and self.process_base(self.base):
                    print "fail to init database with base version DB, give up any other initializtion"
                    self.rollback(file_name)
                    return -1

                if self.isAlterTable and self.process_normal(self.start, self.end):
                    print "fail to alter database,give up any operation!"
                    self.rollback(file_name)
                    return -1
                print "succeed to update ..."
        except:
            stream = StringIO()
            traceback.print_exc(file=stream)
            print stream.getvalue()
            print "something wrong happens!"
            if hasBackup:
                print "give up any operation with database and rollback!"
                self.rollback(file_name)

def mlArgsHandle():
    """
    命令行参数处理
    """
    import optparse

    version_info = "v1.0"
    loOptParser = optparse.OptionParser(usage="python alterDB.py [-b] [-s] [-e] [-v]", version=version_info)
    loOptParser.add_option("-v", action="store_true", dest="version", help="show version information and exit")
    #loOptParser.add_option("-D", action="store_true", dest="dm", help="running in daemon mode")
    loOptParser.add_option("-b", action="store", dest="base_version", type="string", default="", help="the base version when starts to init DB")
    loOptParser.add_option("-s", action="store", dest="start_version", type="string", default="", help="the start version when starts to init DB")
    loOptParser.add_option("-e", action="store", dest="end_version", type="string", default="", help="the end version when starts to init DB")
    opts, args = loOptParser.parse_args()

    if opts.version:
      loOptParser.print_version()
      sys.exit(0)
    return opts, args

def main():
    opts, args = mlArgsHandle()

    alterDB = AlterDB()
    alterDB.init(opts.base_version, opts.start_version, opts.end_version)
    alterDB.run()

if __name__ == "__main__":

    main()


