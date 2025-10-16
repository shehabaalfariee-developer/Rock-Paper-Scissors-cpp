#include <iostream>
#include <string>
using namespace std;

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

struct strGameResults {
    short GameRounds;
    short Player1WinCount;
    short ComputerWinCount;
    short DrawCount;
    enWinner Winner;
    string WinnerName;
};

struct strRoundInfo {
    short RoundNumber;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

string Tabs(int count) {
    string t = "";
    for (int i = 0; i < count; i++)
        t += "\t";
    return t;
}

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

enGameChoice ReadPlayerChoice() {
    short choice;
    do {
        cout << "\nYour Choice: [1] Stone, [2] Paper, [3] Scissors ? ";
        cin >> choice;
    } while (choice < 1 || choice > 3);
    return (enGameChoice)choice;
}

enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWinsTheRound(strRoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice) {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }
    return enWinner::Draw;
}

enWinner WhoWinsTheGame(int PlayerWins, int ComputerWins) {
    if (PlayerWins > ComputerWins)
        return enWinner::Player1;
    else if (ComputerWins > PlayerWins)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string GetWinnerName(enWinner Winner) {
    switch (Winner) {
    case enWinner::Player1: return "Player";
    case enWinner::Computer: return "Computer";
    default: return "No Winner";
    }
}

string GetChoiceName(enGameChoice Choice) {
    switch (Choice) {
    case enGameChoice::Stone: return "Stone";
    case enGameChoice::Paper: return "Paper";
    case enGameChoice::Scissors: return "Scissors";
    default: return "Unknown";
    }
}

void PrintRoundResult(strRoundInfo RoundInfo) {
    cout << "\n--------- Round [" << RoundInfo.RoundNumber << "] ----------\n";
    cout << "Player Choice  : " << GetChoiceName(RoundInfo.Player1Choice) << "\n";
    cout << "Computer Choice: " << GetChoiceName(RoundInfo.ComputerChoice) << "\n";
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "----------------------------------------\n";
}

strGameResults FillGameResult(int TotalRounds, int PlayerWins, int ComputerWins, int Draws) {
    strGameResults GameResults;
    GameResults.GameRounds = TotalRounds;
    GameResults.Player1WinCount = PlayerWins;
    GameResults.ComputerWinCount = ComputerWins;
    GameResults.DrawCount = Draws;
    GameResults.Winner = WhoWinsTheGame(PlayerWins, ComputerWins);
    GameResults.WinnerName = GetWinnerName(GameResults.Winner);
    return GameResults;
}

strGameResults PlayGame(int RoundsCount) {
    strRoundInfo RoundInfo;
    short PlayerWins = 0, ComputerWins = 0, Draws = 0;

    for (int Round = 1; Round <= RoundsCount; Round++) {
        cout << "\nRound [" << Round << "] begins:";
        RoundInfo.RoundNumber = Round;
        RoundInfo.Player1Choice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWinsTheRound(RoundInfo);
        RoundInfo.WinnerName = GetWinnerName(RoundInfo.Winner);

        PrintRoundResult(RoundInfo);

        if (RoundInfo.Winner == enWinner::Player1) {
            PlayerWins++;
            system("color 2F");
        }
        else if (RoundInfo.Winner == enWinner::Computer) {
            ComputerWins++;
            cout << "\a";
            system("color 4F");
        }
        else {
            Draws++;
            system("color 6F");
        }
    }

    return FillGameResult(RoundsCount, PlayerWins, ComputerWins, Draws);
}

void ShowGameResults(strGameResults GameResults) {
    cout << Tabs(2) << "--------------------- [ Game Results ] ----------------------\n";
    cout << Tabs(2) << "Game Rounds       : " << GameResults.GameRounds << "\n";
    cout << Tabs(2) << "Player Wins       : " << GameResults.Player1WinCount << "\n";
    cout << Tabs(2) << "Computer Wins     : " << GameResults.ComputerWinCount << "\n";
    cout << Tabs(2) << "Draws             : " << GameResults.DrawCount << "\n";
    cout << Tabs(2) << "Final Winner      : " << GameResults.WinnerName << "\n";
    cout << Tabs(2) << "-------------------------------------------------------------\n";
}

void PrintGameOver() {
    cout << Tabs(2) << "-----------------------------------------------------------\n";
    cout << Tabs(2) << "              +++  G A M E   O V E R  +++\n";
    cout << Tabs(2) << "-----------------------------------------------------------\n";
}

int HowManyRounds() {
    int Rounds;
    do {
        cout << "How many rounds (1 to 10)? ";
        cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);
    return Rounds;
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        strGameResults GameResults = PlayGame(HowManyRounds());
        PrintGameOver();
        ShowGameResults(GameResults);
        cout << Tabs(2) << "Do you want to play again? [Y/N]: ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main() {
    
    srand((unsigned)time(NULL));
    
    StartGame();
    
    return 0;
}

