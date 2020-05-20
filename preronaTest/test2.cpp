//different levels of indirection
int *x, *y, a, b, **p, *z, ***q, **m;

int main() {
/*int *x,*y;
int a,b;
int **p,**m;
int ***q;*/

	x = &a;
	//*x = a+b;  -pointer has no involvement here
	y = x;
	p = &y;
	q = &m;
	*q = p;
	q = &p;
	**q = x;
	//z = *p;

	
	return 0;
}


