// structure

typedef struct MyStruct {
	int *ptr;
}mySt;

int a;

mySt arr[2];
int main() {
	mySt s;
	s.ptr = &a;

	arr[0] = s; //first bitcast s, then memcopy
	arr[1].ptr = &a;
	return 0;
}
