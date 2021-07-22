//********************************************************************
//
//  Author:               Jessica Page
//
//  Program #:            Ten
//
//  File Name:            Program10.cpp
//
//  Course:               COSC 1337 Programming Fundamentals II
//
//  Due Date:             7/22/21
//
//  Instructor:           Prof. Fred Kumi 
//
//  Chapter:              Chapter 2 - 11
//
//  Description:
// 
//
//
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

#include <conio.h>

#include "HouseHold.h"

using namespace std;

int openFiles(ifstream&, ofstream&);
void readFile(vector<HouseHold>&, ifstream&);
double averageDataInVector(vector<HouseHold>, int);
void aboveAverage(vector<HouseHold>, double, int, ofstream&);
void belowPovertyLevel(vector<HouseHold>, int, ofstream&);
void printDataInVector(vector<HouseHold>, int, ofstream&);
void printRecord(int, double, int, string, ofstream&);

void closeFiles(ifstream&, ofstream&);
void holdScreen(int);
void developerInfo(ofstream&);

//***************************************************************
//
//  Function:     main
// 
//  Description:  The main function of the program
//
//  Parameters:   None
//
//  Returns:      Zero (0) 
//
//**************************************************************
int main()
{
	int rtnCode = 0;
	int vectorSize = 0;
	double average = 0.0;

	ifstream inputFileObject;                        // create an input file object
	ofstream outputFileObject;                       // create an input file object

	rtnCode = openFiles(inputFileObject, outputFileObject);
	if (rtnCode == 0)
	{
		outputFileObject << fixed
			<< showpoint
			<< setprecision(2);

		developerInfo(outputFileObject);

		vector<HouseHold> houseHold;
		
		readFile(houseHold, inputFileObject);

		vectorSize = houseHold.size();

		printDataInVector(houseHold, vectorSize, outputFileObject);
		average = averageDataInVector(houseHold, vectorSize);
		aboveAverage(houseHold, average, vectorSize, outputFileObject);
		belowPovertyLevel(houseHold, vectorSize, outputFileObject);

		closeFiles(inputFileObject, outputFileObject);

		holdScreen(1);
	}
	else
	{
		holdScreen(0);
	}

	return 0;
}

//***************************************************************
//
//  Function:     openFiles
// 
//  Description:  The function opens the input and output files
//
//  Parameters:   The input and output file objects by reference
//
//  Returns:      Error code 
//
//**************************************************************
int openFiles(ifstream& inFileObject, ofstream& outFileObject)
{
	int rc = 1;

	inFileObject.open("Program10.txt");             // open the file for read
	if (!inFileObject.fail())
	{
		outFileObject.open("Program10-output.txt");  // open the file for write
		if (!outFileObject.fail())
		{
			rc = 0;
		}
		else
		{
			cout << "Unable to create output file \"Program10-output.txt\" " << endl;
		}
	}
	else
	{
		cout << "File \"Program10.txt\" " << "was not found." << endl;
	}

	return rc;
}

//***************************************************************
//
//  Function:     readFile
// 
//  Description:  The function reads the input file into a vector
//
//  Parameters:   The Vector by reference
//                The input file object by reference
//
//  Returns:      N/A 
//
//**************************************************************
void readFile(vector<HouseHold>& houseHold, ifstream& inFileObject)
{
	int rc = 0;
	int tempId;
	double tempIncome;
	int tempMembers;
	string tempState;

	inFileObject >> tempId                      // read first data
		>> tempIncome
		>> tempMembers
		>> tempState;

	while (!inFileObject.eof())                // if data is not end-of-file
	{
		HouseHold family(tempId, tempIncome, tempMembers, tempState);
		houseHold.push_back(family);

		inFileObject >> tempId                   // read the next data
			>> tempIncome
			>> tempMembers
			>> tempState;
	}
}

//*********************************************************************
//
//  Function:     averageDataInVector
// 
//  Description:  Finds the average of the data in a vector
//
//  Parameters:   The Vector 
//
//  Returns:      The average of the data in the vector
//
//*********************************************************************
double averageDataInVector(vector<HouseHold> houseHold, int theSize)
{
	double sum = 0.0;
	for (int index = 0; index < theSize; index++)
	{
		double income = houseHold[index].getAnnualIncome();
		sum += income;
	}
	double average = sum / theSize;
	return average;
}

//*********************************************************************
//
//  Function:     aboveAverage
// 
//  Description:  Prints all incomes above the average
//
//  Parameters:   The Vector,
//                Average Income,
//                Vector size
//                The outfile object by reference
//
//  Returns:      N/A
//
//*********************************************************************
void aboveAverage(vector<HouseHold> houseHold, double theAverage,
	int theSize, ofstream& outFile)
{
	outFile << endl;
	outFile << "Families above the average income of $42,727.73" << endl;
	outFile << endl;
	outFile << setw(12) << left << "ID" << setw(15) << left << "Amount" << setw(10) << left << "Members" << setw(10) << left << "State" << endl;
	outFile << endl;

	for (int index = 0; index < theSize; index++)
	{
		if (houseHold[index].getAnnualIncome() > theAverage)
		{
			outFile << setw(12) << left << houseHold[index].getId() << setw(15) << left << fixed << setprecision(2) << houseHold[index].getAnnualIncome() << setw(10) << houseHold[index].getMembers() << setw(10) << left << houseHold[index].getState() << endl;
		}
	}
}

