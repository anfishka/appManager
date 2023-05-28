#include <iostream>
#include <vector>
#include "battleship.h"
#include "fifteen.h"
#include "todo.h"
using namespace std;

struct APP {
	string name;
	string description;
	void (*functionPointer)();
};

void displayMenu(APP apps[], int size)
{
	cout << "\n����: \n\n";

	for (int i = 0; i < 10; i++)

	{
		cout << "\x1b[31m" << i + 1 << ". " << apps[i].name << "\033[m\n";

	}
	cout << "\n0.�����\n";
}

void menuApps()
{
	setlocale(LC_ALL, "");
	const int appNums = 10;

	APP apps[appNums] = {
		{"������� ���", "������� ����������, ���� ������� ���", *battleship},
		{"��������", "������� ����������, ���� ��������", *fifteen},
		{"������ ���", "���, ���������� ������� ���", *todo},
		{"������", "������� ����������, ���� ������"},
		{"�����������", "�������, ������� �����������"},
		{"������� ��������� �����", "���, ���������� ��������� ��������� �����"},
		{"����������� �������� �������", "�������, ����������� �������� �������"},
		{"�����", "���, ���������� �������"},
		{"���������","���, ���������� �����������"},
		{"�������� ����������", "���, ���������� �������� ������������"}
	};
	int choice;

	do {
		displayMenu(apps, appNums);
		cout << "\n\x1b[36m������� ����� ����������: ";
		cin >> choice;
		if (choice >= 1 && choice <= appNums)
		{
			cout << "\n�� �������: \x1b[32m" << apps[choice - 1].name << ": " << apps[choice - 1].description << "\033[m\n" ;
			apps[choice - 1].functionPointer();
		}
		else if (choice != 0)
		{
			cout << "\n\x1b[31m�������� ���� ������ ����������! ���������� �����: \033[m\n";
		}

	} while (choice != 0);

	cout << "\n����� �� ���������\n";
}