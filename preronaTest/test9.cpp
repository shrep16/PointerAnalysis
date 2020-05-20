// object
int *x, a, b;
class A {
	public :
	A() {
		x = &a;
	}
	int *ptr;
};

int main() {
	A obj;
	obj.ptr = &b;
	return 0;
}
