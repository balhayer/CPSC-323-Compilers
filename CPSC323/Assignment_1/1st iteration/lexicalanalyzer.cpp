//#323 Assignment 1 first iteration
//-- Haowen Yong, Aidin Tavassoli, Balwinder Singh Hayer

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string.h>

using namespace std;

/*
4 tokens: 
identifier: variable names, ex: int num1 = 1, num1 is the identifier
keyword: from previous example, "int" is the keyword
separator: basically punctuations, ex: int num1, num2, num3, "," is the separator
operator: + - * / > < = etc.
*/

char operators[] = {'+', '-', '*', '/', '<', '>', '='};
char separators[] = {'{', '}', '(', ')', ';', ',', '[', ']', '!'};
string keyword[] = {"int", "double", "char", "string", "while", "if", "for", "continue", "break"};
fstream file;
fstream tokenlist;

bool isOperator(char c)
{	int identified = 0;
	for(char i : operators)
	{
		if(c==i)
		{	cout << c << "\t" << " operator" << endl;
			identified = 1;
			break;
		}
	}
	if(identified == 1)
		return true;
	else return false;
}

bool isSeparator(char c)
{	int identified = 0;
	for(char j : separators)
	{	if(c==j)
		{	cout << c << "\t" << " separator" << endl;
			identified = 1;
			break;
		}
	}
	if(identified == 1)
		return true;
	else return false;
}

int main(int argc, char** argv)
{	string filename = argv[1];
	string destination = argv[2];
	file.open(filename); // program reads from text.txt
	tokenlist.open(destination); // program will write the end result into this file

	int identified = 0; // if 0, means character/word has not been identified, if 1, it has been identified and can be skipped
	int word_length=20;
	char word[word_length];
	int k=0; // use k as the iterator for char array "word"
	char c;
	while(!file.eof())
	{	file.get(c);
		//cout<<c<<endl;
		if(isOperator(c))
			continue;
		if(isSeparator(c))
			continue;
		

		if(isalnum(c))
		{	word[k] = c;
			k++;
		}
		else // if code reaches else, it means that the char is an empty space
		{	if((c == ' ' || c == '\n') && k!=0)
			{	word[k] = '\0';
				k++;
				string temp = "";
				for(char ch : word)
					temp += ch;
				//bool key = isKeyword(word);
				bool key = false;
				for(string str : keyword)
				{	if(str == temp)
					{	key = true;
						break;
					}
				}
				if(key == true)
				{	cout << word << "\t" << " keyword" << endl;
				}
				else {cout << word << "\t" << " identifier" << endl;}
				word[word_length];
/*
				for(int i=0; i<=k; i++)
				{	word[i] = ;
				}
*/
				k=0;
			}
		}
	}
	return 0;
}


