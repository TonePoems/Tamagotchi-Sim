#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>
#include <Windows.h>

using namespace std;

class tamagotchi
{
public:
	//constructors
	tamagotchi(); //default constructor

	//methods
	//setters
	void SetFilename(string);
	void SetName(string);
	void SetPoints(int);
	void SetHunger(int);
	void SetHappiness(int);
	void SetSick(bool);
	void SetSprite(int);

	//getters
	string GetFilename();
	string GetName();
	int GetPoints();
	int GetHunger();
	int GetHappiness();
	bool GetSick();
	int GetSprite();

	//custom
	void DrawSprite(); //prints the sprite of the current tamagotchi
	void PlayMiniGame();
	int testForWin(string); //0 for no win, 1 for x win, 2 for o win, 3 for tie

	void DrawHungerMeter();
	void DrawHappinessMeter();

protected:
	string filename;
	string name;
	int points;
	int hunger;
	int happiness;
	bool sick;
	int sprite;

	//tic tac toe variables
	vector <char> rowA;
	vector <char> rowB;
	vector <char> rowC;
	int myCount;

	//set up random responses
	vector <string> quoteChoice;
	int randomQuote;
};

//default costructor
tamagotchi::tamagotchi()
{
	points = 0;
	hunger = 2;
	happiness = 2;
	sick = 0;

	srand(time(NULL)); //for random number generator
}

//setters
void tamagotchi::SetFilename(string F)
{
	filename = F;
}
void tamagotchi::SetName(string N)
{
	name = N;
}
void tamagotchi::SetPoints(int A)
{
	points = A;
}
void tamagotchi::SetHunger(int H)
{
	hunger = H;

	if (hunger < 0)
	{
		hunger = 0;
	}
	else if (hunger > 4)
	{
		hunger = 4;
	}
}
void tamagotchi::SetHappiness(int H)
{
	happiness = H;

	if (happiness < 0)
	{
		happiness = 0;
	}
	else if (happiness > 4)
	{
		happiness = 4;
	}
}
void tamagotchi::SetSick(bool S)
{
	sick = S;
}
void tamagotchi::SetSprite(int S)
{
	sprite = S;
}

//getters
string tamagotchi::GetFilename()
{
	return(filename);
}
string tamagotchi::GetName()
{
	return(name);
}
int tamagotchi::GetPoints()
{
	return(points);
}
int tamagotchi::GetHunger()
{
	return(hunger);
}
int tamagotchi::GetHappiness()
{
	return(happiness);
}
bool tamagotchi::GetSick()
{
	return(sick);
}
int tamagotchi::GetSprite()
{
	return(sprite);
}

//custom
void tamagotchi::DrawSprite()
{
	cout << endl;
	switch (sprite)
	{
	case 1:
		cout << endl;
		cout << setw(37) << " " << " (\\_/)" << endl;
		cout << setw(37) << " " << "(='.'=)" << endl;
		cout << setw(37) << " " << "(\")_(\")" << endl;
		cout << endl;
		break;
	case 2:
		cout << endl;
		cout << setw(36) << " " << "  @..@" << endl;
		cout << setw(36) << " " << " (----)" << endl;
		cout << setw(36) << " " << "( >__< )" << endl;
		cout << setw(36) << " " << "^^ ~~ ^^" << endl;
		break;
	case 3:
		cout << setw(38) << " " << " ,__," << endl;
		cout << setw(38) << " " << "(o.o)" << endl;
		cout << setw(38) << " " << "/),,)" << endl;
		cout << setw(38) << " " << " \" \"" << endl;
		break;
	case 4:
		cout << setw(39) << " " << " _" << endl;
		cout << setw(39) << " " << "('<" << endl;
		cout << setw(39) << " " << "/))" << endl;
		cout << setw(39) << " " << "/\"" << endl;
		cout << endl;
		break;
	case 5:
		cout << setw(36) << " " << "    __" << endl;
		cout << setw(36) << " " << "___( o)>" << endl;
		cout << setw(36) << " " << "\\ <_. )" << endl;
		cout << setw(36) << " " << " `---'" << endl;
		break;
	}
	cout << endl;
}

