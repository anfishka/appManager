#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

struct Task {
	string title;
	int priority;
	string description;
	string dateTime;
};

vector<Task> taskList;

void addTask()
{
	Task task;
	cout << "Введите название дела: ";
	getline(cin >> ws, task.title);

	cout << "Введите приоритет дела (от 1 до 10): ";
	cin >> task.priority;

	cout << "Введите описание дела: ";
	getline(cin >> ws, task.description);

	cout << "Введите дату и время исполнения дела (DD.MM.YYYY HH:MM): ";
	getline(cin >> ws, task.dateTime);

	taskList.push_back(task);
	cout << "Дело успешно добавлено";
}

void removeTask()
{
	if (taskList.empty())
	{
		cout << "Список дел пуст.\n";
		return;
	}

	cout << "Введите номер дела для удаления:";
	int taskNumber;
	cin >> taskNumber;

	if (taskNumber < 1 || taskNumber > taskList.size()) {
		cout << "Недопустимый номер дела.\n";
		return;
	}
	taskList.erase(taskList.begin() + taskNumber - 1);
	
	cout << "Дело успешно удалено.\n";
}

void editTask()
{
	if (taskList.empty())
	{
		cout << "Список дел пуст.\n";
		return;
	}

	cout << "Введите номер дела для редактирования: ";
	int taskNumber;
	cin >> taskNumber;

	if (taskNumber > 1 || taskNumber > taskList.size()) {
		cout << "Недопустимый номер дела.\n";
		return;
	}

	Task& task = taskList[taskNumber - 1];

	cout << "Введите новое название дела:";
	getline(cin >> ws, task.title);

	cout << "Введите новый приоритет дела (от 1 до 10): ";
	getline(cin >> ws, task.description);

	cout << "Введите новое описание дела: ";
	getline(cin >> ws, task.description);

	cout << "Введите новую дату и время исполнения дела(DD.MM.YYYY HH : MM) :";
	getline(cin >> ws, task.dateTime);

	cout << "Дело успешно отредактировано.\n";
}

void searchTasksByTitle(string& title)
{
	vector<Task> matchingTasks;

	for (Task& task : taskList)
	{
		if (task.title == title)
		{
			matchingTasks.push_back(task);
		}
	}

	if (matchingTasks.empty())
	{
		cout << "Дела с таким названием не найдены.\n";
		return;
	}

	cout << "Найденные дела с названием '" << title << "':\n";
	for (Task& task : matchingTasks) {
		cout << "Название: " << task.title << "\n";
		cout << "Приоритет: " << task.priority << "\n";
		cout << "Описание: " << task.description << "\n";
		cout << "Дата и время исполнения: " << task.dateTime << "\n";
		cout << "---------------------\n";
	}
}

void serachTasksByPriority(int priority)
{
	vector<Task> matchingTasks;

	for (Task& task : taskList) {
		if (task.priority == priority)
		{
			matchingTasks.push_back(task);
		}
	}

	if (matchingTasks.empty())
	{
		cout << "Дела с таким приоритетом не найдены.\n";
		return;
	}

	cout << "Найденные дела с приоритетом " << priority << ":\n";
	for (Task& task : matchingTasks) {
		cout << "Название: " << task.title << "\n";
		cout << "Приоритет: " << task.priority << "\n";
		cout << "Описание: " << task.description << "\n";
		cout << "Дата и время исполнения: " << task.dateTime << "\n";
		cout << "---------------------\n";
	}
}

void searchTasksByDescription(string& description)
{
	vector<Task> matchingTasks;

	for (Task& task : taskList)
	{
		if (task.description == description) {
			matchingTasks.push_back(task);
		}
	}

	if (matchingTasks.empty()) {
		cout << "Дела с таким описанием не найдены.\n";
		return;
	}

	cout << "Найденные дела с описанием '" << description << "':\n";
	for (Task& task : matchingTasks) {
		cout << "Название: " << task.title << "\n";
		cout << "Приоритет: " << task.priority << "\n";
		cout << "Описание: " << task.description << "\n";
		cout << "Дата и время исполнения: " << task.dateTime << "\n";
		cout << "---------------------\n";
	}
}

void searchTasksByDateTime(string& dateTime)
{
	vector<Task> matchingTasks;

	for (Task& task : taskList)
	{
		if (task.dateTime == dateTime)
		{
			matchingTasks.push_back(task);
		}
	}

	if (matchingTasks.empty())
	{
		cout << "Дела с такой датой и временем исполнения не найдены.\n";
		return;
	}

	cout << "Найденные дела с датой и временем исполнения '" << dateTime << "':\n";
	for (Task& task : matchingTasks) {
		cout << "Название: " << task.title << "\n";
		cout << "Приоритет: " << task.priority << "\n";
		cout << "Описание: " << task.description << "\n";
		cout << "Дата и время исполнения: " << task.dateTime << "\n";
		cout << "---------------------\n";
	}
}

