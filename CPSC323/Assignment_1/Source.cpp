
/*
GroupMemberNames: Aidin Tavassoli, Haowen Yong, Balwinder Singh Hayer
Lexical Analyzer
CPSC 323 Anthony Le

------------Assignment Description--------------
This assignment creates the first part of the compiler 
and will perform following:
	-Identify Keyword, Integers, Floats, and Invalid Inputs
	-Skip Comment blocks defined as the area between two '!'
	-Skip white spaces
Tokens Type and Lexemes must be displayed in a table.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;


// this is the list of all keywords identified by the any language 
string ListKeyword[20] = { "int", "float", "bool", "if", "else", "then",
						"do", "while", "whileend", "do", "doend",
						"for", "and", "or" , "function" };

// this is the list of all valid operators & separators identified by the language
char separatorOperatorArray[21] =
{
				'*','+','-','=','/','>','<','%',							//it ranges from 0 to 7 which equals to Operators	
				'\'','(',')','{','}','[',']',',','.',':',';','!',' '//it ranges from 8 to 21 which equal to Separatos
};

//FSM is the Finite State Machine Matrix which ranges from 6 to 7
int FSM[6][7] = { 
					     1,2,4,0,0,0,0,
					     1,1,4,0,0,0,0,
					     5,2,4,0,3,0,0,
					     5,3,4,0,5,0,0,
					     4,4,0,4,4,4,4,
					     0,0,0,0,0,0,0
};

// list of all function signatures used in the program
int characterTesting(char ch, int state);
void showTheTemp(string temp);
void showTheCharacter(char ch);

// string outsourceFile is used to assign and output file in the form of text file with extension of .txt
	string outsourceFile = "output.txt";
	vector<pair<string, string>> output;

int main()
{
	string inputSourceFile;
	// input string finds the largest maximum value which comes from input file and between the testing input file
	string input = "";
	string temp;
	char character;
	int currentState = 0;
	int lengthofString = 0;


	// variable ask for the file name to insert into the algorithm 
	cout << "Please enter input file name with extension?: ";

	// it reads the input text file which contains instructions to execute from...
	cin >> inputSourceFile;

	// ifstream streams the input file 
	ifstream inFile(inputSourceFile);

	// if statement verifies if the input file is valid 
	if (!inFile.is_open()) {

		//if input file is not valid, it will throw an error to the user to verify the file name properly
		cout << "Could not open file, please check file name." << endl;
		return 1;
	}	

	// ofstream will create a output file which will be final file
	ofstream outFile(outsourceFile);

	// if statement verifies if the output has been successfully created otherwise throws an error to the user
	if (!outFile.is_open())
	{
		// throws an informative error to the user
		cout << "Cannot open output file" << endl;
		return 1;
	}

	cout << endl << endl;

	cout << "Token\t\t\tLexeme" << endl << "------------------------------------" << endl;
	outFile << "Token\t\t\tLexeme" << endl << "------------------------------------" << endl;

	// while loop will loop to the last when number of readily collected line to read 
	while (getline(inFile, input))
	{
		// lengthOfString holds the exact length of the input value or data
		lengthofString = input.length();

		// for loop will create test case to the characters 
		for (int i = 0; i < lengthofString; i++) 
		{
			// character will be assigns as input
			character = input[i];

			// comment will be broken if the ongoing state becomes equals to four (4)
			if (currentState != 4)
			{
				// it throws a transition call
				currentState = characterTesting(character, currentState);

				switch (currentState) 
				{
				// separator will be recorded and it prints out temp and character
				case 0:				
					showTheTemp(temp);
					showTheCharacter(character);
					temp = "";
					break; // breaks it 

					// it will concatenate until it verifies valid data value
				case 1 || 2 || 3:
					temp += character;
					break;
				case 4:			
					// it shows temp Before comment
					showTheTemp(temp);
					temp = "";
					break;
				case 5:					
					//Invalid Inputs, Display Invalid
					showTheTemp(temp);
					showTheCharacter(character);
					temp = "";
					break;
				}

			}
			else if (character == '!' && currentState == 4)	
				// incase current state becomes equals to four (4), comment will be broken
			{
				// currentState will be assigned into FSM current state (2)
				currentState = FSM[currentState][2];
			}
		}
		showTheTemp(temp);						
		//it will not catch anything and kept clearing the temp variable
		temp = "";
	}

	//it verifies closing the file from reading and close the input file otherwise throws an error
	inFile.close();

	cout << endl;
	// for loop
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i].first << "\t" << output[i].second << endl;
		outFile << output[i].first << "\t" << output[i].second << endl;
	}

	cout << endl << endl;
	outFile.close();

	system("pause");
	return 0;
}

// main program closed here 

int characterTesting(char character, int state)
{
	int currentState = state;


	//isalpha checks whether it is in alphabetic letter
	if (isalpha(character))
	{
		// current state assignes to the FSM
		currentState = FSM[currentState][0];
		return currentState;
	}

	//isdigit checks whether character is a decimal digit character
	else if (isdigit(character) || character == '$')
	{
		// current state assignes to the FSM
		currentState = FSM[currentState][1];
		return currentState;
	}
	else if (character == separatorOperatorArray[19]) 
	{
		// current state assignes to the FSM
		currentState = FSM[currentState][2];
		return currentState;
	}
	else if (character == separatorOperatorArray[15]) 
	{
		// current state assignes to the FSM
		currentState = FSM[currentState][4];
		return currentState;
	}
	// isspace checks whether character is a whitespace or contains any whitespace
	else if (isspace(character))
	{
		currentState = FSM[currentState][6];
	}
	else
	{
		int i = 0;
		for (i = 0; i < 8; i++)
		{
			if (character == separatorOperatorArray[i] || isspace(character))
			{
				currentState = FSM[currentState][5];
				return currentState;
			}
		}
		for (i = 8; i < 22; i++)
		{
			if (character == separatorOperatorArray[i] || isspace(character))
			{
				currentState = FSM[currentState][3];
				return currentState;
			}
		}
	}
}


void showTheTemp(string temp)
{
	
	//it shows the temp until it not properly deleted
	if (temp != "")
	{
		bool is_keyword = 0;
		//now it is testing especially for the keyword
		for (int i = 0; i < 20; i++) {

			if (ListKeyword[i] == temp)
			{
				output.push_back(pair<string, string>("Keyword:\t", temp));
				return;
			}
		}
		is_keyword = 1;
		//now it is testing for Identifiers
		if (isalpha(temp[0]) && is_keyword == 1)
		{
			output.push_back(pair<string, string>("Identifier:\t", temp));
			return;
		}
		//now it is testing for floats and integers
		int test_float = 0;
		for (int i = 0; i < temp.length(); i++)
		{
			if (temp[i] == '.')
			{
				test_float = 1;
				break;
			}
		}

		// an integer
		if (test_float == 0)		
		{
			output.push_back(pair<string, string>("Integer:\t", temp));
			return;
		}
		else if (test_float == 1)	// Float
		{
			output.push_back(pair<string, string>("Float:\t", temp));
			return;
		}
		//incase other cases fail, it will return invalid string
		output.push_back(pair<string, string>("Invalid:\t", temp));
		return;
	}
}


// character testing 
void showTheCharacter(char character)
{
	//it displays whether it is separator or operator
	string temp = string(1, character);
		for (int i = 0; i < 8; i++)
		{
			if (character == separatorOperatorArray[i])
			{
				output.push_back(pair<string, string>("Operator:\t", temp));
			}
		}
		for (int i = 8; i < 22; i++)
		{
			if (character == separatorOperatorArray[i] && character != '!' && !isspace(character))
			{
				output.push_back(pair<string, string>("Separator:\t", temp));
			}
		}
	
}