//pointer arithmetic
int *x,*y;
int **p;
int arr[2];
void mains() {
	x = arr; // points to arr[0]
	x++; // will point to arr[1]

	x = x+4;
	p = &x;
	//*p= x+y;       - not valid statement
}
