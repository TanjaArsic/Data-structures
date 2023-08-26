#include<iostream>

void SelectionSort(int* arr, int n); //ide redom i nalazi minimalni (maksimalni), zamenjuje s tekucim
void BubbleSort(int* arr, int n); //maksimalni (minimalni) odlazi na kraj
void InsertionSort(int* arr, int n); //najintuitivniji, uzima redom i smesta gde treba u sortiranom delu
void Merge(int* arr, int n, int* left, int l, int* right, int m);
void MergeSort(int* arr, int n); //divide and conquer O(nlogn)

int main(int argc, char* argv[])
{
	int A[] = { 3,8,4,6,6,2,7,5 };
	int len = sizeof(A)/sizeof(A[0]);
	
	MergeSort(A, len);

	for (int i = 0; i < len; i++)
		std::cout << A[i] << " ";
	return 0;
}

void SelectionSort(int* arr, int n) // Selection -> bira odgovarajuci element iz nesortiranog dela i prebacuje u sortirani deo
{
	int i = 0;
	while (i < n - 1)
	{
		int min = i;
		int j = i + 1;
		while (j < n)
		{
			if (arr[j] < arr[min])
				min = j;
			j++;
		}
		int tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
		i++;
	}

	//for (int i = 0; i < n - 1; i++)
	//{
	//	int min = i;
	//	for (int j = i + 1; j < n; j++)
	//	{
	//		if (arr[j] < arr[min])
	//			min = j;
	//	}
	//	int tmp = arr[i];
	//	arr[i] = arr[min];
	//	arr[min] = tmp;
	//}
}

void BubbleSort(int* arr, int n)
{
	
	int loop = n;
	while (loop > 0) 
	{
		bool flag = false;
		int i = 0;
		while (i < loop - 1)
		{
			if (arr[i] > arr[i + 1])
			{
				flag = true;
				int tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
			i++;
		}
		if (!flag) break; //ako je vec sortiran, ne prolazi opet
		loop--;
	}

	/*for (int loop = n; loop > 0; loop--)
	{
		bool flag = false; 
		for (int i = 0; i < loop - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				flag = true;
				int tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
		if (!flag) break;
	}*/
	
}

void InsertionSort(int* arr, int n)
{
	int i = 1;
	while (i < n)
	{
		int value = arr[i];
		int curr = i;
		while (curr > 0 && arr[curr-1] > value)
		{
			arr[curr] = arr[curr-1];
			curr--;
		}
		arr[curr] = value;
		i++;
	}
	
}

void Merge(int* arr, int n, int* left, int l, int* right, int m)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < l && j < m)
	{
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	while (i < l)
		arr[k++] = left[i++];
	while (j < m)
		arr[k++] = right[j++];

}
void MergeSort(int* arr, int n)
{
	if (n < 2)	return;
	int mid = n / 2;
	int* left = new int[mid];
	int* right = new int[n-mid];

	for (int i = 0; i < mid; i++)
		left[i] = arr[i];
	for (int i = mid; i < n; i++)
		right[i - mid] = arr[i];

	MergeSort(left, mid);
	MergeSort(right, n-mid);
	Merge(arr, n, left, mid, right, n-mid);
	delete[] left;
	delete[] right;
}