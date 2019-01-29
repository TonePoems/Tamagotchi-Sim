/*
Program: Tamagotchi_Game.cpp
Programmer: Anthony Mitchell
7/27/16

Play Testers

This program is an attempt at creating a 
saving system for a game. It will use file
io to write and read the save 
states from the files.
*/

//include files
#include <iostream>
#include <string>
#include <fstream>
#include "Tamagotchi.h"

using namespace std;

//declare functions
void PrintTamagotchiBanner();

int main()
{
	//declare variables
	int start; //what the user chooses to do at the beginning of the program
	string filename;; //what the name of the file to be used is
	string file;

	//declare Tamagotchi object
	tamagotchi tamagotchi;

	string tamagotchiName;
	int points;
	int hunger;
	int happiness;
	bool sick;
	int spriteNum;

	int choice = 0;

	bool keepPlaying = 1;

	int rNumHunger, rNumHappiness, rNumSick; //random number generator
	srand(time(NULL));

	int numOfSnacks = 0;
	int numOfGames = 0;

	//file io declarations
	ifstream infile; 
	ofstream outfile; 

	//start menu
	do
	{
		do //user validate
		{
			PrintTamagotchiBanner();

			cout << " 1: Start a new game	 	 5: Quit game	   	 0: Load a saved game" << endl;
			cout << "Please enter your selection: ";
			cin >> start;

			if (start != 0 && start != 1 && start != 5) //user validate
			{
				cout << "Error: Please enter a valid answer of 1, 5, or 0." << endl;
				system("pause&cls");
			}
		}
		while (start != 0 && start != 1 && start != 5); //user validate
		system("cls");

		if (start == 5)
		{
			break;
		}

		switch (start) //switch case for handling the user choice
		{
		case 1: //if they choose to start a new game
			cout << "Reminder: Do not add \".txt\" to the file name and no spaces are allowed." << endl;
			cout << "Please enter the name you would like to use for your save file: ";
			cin >> file;

			system("cls"); //clear screen

			filename = file + ".txt"; //set the fie name to the file to be used

			//set up the player's tamagotchi
			cout << "Please enter the name of your new Tamagotchi: ";
			cin >> tamagotchiName;
			tamagotchi.SetName(tamagotchiName); //sets the name of the player's tamagotchi
			system("cls");

			//player sprite selection
			do //user validate
			{
				for (int s = 1; s <= 5; s++) //print out all sprite options
				{
					tamagotchi.SetSprite(s);
					tamagotchi.DrawSprite();

					cout << setw(41) << s << endl << endl;
				}

				cout << "Please enter the number of the sprite you would like to use: ";
				cin >> spriteNum;

				if (spriteNum < 1 || spriteNum > 5)
				{
					cout << "Error: Please enter a number from 1 to 5." << endl;
					system("pause&cls");
				}

			}
			while (spriteNum < 1 || spriteNum > 5); //end user validate

			tamagotchi.SetSprite(spriteNum);
			system("cls");
			break; //tamagotchi is now set up and game can begin

		case 0: //if they choose to use a saved game 
			//file io declarations
			ifstream infile; 
			ofstream outfile; 

			cout << "Reminder: Do not add \".txt\" to the file name." << endl;
			cout << "Please enter the name of your save file: ";
			cin >> file;

			system("cls"); //clear screen

			filename = file + ".txt"; //set the fie name to the file to be used

			infile.open(filename,ios::in); //open file for input

			if ((!infile)) //if file error print message and end program
			{
				cout << "Error opening file, most likely the result of the wrong file name being entered." << endl;
				cout << "Program ending to protect files." << endl;
				system("pause");
				//close file io
				infile.close();
				outfile.close();
				return 0;
			}

			//read in the stats from the file
			infile >> tamagotchiName;
			tamagotchi.SetName(tamagotchiName);

			infile >> points;
			tamagotchi.SetPoints(points);

			infile >> hunger;
			tamagotchi.SetHunger(hunger);

			infile >> happiness;
			tamagotchi.SetHappiness(happiness);

			infile >> sick;
			tamagotchi.SetSick(sick);

			infile >> spriteNum;
			tamagotchi.SetSprite(spriteNum);
			break;
		}

		//random game generator works
		/*
		for (int a = 0; a <= 20; a++)
		{
			tamagotchi.PlayMiniGame();
			cout << "Play again" << endl;
			system("pause");
		}
		*/

		//start Tamagotchi gameplay ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		do
		{
			system("cls"); //clear screen every turn

			//check if lost hunger or happiness or became sick
			rNumHunger = rand() % 5; //40% chance to lose hunger
			if (rNumHunger == 1 || rNumHunger == 2)
			{
				tamagotchi.SetHunger(tamagotchi.GetHunger() - 1);
			}

			rNumHappiness = rand() % 2; //40% chance to lose happiness
			if (rNumHappiness == 1 || rNumHappiness == 2)
			{
				tamagotchi.SetHappiness(tamagotchi.GetHappiness() - 1);
			}

			rNumSick = rand() % 5; //20% chance to become sick
			if (rNumSick == 1)
			{
				tamagotchi.SetSick(1);
			}

			//if hunger or happiness is 4, get 2 points
			if (tamagotchi.GetHunger() == 4)
			{
				if (tamagotchi.GetSick() == false)
				{
					tamagotchi.SetPoints(tamagotchi.GetPoints() + 2); //add points
				}
			}
			if (tamagotchi.GetHappiness() == 4)
			{
				if (tamagotchi.GetSick() == false)
				{
					tamagotchi.SetPoints(tamagotchi.GetPoints() + 2); //add points
				}
			}

			do //user validate the menu
			{
				//format the menu
				tamagotchi.DrawSprite();

				cout << "Points: " << tamagotchi.GetPoints() << endl;
				cout << "Fullness:  "; //hunger bar
				tamagotchi.DrawHungerMeter();
				cout << "Happiness: "; //happiness bar
				tamagotchi.DrawHappinessMeter();

				if (tamagotchi.GetSick() == 1) //if sick
				{
					cout << "Your Tamagotchi, " << tamagotchi.GetName() << ", is sick." << endl << endl;
				}
				else
				{
					cout << "Your Tamagotchi, " << tamagotchi.GetName() << ", is healthy." << endl << endl;
				}

				//gaining a point
				if (tamagotchi.GetHunger() == 4) //if tamagotchi is completely full
				{
					cout << tamagotchi.GetName() << " is completely full, awesome job!" << endl;
				}
				else if (choice == 1)
				{
					cout << tamagotchi.GetName() << " gained a fullness point." << endl;
				}
				if (tamagotchi.GetHappiness() == 4) //if tamagotchi is completely happy
				{
					cout << tamagotchi.GetName() << " is completely happy, awesome job!" << endl;
				}
				else if (choice == 2 || choice == 3)
				{
					cout << tamagotchi.GetName() << " gained a happiness point." << endl;
				}

				if (tamagotchi.GetHunger() == 4 || choice == 1 || tamagotchi.GetHappiness() == 4 || choice == 2 || choice == 3)
				{
					cout << endl;	
				}


				//losing points
				if (tamagotchi.GetHunger() == 0) //if tamagotchi is completely hungry
				{
					cout << tamagotchi.GetName() << " is completely starving, perhaps you should feed it a meal." << endl;
					tamagotchi.SetSick(1);
				}
				else if (rNumHunger == 1) //if lost hunger
				{
					cout << tamagotchi.GetName() << " lost a fullness point." << endl;
				}

				if (tamagotchi.GetHappiness() == 0) //if tamagotchi is completely unhappy
				{
					cout << tamagotchi.GetName() << " is completely unhappy, perhaps you should play a game." << endl;
					tamagotchi.SetSick(1);
				}
				else if (rNumHappiness == 1) //if lost happiness
				{
					cout << tamagotchi.GetName() << " lost a happiness point." << endl;
				}

				if (tamagotchi.GetHunger() == 0 || rNumHunger == 1 || tamagotchi.GetHappiness() == 0 || rNumHappiness == 1)
				{
					cout << endl;
				}

				//print choice menu
				cout << "1: Feed your Tamagotchi a meal.		4. Give your Tamagotchi medicine." << endl;
				cout << "2: Feed your Tamagotchi a snack.	5. Read instructions." << endl;
				cout << "3: Play a game with your Tamagotchi.	6. Save and return to start." << endl << endl;

				cout << "Please enter your selection: ";
				cin >> choice;

				switch (choice)
				{
				case 1: //feed a meal
					if (tamagotchi.GetHunger() == 4) //if fed a meal while full, pet become sick
					{
						tamagotchi.SetSick(1);
					}
					tamagotchi.SetHunger(tamagotchi.GetHunger() + 1);
					break;
				case 2: //feed a snack
					numOfSnacks++;
					if (numOfSnacks == 5) //every 5 snacks make pet sick
					{
						numOfSnacks = 0;
						tamagotchi.SetSick(1);
					}
					tamagotchi.SetHappiness(tamagotchi.GetHappiness() + 1);
					break;
				case 3: //play a game
					tamagotchi.SetHappiness(tamagotchi.GetHappiness() + 1);

					numOfGames++;
					if (numOfGames == 3) //every 3 games
					{
						numOfGames = 0; //set back to 0
						if (tamagotchi.GetSick() == false)
						{
							tamagotchi.SetPoints(tamagotchi.GetPoints() + 1); //add one point
						}
					}

					tamagotchi.PlayMiniGame();
					break;
				case 4:
					if (tamagotchi.GetSick() == 0)
					{
						cout << "You can not give " << tamagotchi.GetName() << " medicine while not sick." << endl; 
						system("pause");
					}
					tamagotchi.SetSick(0);

					//if hunger or happiness is 4, get 2 points
					if (tamagotchi.GetHunger() == 4)
					{
						if (tamagotchi.GetSick() == false)
						{
							tamagotchi.SetPoints(tamagotchi.GetPoints() + 2); //add points
						}
					}
					if (tamagotchi.GetHappiness() == 4)
					{
						if (tamagotchi.GetSick() == false)
						{
							tamagotchi.SetPoints(tamagotchi.GetPoints() + 2); //add points
						}
					}
					system("cls");
					break;
				case 5:
					system("cls");
					//print instructions                                                                    " << endl;
					cout << "The goal of this game is to get a high score. This is accomplished in     " << endl;
					cout << "several ways:                                                                  " << endl;
					cout << "1: Gain 2 points by getting 4 bars of fullness                                 " << endl;
					cout << "2: Gain 2 points by getting 4 bars of happiness                                " << endl;
					cout << "3: Gain 1 point by playing 3 games                                             " << endl;
					cout << "You will not be able to gain points if your Tamagotchi is sick that turn.      " << endl << endl;
					cout << "Each round, your Tamagotchi has a 40% chance to lose fullness or happiness, as " << endl;
					cout << "well as a 20% chance to become sick.                                           " << endl << endl;
					cout << "To increase your Tamagotchi's fullness, you must feed it a meal. To increase   " << endl;
					cout << "it's happiness meter, you can feed it a snack or play a game with it.          " << endl;
					cout << "Be mindful of your choices, if you feed your Tamagotchi a meal while full, it  " << endl;
					cout << "will become sick, and after every 5 snacks you feed it, the Tamagotchi will    " << endl;
					cout << "become sick.                                                                   " << endl << endl;


					system("pause&cls");
					break;
				case 6:
					keepPlaying = 0;
					break;
				default: //user validate
					cout << "Error: Invalid input. Please enter a number 1 - 6." << endl;
					system("pause&cls");
					break;
				}
			}
			while(choice > 6 || choice < 1 || choice == 5 || choice == 4 && tamagotchi.GetSick() == 0);

		}
		while(keepPlaying);

		//end Tamagotchi gameplay ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//export info to file 
		outfile.open(filename,ios::out);

		outfile << tamagotchi.GetName() << endl;

		outfile << tamagotchi.GetPoints() << endl;

		outfile << tamagotchi.GetHunger() << endl;

		outfile << tamagotchi.GetHappiness() << endl;

		outfile << tamagotchi.GetSick() << endl;

		outfile << tamagotchi.GetSprite() << endl;


		system("cls");
		tamagotchi.DrawSprite();
		cout << "Remember to use filename \"" << file << "\" to pick up where you left off!" << endl;
		system("pause&cls");

	}
	while (start != 5);

	PrintTamagotchiBanner();

	cout << "Thank you for playing this Tamagotchi game by Anthony Mitchell." << endl;

	//close file io
	infile.close();
	outfile.close();

	system("pause");
	return 0;
}

void PrintTamagotchiBanner()
{
	cout << endl;

	cout << "     ___________                                     __         .__    .__ " << endl;
	cout << "     \\__    ___/____    _____ _____     ____   _____/  |_  ____ |  |__ |__|" << endl;
	cout << "       |    |  \\__  \\  /     \\\\__  \\   / ___\\ /  _ \\   __\\/ ___\\|  |  \\|  |" << endl;
	cout << "       |    |   / __ \\|  Y Y  \\/ __ \\_/ /_/  >  <_> )  | \\  \\___|   Y  \\  |" << endl;
	cout << "       |____|  (____  /__|_|  (____  /\\___  / \\____/|__|  \\___  >___|  /__|" << endl;
	cout << "                    \\/      \\/     \\//_____/                  \\/     \\/    " << endl;

	cout << endl;

	cout << "                      _____ _           _     _             " << endl;
	cout << "                     |   __|_|_____ _ _| |___| |_ ___ ___   " << endl;
	cout << "                     |__   | |     | | | | .'|  _| . |  _|  " << endl;
	cout << "                     |_____|_|_|_|_|___|_|__,|_| |___|_|    " << endl;

	cout << endl << endl;
}