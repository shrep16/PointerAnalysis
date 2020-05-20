int *x, *y, a, b, c, d, **p, *z, ***q, **l, **r, **s;
/*int main() {
	x = &a;
	y = x;
	p = &y;
	*p = x;
	q = &p;
	**q = x;
	z = *p;
	return 0;
}*/

/*void temp() {
	int a;
	int *x,*y;
	x = &a;
	y = x;
}*/


void if_else(){
	a = 10;
	if(a>0) 
		x = &a;
	else
		x = &b;
	y = x; //basic union of OUTs of Predecessors
	
	c = 12;
	if(c == 13)
		p = &x;
	else
		p = &y;

	*p = &c; //p points to both x and y, hence x and y will not point to c ONLY

	z = x; // z earlier pointing to a,b,c
	p = &z;
	*p = &d; // now z will point to only d

	x = *p; //now x will point to what z is pointing to 
	
	
}

/*void check() {
	/*x = &c;
	p = &x;
	q = &p;
	z = **q;*/

	
	/*x = &a;
	y = &b;	
	c = 12;
	if( c>12) 
		p = &x;
	else
		p = &y;

	
	if(c==12)
		q = &r;
	else
		q = &s;
	z = *p;
	*q = p;

	//*p = x;
	//*p = z;
	//l = p;
	//**q = x;
}*/
