#pragma once
#pragma execution_character_set("utf-8")
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <random>
#include <iterator>
#include <sstream>	// cast str to int
#include <algorithm> // random shuffle


//==========================================================================================//begin supplied code
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
void CallProcedure(std::string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonGrocer");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}
/*
Description:
	To call this function, pass the name of the Python functin you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(std::string proc, std::string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonGrocer");
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
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(std::string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonGrocer");
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
// ============================================================= //end supplied code
//
//
//
//
//
//
//
//
// 
// 
// 
// 
// 
// 
// ========================= student work is below =================================



// color setter; sourced from --> [http://www.cplusplus.com/forum/beginner/77879/]

inline void SetColor(WORD color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//color helper class
class color {
public:
	color(WORD val) : val1(val) { }

	void set() const {
		SetColor(val1);
	}
private:
	WORD val1;
};
static const color blue(1);
static const color green(2);
static const color cyan(3);
static const color red(4);
static const color purple(5);
static const color darkYellow(6);
static const color white(7);
static const color gray(8);
static const color briteBlue(9);
static const color briteGreen(10);
static const color briteCyan(11);
static const color briteRed(12);
static const color pink(13);
static const color yellow(14);
static const color briteWhite(15);

inline std::ostream& operator << (std::ostream& os, const color& c) {
	c.set();
	return os;
}//=============================================================================




	// this function outputs the histogram based on the user choice of sorting
int Runner(const std::vector <std::string> & v) {


	std::string numStars = " ";				// declare amount of stars 
	const unsigned char BLOCK = char(166); // █ block for histogram

	// ITERATE THROUGH ARRAY AND DISPLAY HISTOGRAM WITH CHOSEN FORMAT
	for (unsigned int i = 0; i < v.size(); i++) {   // get each string from 0 to [-1]

		//declarations
		std::string x = v.at(i);			   // each line of file becomes x 
		int pos = x.find(" ");				   // find separator whitespace

		// product namer [sku]
		std::string sku = x.substr(0, pos); // get product name via substring method


		// star creator  [numStars]; get substring from pos to -1
		std::string qty = x.substr(pos + 1, x.length());

		std::stringstream stars(qty);		// enable stringstream conversion
		int z = 0;								// declare int
		stars >> z;								// convert



		for (int j = 0; j < z; j++) {		// iterator

					// numStars is called this because it was originally used with asterisks,
					// but then ascii characters made their way into the program
					// so these ascii characters which print the histogram are referred to as "stars"

			numStars += BLOCK;		   // append stars for display

		}


		// print product name wih following whitespace
		// align product name right at fixed width, print green, unicode arrow
		std::cout.width(15); std::cout << std::right << briteGreen << sku << " " << gray << char(16);

		//results of numStars is printed in red 
		std::cout << briteRed << numStars << "\n\n";

		//if (i < 19) { //stops separator from printing after histogram is complete

			// just a separator line printed in green
			//std::cout.width(18); std::cout << std::right << gray << char(16) << " " << "\n";
		//}

		numStars = " ";	// clear numStars
		x = " ";				// clear x

	}//for

	return 0;
}

	//menu option 1 ===================================== generate end of day count sheet
void Option1() {

	system("CLS"); // clear screen

	std::cout << briteWhite;		 // white
	CallProcedure("CornerSplash"); // py.CornerSplash logo
	std::cout << briteGreen;		 // green

	std::cout << cyan;
	CallProcedure("PyPurchaseCount"); // run PyPurchaseCount py.function
	std::cout << briteGreen;

}





	//menu option 2 ===================================== generate search ability -> unique item report
void Option2() {

	std::string userItem;			 // declare variable

	system("CLS");						 // clear screen

	std::cout << briteWhite;		 // white
	CallProcedure("CornerSplash"); // py.CornerSplash logo
	std::cout << briteGreen;		 // green


	// header; sku = stock keeping unit
	std::cout << "           SEARCH BY SKU\n";
	std::cout << "           _____________\n\n\n";


	// prompt user for specific item search
	std::cout << "\nPlease enter an item name: " << briteWhite;
	std::cin >> userItem; //user input
	std::cout << briteGreen;


	system("CLS"); //clear screen

	std::cout << briteWhite;		 // white
	CallProcedure("CornerSplash"); // py.CornerSplash logo
	std::cout << cyan;				 // blue 


	// pass search term to py.ItemSearch
	// return num occurences from python as int
	std::cout << callIntFunc("PyItemSearch", userItem);
	std::cout << ("\n\n\n\n");


}




//menu option 3 ===============================================  generate histogram; this function also allows 
//																					  for different outputs of histograms based on user preference

void Option3() {

	system("CLS");						 // clear screen
	std::cout << briteWhite;		 // white
	CallProcedure("CornerSplash"); // py.CornerSplash logo
	std::cout << briteGreen;		 // green

	CallProcedure("PyHistogram");  // run histogram function.py

	int enterKey;     // variable for menu below

	system("CLS");						 // clear screen
	std::cout << briteWhite;		 // white
	CallProcedure("CornerSplash"); // py.CornerSplash logo
	std::cout << briteGreen;		 // green

	std::cout << "    Press any key to create a product histogram . . .\n";
	std::cout << "    ________________________________________________\n\n\n\n";

	std::cout << "\n\n\nEnter any key: ";

	std::cout << briteWhite; // white
	if (std::cin.get()) {    // wait for any key
	}
	std::cout << briteGreen; // green
	std::cout << briteWhite; // white

	if (std::cin.get()) { // if enter key is pressed, continue

		std::cout << briteGreen; // green

		system("CLS");

		int arrayChoice;   // user choice for this section

		std::vector <std::string> v;  // declare vector to be used
		std::string line;					// declare line as string
		std::string productName;		// product name variable



		std::ifstream fin("frequency.dat"); // read file


		while (getline(fin, line)) {	// read each line
			v.push_back(line);			// add line as string in element 
		}

		std::cout << briteWhite;
		CallProcedure("CornerSplash"); // displays corner grocer logo
		std::cout << briteGreen;

		//menu display which asks user sort preference
		std::cout << "    How would you like to sort?\n";
		std::cout << "    ___________________________\n\n\n\n";
		std::cout << "1: Alphabetically\n\n";
		std::cout << "2: Decrementally\n\n";
		std::cout << "3: Incrementally\n\n";
		std::cout << "4: Randomized\n\n";
		std::cout << "\n\n\nEnter your selection: ";


		// cin arrayChoice and error check for arrayChoice while arrayChoice != 1, 2, 3, 4 
		std::cout << briteWhite; //white

		while (!(std::cin >> arrayChoice) || (arrayChoice < 1 || arrayChoice > 4)) {

			//explain error
			std::cout << "[Invalid Entry.]\nPlease enter [1|2|3|4]: ";

			//clear input stream
			std::cin.clear();

			//discard prev input
			std::cin.ignore(127, '\n');
		}


		//======= array modulators for histogram based on user choice

		// A L P H A B E T I Z E 
		if (arrayChoice == 1) {
			std::sort(v.begin(), v.end()); //alphabetize array
			system("CLS");						 //clear scree

			std::cout << briteWhite;		 // white
			CallProcedure("CornerSplash"); // py.CornerSplash logo


			std::cout << darkYellow << "   PRODUCT HISTOGRAM [" << briteWhite << "ALPHABETICAL" << darkYellow << "]\n\n";
			std::cout << briteBlue << "   ----------------> ";  std::cout << yellow; CallProcedure("PyDate"); std::cout << green;
			std::cout << gray << "   ________________________________\n\n" << green;
			//std::cout.width(18); std::cout << std::right << "| " << "\n";

			Runner(v); //send to histogram output function
		}



		// D E C R E M E N T
		if (arrayChoice == 2) {
			std::reverse(v.begin(), v.end()); // vector is already incremental; this reverses
			system("CLS");						    // clear screen

			std::cout << briteWhite;		 // white
			CallProcedure("CornerSplash"); // py.CornerSplash logo

			std::cout << darkYellow << "   PRODUCT HISTOGRAM [" << briteWhite << "DECREMENTAL" << darkYellow << "]\n\n";
			std::cout << briteBlue << "   ---------------> ";  std::cout << yellow; CallProcedure("PyDate"); std::cout << green;
			std::cout << gray << "   _______________________________\n\n" << green;
			//std::cout.width(18); std::cout << std::right << "| " << "\n";

			Runner(v); //send to histogram output function
		}



		// I N C R E M E N T
		if (arrayChoice == 3) {
			v = v;							    // no change in vector
			system("CLS");						 //clear screen

			std::cout << briteWhite;		 // white
			CallProcedure("CornerSplash"); // py.CornerSplash logo

			std::cout << darkYellow << "   PRODUCT HISTOGRAM [" << briteWhite << "INCREMENTAL" << darkYellow << "]\n\n";
			std::cout << briteBlue << "   ---------------> ";  std::cout << yellow; CallProcedure("PyDate"); std::cout << green;
			std::cout << gray << "   _______________________________\n\n" << green;
			//std::cout.width(18); std::cout << std::right << "| " << "\n";

			Runner(v); //send to histogram output function
		}


		//	R A N D O M I Z E 
		if (arrayChoice == 4) {

			std::random_device rd;  // random seed generator
			std::mt19937 g(rd());   // Mersenne Twister pseudo-random generator [https://www.cplusplus.com/reference/random/mt19937/]

			std::shuffle(v.begin(), v.end(), g); // shuffle array

			for (unsigned int k = 0; k < v.size(); k++) {
				std::cout << v.at(k) << "\n";		 // resets element positions
			}

			system("CLS");						       // clear screen

			std::cout << briteWhite;		 // white
			CallProcedure("CornerSplash"); // py.CornerSplash logo

			std::cout << darkYellow << "   PRODUCT HISTOGRAM [" << briteWhite << "RANDOMIZED" << darkYellow << "]\n\n";
			std::cout << briteBlue << "   --------------> "; std::cout << yellow; CallProcedure("PyDate"); std::cout << green;
			std::cout << gray << "   ______________________________\n\n" << green;
			//std::cout.width(18); std::cout << std::right << "| " << "\n";

			Runner(v); //send to histogram output function
		}


	}
}










	//displays user menu
	void UserMenu() {


		//declare variables
		int userChoice;

		std::cout << briteWhite;		 // white
		CallProcedure("CornerSplash"); // py.CornerSplash logo
		std::cout << briteGreen;		 // green

		//menu display
		std::cout << "    What would you like to do?\n";
		std::cout << "    __________________________\n\n\n\n";
		std::cout << "1: Display Product Purchase Count\n\n";
		std::cout << "2: Search For a Specific Item (SKU)\n\n";
		std::cout << "3: Generate a Product Histogram\n\n";
		std::cout << "4: Exit\n\n";
		std::cout << "\n\n\nEnter your selection: ";

		std::cout << briteWhite;

		// cin userChoice and error check for userChoice while userChoice != 1, 2, 3, 4 

		while (!(std::cin >> userChoice) || (userChoice < 1 || userChoice > 4)) {

			//explain error
			std::cout << briteGreen << "[Invalid Entry.]\nPlease enter [1|2|3|4]: " << briteWhite;

			//clear input stream
			std::cin.clear();

			//discard prev input
			std::cin.ignore(127, '\n');
		}






		//============ PRODUCT PRUCHASE COUNT ====================== OPTION 1
		if (userChoice == 1) {

			Option1(); // run 

			// prompts user for any key to continue
			std::cout << "\n\n\n\n\nPress any key to continue to main menu . . . ";
			std::cin.ignore(); // clear cin

			std::cout << briteWhite; //white

			if (std::cin.get()) {  // if enter key is pressed
				system("CLS");      // clear screen
				UserMenu();         // loop menu
			}


			else {            // otherwise continue
				system("CLS"); // clear screen
				UserMenu();    // loop menu
			}

		};



		//========= SEARCH FOR SPECIFIC ITEM ====================== OPTION 2 
		if (userChoice == 2) {


			Option2(); // go to search function

			std::cout << briteGreen; //white

			// prompts user for any key to continue after return
			std::cout << "\nPress any key to continue to main menu . . . " << briteWhite;
			std::cin.ignore();     // clear cin


			if (std::cin.get()) {  // if enter key is pressed
				system("CLS");      // clear screen
				UserMenu();         // loop menu
			}
			else {                 // otherwise continue
				system("CLS");      // clear screen
				UserMenu();         // loop menu
			}

		}
		





		//=================== GENERATE HISTOGRAM ==================== option 3
		if (userChoice == 3) {
			
			
			Option3(); // go to histogram function


			//console back to green
			std::cout << briteGreen;


			// prompts user for any key to continue after return
			std::cout << "\n\n\nPress any key to continue to main menu . . . " << briteWhite;
			std::cin.ignore();     // clear cin


			if (std::cin.get()) {  // if enter key is pressed
				system("CLS");      // clear screen
				UserMenu();         // loop menu
			}
			else {                 // otherwise continue
				system("CLS");      // clear screen
				UserMenu();         // loop menu
			}

		}
		


		//=====================option 4 exit
		if (userChoice == 4) {
			std::cout << std::endl;

			system("CLS");				 // clear screen

			std::cout << briteWhite;		 // white

			CallProcedure("PyExit"); // call for exit message in py.Exit

			std::exit(3);            // end program
		}
	}




int main() {	//main

	UserMenu(); //begin program

}