void tamagotchi::PlayMiniGame()
{
	//randomly pick between playing tic tac toe and hangman with the computer
	int rNum;

	rNum = rand() % 2; //pick a random game to play;

	if (rNum == 1)
	{
		//play hangman
		//ascii hangman chars
		char corner1 = 201;
		char corner2 = 184;
		char vertical = 186;
		char horizontal = 205;
		char support = 202;
		char vertical2 = 179;

		//declare variables
		vector <string> easywords(10); //declare vector of easy names

		int MAX_TRIES = 5; //number of tries they get
		int length; //length of the word to be guessed
		int number_of_wrong_guesses; //how many times they enter a worng answer
		int rNum2; //random number for selecting the random word

		string secretword; //randomly generated word
		string guessword; //current state of the word

		bool won = false; //to tell if the game is over

		char guess;

		srand(time(NULL)); //create the random timer

		//initialise easy words
		easywords[0] = "happy";
		easywords[1] = "rabbit";
		easywords[2] = "bunny";
		easywords[3] = "duck";
		easywords[4] = "owl";
		easywords[5] = "bird";
		easywords[6] = "frog";
		easywords[7] = "tadpole";
		easywords[8] = "tamagotchi";
		easywords[9] = "hoot";

		//display the menu
		system("cls");
		tamagotchi::DrawSprite();

		//specify quotes
		quoteChoice.resize(4);
		quoteChoice[0] = "Welcome to Hangman!";
		quoteChoice[1] = "Let's play Hangman!";
		quoteChoice[2] = "We should play Hangman!";
		quoteChoice[3] = "Hangman it is!";

		randomQuote = rand() % 4;

		cout << quoteChoice[randomQuote] << endl;
		cout << "Your job is to guess the randomly selected word." << endl; //first line of the menu
		cout << "Each letter is represented by an asterisk." << endl; //second line of the menu
		cout << "You have to type only one letter in one try." << endl; //third line of code
		cout << "You have 5 tries to try and guess the word." << endl; //fourth line of the menu
		cout << "********************************************" << endl; //asterisks completing the menu


		cout << "Let's Start The Game!\n\n"; //print to the top of the screen

		system("pause");

		//set the number of guesses to 5
		number_of_wrong_guesses = 0;
		//set the secret word from the easy list of words
		rNum2 = rand() % 10; //picks a random number from 0 to 9
		secretword = easywords[rNum2]; //set the secret word to one from the list
		length = secretword.length(); //set the length to the length of the string
		guessword.resize(0); //set the size to 0 to clear the string

		for (int a = 0; a < length; a++) //loop to add the same number of asterisks to the guess word
		{
			guessword += "*"; //add an asterisks to the guess word variable
		}


		system("cls");

		//print the hangman
				//line 1
				cout << endl << " " << corner1 << horizontal << horizontal << corner2 << endl;
				//line 2
				cout << " " << vertical << "  ";
				if (number_of_wrong_guesses > 0)
				{
					cout << "O";
				}
				cout << endl;
				//line 3
				cout << " " << vertical << " ";
				if (number_of_wrong_guesses > 1)
				{
					cout << "/";
				}
				else
				{
					cout << " ";
				}
				if (number_of_wrong_guesses > 0)
				{
					cout << vertical2;
				}
				if (number_of_wrong_guesses > 3)
				{
					cout << "\\";
				}
				cout << endl;
				//line 4
				cout << " " << vertical << "  ";
				if (number_of_wrong_guesses > 0)
				{
					cout << vertical2;
				}
				cout << endl;
				//line 5
				cout << " " << vertical << " ";
				if (number_of_wrong_guesses > 2)
				{
					cout << "/";
				}
				cout << " ";
				if (number_of_wrong_guesses > 4)
				{
					cout << "\\";
				}
				cout << endl;
				//line 6
				cout << horizontal << support << horizontal << endl;

		cout << guessword << endl;
		//get the users char guess
		cout << "Please enter your letter guess: ";
		cin >> guess;

		system("cls");
		do
		{
			//check to see if the character matches one in the secret word
			int correct = 0; //number of correct chars
			for (int a = 0; a < length; a++) //loop to go through all the letters in the secret word
			{
				if (guess == secretword[a] && guessword[a] != guess) //if the guess is correct and the letter is not already guessed
				{
					correct++; //add one to correct

					guessword[a] = secretword[a]; //set the letter that is correct in the guessword
				}
			}

			if (correct == 0) //if they dont have a correct guess...
			{
				number_of_wrong_guesses++; //add one to number of wrong guesses

				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "Whoops! That letter isnt there...";
				quoteChoice[1] = "Wow, you really tried that letter???";
				quoteChoice[2] = "C'mon man, try harder.";
				quoteChoice[3] = "That wasn't even close.";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;

				cout << "You have " << MAX_TRIES - number_of_wrong_guesses << " guesses left." << endl; //tells the user how many guesses they have left
			}
			else if (correct == 1 || correct == 2) //if the guess is correct
			{
				system("cls");

				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "You found a letter! Isn't that exciting?";
				quoteChoice[1] = "You got mad skillz, you found a letter!";
				quoteChoice[2] = "You found a letter! That's awesome!";
				quoteChoice[3] = "Encontraste una carta!";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;

				cout << "You have " << MAX_TRIES - number_of_wrong_guesses << " guesses left." << endl; //tells the user how many guesses they have left
			}

			if (number_of_wrong_guesses == MAX_TRIES) // if they use all 5 tries, game over
			{
				system("cls");
				tamagotchi::DrawSprite();

				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "Yes! I beat you! See if you can do better next time.";
				quoteChoice[1] = "JA ich dich schlagen!";
				quoteChoice[2] = "You just got beat by a computer program...";
				quoteChoice[3] = "How do you feel to lose to a computer?";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;

				//print the hangman
				//line 1
				cout << endl << " " << corner1 << horizontal << horizontal << corner2 << endl;
				//line 2
				cout << " " << vertical << "  ";
				if (number_of_wrong_guesses > 0)
				{
					cout << "O";
				}
				cout << endl;
				//line 3
				cout << " " << vertical << " ";
				if (number_of_wrong_guesses > 1)
				{
					cout << "/";
				}
				else
				{
					cout << " ";
				}
				if (number_of_wrong_guesses > 0)
				{
					cout << vertical2;
				}
				if (number_of_wrong_guesses > 3)
				{
					cout << "\\";
				}
				cout << endl;
				//line 4
				cout << " " << vertical << "  ";
				if (number_of_wrong_guesses > 0)
				{
					cout << vertical2;
				}
				cout << endl;
				//line 5
				cout << " " << vertical << " ";
				if (number_of_wrong_guesses > 2)
				{
					cout << "/";
				}
				cout << " ";
				if (number_of_wrong_guesses > 4)
				{
					cout << "\\";
				}
				cout << endl;
				//line 6
				cout << horizontal << support << horizontal << endl;

				cout << "The word was : " << secretword << endl;
				system("pause");
				won = true; //game is over
			}

			if (guessword == secretword) //if all the letters are the same...
			{
				system("cls");
				tamagotchi::DrawSprite();

				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "Yeah! You got it!";
				quoteChoice[1] = "Good for you!";
				quoteChoice[2] = "Ding Ding Ding WINNER!!!";
				quoteChoice[3] = "You won!";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;

				//print the hangman
				//line 1
				cout << endl << " " << corner1 << horizontal << horizontal << corner2 << endl;
				//line 2
				cout << " " << vertical << "  ";
				if (number_of_wrong_guesses > 0)
				{
					cout << "O";
				}
				cout << endl;
				//line 3
				cout << " " << vertical << " ";
				if (number_of_wrong_guesses > 1)
				{
					cout << "/";
				}
				else
				{
					cout << " ";
				}
				if (number_of_wrong_guesses > 0)
				{
					cout << vertical2;
				}
				if (number_of_wrong_guesses > 3)
				{
					cout << "\\";
				}
				cout << endl;
				//line 4
				cout << " " << vertical << "  ";
				if (number_of_wrong_guesses > 0)
				{
					cout << vertical2;
				}
				cout << endl;
				//line 5
				cout << " " << vertical << " ";
				if (number_of_wrong_guesses > 2)
				{
					cout << "/";
				}
				cout << " ";
				if (number_of_wrong_guesses > 4)
				{
					cout << "\\";
				}
				cout << endl;
				//line 6
				cout << horizontal << support << horizontal << endl;

				cout << "The word was " << secretword << "." << endl;
				system("pause");
				won = true; //game is over
			}

			if (won != true)
			{
				//print the hangman
				//line 1
				cout << endl << " " << corner1 << horizontal << horizontal << corner2 << endl;
				//line 2
				cout << " " << vertical << "  ";
				if (number_of_wrong_guesses > 0)
				{
					cout << "O";
				}
				cout << endl;
				//line 3
				cout << " " << vertical << " ";
				if (number_of_wrong_guesses > 1)
				{
					cout << "/";
				}
				else
				{
					cout << " ";
				}
				if (number_of_wrong_guesses > 0)
				{
					cout << vertical2;
				}
				if (number_of_wrong_guesses > 3)
				{
					cout << "\\";
				}
				cout << endl;
				//line 4
				cout << " " << vertical << "  ";
				if (number_of_wrong_guesses > 0)
				{
					cout << vertical2;
				}
				cout << endl;
				//line 5
				cout << " " << vertical << " ";
				if (number_of_wrong_guesses > 2)
				{
					cout << "/";
				}
				cout << " ";
				if (number_of_wrong_guesses > 4)
				{
					cout << "\\";
				}
				cout << endl;
				//line 6
				cout << horizontal << support << horizontal << endl;

				cout << guessword << endl;
				//get the users char guess
				cout << "Please enter your letter guess: ";
				cin >> guess;

				system("cls");
			}
		}
		while (won != true);
		system("cls");
	}

	else if (rNum == 0)		//play tic tac toe ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	{
		//print greeting and rules
		system("cls");
		tamagotchi::DrawSprite(); 

		//specify quotes
		quoteChoice.resize(4);
		quoteChoice[0] = "Hya there! Lets play Tic Tac Toe!";
		quoteChoice[1] = "I know, let's play Tic Tac Toe!";
		quoteChoice[2] = "We should play Toe Tac Tic!";
		quoteChoice[3] = "Can you beat me in Tic Tac Toe?";

		randomQuote = rand() % 4;

		cout << quoteChoice[randomQuote] << endl;
		cout << "Your goal is to get 3 O's in a row and stop my X's from winning!" << endl;
		cout << "When it's your turn, enter the row letter and column number you would like to   play." << endl;

		system("pause");

		rowA.resize(3);
		rowB.resize(3);
		rowC.resize(3);

		//reset variables
		rowA[0] = ' ';
		rowA[1] = ' ';
		rowA[2] = ' ';
		rowB[0] = ' ';
		rowB[1] = ' ';
		rowB[2] = ' ';
		rowC[0] = ' ';
		rowC[1] = ' ';
		rowC[2] = ' ';

		bool quit = false, winner = false, played;
		char player;
		string choice;
		int win;

		char vertical = 179;
		char horizontal = 196;
		char cross = 197;

		myCount = 0;
		srand(time(NULL));
		int rNum1, rNum2;
		do
		{
			//computer's turn

			//simulate computer "thinking"
			system("cls");

			//specify quotes
			quoteChoice.resize(4);
			quoteChoice[0] = "Let me make my move...";
			quoteChoice[1] = "Trying to beat you...";
			quoteChoice[2] = "Figuring out my next move...";
			quoteChoice[3] = "Plotting my move...";

			randomQuote = rand() % 4;

			cout << quoteChoice[randomQuote] << endl << endl;

			cout << "  1   2   3" << endl;
			cout << "a " << rowA[0] << " " << vertical << " " << rowA[1] << " " << vertical << " " << rowA[2] << endl;
			cout << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
			cout << "b " << rowB[0] << " " << vertical << " " << rowB[1] << " " << vertical << " " << rowB[2] << endl;
			cout  << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
			cout << "c " << rowC[0] << " " << vertical << " " << rowC[1] << " " << vertical << " " << rowC[2] << endl << endl;

			Sleep(4000);

			system("cls");
			//end thinking 

			myCount++;

			player = 'X';

			played = false;

			//offensive moves
			if (rowA[0] == 'X' && rowA[1] == 'X' || rowA[1] == 'X' && rowA[2] == 'X' ||rowA[0] == 'X' && rowA[2] == 'X') //if the computer must block...
			{
				if (rowA[0] == ' ')
				{
					rowA[0] = player;
					played = true;
					win = tamagotchi::testForWin("a1");
				}
				else if (rowA[1] == ' ')
				{
					rowA[1] = player;
					played = true;
					win = tamagotchi::testForWin("a2");
				}
				else if (rowA[2] == ' ')
				{
					rowA[2] = player;
					played = true;
					win = tamagotchi::testForWin("a3");
				}
			}
			else if (rowB[0] == 'X' && rowB[1] == 'X' || rowB[1] == 'X' && rowB[2] == 'X' ||rowB[0] == 'X' && rowB[2] == 'X') //if the computer must block...
			{
				if (rowB[0] == ' ')
				{
					rowB[0] = player;
					played = true;
					win = tamagotchi::testForWin("b1");
				}
				else if (rowB[1] == ' ')
				{
					rowB[1] = player;
					played = true;
					win = tamagotchi::testForWin("b2");
				}
				else if (rowB[2] == ' ')
				{
					rowB[2] = player;
					played = true;
					win = tamagotchi::testForWin("b3");
				}
			}
			else if (rowC[0] == 'X' && rowC[1] == 'X' || rowC[1] == 'X' && rowC[2] == 'X' ||rowC[0] == 'X' && rowC[2] == 'X') //if the computer must block...
			{
				if (rowC[0] == ' ')
				{
					rowC[0] = player;
					played = true;
					win = tamagotchi::testForWin("c1");
				}
				else if (rowC[1] == ' ')
				{
					rowC[1] = player;
					played = true;
					win = tamagotchi::testForWin("c2");
				}
				else if (rowC[2] == ' ')
				{
					rowC[2] = player;
					played = true;
					win = tamagotchi::testForWin("c3");
				}
			}

			else if (rowA[0] == 'X' && rowB[0] == 'X' || rowB[0] == 'X' && rowC[0] == 'X' || rowA[0] == 'X' && rowC[0] == 'X') //if the computer must block...
			{
				if (rowA[0] == ' ')
				{
					rowA[0] = player;
					played = true;
					win = tamagotchi::testForWin("a1");
				}
				else if (rowB[0] == ' ')
				{
					rowB[0] = player;
					played = true;
					win = tamagotchi::testForWin("b1");
				}
				else if (rowC[2] == ' ')
				{
					rowC[0] = player;
					played = true;
					win = tamagotchi::testForWin("c1");
				}
			}
			else if (rowA[1] == 'X' && rowB[1] == 'X' || rowB[1] == 'X' && rowC[1] == 'X' || rowA[1] == 'X' && rowC[1] == 'X') //if the computer must block...
			{
				if (rowA[1] == ' ')
				{
					rowA[1] = player;
					played = true;
					win = tamagotchi::testForWin("a2");
				}
				else if (rowB[1] == ' ')
				{
					rowB[1] = player;
					played = true;
					win = tamagotchi::testForWin("b2");
				}
				else if (rowC[1] == ' ')
				{
					rowC[1] = player;
					played = true;
					win = tamagotchi::testForWin("c2");
				}
			}
			else if (rowA[2] == 'X' && rowB[2] == 'X' || rowB[2] == 'X' && rowC[2] == 'X' || rowA[2] == 'X' && rowC[2] == 'X') //if the computer must block...
			{
				if (rowA[2] == ' ')
				{
					rowA[2] = player;
					played = true;
					win = tamagotchi::testForWin("a3");
				}
				else if (rowB[2] == ' ')
				{
					rowB[2] = player;
					played = true;
					win = tamagotchi::testForWin("b3");
				}
				else if (rowC[2] == ' ')
				{
					rowC[2] = player;
					played = true;
					win = tamagotchi::testForWin("c3");
				}
			}
			else if (rowA[0] == 'X' && rowB[1] == 'X' || rowB[1] == 'X' && rowC[2] == 'X' || rowA[0] == 'X' && rowC[2] == 'X')
			{
				if (rowA[0] == ' ')
				{
					rowA[0] = player;
					played = true;
					win = tamagotchi::testForWin("a1");
				}
				else if (rowB[1] == ' ')
				{
					rowB[1] = player;
					played = true;
					win = tamagotchi::testForWin("b2");
				}
				else if (rowC[2] == ' ')
				{
					rowC[2] = player;
					played = true;
					win = tamagotchi::testForWin("c3");
				}
			}
			else if (rowA[2] == 'X' && rowB[1] == 'X' || rowB[1] == 'X' && rowC[0] == 'X' || rowA[2] == 'X' && rowC[0] == 'X')
			{
				if (rowA[2] == ' ')
				{
					rowA[2] = player;
					played = true;
					win = tamagotchi::testForWin("a3");
				}
				else if (rowB[1] == ' ')
				{
					rowB[1] = player;
					played = true;
					win = tamagotchi::testForWin("b2");
				}
				else if (rowC[0] == ' ')
				{
					rowC[0] = player;
					played = true;
					win = tamagotchi::testForWin("c1");
				}
			}

			if (played != true) //if no moves were made offensivly
			{
				if (rowA[0] == 'O' && rowA[1] == 'O' || rowA[1] == 'O' && rowA[2] == 'O' ||rowA[0] == 'O' && rowA[2] == 'O') //if the computer must block...
				{
					if (rowA[0] == ' ')
					{
						rowA[0] = player;
						played = true;
						win = tamagotchi::testForWin("a1");
					}
					else if (rowA[1] == ' ')
					{
						rowA[1] = player;
						played = true;
						win = tamagotchi::testForWin("a2");
					}
					else if (rowA[2] == ' ')
					{
						rowA[2] = player;
						played = true;
						win = tamagotchi::testForWin("a3");
					}
				}
				else if (rowB[0] == 'O' && rowB[1] == 'O' || rowB[1] == 'O' && rowB[2] == 'O' ||rowB[0] == 'O' && rowB[2] == 'O') //if the computer must block...
				{
					if (rowB[0] == ' ')
					{
						rowB[0] = player;
						played = true;
						win = tamagotchi::testForWin("b1");
					}
					else if (rowB[1] == ' ')
					{
						rowB[1] = player;
						played = true;
						win = tamagotchi::testForWin("b2");
					}
					else if (rowB[2] == ' ')
					{
						rowB[2] = player;
						played = true;
						win = tamagotchi::testForWin("b3");
					}
				}
				else if (rowC[0] == 'O' && rowC[1] == 'O' || rowC[1] == 'O' && rowC[2] == 'O' ||rowC[0] == 'O' && rowC[2] == 'O') //if the computer must block...
				{
					if (rowC[0] == ' ')
					{
						rowC[0] = player;
						played = true;
						win = tamagotchi::testForWin("c1");
					}
					else if (rowC[1] == ' ')
					{
						rowC[1] = player;
						played = true;
						win = tamagotchi::testForWin("c2");
					}
					else if (rowC[2] == ' ')
					{
						rowC[2] = player;
						played = true;
						win = tamagotchi::testForWin("c3");
					}
				}

				else if (rowA[0] == 'O' && rowB[0] == 'O' || rowB[0] == 'O' && rowC[0] == 'O' || rowA[0] == 'O' && rowC[0] == 'O') //if the computer must block...
				{
					if (rowA[0] == ' ')
					{
						rowA[0] = player;
						played = true;
						win = tamagotchi::testForWin("a1");
					}
					else if (rowB[0] == ' ')
					{
						rowB[0] = player;
						played = true;
						win = tamagotchi::testForWin("b1");
					}
					else if (rowC[2] == ' ')
					{
						rowC[0] = player;
						played = true;
						win = tamagotchi::testForWin("c1");
					}
				}
				else if (rowA[1] == 'O' && rowB[1] == 'O' || rowB[1] == 'O' && rowC[1] == 'O' || rowA[1] == 'O' && rowC[1] == 'O') //if the computer must block...
				{
					if (rowA[1] == ' ')
					{
						rowA[1] = player;
						played = true;
						win = tamagotchi::testForWin("a2");
					}
					else if (rowB[1] == ' ')
					{
						rowB[1] = player;
						played = true;
						win = tamagotchi::testForWin("b2");
					}
					else if (rowC[1] == ' ')
					{
						rowC[1] = player;
						played = true;
						win = tamagotchi::testForWin("c2");
					}
				}
				else if (rowA[2] == 'O' && rowB[2] == 'O' || rowB[2] == 'O' && rowC[2] == 'O' || rowA[2] == 'O' && rowC[2] == 'O') //if the computer must block...
				{
					if (rowA[2] == ' ')
					{
						rowA[2] = player;
						played = true;
						win = tamagotchi::testForWin("a3");
					}
					else if (rowB[2] == ' ')
					{
						rowB[2] = player;
						played = true;
						win = tamagotchi::testForWin("b3");
					}
					else if (rowC[2] == ' ')
					{
						rowC[2] = player;
						played = true;
						win = tamagotchi::testForWin("c3");
					}
				}
				else if (rowA[0] == 'O' && rowB[1] == 'O' || rowB[1] == 'O' && rowC[2] == 'O' || rowA[0] == '0' && rowC[2] == 'O')
				{
					if (rowA[0] == ' ')
					{
						rowA[0] = player;
						played = true;
						win = tamagotchi::testForWin("a1");
					}
					else if (rowB[1] == ' ')
					{
						rowB[1] = player;
						played = true;
						win = tamagotchi::testForWin("b2");
					}
					else if (rowC[2] == ' ')
					{
						rowC[2] = player;
						played = true;
						win = tamagotchi::testForWin("c3");
					}
				}
				else if (rowA[2] == 'O' && rowB[1] == 'O' || rowB[1] == 'O' && rowC[0] == 'O' || rowA[2] == '0' && rowC[0] == 'O')
				{
					if (rowA[2] == ' ')
					{
						rowA[2] = player;
						played = true;
						win = tamagotchi::testForWin("a3");
					}
					else if (rowB[1] == ' ')
					{
						rowB[1] = player;
						played = true;
						win = tamagotchi::testForWin("b2");
					}
					else if (rowC[0] == ' ')
					{
						rowC[0] = player;
						played = true;
						win = tamagotchi::testForWin("c1");
					}
				}
			}


			do
			{
				if (played != true) //if no blocking moves must be made....
				{
					rNum1 = rand() % 3;
					rNum2 = rand() % 3;

					if (rNum1 == 0) //row a
					{
						if (rNum2 == 0)
						{
							if (rowA[0] == ' ')
							{
								rowA[0] = player;
								played = true;
								win = tamagotchi::testForWin("a1");
							}
						}
						else if (rNum2 == 1)
						{
							if (rowA[1] == ' ')
							{
								rowA[1] = player;
								played = true;
								win = tamagotchi::testForWin("a2");
							}
						}
						else if (rNum2 == 2)
						{
							if (rowA[2] == ' ')
							{
								rowA[2] = player;
								played = true;
								win = tamagotchi::testForWin("a3");
							}
						}
					}
					else if (rNum1 == 1) //row b
					{
						if (rNum2 == 0)
						{
							if (rowB[0] == ' ')
							{
								rowB[0] = player;
								played = true;
								win = tamagotchi::testForWin("b1");
							}
						}
						else if (rNum2 == 1)
						{
							if (rowB[1] == ' ')
							{
								rowB[1] = player;
								played = true;
								win = tamagotchi::testForWin("b2");
							}
						}
						else if (rNum2 == 2)
						{
							if (rowB[2] == ' ')
							{
								rowB[2] = player;
								played = true;
								win = tamagotchi::testForWin("b3");
							}
						}
					}
					else if (rNum1 == 2) //row c
					{
						if (rNum2 == 0)
						{
							if (rowC[0] == ' ')
							{
								rowC[0] = player;
								played = true;
								win = tamagotchi::testForWin("c1");
							}
						}
						else if (rNum2 == 1)
						{
							if (rowC[1] == ' ')
							{
								rowC[1] = player;
								played = true;
								win = tamagotchi::testForWin("c2");
							}
						}
						else if (rNum2 == 2)
						{
							if (rowC[2] == ' ')
							{
								rowC[2] = player;
								played = true;
								win = tamagotchi::testForWin("c3");
							}
						}
					}
				}


			}
			while (played != true);

			if (win == 1)
			{
				system("cls");
				winner = true;
				tamagotchi::DrawSprite();

				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "You suck, a computer won the game!";
				quoteChoice[1] = "Wow, you need to rethink your life... a computer beat you.";
				quoteChoice[2] = "Tell your friends a computer beat you.";
				quoteChoice[3] = "How do you feel, losing to a computer?";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;
				cout << "  1   2   3" << endl;
				cout << "a " << rowA[0] << " " << vertical << " " << rowA[1] << " " << vertical << " " << rowA[2] << endl;
				cout << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "b " << rowB[0] << " " << vertical << " " << rowB[1] << " " << vertical << " " << rowB[2] << endl;
				cout  << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "c " << rowC[0] << " " << vertical << " " << rowC[1] << " " << vertical << " " << rowC[2] << endl << endl;
				system("pause");
				return;
			}
			else if (win == 2)
			{
				system("cls");
				winner = true;
				tamagotchi::DrawSprite();

				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "Congrats, You won the game!";
				quoteChoice[1] = "GG";
				quoteChoice[2] = "I'm gonna go practice some more.";
				quoteChoice[3] = "Hopefuly I'll do better against you next time.";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;
				cout << "  1   2   3" << endl;
				cout << "a " << rowA[0] << " " << vertical << " " << rowA[1] << " " << vertical << " " << rowA[2] << endl;
				cout << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "b " << rowB[0] << " " << vertical << " " << rowB[1] << " " << vertical << " " << rowB[2] << endl;
				cout  << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "c " << rowC[0] << " " << vertical << " " << rowC[1] << " " << vertical << " " << rowC[2] << endl << endl;
				system("pause");
				return;
			}
			else if (win == 3)
			{
				system("cls");
				winner = true;
				tamagotchi::DrawSprite();

				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "The game was a tie, better luck next time!";
				quoteChoice[1] = "Hopefuly I'll beat you next time.";
				quoteChoice[2] = "That was a close game, but we tied!";
				quoteChoice[3] = "Even match I see, good job!";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;
				cout << "  1   2   3" << endl;
				cout << "a " << rowA[0] << " " << vertical << " " << rowA[1] << " " << vertical << " " << rowA[2] << endl;
				cout << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "b " << rowB[0] << " " << vertical << " " << rowB[1] << " " << vertical << " " << rowB[2] << endl;
				cout  << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "c " << rowC[0] << " " << vertical << " " << rowC[1] << " " << vertical << " " << rowC[2] << endl << endl;
				system("pause");
				return;
			}


			myCount++;
			system("cls");

			player = 'O';

			//specify quotes
			quoteChoice.resize(4);
			quoteChoice[0] = "Your turn!";
			quoteChoice[1] = "Make your move!";
			quoteChoice[2] = "Do your worst!";
			quoteChoice[3] = "Bring it on!";

			randomQuote = rand() % 4;

			cout << quoteChoice[randomQuote] << endl << endl;

			//menu display
			cout << "  1   2   3" << endl;
			cout << "a " << rowA[0] << " " << vertical << " " << rowA[1] << " " << vertical << " " << rowA[2] << endl;
			cout << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
			cout << "b " << rowB[0] << " " << vertical << " " << rowB[1] << " " << vertical << " " << rowB[2] << endl;
			cout  << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
			cout << "c " << rowC[0] << " " << vertical << " " << rowC[1] << " " << vertical << " " << rowC[2] << endl << endl;

			cout << "Please enter your selection: ";
			cin >> choice;


			if (choice == "a1" || choice == "1a")
			{
				if (rowA[0] == ' ')
				{
					rowA[0] = player;
					win = tamagotchi::testForWin("a1");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}
			else if (choice == "a2" || choice == "2a")
			{
				if (rowA[1] == ' ')
				{
					rowA[1] = player;
					win = tamagotchi::testForWin("a2");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}
			else if (choice == "a3" || choice == "3a")
			{
				if (rowA[2] == ' ')
				{
					rowA[2] = player;
					win = tamagotchi::testForWin("a3");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}

			else if (choice == "b1" || choice == "1b")
			{
				if (rowB[0] == ' ')
				{
					rowB[0] = player;
					win = tamagotchi::testForWin("b1");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}
			else if (choice == "b2" || choice == "2b")
			{
				if (rowB[1] == ' ')
				{
					rowB[1] = player;
					win = tamagotchi::testForWin("b2");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}
			else if (choice == "b3" || choice == "3b")
			{
				if (rowB[2] == ' ')
				{
					rowB[2] = player;
					win = tamagotchi::testForWin("b3");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}

			else if (choice == "c1" || choice == "1c")
			{
				if (rowC[0] == ' ')
				{
					rowC[0] = player;
					win = tamagotchi::testForWin("c1");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}
			else if (choice == "c2" || choice == "2c")
			{
				if (rowC[1] == ' ')
				{
					rowC[1] = player;
					win = tamagotchi::testForWin("c2");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}
			else if (choice == "c3" || choice == "3c")
			{
				if (rowC[2] == ' ')
				{
					rowC[2] = player;
					win = tamagotchi::testForWin("c3");
				}
				else
				{
					system("cls");
					myCount--;
					cout << "Illegal Entry, Space is occupied." << endl;
					system("pause");
				}
			}
			else
			{
				system("cls");
				cout << "Illegal entry, try again." << endl;
				myCount--;
				system("pause");
			}


			if (win == 1)
			{
				system("cls");
				winner = true;
				tamagotchi::DrawSprite();
				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "You suck, a computer won the game!";
				quoteChoice[1] = "Wow, you need to rethink your life... a computer beat you.";
				quoteChoice[2] = "Tell your friends a computer beat you.";
				quoteChoice[3] = "How do you feel, losing to a computer?";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;
				cout << "  1   2   3" << endl;
				cout << "a " << rowA[0] << " " << vertical << " " << rowA[1] << " " << vertical << " " << rowA[2] << endl;
				cout << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "b " << rowB[0] << " " << vertical << " " << rowB[1] << " " << vertical << " " << rowB[2] << endl;
				cout  << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "c " << rowC[0] << " " << vertical << " " << rowC[1] << " " << vertical << " " << rowC[2] << endl << endl;
				system("pause");
				return;
			}
			else if (win == 2)
			{
				system("cls");
				winner = true;
				tamagotchi::DrawSprite();
				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "Congrats, You won the game!";
				quoteChoice[1] = "GG";
				quoteChoice[2] = "I'm gonna go practice some more.";
				quoteChoice[3] = "Hopefuly I'll do better against you next time.";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;
				cout << "  1   2   3" << endl;
				cout << "a " << rowA[0] << " " << vertical << " " << rowA[1] << " " << vertical << " " << rowA[2] << endl;
				cout << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "b " << rowB[0] << " " << vertical << " " << rowB[1] << " " << vertical << " " << rowB[2] << endl;
				cout  << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "c " << rowC[0] << " " << vertical << " " << rowC[1] << " " << vertical << " " << rowC[2] << endl << endl;
				system("pause");
				return;
			}
			else if (win == 3)
			{
				system("cls");
				winner = true;
				tamagotchi::DrawSprite();
				//specify quotes
				quoteChoice.resize(4);
				quoteChoice[0] = "The game was a tie, better luck next time!";
				quoteChoice[1] = "Hopefuly I'll beat you next time.";
				quoteChoice[2] = "That was a close game, but we tied!";
				quoteChoice[3] = "Even match I see, good job!";

				randomQuote = rand() % 4;

				cout << quoteChoice[randomQuote] << endl;
				cout << "  1   2   3" << endl;
				cout << "a " << rowA[0] << " " << vertical << " " << rowA[1] << " " << vertical << " " << rowA[2] << endl;
				cout << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "b " << rowB[0] << " " << vertical << " " << rowB[1] << " " << vertical << " " << rowB[2] << endl;
				cout  << "  " << horizontal << horizontal << cross << horizontal << horizontal << horizontal << cross << horizontal << horizontal << endl;
				cout << "c " << rowC[0] << " " << vertical << " " << rowC[1] << " " << vertical << " " << rowC[2] << endl << endl;
				system("pause");
				return;
			}
		}
		while (winner == false);
	}
}

int tamagotchi::testForWin(string a)
{
	if (a[0] == 'a')
	{
		if (rowA[0] == rowA[1] && rowA[1] == rowA[2]) //if all in row a are the same
		{
			if (rowA[0] == 'X')
			{
				return (1);
			}
			else if (rowA[0] == 'O')
			{
				return (2);
			}
		}
	}
	else if (a[0] == 'b')
	{
		if (rowB[0] == rowB[1] && rowB[1] == rowB[2]) //if all in row b are the same
		{
			if (rowB[0] == 'X')
			{
				return (1);
			}
			else if (rowB[0] == 'O')
			{
				return (2);
			}
		}
	}
	else if (a[0] == 'c')
	{
		if (rowC[0] == rowC[1] && rowC[1] == rowC[2]) //if all in row b are the same
		{
			if (rowC[0] == 'X')
			{
				return (1);
			}
			else if (rowC[0] == 'O')
			{
				return (2);
			}
		}
	}

	if (a[1] == '1') //test coloums
	{
		if (rowA[0] == rowB[0] && rowB[0] == rowC[0]) //if all in coloum 1 are the same
		{
			if (rowC[0] == 'X')
			{
				return (1);
			}
			else if (rowC[0] == 'O')
			{
				return (2);
			}
		}
	}
	else if (a[1] == '2') //test coloums
	{
		if (rowA[1] == rowB[1] && rowB[1] == rowC[1]) 
		{
			if (rowC[1] == 'X')
			{
				return (1);
			}
			else if (rowC[1] == 'O')
			{
				return (2);
			}
		}
	}
	else if (a[1] == '3') //test coloums
	{
		if (rowA[2] == rowB[2] && rowB[2] == rowC[2]) 
		{
			if (rowC[2] == 'X')
			{
				return (1);
			}
			else if (rowC[2] == 'O')
			{
				return (2);
			}
		}
	}

	if (rowA[0] == rowB[1] && rowB[1] == rowC[2])
	{
		if (rowC[2] == 'X')
		{
			return (1);
		}
		else if (rowC[2] == 'O')
		{
			return (2);
		}
	}
	else if (rowA[2] == rowB[1] && rowB[1] == rowC[0])
	{
		if (rowC[0] == 'X')
		{
			return (1);
		}
		else if (rowC[0] == 'O')
		{
			return (2);
		}
	}

	if (myCount == 9)
	{
		return (3);
	}

	return 0;
}

void tamagotchi::DrawHappinessMeter()
{
	char block = 254;

	cout << "(";

	for (int a = 0; a < happiness; a++)
	{
		cout << block;
	}

	for (int a = 0; a < (4 - happiness); a++)
	{
		cout << " ";
	}

	cout << ")" << endl;
}
void tamagotchi::DrawHungerMeter()
{
	char block = 254;

	cout << "(";

	for (int a = 0; a < hunger; a++)
	{
		cout << block;
	}

	for (int a = 0; a < (4 - hunger); a++)
	{
		cout << " ";
	}

	cout << ")" << endl;
}