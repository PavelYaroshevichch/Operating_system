#include <windows.h>
#include <iostream>
#include<vector>
#include<string>
using namespace std;


double average;
struct fun {
	int min = 0;
	int max = 0;
	int* vec = NULL;
	int size = 0;
	double average = 0;
};



DWORD WINAPI Min_max(LPVOID aa) {
	fun* a = (fun*)aa;
	cout << "Stream Min_max open" << "\n";
	a->min = a->vec[0];
	a->max = a->vec[0];

	for (int i = 1; i <a->size; i++)
	{
		if (a->max < a->vec[i]) {
			a->max = a->vec[i];
		}Sleep(7);
		if (a->min > a->vec[i]) {
			a->min = a->vec[i];
		}Sleep(7);
	}

	cout << "min in array is: " << a->min << "\n";
	cout << "max in array is: " << a->max << "\n";
	cout << "Stream Min_max close" << "\n";
    return 0;
}

DWORD WINAPI Average(LPVOID aa) {
	fun* a = (fun*)aa;
	cout << "Stream Average open" << "\n";

	for (int i = 0; i < a->size; i++) {
		a->average += a->vec[i];
		Sleep(12);
	}
	a->average = a->average / (double)(a->size);
	cout << "The average number is:" << a->average << "\n";
	cout << "Stream Average close" << "\n";
	return 0;

}




int main()
{
	int size;
	cout << "Write size of array";
	cin >> size;
	int* vec = new int[size];
	cout << "Fill array";
	for (int i = 0; i < size; i++) {
		std::cin >>vec[i];

	}

	struct fun* a = new fun;
	a->vec = vec;
	a->size = size;

	LPTHREAD_START_ROUTINE mm = (LPTHREAD_START_ROUTINE)Min_max;
	HANDLE hThread_mm;
	DWORD IDThread_mm;
	hThread_mm = CreateThread(NULL,
		0,
		mm,(LPVOID) a,
		0,
		&IDThread_mm);
	if (hThread_mm == NULL) return GetLastError();




	LPTHREAD_START_ROUTINE av = (LPTHREAD_START_ROUTINE)Average;
	HANDLE hThread_av;
	DWORD IDThread_av;
	hThread_av= CreateThread(NULL,0,av, (LPVOID)a, 0,&IDThread_av);
	if (hThread_av == NULL) return GetLastError();

	WaitForSingleObject(hThread_mm, INFINITE);
	WaitForSingleObject(hThread_av, INFINITE);



	CloseHandle(hThread_mm);
	CloseHandle(hThread_av);


	for (int i = 0; i < size; i++) {
		if (vec[i] == a->max) vec[i] = a->average;
		if (vec[i] == a->min) vec[i] = a->average;
	}

	cout << "new array is: ";
	for (int i = 0; i < size; i++) {
		cout << vec[i] << " ";
	}

	delete[] vec;
	delete a;
	return 0;
}
