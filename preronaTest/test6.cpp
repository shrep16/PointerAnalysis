//arrays
//for out of range array indices check for warnings generated
int **arr[3];
int *a, *b, *c;

int main() {
	arr[0] = &a;
	arr[1] = &b;
	arr[2] = arr[0];
	return 0;
}
