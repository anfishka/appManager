#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Tenant {
    string name;
    string apartment;

    bool operator==(const Tenant& other) const {
        return name == other.name && apartment == other.apartment;
    }
};


struct Apartment {
    string number;
    string floor;
    vector<Tenant> tenants;
};

void addTenantToApartment(Apartment& apartment, Tenant& tenant) {
    apartment.tenants.push_back(tenant);
}

void removeTenantFromApartment(Apartment& apartment, Tenant& tenant) {
    auto it = find(apartment.tenants.begin(), apartment.tenants.end(), tenant);
    if (it != apartment.tenants.end()) {
        apartment.tenants.erase(it);
    }
}

void saveToFile(vector<Apartment>& apartments, string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto& apartment : apartments) {
            file << "Apartment: " << apartment.number << ", Floor: " << apartment.floor << "\n";
            for (const auto& tenant : apartment.tenants) {
                file << "Tenant: " << tenant.name << ", Apartment: " << tenant.apartment << "\n";
            }
            file << "\n";
        }
        file.close();
        cout << "Информация сохранена в файл " << filename << "\n";
    }
    else {
        cerr << "Ошибка при открытии файла " << filename << "\n";
    }
}

vector<Apartment> loadFromFile(string& filename) {
    vector<Apartment> apartments;
    ifstream file(filename);
    if (file.is_open()) {
        Apartment currentApartment;
        string line;
        while (getline(file, line)) {
            if (line.find("Apartment:") != string::npos) {
                if (!currentApartment.number.empty()) {
                    apartments.push_back(currentApartment);
                    currentApartment = Apartment();
                }
                size_t pos = line.find("Apartment: ");
                currentApartment.number = line.substr(pos + 11);
            }
            else if (line.find("Floor:") != string::npos) {
                size_t pos = line.find("Floor: ");
                currentApartment.floor = line.substr(pos + 7);
            }
            else if (line.find("Tenant:") != string::npos) {
                size_t pos = line.find("Tenant: ");
                Tenant tenant;
                tenant.name = line.substr(pos + 8);
                size_t commaPos = tenant.name.find(", Apartment: ");
                tenant.apartment = tenant.name.substr(commaPos + 13);
                tenant.name = tenant.name.substr(0, commaPos);
                currentApartment.tenants.push_back(tenant);
            }
        }
        if (!currentApartment.number.empty()) {
            apartments.push_back(currentApartment);
        }
        file.close();
        cout << "Информация загружена из файла " << filename << "\n";
    }
    else {
        cerr << "Ошибка при открытии файла " << filename << "\n";
    }
    return apartments;
}

void displayAllTenants(vector<Apartment>& apartments) {
    cout << "Полный список жильцов:\n";
    for (const auto& apartment : apartments) {
        for (const auto& tenant : apartment.tenants) {
            cout << "Жилец: " << tenant.name << ", Квартира: " << tenant.apartment << "\n";
        }
    }
}

void displayAllApartments(vector<Apartment>& apartments) {
    cout << "Полный список квартир:\n";
    for (const auto& apartment : apartments) {
        cout << "Квартира: " << apartment.number << ", Этаж: " << apartment.floor << "\n";
    }
}

void displayApartmentInfo(const Apartment& apartment) {
    cout << "Информация о квартире:\n";
    cout << "Квартира: " << apartment.number << ", Этаж: " << apartment.floor << "\n";
    cout << "Жильцы:\n";
    for (const auto& tenant : apartment.tenants) {
        cout << "Жилец: " << tenant.name << ", Квартира: " << tenant.apartment << "\n";
    }
}

void displayApartmentsOnFloor(vector<Apartment>& apartments, const string& floor) {
    cout << "Квартиры на этаже " << floor << ":\n";
    for (auto& apartment : apartments) {
        if (apartment.floor == floor) {
            cout << "Квартира: " << apartment.number << "\n";
        }
    }
}

void displayApartmentsByType(vector<Apartment>& apartments, const string& type) {
    cout << "Квартиры типа " << type << ":\n";
    for (auto& apartment : apartments) {
        if (apartment.number.find(type) != string::npos) {
            cout << "Квартира: " << apartment.number << "\n";
        }
    }
}

void displayMenu() {
    cout << "Меню:\n";
    cout << "1. Показать всех жильцов\n";
    cout << "2. Показать все квартиры\n";
    cout << "3. Показать информацию о квартире\n";
    cout << "4. Показать квартиры на этаже\n";
    cout << "5. Показать квартиры по типу\n";
    cout << "6. Выход\n";
    cout << "Выберите опцию (1-6): ";
}

void management() {
    vector<Apartment> apartments;
    string filename = "data.txt";
    vector<Apartment> loadedApartments = loadFromFile(filename);
    if (!loadedApartments.empty()) {
        apartments = loadedApartments;
    }
    else {
        Apartment apartment1;
        apartment1.number = "1A";
        apartment1.floor = "1";
        Tenant tenant1;
        tenant1.name = "Иванов";
        tenant1.apartment = apartment1.number;
        addTenantToApartment(apartment1, tenant1);
        apartments.push_back(apartment1);

        Apartment apartment2;
        apartment2.number = "2B";
        apartment2.floor = "2";
        Tenant tenant2;
        tenant2.name = "Петров";
        tenant2.apartment = apartment2.number;
        addTenantToApartment(apartment2, tenant2);
        apartments.push_back(apartment2);
    }

    int choice = 0;
    while (choice != 6) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            displayAllTenants(apartments);
            break;
        case 2:
            displayAllApartments(apartments);
            break;
        case 3: {
            string apartmentNumber;
            cout << "Введите номер квартиры: ";
            cin >> apartmentNumber;
            bool found = false;
            for (const auto& apartment : apartments) {
                if (apartment.number == apartmentNumber) {
                    displayApartmentInfo(apartment);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Квартира с номером " << apartmentNumber << " не найдена.\n";
            }
            break;
        }
        case 4: {
            string floor;
            cout << "Введите номер этажа: ";
            cin >> floor;
            displayApartmentsOnFloor(apartments, floor);
            break;
        }
        case 5: {
            string type;
            cout << "Введите тип квартиры: ";
            cin >> type;
            displayApartmentsByType(apartments, type);
            break;
        }
        case 6:
            saveToFile(apartments, filename);
            cout << "Программа завершена.\n";
            break;
        default:
            cout << "Некорректный выбор. Пожалуйста, выберите опцию от 1 до 6.\n";
            break;
        }

        cout << endl;
    }
}