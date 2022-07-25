#include<iostream>
#include <iterator>
using namespace std;

int maxEl(int B[], int m) {
	int naj = B[0];
	for (int i = 0; i < m; i++) {
		if (naj < B[i]) {
			naj = B[i];
		}
	}
	return naj;

}

int binarySearch(int C[], int d, int element) {
	int donja = 0;
	int gornja = d - 1;
	bool nadjen = false;
	int sredina;
	while (donja<=gornja && !nadjen) {

		 sredina = (donja + gornja) / 2;

		if (element > C[sredina]) {
			donja = sredina + 1;
		}
		else if (element < C[sredina]) {
			gornja = sredina - 1;
		}
		else nadjen = true;
	}
	if (nadjen) return sredina;
	else return false;

}

int main() {
	int A[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	int duzina = 0;
	while (A[duzina]>0) {
		duzina++;
	}
	cout << "element je na lokaciji:" << binarySearch(A,duzina, 10) << endl;
}