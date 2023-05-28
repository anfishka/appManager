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
	cout << "\nМеню: \n\n";

	for (int i = 0; i < 10; i++)

	{
		cout << "\x1b[31m" << i + 1 << ". " << apps[i].name << "\033[m\n";

	}
	cout << "\n0.Выход\n";
}

void menuApps()
{
	setlocale(LC_ALL, "");
	const int appNums = 10;

	APP apps[appNums] = {
		{"МОРСКОЙ БОЙ", "Игровое приложение, игра морской бой", *battleship},
		{"ПЯТНАШКИ", "Игровое приложение, игра пятнашки", *fifteen},
		{"СПИСОК ДЕЛ", "СРМ, управление списком дел", *todo},
		{"ПАМЯТЬ", "Игровое приложение, игра память"},
		{"КАЛЬКУЛЯТОР", "Утилита, простой калькулятор"},
		{"КАТАЛОГ ТЕКСТОВЫХ ПЕСЕН", "СРМ, управление каталогом текстовых песен"},
		{"ОТОБРАЖЕНИЕ ФАЙЛОВОЙ СИСТЕМЫ", "Утилита, отображение файловой системы"},
		{"СКЛАД", "СРМ, управление складом"},
		{"АВТОСАЛОН","СРМ, управление автосалоном"},
		{"ДОМАШНИЙ МЕНЕДЖМЕНТ", "СРМ, управление домашним менеджментом"}
	};
	int choice;

	do {
		displayMenu(apps, appNums);
		cout << "\n\x1b[36mВведите номер приложения: ";
		cin >> choice;
		if (choice >= 1 && choice <= appNums)
		{
			cout << "\nВы выбрали: \x1b[32m" << apps[choice - 1].name << ": " << apps[choice - 1].description << "\033[m\n" ;
			apps[choice - 1].functionPointer();
		}
		else if (choice != 0)
		{
			cout << "\n\x1b[31mНеверный ввод номера приложения! Попробуйте снова: \033[m\n";
		}

	} while (choice != 0);

	cout << "\nВыход из программы\n";
}