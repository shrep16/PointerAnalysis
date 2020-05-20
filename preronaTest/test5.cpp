//x surely points to c
int *x, *y, c, d, *z;

int main() {
	for(int t=0;t<11;t++) {
		z = x;
		if(t%2==0) { //if cond =1 
			x = &c;
		} else {
			x = &d;
		}
	}
	y = x;
}