void displayTasksByDay()
{
	time_t currentTime = time(nullptr);
	tm* currentDate = localtime(&currentTime);
	int day = currentDate->tm_mday;
	int month = currentDate->tm_mon + 1;
	int year = currentDate->tm_year + 1900;

	string currentDateString = to_string(day) + "." + to_string(month) + "." + to_string(year);
	searchTasksByDateTime(currentDateString);
}

void displayTasksByWeek()
{
	time_t currentTime = time(nullptr);
	tm* currentDate = localtime(&currentTime);
	int day = currentDate->tm_wday;
	int month = currentDate->tm_mon + 1;
	int year = currentDate->tm_year + 1990;

	cout << "Дела на неделю с " << setfill('0') << setw(2) << day << "." << setw(2) << month << "." << year << ":\n";

	for (int i = 0; i < 7; i++)
	{
		string currentDateString = to_string(day + i) + "." + to_string(month) + "." + to_string(year);
		cout << "Дата: " << currentDateString << "\n";
		searchTasksByDateTime(currentDateString);
	}
}

void displayTasksByMonth()
{
	time_t currentTime = time(nullptr);
	tm* currentDate = localtime(&currentTime);
	int month = currentDate->tm_mon + 1;
	int year = currentDate->tm_year + 1900;

	cout << "Дела на месяц " << setfill('0') << setw(2) << month << "." << year << ":\n";

	for (int day = 1; day <= 31; day++) {
		string currentDateString = to_string(day) + "." + to_string(month) + "." + to_string(year);
		cout << "Дата: " << currentDateString << "\n";
		searchTasksByDateTime(currentDateString);
	}
}

void displayTaskList()
{
	if (taskList.empty())
	{
		cout << "Список дел пуст.\n";
		return;
	}

	cout << "Список дел:\n";
	for (Task& task : taskList) {
		cout << "Название: " << task.title << "\n";
		cout << "Приоритет: " << task.priority << "\n";
		cout << "Описание: " << task.description << "\n";
		cout << "Дата и время исполнения: " << task.dateTime << "\n";
		cout << "---------------------\n";
	}

}

void sortByPrioirity()
{
	if (taskList.empty())
	{
		cout << "Список дел пуст.\n";
			return;
	}

	sort(taskList.begin(), taskList.end(), [&](Task& task1, Task& task2) {
		return task1.priority < task2.priority;
		});

	cout << "Список дел отсортирован по приоритету.\n";
}

void sortByDateTime()
{
	if (taskList.empty())
	{
		cout << "Список дел пуст.\n";
		return;
	}

	sort(taskList.begin(), taskList.end(), [&](Task& task1, Task& task2) {
		return task1.dateTime < task2.dateTime;
		});
	cout << "Список дел отсортирован по дате и времени исполнения.\n";
}

void todo() {
	int choice;

	do {
		cout << "Меню:\n";
		cout << "1. Добавить дело\n";
		cout << "2. Удалить дело\n";
		cout << "3. Редактировать дело\n";
		cout << "4. Поиск дела по названию\n";
		cout << "5. Поиск дела по приоритету\n";
		cout << "6. Поиск дела по описанию\n";
		cout << "7. Поиск дела по дате и времени исполнения\n";
		cout << "8. Отобразить список дел на день\n";
		cout << "9. Отобразить список дел на неделю\n";
		cout << "10. Отобразить список дел на месяц\n";
		cout << "11. Отобразить весь список дел\n";
		cout << "12. Отсортировать список дел по приоритету\n";
		cout << "13. Отсортировать список дел по дате и времени исполнения\n";
		cout << "0. Выход\n";
		cout << "Выберите действие: ";
		cin >> choice;

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (choice)
		{
		case 1:
			addTask();
			break;
		case 2:
			removeTask();
			break;
		case 3:
			editTask();
			break;
		case 4:
		{
			string title;
			cout << "Введите название дела для поиска: ";
			getline(cin >> ws, title);
			searchTasksByTitle(title);
			break;
		}
		case 5: {
			int priority;
			cout << "Введите приоритет дела для поиска: ";
			cin >> priority;
			serachTasksByPriority(priority);
			break;
		}
		case 6: {
			string description;
			cout << "Введите описание дела для поиска: ";
			getline(cin >> ws, description);
			searchTasksByDescription(description);
			break;
		}
		case 7: {
			string dateTime;
			cout << "Введите дату и время исполнения для поиска (DD.MM.YYYY HH:MM): ";
			getline(cin >> ws, dateTime);
			searchTasksByDateTime(dateTime);
			break;
		}
		case 8:
			displayTasksByDay();
			break;
		case 9:
			displayTasksByWeek();
			break;

		case 10:
			displayTasksByMonth();
			break;
		case 11:
			displayTaskList();
			break;
		case 12:
			sortByPrioirity();
			break;
		case 13:
			sortByDateTime();
			break;
		case 0:
			cout << "До свидания!\n";
			break;

		default:
			cout << "Недопустимый выбор.\n";
			break;
		}
		cout << "\n";
	} while (choice != 0);

}