//*********************************************************************
//
//  Function:     belowPovertyLevel
// 
//  Description:  Calculates and prints all incomes below the poverty level
//
//  Parameters:   Vector,
//                Vector size
//                The outfile object by reference
//
//  Returns:      N/A
//
//*********************************************************************
void belowPovertyLevel(vector<HouseHold> houseHold, int theSize, ofstream& outFile)
{
	outFile << endl;
	outFile << "Families below the poverty level :" << endl;
	outFile << endl;
	outFile << setw(20) << left << "Poverty Level" << setw(12) << left << "ID" << setw(15) << left << "Amount" << setw(10) << left << "Members" << setw(10) << left << "State" << endl;
	outFile << endl;

	double povertyLevel = 0.0;
	double count = 0.0;
	for (int index = 0; index < theSize; index++)
	{
		string state = houseHold[index].getState();
		int members = houseHold[index].getMembers();
		double income = houseHold[index].getAnnualIncome();
		int id = houseHold[index].getId();

		if (state == "Hawaii")
		{
			povertyLevel = 20040.00 + 5220.00 * (members - 2);
		}
		else if (state == "Alaska")
		{
			povertyLevel = 21770.00 + 5680.00 * (members - 2);
		}
		else
		{
			povertyLevel = 17420.00 + 4540.00 * (members - 2);
		}
		if (income < povertyLevel)
		{
			outFile << setw(20) << left << povertyLevel << setw(12) << left << id << setw(15) << left << fixed << setprecision(2) << income << setw(10) << left << members << setw(10) << left << state << endl;
			count++;
		}
	}
	double decimal = count / theSize;
	double percentage = decimal * 100;
	outFile << endl;
	outFile << "Percentage below the 2020 poverty level is: " << fixed << setprecision(2) << percentage << "%" << endl;
}

//*********************************************************************
//
//  Function:     printDataInVector
// 
//  Description:  Prints all the data in the vector
//
//  Parameters:   The Vector
//                Vector size
//                The outfile object by reference
//
//  Returns:      N/A
//
//*********************************************************************
void printDataInVector(vector<HouseHold> houseHold, int theSize, ofstream& outFile)
{
	outFile << endl;
	outFile << setw(12) << left << "ID" << setw(15) << left << "Amount" << setw(10) << left << "Members" << setw(10) << left << "State" << endl;
	outFile << endl;

	for (int index = 0; index < theSize; index++)
	{
		outFile << setw(12) << left << houseHold[index].getId() << setw(15) << left << fixed << setprecision(2)<< houseHold[index].getAnnualIncome() << setw(10) << houseHold[index].getMembers() << setw(10) << left << houseHold[index].getState() << endl;
	}
}

//*********************************************************************
//
//  Function:     printRecord
// 
//  Description:  Prints a record in the vector
//
//  Parameters:   IDs,
//                Income,
//                Members,
//                State,
//                The outfile object by reference

//  Returns:      N/A
//
//*********************************************************************
void printRecord(int theId, double theIncome, int theMembers,
	string theState, ofstream& outFile)
{
	outFile << endl;

}

//*********************************************************************
//
//  Function:     holeScreen
// 
//  Description:  The hold screen function
//
//  Parameters:   None
//
//  Returns:      N/A 
//
//*********************************************************************
void holdScreen(int theFlag)
{
	char ch;

	if (theFlag)
		cout << "\nOutput sent to \"Program10-output.txt\". Press any key to exit... ";
	else
		cout << "\nPress any key to exit... ";

	ch = getch();
	cout << endl;
}


//***************************************************************
//
//  Function:     developerInfo
// 
//  Description:  The developer information function of the program
//
//  Parameters:   The output file object by reference
//
//  Returns:      N/A 
//
//**************************************************************
void developerInfo(ofstream& outputFileObject)
{
	outputFileObject << "Name:     Jessica Page" << endl;
	outputFileObject << "Course:   COSC-1337 Programming Fundamentals II" << endl;
	outputFileObject << "Program:  Ten"
		<< endl
		<< endl;
} // End of developerInfo

//***************************************************************
//
//  Function:     closeFiles
// 
//  Description:  The function closes both files
//
//  Parameters:   The input and output files object by reference
//
//  Returns:      N/A 
//
//**************************************************************
void closeFiles(ifstream& inFileObject, ofstream& outFileObject)
{
	inFileObject.close();
	outFileObject.close();
}