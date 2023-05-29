#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Song {
	string title;
	string author;
	int year;
	string lyrics;
};

vector <Song> catalog;

void addSong()
{
	Song newSong;

	cout << "������� ��������: ";
	getline(cin >> ws, newSong.title);
	cout << "������� ������: ";
	getline(cin >> ws, newSong.author);
	cout << "������� ���: ";
	cin >> newSong.year;
	cout << "������� ����� ����� (������� Enter �� ������ ������, ����� ���������): \n";
	string line;
	while (getline(cin >> ws, line) && !line.empty()) {
		newSong.lyrics += line + "\n";
	}
	catalog.push_back(newSong);
	cout << "����� ����� ������� ���������!\n";
}

void loadSongsFromFile()
{
	string filename;
	cout << "������� �������� �����: ";
	cin >> filename;
	ifstream file(filename);
	if (!file)
	{
		cout << "�� ������� ������� ����.\n";
		return;
	}
	Song newSong;
	while (getline(file, newSong.title) && getline(file, newSong.author) && file >> newSong.year) {
		string line;
		getline(file >> ws, line);
		while (getline(file, line) && !line.empty()) {
				newSong.lyrics += line + "\n";
		}
		catalog.push_back(newSong);
		newSong = {};
	}
	cout << "����� �������� �������!\n";
}

void removeSong()
{
	if (catalog.empty()) {
		cout << "������� ����.\n";
		return;
	}
	cout << "������� ������ ����� ��� �������� (0 -" << catalog.size() - 1 << "): ";
	int index;
	cin >> index;
	if (index >= 0 && index < catalog.size()) {
		catalog.erase(catalog.begin() + index);
		cout << "����� ������� �������!\n";
	}
	else {
		cout << "�������� ������.\n";
	}
}

void editSong() {
	if (catalog.empty()) {
		cout << "������� ����.\n";
		return;
	}
	cout << "������� ������ ����� ��� �������������� ( 0 - " << catalog.size() - 1 << " ) ";
	int index;
	cin >> index;
	if (index >= 0 && index < catalog.size()) {
		Song& song = catalog[index];
		cout << "����� ����� ����� �����(����� Enter �� ������ ������, ����� ���������) :\n";
		string line;
		song.lyrics.clear();
		while (getline(cin >> ws, line) && !line.empty()) {
			song.lyrics += line + "\n";

		}
		cout << "����� ����� ������� ��������������!\n";
	}
	else {
		cout << "�������� ������.\n";
	}
}

void displaySong(Song& song) {
	cout << "��������: " << song.title << "\n";
	cout << "�����: " << song.author << "\n";
	cout << "���: " << song.year << "\n";
	cout << "����� �����:\n" << song.lyrics << "\n";
}

void displayAllSongs() {
	if (catalog.empty()) {
		cout << "������� ����.\n";
		return;
	}
	for (Song& song : catalog) {
		displaySong(song);
		std::cout << "-------------------------\n";
	}
}


void saveSongToFile(Song song) {
	ofstream file("songs.txt, ios:: app");
	if (!file) {
		cout << "�� ������� ������� ����.\n";
		return;
	}
	file << song.title << "\n";
	file << song.author << "\n";
	file << song.year << "\n";
	file << song.lyrics << "\n";
	file << "-------------------------\n";
	cout << "����� ������� ���������!\n";
}

void searchByAuthor() {
	string author;
	cout << "������� ��� ������: ";
	getline(cin >> ws, author);

	vector <Song> matchingSongs;
	for (Song& song : catalog) {
		if (song.author == author) {
			matchingSongs.push_back(song);
		}
	}
	if (matchingSongs.empty()) {
		cout << "����� ������ �� �������.\n";
	}else{
		cout << "����� " << author << ": \n";
		for (Song& song : matchingSongs) {
			displaySong(song);
			cout << "-------------------------\n";
		}
	}
}

void searchByWord() {
	string word;
	cout << "������� ����� ��� ������: ";
	getline(cin >> ws, word);

	vector <Song> matchingSongs;
	for (Song& song : catalog) {
		if (song.lyrics.find(word) != string::npos) {
			matchingSongs.push_back(song);
		}
	}
	if (matchingSongs.empty()) {
		cout << "����� �� �������.\n";
	}
	else {
		cout << "�����, ���������� ����� "" << word << "":\n";
		for (Song& song : matchingSongs) {
			displaySong(song);
			cout << "-------------------------\n";
		}
	}
}

void lyrics() {
	int choice;
	do{
		cout << "1. �������� �����\n";
		cout << "2. ��������� ����� �� �����\n";
		cout << "3. ������� �����\n";
		cout << "4. ������������� �����\n";
		cout << "5. �������� ��� �����\n";
		cout << "6. ��������� ����� � ����\n";
		cout << "7. ����� ����� � �����\n";
		cout << "8. ����� ����� �� �����\n";
		cout << "9. �����\n";
		cout << "������� ��� ����� ";
	cin >> choice;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (choice) {
	case 1:
		addSong();
		break;
	case 2:
		loadSongsFromFile();
		break;
	case 3:
		removeSong();
		break;
	case 4:
		editSong();
		break;
	case 5:
		displayAllSongs();
		break;
	case 6:
		if (!catalog.empty()) {
			cout << "������� ������ ����� ��� ���������� (0-" << catalog.size() - 1 << ")";
			int index;
			cin >> index;
			if (index >= 0 && index < catalog.size()) {
				saveSongToFile(catalog[index]);
			}
			else {
				cout << "������������ ������.\n";
			}
		}
	else {
			cout << "������� ����.\n";
	}
	break;
	case 7:
		searchByAuthor();
		break;
	case 8:
		searchByWord();
		break;
	case 9:
		cout << "����� �� ���������. �� ��������!\n";
		break;
	default:
		cout << "�������� �����. ����������, ���������� �����.\n";
		break;
	}
		cout << "\n";
	} while (choice != 9);
}
