#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 4;

struct Game {
	int board[SIZE][SIZE];
	int emptyCellRow;
	int emptyCellCol;
	int moves;
	time_t startTime;


	void init()
	{
		for (int i = 0; i < SIZE; i++){
			for (int j = 0; j < SIZE; j++){
				board[i][j] = i * SIZE + j + 1;
			}
		}
		board[SIZE - 1][SIZE - 1];
		emptyCellRow = SIZE - 1;
		emptyCellCol = SIZE - 1;
		moves = 0; 
		startTime = time(nullptr);
	}

	void printBoard()
	{
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++)
			{
				if (board[i][j] == 0)
				{
					cout << "  ";
				}
				else {
					cout << board[i][j];
					if (board[i][j] < 10) {
						cout << "  ";
					}
					else {
						cout << "  ";
					}
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	bool checkWin()
	{
		int val = 1;
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (i == SIZE - 1 && j == SIZE - 1)
				{
					if (board[i][j] != 0)
					{
						return false;
					}
				}
				else {
					if (board[i][j] != val)
					{
						return false;
					}
					val++;
				}
			}
		}
		return true;
	}

	void shuffle()
	{
		srand(time(nullptr));
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				int randomRow = rand() % SIZE;
				int randomCol = rand() % SIZE;
				swap(board[i][j], board[randomRow][randomCol]);
				if(board[i][j] == 0){
					emptyCellRow = i;
					emptyCellCol = j;
				}
			}
		}
	}

	void move(int row, int col)
	{
		if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)
		{
			return;
		}

		if ((row == emptyCellRow && abs(col - emptyCellCol) == 1) ||
			(col == emptyCellCol && abs(row - emptyCellRow) == 1)) {
			swap(board[row][col], board[emptyCellRow][emptyCellCol]);
			emptyCellRow = row;
			emptyCellCol = col;
			moves++;

			if (checkWin()) {
				time_t endTime = time(nullptr);
				int elapsedTime = static_cast<int>(endTime - startTime);
				cout << "Поздравляем! Вы выиграли!" << endl;
				cout << "Количество ходов: " << moves << endl;
				cout << "Время: " << elapsedTime << " секунд" << endl;
			}
		}
	}
};
	

void fifteen()
{
	Game game;
	int mode;

	cout << "Выберите режим игры:" << endl;
	cout << "1. Человек собирает" << endl;
	cout << "2. Компьютер собирает" << endl;
	cin >> mode;

	game.init();

	if (mode == 1) {
		game.shuffle();
		cout << "Игра началась! Перемешанные пятнашки:" << endl;
		game.printBoard();

		while (!game.checkWin())
		{
			int row, col;
			cout << "Введите координаты пятнашки для перемещения (строка столбец): ";
			cin >> row >> col;
			game.move(row, col);
			game.printBoard();
		}
	}
	else if (mode == 2)
	{
		cout << "Компьютерный режим пока не реализован." << endl;
	}
	else {
		cout << "Некорректный режим игры." << endl;
	}

}