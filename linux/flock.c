#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	if (argc > 1) {
		int fd = open(argv[1], O_WRONLY);
		if(fd == -1) {
			printf("Unable to open the file\n");
			exit(1);
		}
		static struct flock lock;

		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_whence = SEEK_SET;
		lock.l_len = 0;
		lock.l_pid = getpid();

		int ret = fcntl(fd, F_SETLKW, &lock);
		printf("Return value of fcntl:%d\n",ret);
		if(ret==0) {
			while (1) {
				scanf("%c", NULL);
			}
		}
	}
}

/*
使用mount命令带“mand”参数来重新挂载根文件系统，如下所示。这将在文件系统级别使能强制锁功能,对于“mandatory.txt”使能Set-Group-ID，同时不使能Group-Execute-Bit.
对于要打开强制锁功能的文件lock_file，必须打开set-group-ID位，关闭group-execute位。（选择此方法的原因是，当你关闭group-execute时，设置set-group-ID就没有实际的意义了
# mount -oremount,mand /
# touch advisory.txt
# touch mandatory.txt
# chmod g+s,g-x mandatory.txt

# ./file_lock advisory.txt   -->  other file use advisory.txt will block.
# ./file_lock mandatory.txt   -->  other file use mandatory.txt will block.
*/

