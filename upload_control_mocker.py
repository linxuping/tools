# -*- coding: utf-8 -*-
# vim:sw=4 ts=4 si et

# system import
import os
import sys
import time
import traceback
from cStringIO import StringIO
import urllib
import urllib2

def send_HTTP(url, timeout=120, params=None):
    """
    发送Http请求获取数据
    :param url: 请求地址
    :param params: 请求参数
    :return:
    :except: IOError
    """
    try:
        req = urllib2.Request(url)
        opener = urllib2.build_opener()
        if params:
            data = urllib.urlencode(params)
            if timeout:
                response = opener.open(req, data, timeout=timeout)
            else:
                response = opener.open(req, data)
        else:
            if timeout:
                response = opener.open(req, timeout=timeout)
            else:
                response = opener.open(req)
        return response.read()
    except Exception,e:
        stream = StringIO()
        traceback.print_exc(file=stream)
        err_msg = stream.getvalue()
        print "send_HTTP(url='%s', params=%s) error:\n%s" %(url, params, err_msg)
        raise e

def upload_file(url, account_dict, upload_dict, timeout=None):
    #buld post body data
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'user')
    data.append(account_dict['user'])
    data.append('--%s' % boundary)
    
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'passwd')
    data.append(account_dict['passwd'])
    data.append('--%s' % boundary)
    
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'clusters')
    data.append(upload_dict['clusters'])
    data.append('--%s' % boundary)
    
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'description')
    data.append(upload_dict['description'])
    data.append('--%s' % boundary)
    
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'product')
    data.append(upload_dict['product'])
    data.append('--%s' % boundary)
    
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'pack_md5')
    data.append(upload_dict['pack_md5'])
    data.append('--%s' % boundary)
    
    fr = open(upload_dict['file_path'], 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename="%s"' %(
        'Filedata', upload_dict['pack_name']))
    data.append('Content-Type: %s\r\n' % 'text/xml')
    data.append(fr.read())
    fr.close()
    data.append('--%s--\r\n' % boundary)

    http_body='\r\n'.join(data)
    #print http_body
    try:
        #buld http request
        req=urllib2.Request(url, data=http_body)
        opener = urllib2.build_opener()
        #header
        req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
        req.add_header('User-Agent','Mozilla/5.0')
        #req.add_header('Referer','http://remotserver.com/')
        #post data to server
        #resp = urllib2.urlopen(req, timeout=35)
        resp = opener.open(req, timeout=timeout)
        #get response
        qrcont=resp.read()
        print qrcont
        return qrcont
    except:
        stream = StringIO()
        traceback.print_exc(file=stream)
        err_msg = stream.getvalue()
        print "upload file %s error:\n%s" %(upload_dict['file_path'], err_msg)
        return None


if __name__ == "__main__":
    url = "http://devz.ucweb.local:8794/api/upload/addFroBack/1"
    #url = "http://devz.ucweb.local:8794/api/upload/add/1"
    account_dict = {
        #"user":   "hummer_back",
        "user":   "chenys3",
        "passwd": "abcd",
    }

    upload_dict = {
        "clusters":       "wx",
        "description":       "测试",
        "product":   "Hummer",
        "pack_md5":       "98d81d0eb8635524841bcdbf6f96b2a8",
        "pack_name":      "hummer.config.tar.gz",
        "file_path":      "/home/chenys3/code/salmon-5.0/salmon/deployer/hummer.config.tar.gz"
    }

    response = upload_file(url, account_dict, upload_dict)
    import json
    if response:
        ret = json.loads(response)
        for key, value in ret.items():
            if key != "body":
                print "key = [%s], value = [%s]" %(key, value)
            else:
                if type(value) == dict:
                    print "key = [%s]" %(key)
                    for key1, value1 in value.items():
                        print "key1 = [%s], value1 = [%s]" %(key1, value1)
                else:
                    print "key = [%s], value = [%s]" %(key, value)
                print "\n"
    #upload_file('http://ucmt.ucweb.local/deploy/api/upload_file',
    #    'cb5e1442-8299-11e4-b5b1-000c29b2b0f8', 'chenys',
    #    '/home/chenys3/salt/code/salmon-3.0/salmon/deployer/a.txt')




