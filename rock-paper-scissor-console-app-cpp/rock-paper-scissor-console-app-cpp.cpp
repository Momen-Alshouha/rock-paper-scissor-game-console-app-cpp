// rock-paper-scissor-console-app-cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<windows.h>  
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <conio.h>


using namespace std;

enum enWinner
{
	player = 1, computer, draw
};
enum enChoice
{
	rock=1,paper,scissor
};

struct stGameInfo {
	short roundsNumber=0;
	short playerWonTimes=0;
	short computerWonTimes=0;
	short drawTimes=0;
	enWinner gameWinner;
};

struct stRoundInfo {
	short roundNumber;
	enChoice playerChoice, computerChoice;
	enWinner roundWinner;
};

short randomNumberFromTo() {
	return rand() % (3 - 1+ 1) + 1;
}

short readPostiveNumber(string message) {
	short number;
	cout << message << endl;
	cin >> number;
	if (number<=0)
	{
		cout << "Wrong Entry! Try Again\n";
		 return readPostiveNumber("How Many Rounds:\n");
	}
	return number;
}

short readChoice(string message) {
	short number;
	cout << message << endl;
	cin >> number;
	if (number <= 0 || number>3)
	{
		cout << "Wrong Entry! Try Again\n";
		return readChoice("Enter A Number From 1 - 3");
	}
	return number;
}
void printGameMenu(short roundeNumber) {
	cout << "________________________ Round " << roundeNumber << " Begins ________________________\n";
	cout << "Select Your Choice..\n[1] Rock\n[2] Paper\n[3] scissor\n";
}

enChoice getPlayerChoice() {
	short number = 0;
	cin >> number;
	return (enChoice)number;
}

enChoice getComputerChoice() {
	short number = 0;
	number = randomNumberFromTo();
	return (enChoice)number;
}

enWinner getRoundWinner(stRoundInfo info) {
	if (info.playerChoice == info.computerChoice ) {
		return ::draw;
	}
	else if (info.computerChoice==::rock &&(info.playerChoice == ::paper))
	{
		return ::player;
	}
	else if (info.computerChoice == ::paper && info.playerChoice ==::scissor) {
		return ::player;
	}
	else if (info.computerChoice == ::scissor && info.playerChoice == ::rock) {
		return ::player;
	}
	else {
		return ::computer;
	}
}

enWinner getGameWinner(stGameInfo info) {
	if (info.drawTimes>=ceil(info.roundsNumber/2))
	{
		return ::draw;
	} else if(info.playerWonTimes>info.computerWonTimes){
		return ::computer;
	}
	else {
		return ::player;
	}
}



void printChoice(enChoice choice) {
	switch (choice)
	{
	case rock:
		cout << " rock\n";
		break;
	case paper:
		cout << " paper\n";
		break;
	case scissor:
		cout << " scissor\n";
		break;
	}
}

void printRoundWinner(enWinner winner) {
	switch (winner)
	{
	case player:
		cout << "player!";
		break;
	case computer:
		cout << "Computer!";
		break;
	case draw:
		cout << "Draw!";
		break;
	}
}


void changeScreenColorandRingAbill(enWinner roundWinner) {
	switch (roundWinner)
	{
	case player:
		cout << "\a";
		system("color 20");
		break;
	case computer:
		cout << "\a";
		system("color 40");
		break;
	case draw:
		cout << "\a";
		system("color 60");
		break;
	}

}

void printRoundInfo(stRoundInfo info) {
	changeScreenColorandRingAbill(info.roundWinner);
	cout << "_____________________ Round " << info.roundNumber << " Result _____________________\n";
	if (info.roundWinner==player)
	{
		cout << "You Are Win! :) \n";
	}
	else if (info.roundNumber == computer) {
		cout << "You Are Lost! :(\n";
	}
	else if(info.roundWinner==draw) {
		cout << "Draw!\n";
	}
	cout << "Player Choice :";
	printChoice(info.playerChoice);
	cout << "Computer choice :";
	printChoice(info.computerChoice);
	cout << "Round Winner : ";
	printRoundWinner(info.roundWinner);
	cout << "\n__________________________________________________________\n\n";
}

enWinner getFinalWiner(stGameInfo info) {
	if (info.playerWonTimes == info.computerWonTimes)
	{
		return draw;
	}
	else if(info.playerWonTimes>info.computerWonTimes) {
		return player;
	}
	else {
		return computer;
	}
}

void printFinalWinner(enWinner winner) {
	switch (winner)
	{
	case player:
		cout << " Player!\n";
		break;
	case computer:
		cout << " Computer!\n";
		break;
	case draw:
		cout << " No one!\n";
		break;
	}
}


void printGameInfo(stGameInfo info) {
	cout << "\n\n__________________________ Game Over ! __________________________\n";
	cout << "Game Rounds : " << info.roundsNumber << endl;
	cout << "Computer Wins Time : " << info.computerWonTimes << endl;
	cout << "player Wins Times : " << info.playerWonTimes << endl;
	cout << "Draw Times : " << info.drawTimes << endl;
	cout << "Final Winner:";
	printFinalWinner(info.gameWinner);
	cout << "__________________________ Game Over ! __________________________ \n";
}

void changeGameInfo(stGameInfo &gameInfo,stRoundInfo roundInfo,short rounds) {
	if (roundInfo.roundWinner==player)
	{
		gameInfo.playerWonTimes++;
	}
	else if (roundInfo.roundWinner == computer) {
		gameInfo.computerWonTimes++;
	}
	else if (roundInfo.roundWinner == draw) {
		gameInfo.drawTimes++;
	}
	gameInfo.gameWinner = getFinalWiner(gameInfo);
	gameInfo.roundsNumber = rounds;
}


void startGame() {
	char playMore='y';
	stRoundInfo roundInfo;
	stGameInfo gameInfo;
	roundInfo.roundNumber = 1;
	short roundsNumber;
	short playChoice = 0, compChoice;
	enWinner roundWinner;
	do
	{
		short counter = readPostiveNumber("How Many Rounds Do You Want To Play:");
		gameInfo.roundsNumber = counter;
		do
		{
			printGameMenu(roundInfo.roundNumber);
			playChoice = readChoice("Enter Your Choice:");
			roundInfo.playerChoice = (enChoice)playChoice;
			compChoice = getComputerChoice();
			roundInfo.computerChoice = (enChoice)compChoice;
			roundInfo.roundWinner = getRoundWinner(roundInfo);
			changeGameInfo(gameInfo, roundInfo, gameInfo.roundsNumber);
			printRoundInfo(roundInfo);			
			counter--;
		} while (counter >0);
		cout << "\nPLEASE WAIT To Load Game Final Result !\n";
		Sleep(5000);
		printGameInfo(gameInfo);
		cout << "\nPLEASE WAIT To Continue !\n";
		Sleep(10000);
		system("cls");
		cout << "\nDo Yo Want To Play More (Y,N) ?\n";
		cin >> playMore;


	} while (playMore == 'y' || playMore == 'Y');
}




int main()
{
	srand((unsigned)time(NULL));
	startGame();
}
