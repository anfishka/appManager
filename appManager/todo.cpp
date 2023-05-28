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
	cout << "������� �������� ����: ";
	getline(cin >> ws, task.title);

	cout << "������� ��������� ���� (�� 1 �� 10): ";
	cin >> task.priority;

	cout << "������� �������� ����: ";
	getline(cin >> ws, task.description);

	cout << "������� ���� � ����� ���������� ���� (DD.MM.YYYY HH:MM): ";
	getline(cin >> ws, task.dateTime);

	taskList.push_back(task);
	cout << "���� ������� ���������";
}

void removeTask()
{
	if (taskList.empty())
	{
		cout << "������ ��� ����.\n";
		return;
	}

	cout << "������� ����� ���� ��� ��������:";
	int taskNumber;
	cin >> taskNumber;

	if (taskNumber < 1 || taskNumber > taskList.size()) {
		cout << "������������ ����� ����.\n";
		return;
	}
	taskList.erase(taskList.begin() + taskNumber - 1);
	
	cout << "���� ������� �������.\n";
}

void editTask()
{
	if (taskList.empty())
	{
		cout << "������ ��� ����.\n";
		return;
	}

	cout << "������� ����� ���� ��� ��������������: ";
	int taskNumber;
	cin >> taskNumber;

	if (taskNumber > 1 || taskNumber > taskList.size()) {
		cout << "������������ ����� ����.\n";
		return;
	}

	Task& task = taskList[taskNumber - 1];

	cout << "������� ����� �������� ����:";
	getline(cin >> ws, task.title);

	cout << "������� ����� ��������� ���� (�� 1 �� 10): ";
	getline(cin >> ws, task.description);

	cout << "������� ����� �������� ����: ";
	getline(cin >> ws, task.description);

	cout << "������� ����� ���� � ����� ���������� ����(DD.MM.YYYY HH : MM) :";
	getline(cin >> ws, task.dateTime);

	cout << "���� ������� ���������������.\n";
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
		cout << "���� � ����� ��������� �� �������.\n";
		return;
	}

	cout << "��������� ���� � ��������� '" << title << "':\n";
	for (Task& task : matchingTasks) {
		cout << "��������: " << task.title << "\n";
		cout << "���������: " << task.priority << "\n";
		cout << "��������: " << task.description << "\n";
		cout << "���� � ����� ����������: " << task.dateTime << "\n";
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
		cout << "���� � ����� ����������� �� �������.\n";
		return;
	}

	cout << "��������� ���� � ����������� " << priority << ":\n";
	for (Task& task : matchingTasks) {
		cout << "��������: " << task.title << "\n";
		cout << "���������: " << task.priority << "\n";
		cout << "��������: " << task.description << "\n";
		cout << "���� � ����� ����������: " << task.dateTime << "\n";
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
		cout << "���� � ����� ��������� �� �������.\n";
		return;
	}

	cout << "��������� ���� � ��������� '" << description << "':\n";
	for (Task& task : matchingTasks) {
		cout << "��������: " << task.title << "\n";
		cout << "���������: " << task.priority << "\n";
		cout << "��������: " << task.description << "\n";
		cout << "���� � ����� ����������: " << task.dateTime << "\n";
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
		cout << "���� � ����� ����� � �������� ���������� �� �������.\n";
		return;
	}

	cout << "��������� ���� � ����� � �������� ���������� '" << dateTime << "':\n";
	for (Task& task : matchingTasks) {
		cout << "��������: " << task.title << "\n";
		cout << "���������: " << task.priority << "\n";
		cout << "��������: " << task.description << "\n";
		cout << "���� � ����� ����������: " << task.dateTime << "\n";
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

	cout << "���� �� ������ � " << setfill('0') << setw(2) << day << "." << setw(2) << month << "." << year << ":\n";

	for (int i = 0; i < 7; i++)
	{
		string currentDateString = to_string(day + i) + "." + to_string(month) + "." + to_string(year);
		cout << "����: " << currentDateString << "\n";
		searchTasksByDateTime(currentDateString);
	}
}

void displayTasksByMonth()
{
	time_t currentTime = time(nullptr);
	tm* currentDate = localtime(&currentTime);
	int month = currentDate->tm_mon + 1;
	int year = currentDate->tm_year + 1900;

	cout << "���� �� ����� " << setfill('0') << setw(2) << month << "." << year << ":\n";

	for (int day = 1; day <= 31; day++) {
		string currentDateString = to_string(day) + "." + to_string(month) + "." + to_string(year);
		cout << "����: " << currentDateString << "\n";
		searchTasksByDateTime(currentDateString);
	}
}

void displayTaskList()
{
	if (taskList.empty())
	{
		cout << "������ ��� ����.\n";
		return;
	}

	cout << "������ ���:\n";
	for (Task& task : taskList) {
		cout << "��������: " << task.title << "\n";
		cout << "���������: " << task.priority << "\n";
		cout << "��������: " << task.description << "\n";
		cout << "���� � ����� ����������: " << task.dateTime << "\n";
		cout << "---------------------\n";
	}

}

void sortByPrioirity()
{
	if (taskList.empty())
	{
		cout << "������ ��� ����.\n";
			return;
	}

	sort(taskList.begin(), taskList.end(), [&](Task& task1, Task& task2) {
		return task1.priority < task2.priority;
		});

	cout << "������ ��� ������������ �� ����������.\n";
}

void sortByDateTime()
{
	if (taskList.empty())
	{
		cout << "������ ��� ����.\n";
		return;
	}

	sort(taskList.begin(), taskList.end(), [&](Task& task1, Task& task2) {
		return task1.dateTime < task2.dateTime;
		});
	cout << "������ ��� ������������ �� ���� � ������� ����������.\n";
}

void todo() {
	int choice;

	do {
		cout << "����:\n";
		cout << "1. �������� ����\n";
		cout << "2. ������� ����\n";
		cout << "3. ������������� ����\n";
		cout << "4. ����� ���� �� ��������\n";
		cout << "5. ����� ���� �� ����������\n";
		cout << "6. ����� ���� �� ��������\n";
		cout << "7. ����� ���� �� ���� � ������� ����������\n";
		cout << "8. ���������� ������ ��� �� ����\n";
		cout << "9. ���������� ������ ��� �� ������\n";
		cout << "10. ���������� ������ ��� �� �����\n";
		cout << "11. ���������� ���� ������ ���\n";
		cout << "12. ������������� ������ ��� �� ����������\n";
		cout << "13. ������������� ������ ��� �� ���� � ������� ����������\n";
		cout << "0. �����\n";
		cout << "�������� ��������: ";
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
			cout << "������� �������� ���� ��� ������: ";
			getline(cin >> ws, title);
			searchTasksByTitle(title);
			break;
		}
		case 5: {
			int priority;
			cout << "������� ��������� ���� ��� ������: ";
			cin >> priority;
			serachTasksByPriority(priority);
			break;
		}
		case 6: {
			string description;
			cout << "������� �������� ���� ��� ������: ";
			getline(cin >> ws, description);
			searchTasksByDescription(description);
			break;
		}
		case 7: {
			string dateTime;
			cout << "������� ���� � ����� ���������� ��� ������ (DD.MM.YYYY HH:MM): ";
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
			cout << "�� ��������!\n";
			break;

		default:
			cout << "������������ �����.\n";
			break;
		}
		cout << "\n";
	} while (choice != 0);

}