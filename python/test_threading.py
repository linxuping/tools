import threading
import time

def run(i):
    time.sleep(2)
    #print('thread name:  ', threading.current_thread().name, i)
    print("%d\n"%i)
    time.sleep(2)


if __name__ == '__main__':

    start_time = time.time()

    print('main thread: ', threading.current_thread().name)
    thread_list = []
    for i in range(5):
        t = threading.Thread(target=run, args=[i])
        thread_list.append(t)

    for t in thread_list:
        t.setDaemon(True)
        t.start()

    for t in thread_list:
        t.join()

    print('main thread end.' , threading.current_thread().name)
    print('time weight: ', time.time()-start_time)
