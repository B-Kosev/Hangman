#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#define NOMINMAX
#include <windows.h>

using namespace std;

int lives = 5,choice=0;
int lowerLim = 0, upperLim = 0; //lenght limitations for word
vector<string> wordArr;
vector<char> usedLetters;
string word, blankWord;

void drawMenu();

void onStart()
{
	//fill array with words
	string readWord;
	ifstream in("words.txt", ios::in);
	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> readWord;
			wordArr.push_back(readWord);
		}
	}
	in.close();
}

void pickWord()
{
	//pick random word
	if (lowerLim != 0 && upperLim != 0) //if user defined lenght
	{
		do
		{
			srand(time(NULL));
			int numb = rand() % wordArr.size() + 1; //get random number to pick a word from the array
			word = wordArr[numb];
		} while (word.size() < lowerLim || word.size() > upperLim);
	}
	else
	{
		srand(time(NULL));
		int numb = rand() % wordArr.size() + 1; //get random number to pick a word from the array
		word = wordArr[numb];
	}

	//replace every character with *
	blankWord = word;
	for (int i = 0;i < blankWord.size();i++)
	{
		blankWord[i] = '*';
	}
}

int menuInputValidation(int numb, int lowerBound, int upperBound)
{
	cout << "Please enter your input: ";
	cin >> numb;
	while (numb<lowerBound || numb>upperBound)
	{
		cout << "Invalid input.\n";
		cout << "Please enter your input: ";
		cin >> numb;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
	}
	return numb;
}

void drawGame()
{
	system("CLS");
	cout << "-----------------Welcome to the Hangman game!-----------------\n\n";
	cout << "The word you have to guess is: " << blankWord << "\n";
	cout << "Used letters so far: ";
	for (int i = 0;i < usedLetters.size();i++)
		cout << usedLetters[i] << " ";
	cout << "\n\nNumber of lives: " << lives;
	cout << "\n\n---------------------------------------------------------------\n\n";
}

void gameEngine()
{
	int counter = 0;
	char input;
	bool isLetterUsed = false;
	bool correctInput = false;

	pickWord();
	usedLetters.clear();

	do
	{
		isLetterUsed = false;
		correctInput = false;
		drawGame();
		
		cout << "Please enter your guess: ";
		cin >> input;

		//check for correct input
		for (int i = 0;i < word.size();i++)
		{
			if (input == word[i])
			{
				blankWord[i] = input;
				correctInput = true;
			}
		}

		//check array with used letters if current input is in it
		for (int i = 0;i < usedLetters.size();i++)
		{
			if (input == usedLetters[i])
			{
				isLetterUsed = true;
				break;
			}
			else
				isLetterUsed = false;
		}
		if (isLetterUsed == false)
			usedLetters.push_back(input);

		//logic for lowering lives
		if (correctInput == false)
		{
			if (isLetterUsed == false)
				lives--;
		}


		//count how many * in the blank word
		counter = 0;
		for (int i = 0;i < blankWord.size();i++)
		{
			if (blankWord[i] == '*')
				counter++;
		}

	} while (counter > 0 && lives > 0);


	drawGame();
	if (counter == 0)
	{
		cout << "Congratulations! You won!";
		Sleep(3000);
	}
	else
	{
		cout << "You lost.";
		cout << "The word was: " << word;
		Sleep(3000);
	}
}

void drawOptions()
{
OPTBEGIN:
	system("CLS");
	cout << "\n-----------------Options-----------------\n\n";
	cout << "1) Change lives;\n2) Change lenght range;\n3) Exit to main menu.\n\n";

	choice = menuInputValidation(choice, 1, 3);

	switch (choice)
	{
	case 1:
	{
		cout << "\n-----------------Changing number of lives-----------------------------\n";
		int newLives = 0;
		newLives = menuInputValidation(newLives, 1, 20);
		lives = newLives;
		Sleep(2000);
		goto OPTBEGIN;
		break;
	}
	case 2:
	{
		cout << "\n-----------------Changing lenght of word-----------------------------\n";
		lowerLim = menuInputValidation(lowerLim, 1, 20);
		upperLim = menuInputValidation(upperLim, lowerLim, 20);
		Sleep(2000);
		goto OPTBEGIN;
		break;
	}
	case 3:
	{
		drawMenu();
		break;
	}
	default:
		break;
	}
}

void drawMenu()
{
	MENU:
	system("CLS");
	cout << "-----------------Welcome to the Hangman game!-----------------\n\n";
	cout << "1) Start a new game;\n2) Options;\n3) Exit.\n\n";
	
	choice=menuInputValidation(choice, 1, 3);

	switch (choice)
	{
	case 1:
	{
		gameEngine();
		break;
	}
	case 2:
	{
		drawOptions();
		break;
	}
	case 3:
	{
		return;
	}
	default:
		break;
	}
	goto MENU;
}