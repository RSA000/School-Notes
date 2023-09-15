//: GoodDocs.cpp

/* 
 Title: GoodDocsF2.cpp
 Description: Modified Temperature Conversion Program
 Date: July 27th, 2023
 Author: Richard S. Huntrods, Modified by Sullivan Andison
 Version: 1.0
 Copyright: 2013 Richard S. Huntrods
*/

/*
 DOCUMENTATION
 
 Program Purpose:
    Demonstrate proper format for documentation, test plans and comments.
    Also demonstrate user prompts, keyboard input, simple calculations and output,
    specifically converting temperatures from F to C.

 Compile: (Assuming on Arm64 Macbook with VisualStudioCode terminal and C/C++ Extension package): make GoodDocsF2
 Execution (In terminal window in proper directory): ./GoodDocsF2
 
 Classes: none

 Variables:
		CHAR variables:
			input_units (char) = C or F to designate temperature units for the supplied input temperature.
			output_units (char) = C or F to designate temperature units desired for the output conversion,
		FLOAT Variables
			input_temp (float) = real (decimal) number supplied by the user which is the input temperature.
			output_temp (float) = calculated output temperature in output_units as a real (decimal) number.

 Formulae:
    The formula for converting temperatures from Fahrenheit to Celcius is:
    T(C) = (T(F) - 32.0) * 5.0 / 9.0;
    The formula for converting temperatures from Celcius to Fahrenheit is:
    T(F) = (T(C) * 9.0 / 5.0) + 32.0

    It is important to use decimal numbers, especially in the division to avoid integer division.
    It is also important to use the parenthesis to enforce calculation order.
*/

/*
 TEST PLAN
 
 Normal case 1:
    >What is the input temperature? 32
    >What are the units of the input temperature (C for Celcius or F for Fahrenheit)? F
    >Your input temperature is 32F which is 0C.

 Normal case 2:
    >What is the input temperature? 100
    >What are the units of the input temperature (C for Celcius or F for Fahrenheit)? C
    >Your input temperature is 100C which is 212F.

 Bad Data Case 1 (temperature out of range):
    >What is the input temperature? -4000
    >What are the units of the input temperature (C for Celcius or F for Fahrenheit)? C
    >Your input temperature is -4000C which is out of range (less than -273.15C or -416F)..

 Bad Data Case 2 (incorrect units):
    >What is the input temperature? -40
    >What are the units of the input temperature (C for Celcius or F for Fahrenheit)? Q
    >The units you have specified are not one of C (Celcius) or F (Fahrenheit).

 Discussion:
    The program accepts any integer or decimal input temperature and a unit character which must be either C, c, F or f.
    The program then prints the input temperature as well as the temperature converted into the non-input units.
    The temperature range is from -273C (-415F) to any positive number. 
 
*/

#include <iostream> // Stream declarations
using namespace std;

int main(void) {
	char input_units, output_units;
	float input_temp, output_temp;
	int error = 0;

	// Print out a greeting and some basic explanation to the user.
	cout << "\n\nGreetings! This is temperature conversion app! ";
	cout << "You will first be prompted for a temperature and then the temperature scale (Fahrenheit or Celcius).";

	// request and obtain temperature
	cout << "\n\nWhat is the input temperature? ";
	cin >> input_temp;

	// request and obtain input temperature unit to be converted(Celcius or Fahrenheit)
	cout << "\n\nWhat are the units of the input temperature (C for Celcius or F for Fahrenheit)? ";
	cin >> input_units;

	// convert input units to upper case
	input_units = toupper(input_units);

	// check input_units for acceptable response; perform appropriate conversion if acceptable and print error message if not
	if(input_units == 'C') {
		// display input
		cout << "\n\nYour input temperature is " << input_temp << input_units;

		// range check input_temp
		if(input_temp < -273.15) {
			// disply out of range error message
			cout << " which is out of range (less than -273C or -459F)." << endl;
			cout << " Absolute zero is -273.15C or -459.67F. It is impossible to go below these temperatures" << endl;
		}
		else {
			// convert from Celcius to Fahrenheit
			// T(F) = (T(C) * 9.0 / 5.0) + 32.0
			output_units = 'F';
			output_temp = (input_temp * 9.0 / 5.0) + 32.0;

			// display converted output
			cout << " which is " << output_temp << output_units << "." << endl;
		}
	}
	else if(input_units == 'F') {
		// display input
		cout << "\n\nYour input temperature is: " << input_temp << input_units;

		// range check input_temp
		if(input_temp < -459.67) {
			// out of range
			cout << " which is out of range (less than -273.15C or -459.67F)." << endl;
			cout << " Absolute zero is -273.15C or -459.67F. It is impossible to go below these temperatures" << endl;
		}
		else {
			// convert from Fahrenheit to Celcius
			output_units = 'C';
			output_temp = (input_temp - 32.0) * 5.0 / 9.0;

			// display converted output
			cout << " which is " << output_temp << output_units << "." << endl;
		}
	}
	else {
		// display input_unit error message
 		cout << "\n\nThe units you have specified are not one of C (Celcius) or F (Fahrenheit)" << endl;
		cout << "The temperature unit must be a C for Celcius or F for Fahrenheit" << endl; 
	}
} ///:~
