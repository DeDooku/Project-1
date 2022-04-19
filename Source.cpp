#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>


using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void CHistogram() {
	string object;
	string oldObject;
	int freq;
	int i;

	ifstream inFS;  // starts input steam //

	inFS.open("frequency.dat");  // opens frequency.dat with input stream //

	try {
		if (!inFS.is_open()) {  // if file doesn't open, display error message //
			cout << "Could not open file numFile.txt." << endl;
			throw runtime_error("File could not be opened");
		}

		while (!inFS.fail()) {  // while loop runs until nothing is left in file //
			inFS >> object;  
			inFS >> freq;

			if (object == oldObject) {  // if the object is the same as the last object, it stops the loop //
				break;
			}
			
			cout << object << " ";
			for (i = 0; i < freq; ++i) {  // prints * number of times equal to the frequency //
				cout << '*';
			}
			cout << endl;
			oldObject = object;
		}
	}
	catch (runtime_error& excpt) {
		cout << "Error Occured" << endl;
	}

	inFS.close();  // closes input stream //
	cout << endl;
}


void Menu() {
	int userInput;
	string userString;

	while (true) {  // runs until broken //
		
		cout << "Grocery Tracking Menu" << endl;  // menu is displayed to user //
		cout << endl;
		cout << "1. Full List" << endl;
		cout << "2. Single Item" << endl;
		cout << "3. Histogram" << endl;
		cout << "4. Quit" << endl;
		cout << endl;

		cin >> userInput;  // waits for user input //
		
		try {
			if (userInput == 1) {  // runs the printFullList function from python, then restarts loop //
				cout << endl;
				CallProcedure("printFullList");
				cout << endl;
				continue;
			}

			if (userInput == 2) {  // runs the printItem function from python, then restarts loop //
				cout << "Which item would you like to look up? Please capitalize." << endl;
				cin >> userString;
				callIntFunc("printItem", userString);
				cout << endl;
				continue;
			}

			if (userInput == 3) { // runs the histogram function from python, then runs the histogram function in C++, then restarts loop  //
				cout << endl;
				CallProcedure("histogram");
				CHistogram();
				
				continue;
			}

			if (userInput == 4) {  // breaks the loop if q is entered //
				break;
			}
			
			else {  // if something else is entered, then throw error //
				throw runtime_error("Invalid Input");
			}
		}
		catch (runtime_error& excpt) {  // catchs errors and clears input //
			cout << "Invalid Input, please re-enter" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << endl;
		}
	}

}


int main()
{
	system("Color 0B");  // changes text color to blue //

	Menu();  // runs the menu loop //

	cout << "Closing Program" << endl;  // When menu loop is broken, outputs a message showing program is ending //

}