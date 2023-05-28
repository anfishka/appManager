#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

using namespace std;

const int ROWS = 4;
const int COLS = 4;


const int NUM_VALUES = ROWS * COLS / 2;

struct Card {
    int value;     
    bool isRevealed;  
};

Card board[ROWS][COLS]; 
int flipsCount = 0;    
int matchesCount = 0; 
clock_t startTime;      


void InitializeBoard() {
  
    int totalCards = ROWS * COLS;
    int* values = new int[totalCards];

   
    for (int i = 0; i < totalCards; i++) {
        values[i] = i % NUM_VALUES;
    }

  
    for (int i = 0; i < totalCards; i++) {
        int randomIndex = rand() % totalCards;
        swap(values[i], values[randomIndex]);
    }

    int cardIndex = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j].value = values[cardIndex];
            board[i][j].isRevealed = false;
            cardIndex++;
        }
    }

    delete[] values;
}

void DrawBoard() {
    system("cls");  

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].isRevealed) {
                cout << board[i][j].value << " ";
            }
            else {
                cout << "* ";
            }
        }
       cout << endl;
    }
}


void PlaySound(bool match) {
    if (match) {
      
        Beep(900, 200);
    }
    else {
     
        Beep(500, 200);
    }
}


bool IsGameOver() {
    return matchesCount == NUM_VALUES;
}


void ProcessTurn() {
    int row1, col1, row2, col2;


    cout << "Enter the coordinates of the first card (row column): ";
    cin >> row1 >> col1;

   
    while (row1 < 1 || row1 > ROWS || col1 < 1 || col1 > COLS || board[row1 - 1][col1 - 1].isRevealed) {
        cout << "Invalid input! Enter the coordinates again: ";
        cin >> row1 >> col1;
    }

   
    board[row1 - 1][col1 - 1].isRevealed = true;
    flipsCount++;
    DrawBoard();


    cout << "Enter the coordinates of the second card (row column): ";
    cin >> row2 >> col2;

  
    while (row2 < 1 || row2 > ROWS || col2 < 1 || col2 > COLS || board[row2 - 1][col2 - 1].isRevealed) {
        cout << "Invalid input! Enter the coordinates again: ";
        cin >> row2 >> col2;
    }


    board[row2 - 1][col2 - 1].isRevealed = true;
    flipsCount++;
    DrawBoard();

  
    if (board[row1 - 1][col1 - 1].value == board[row2 - 1][col2 - 1].value) {
        matchesCount++;
        PlaySound(true);
    }
    else {
       
        Sleep(1000);
        board[row1 - 1][col1 - 1].isRevealed = false;
        board[row2 - 1][col2 - 1].isRevealed = false;
        PlaySound(false);
    }
}


void DisplayStats() {
    clock_t endTime = clock();
    double gameTime = (endTime - startTime) / static_cast<double>(CLOCKS_PER_SEC);

    cout << "\nGame Over!\n";
    cout << "Total flips: " << flipsCount << endl;
    cout << "Total time: " << gameTime << " seconds" << endl;
}

void memory()
{
    srand(static_cast<unsigned int>(time(nullptr)));  
    InitializeBoard();
    DrawBoard();
    startTime = clock();


    while (!IsGameOver()) {
        ProcessTurn();
    }

    DisplayStats();
}