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
		cout << "���������� ������� " << i << " �� " << NUM_SHIPS << endl;
		int x, y;
		do {
			cout << "������� ���������� �������(x, y): ";
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

	cout << "����������� �������� ������\n";
	manuallyPlaceShips(playerShips);

	cout << "�������������� ����������� �������� ����������\n";
	randomlyPlaceShips(computerShips);

	cout << "���� ��������!\n";

	while (true)
	{
		cout << "��� ������\n";
		displayBoard(playerBoard);
		int x, y;
		do {
			cout << "������� ���������� ��������(x, y): ";
			cin >> x >> y;
		} while (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE);

		if (isHitShip(computerShips, x, y))
		{
			cout << "�� ������ � ������� ����������!\n";
			playerBoard[x][y] = 'X';
		}
		else
		{
			cout << "������!\n";
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
			cout << "�����������! �� ��������!\n";
			break;
		}
		cout << "��� ����������\n";
		x = rand() % BOARD_SIZE;
		y = rand() % BOARD_SIZE;

		if (isHitShip(playerShips, x, y)) {
			cout << "��������� ����� � ��� �������!\n";
			computerBoard[x][y] = 'X';
			for (Ship& ship : playerShips) {
				if (ship.x == x && ship.y == y) {
					ship.isHit = true;
					break;
				}
			}
		}
		else {
			cout << "��������� �����������!\n";
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
			cout << "��������� �������!\n";
			break;
		}
	}


}