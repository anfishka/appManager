#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 10;
const int NUM_SHIPS = 5;

struct Ship {
	int x;
	int y;
	bool isHit;
};

void displayBoard(vector<vector<char>>& board)
{
	cout << " ";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << i << "";
	}
	cout << endl;

	for(int i = 0; i < BOARD_SIZE; i++)
	{
		cout << i << "";
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cout << board[i][j] << "";
		}
		cout << endl;
	}
}

void manuallyPlaceShips(vector <Ship>& ships)
{
	for (int i = 1; i <= NUM_SHIPS; i++)
	{
		cout << "Расставьте корабль " << i << " из " << NUM_SHIPS << endl;
		int x, y;
		do {
			cout << "Введите координаты корабля(x, y): ";
			cin >> x >> y;
		} while (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE);

		Ship ship;
		ship.x = x;
		ship.y = y;
		ship.isHit = false;
		ships.push_back(ship);
	}
}

void randomlyPlaceShips(vector<Ship>& ships)
{
	srand(time(0));
	for (int i = 0; i <= NUM_SHIPS; i++)
	{
		Ship ship;
		ship.x = rand() % BOARD_SIZE;
		ship.y = rand() % BOARD_SIZE;
		ship.isHit = false;
		ships.push_back(ship);
	}
}

bool isHitShip(vector<Ship>& ships, int x, int y)
{
	for (Ship& ship : ships)
	{
		if (ship.x == x && ship.y == y)
		{
			return true;
		}
	}
	return false;
}

void battleMain()
{
	vector<Ship> playerShips;
	vector<Ship> computerShips;
	vector<vector<char>> playerBoard(BOARD_SIZE, vector<char>(BOARD_SIZE, '~'));
	vector<vector<char>>computerBoard(BOARD_SIZE, vector<char>(BOARD_SIZE, '~'));

	cout << "Расстановка кораблей игрока\n";
	manuallyPlaceShips(playerShips);

	cout << "Автоматическая расстановка кораблей компьютера\n";
	randomlyPlaceShips(computerShips);

	cout << "Игра началась!\n";

	while (true)
	{
		cout << "Ход игрока\n";
		displayBoard(playerBoard);
		int x, y;
		do {
			cout << "Введите координаты выстрела(x, y): ";
			cin >> x >> y;
		} while (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE);

		if (isHitShip(computerShips, x, y))
		{
			cout << "Вы попали в корабль компьютера!\n";
			playerBoard[x][y] = 'X';
		}
		else
		{
			cout << "Промах!\n";
			playerBoard[x][y] = 'O';
		}
		bool playerWon = true;
		for (Ship& ship : computerShips)
		{
			if (!ship.isHit)
			{
				playerWon = false;
				break;
			}
		}
		if (playerWon) {
			cout << "Поздравляем! Вы победили!\n";
			break;
		}
		cout << "Ход компьютера\n";
		x = rand() % BOARD_SIZE;
		y = rand() % BOARD_SIZE;

		if (isHitShip(playerShips, x, y)) {
			cout << "Компьютер попал в ваш корабль!\n";
			computerBoard[x][y] = 'X';
			for (Ship& ship : playerShips) {
				if (ship.x == x && ship.y == y) {
					ship.isHit = true;
					break;
				}
			}
		}
		else {
			cout << "Компьютер промахнулся!\n";
			computerBoard[x][y] = 'O';
		}

		bool computerWon = true;
		for (const Ship& ship : playerShips) {
			if (!ship.isHit) {
				computerWon = false;
				break;
			}
		}
		if (computerWon) {
			cout << "Компьютер победил!\n";
			break;
		}
	}


}