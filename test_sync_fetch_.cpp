/*
 * 在用gcc编译的时候要加上选项 -march=i686
 * fetch_and_add i++
 * add_and_fetch ++i
 */
#include <stdio.h>

int main()
{
	int val=0, val2=10;
	printf("init:0  val:%d val2:%d\n",val,val2);
	__sync_add_and_fetch(&val ,1); //used for atomic counting.
	printf("add:1  %d\n",val);
	__sync_sub_and_fetch(&val ,1);
	printf("sub:0  %d\n",val);
	__sync_or_and_fetch(&val ,1);
	printf("or :1  %d\n",val);
	__sync_and_and_fetch(&val ,0);
	printf("and:0  %d\n",val);
	__sync_xor_and_fetch(&val ,0);
	printf("xor:0  %d\n",val);
	//__sync_nand_and_fetch(&val ,1);
	//printf("nand(not and):1  %d\n",val);
	val = 8;
	__sync_bool_compare_and_swap(&val ,8, 88);
	printf("__sync_bool_compare_and_swap: %d\n",__sync_bool_compare_and_swap(&val ,4, 88));
	printf("__sync_bool_compare_and_swap: %d\n",__sync_bool_compare_and_swap(&val ,8, 88));
	val = 8;
	printf("__sync_val_compare_and_swap: %d\n",__sync_val_compare_and_swap(&val ,8, 88));

	val = 8;
	printf("__sync_lock_test_and_set: %d\n",__sync_lock_test_and_set(&val, 88));
	__sync_lock_release(&val);
	printf("__sync_lock_release: %d\n",val);

	return 0;
}

