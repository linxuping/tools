from tornado.options import define, options  
  
define("param1", default="it's parameter 1", help="value for param 1")  
define("param2", default="it's parameter 2", help="value for param 2")  
  
options.parse_command_line()  
  
if __name__ == "__main__":  
    print options.param1  
    print options.param2 

'''
$ python options.py --help
Usage: options.py [OPTIONS]

Options:

  --help                           show this help information

/usr/local/lib/python2.7/site-packages/tornado/log.py options:

  --log-file-max-size              max size of log files before rollover
                                   (default 100000000)
  --log-file-num-backups           number of log files to keep (default 10)
  --log-file-prefix=PATH           Path prefix for log files. Note that if you
                                   are running multiple tornado processes,
                                   log_file_prefix must be different for each
                                   of them (e.g. include the port number)
  --log-rotate-interval            The interval value of timed rotating
                                   (default 1)
  --log-rotate-mode                The mode of rotating files(time or size)
                                   (default size)
  --log-rotate-when                specify the type of TimedRotatingFileHandler
                                   interval other options:('S', 'M', 'H', 'D',
                                   'W0'-'W6') (default midnight)
  --log-to-stderr                  Send log output to stderr (colorized if
                                   possible). By default use stderr if
                                   --log_file_prefix is not set and no other
                                   logging is configured.
  --logging=debug|info|warning|error|none 
                                   Set the Python log level. If 'none', tornado
                                   won't touch the logging configuration.
                                   (default info)

options.py options:

  --param1                         value for param 1 (default it's parameter 1)
  --param2                         value for param 2 (default it's parameter 2)


$ python options.py --param1="123"
123
it's parameter 2


'''
