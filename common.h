/*comments*/
#if !defined LXP_TEST
# define LXP_TEST 0

# include <stdio.h>
# define ENTER_TEST() printf("\n+---- ---- %s ---- ---- ---- ---- ---- ----> \n",__FUNCTION__)
# define ENTER_TEST2(s) printf("\n+---- ---- %s ---- ---- ---- ---- ---- ---->(测试: %s) \n",__FUNCTION__,s)
#endif
