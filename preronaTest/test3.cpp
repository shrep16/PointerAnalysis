//structure
int a = 10;
int *y = &a;
int k[11];

struct myStruct {
	int *pt;
	int val;
};
struct myStruct global = {&a,30};
//y = &a;

void func() {
	
	//y = &a;
	
	//int *m = &a;
	global.val = 70;
	global.pt = y;
	
	k[2] = 112;
	
	
	//k[199991] =13;
}
