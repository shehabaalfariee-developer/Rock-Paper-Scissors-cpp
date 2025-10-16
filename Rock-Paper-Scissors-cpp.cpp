#include<iostream>
#include<string>
using namespace std;

eenum enWinner{ Player1 = 1, Computer = 2, Draw = 3 };

enum enGameChoise { Stone = 1, Paper = 2, Scissors = 3 };

struct strGameResults {
	short GameRounds;
	short Player1WonTime;
	short ComputerWonTime;
	short DrawTime;
	enWinner Winner;
	string WinnerName;
};

struct strRoundInfo {
	short RoundsNumber;
	short Player1Choise;
	short ComputerChoise;
	enWinner Winner;
	string WinnerName;
};

string Tabs(int tab) {
	string t = " ";
	for (int i = 1; i <= tab; i++)
		t += "\t";
	return t;
}

enGameChoise ReadPlayerChoise() {
	short chois;
	do {
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> chois;
	} while (chois < 1 || chois > 3);
	return (enGameChoise)chois;
}

int RandomNumber(int From, int To) {

	return rand() % (To - From + 1) + From;
}

enGameChoise GetComputerChoise() {

	return (enGameChoise)RandomNumber(1, 3);
}

enWinner WoWinTheRound(strRoundInfo RoundInfo) {

	if (RoundInfo.Player1Choise == RoundInfo.ComputerChoise)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choise)
	{
	case enGameChoise::Stone:
	{
		if (RoundInfo.ComputerChoise == enGameChoise::Paper)
			return enWinner::Computer;
		break;
	}
	case enGameChoise::Paper:
	{
		if (RoundInfo.ComputerChoise == enGameChoise::Scissors)
			return enWinner::Computer;
		break;
	}
	case enGameChoise::Scissors:
	{
		if (RoundInfo.ComputerChoise == enGameChoise::Stone)
			return enWinner::Computer;
		break;
	}
	}
	return enWinner::Player1;
}

enWinner WoWinTheGame(int PlayerChoiseTime, int ComputerChoiseTime) {

	if (PlayerChoiseTime > ComputerChoiseTime)
		return enWinner::Player1;
	else if (ComputerChoiseTime > PlayerChoiseTime)
		return enWinner::Computer;
	else
		enWinner::Draw;
}

string GetWinnerName(int Winner) {
	string arrWinnerName[3] = { "Player", "Computer", "No Winner" };
	return arrWinnerName[Winner - 1];
}

string GetChoiseName(int Winner) {
	string arrChoiseName[3] = { "Stone", "Paper", "Scissors" };
	return arrChoiseName[Winner - 1];
}

void PrintRoundResult(strRoundInfo RoundInfo) {

	cout << "\n---------Round [" << RoundInfo.RoundsNumber << "] ----------\n";

	cout << "Player1 Choise  : " << GetChoiseName(RoundInfo.Player1Choise) << "\n";
	cout << "Computer Choise : " << GetChoiseName(RoundInfo.ComputerChoise) << "\n";
	cout << "Round Winner    : [" << RoundInfo.WinnerName << "]\n";

	cout << "\n----------------------------------------\n";
}

strGameResults FillGameResult(int RoundNumber, int PlayerChoiseTime, int ComputerChoiseTime, int DrawTime) {
	strGameResults GameResults;

	GameResults.GameRounds = RoundNumber;
	GameResults.Player1WonTime = PlayerChoiseTime;
	GameResults.ComputerWonTime = ComputerChoiseTime;
	GameResults.DrawTime = DrawTime;
	GameResults.Winner = WoWinTheGame(PlayerChoiseTime, ComputerChoiseTime);
	GameResults.WinnerName = GetWinnerName(GameResults.Winner);

	return GameResults;

}

strGameResults PlayGame(int HowManyRound) {
	strRoundInfo RoundInfo;
	short PlayerChoiseTime = 0, ComputerChoiseTime = 0, DrawTime = 0;
	for (int GameRound = 1; GameRound <= HowManyRound; GameRound++) {
		cout << "\nRound [" << GameRound << "] begines :";
		RoundInfo.RoundsNumber = GameRound;
		RoundInfo.Player1Choise = ReadPlayerChoise();
		RoundInfo.ComputerChoise = GetComputerChoise();
		RoundInfo.Winner = WoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = GetWinnerName(RoundInfo.Winner);

		PrintRoundResult(RoundInfo);

		if (RoundInfo.Winner == enWinner::Player1) {
			PlayerChoiseTime++;
			system("color 2F");
		}
		else if (RoundInfo.Winner == enWinner::Computer) {
			cout << "\a";
			ComputerChoiseTime++;
			system("color 4F");
		}
		else {
			DrawTime++;
			system("color 6F");
		}
	}

	return FillGameResult(HowManyRound, PlayerChoiseTime, ComputerChoiseTime, DrawTime);
}

void ShowGameResults(strGameResults GameResults) {

	cout << Tabs(4) << "--------------------- [ Game Results] ----------------------\n";

	cout << Tabs(4) << "Game Rounds         : " << GameResults.GameRounds << "\n";
	cout << Tabs(4) << "Player1 won times   : " << GameResults.Player1WonTime << "\n";
	cout << Tabs(4) << "Computer won times  : " << GameResults.ComputerWonTime << "\n";
	cout << Tabs(4) << "Draw times          : " << GameResults.DrawTime << "\n";
	cout << Tabs(4) << "Final Winner        : " << GameResults.WinnerName << "\n";

	cout << Tabs(4) << "-------------------------------------------------------------\n";

}

void PrintGameOver() {
	cout << Tabs(4) << "-----------------------------------------------------------\n";
	cout << Tabs(4) << "            +++ G a m e O v e r +++" << Tabs(1) << "\n";
	cout << Tabs(4) << "-----------------------------------------------------------\n";
}

int HowManyRounds() {
	int Rounds = 1;
	do {
		cout << "How Many Rounds Want To Play 1 To 10 ? ";
		cin >> Rounds;
	} while (Rounds < 1 || Rounds > 10);
	return Rounds;
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void StartGame() {
	char TrayAgaine = 'Y';

	do {
		ResetScreen();
		strGameResults GameResults = PlayGame(HowManyRounds());
		PrintGameOver();
		ShowGameResults(GameResults);
		cout << Tabs(4) << "Do You Want To Play Againe? Y/N : ";
		cin >> TrayAgaine;

	} while (TrayAgaine == 'Y' || TrayAgaine == 'y');
}


int main()
{
	srand((unsigned)time(NULL));
	StartGame();




	return 0;
}
