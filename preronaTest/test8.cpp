//malloc
#include<stdlib.h>
int *x, *y, a, b;

int main() {
	x = (int *) malloc (sizeof(int)); //no alias call and then bitcast
	return 0;
}
