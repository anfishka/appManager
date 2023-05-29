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

	cout << "Введите название: ";
	getline(cin >> ws, newSong.title);
	cout << "Введите автора: ";
	getline(cin >> ws, newSong.author);
	cout << "Введите год: ";
	cin >> newSong.year;
	cout << "Введите текст песни (нажмите Enter на пустой строке, чтобы завершить): \n";
	string line;
	while (getline(cin >> ws, line) && !line.empty()) {
		newSong.lyrics += line + "\n";
	}
	catalog.push_back(newSong);
	cout << "Текст песни успешно добавлена!\n";
}

void loadSongsFromFile()
{
	string filename;
	cout << "Введите название песни: ";
	cin >> filename;
	ifstream file(filename);
	if (!file)
	{
		cout << "Не удалось открыть файл.\n";
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
	cout << "Песни звгружєені успешно!\n";
}

void removeSong()
{
	if (catalog.empty()) {
		cout << "Каталог пуст.\n";
		return;
	}
	cout << "ВВедите индекс песни для удаления (0 -" << catalog.size() - 1 << "): ";
	int index;
	cin >> index;
	if (index >= 0 && index < catalog.size()) {
		catalog.erase(catalog.begin() + index);
		cout << "Пусня успешно удалена!\n";
	}
	else {
		cout << "Неверный индекс.\n";
	}
}

void editSong() {
	if (catalog.empty()) {
		cout << "Каталог пуст.\n";
		return;
	}
	cout << "Введите индекс песни для редактирования ( 0 - " << catalog.size() - 1 << " ) ";
	int index;
	cin >> index;
	if (index >= 0 && index < catalog.size()) {
		Song& song = catalog[index];
		cout << "Введи новый текст песни(нажми Enter на пустой строке, чтобы закончить) :\n";
		string line;
		song.lyrics.clear();
		while (getline(cin >> ws, line) && !line.empty()) {
			song.lyrics += line + "\n";

		}
		cout << "Текст песни успешно отредактирован!\n";
	}
	else {
		cout << "Неверный индекс.\n";
	}
}

void displaySong(Song& song) {
	cout << "Название: " << song.title << "\n";
	cout << "Автор: " << song.author << "\n";
	cout << "Год: " << song.year << "\n";
	cout << "Текст песни:\n" << song.lyrics << "\n";
}

void displayAllSongs() {
	if (catalog.empty()) {
		cout << "Каталог пуст.\n";
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
		cout << "Не удалось открыть файл.\n";
		return;
	}
	file << song.title << "\n";
	file << song.author << "\n";
	file << song.year << "\n";
	file << song.lyrics << "\n";
	file << "-------------------------\n";
	cout << "Песня успешно сохранена!\n";
}

void searchByAuthor() {
	string author;
	cout << "Введите имя автора: ";
	getline(cin >> ws, author);

	vector <Song> matchingSongs;
	for (Song& song : catalog) {
		if (song.author == author) {
			matchingSongs.push_back(song);
		}
	}
	if (matchingSongs.empty()) {
		cout << "Песни автора не найдены.\n";
	}else{
		cout << "Песни " << author << ": \n";
		for (Song& song : matchingSongs) {
			displaySong(song);
			cout << "-------------------------\n";
		}
	}
}

void searchByWord() {
	string word;
	cout << "Введите слово для поиска: ";
	getline(cin >> ws, word);

	vector <Song> matchingSongs;
	for (Song& song : catalog) {
		if (song.lyrics.find(word) != string::npos) {
			matchingSongs.push_back(song);
		}
	}
	if (matchingSongs.empty()) {
		cout << "Слова не найдены.\n";
	}
	else {
		cout << "Песни, содержащие слово "" << word << "":\n";
		for (Song& song : matchingSongs) {
			displaySong(song);
			cout << "-------------------------\n";
		}
	}
}

void lyrics() {
	int choice;
	do{
		cout << "1. Добавить песню\n";
		cout << "2. Загрузить песни из файла\n";
		cout << "3. Удалить песню\n";
		cout << "4. Редактировать песню\n";
		cout << "5. Показать все песни\n";
		cout << "6. Сохранить песню в файл\n";
		cout << "7. Поиск песен в файле\n";
		cout << "8. Поиск песен по слову\n";
		cout << "9. Выход\n";
		cout << "Введите ваш выбор ";
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
			cout << "Введите индекс песни для сохранения (0-" << catalog.size() - 1 << ")";
			int index;
			cin >> index;
			if (index >= 0 && index < catalog.size()) {
				saveSongToFile(catalog[index]);
			}
			else {
				cout << "Недопустимый индекс.\n";
			}
		}
	else {
			cout << "Каталог пуст.\n";
	}
	break;
	case 7:
		searchByAuthor();
		break;
	case 8:
		searchByWord();
		break;
	case 9:
		cout << "Выход из программы. До свидания!\n";
		break;
	default:
		cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
		break;
	}
		cout << "\n";
	} while (choice != 9);
}
