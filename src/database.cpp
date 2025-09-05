#include "database.hpp"

int reqCode;
char* errMsg = nullptr;
vector<string> tables;
vector<string> dbNames;
sqlite3* db = nullptr; // Определяем глобальную переменную

void createDatabase() {
    sqlite3 *new_database;
    cout << "Введите название базы данных: ";
    string new_database_name;
    cin >> new_database_name;

    for (auto &database : dbNames) {
        if (database == new_database_name) {
            cout << "База данных с таким названием уже существует" << endl;
            return;
        }
    }

    new_database_name += ".db";

    reqCode = sqlite3_open(new_database_name.c_str(), &new_database);
    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных: " << sqlite3_errmsg(new_database) << endl;
        sqlite3_close(new_database);
        return;
    } else {
        cout << "База данных " << new_database_name << " открыта успешно....." << endl;
    }

    dbNames.push_back(new_database_name);
}

void createTable(vector<string>& dbNames) {
    bool found = false;
    cout << "Выберите базу данных: ";
    string databaseName;
    cin >> databaseName;
    
    // Добавляем расширение .db если его нет
    if (databaseName.length() < 3 || databaseName.substr(databaseName.length() - 3) != ".db") {
        databaseName += ".db";
    }

    sqlite3* selectedDb = nullptr;
    for (auto dbname : dbNames) {
        if (dbname == databaseName) {
            cout << "Найдена база данных " << dbname << " ...." << endl;
            reqCode = sqlite3_open(databaseName.c_str(), &selectedDb);
            if (reqCode != SQLITE_OK) {
                cout << "Ошибка открытия базы данных: " << sqlite3_errmsg(selectedDb) << endl;
                return;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "База данных не найдена...." << endl;
        return;
    }

    cout << "Введите название таблицы: ";
    string tableName;
    cin >> tableName;

    for (auto &table : tables) {
        if (table == tableName) {
            cout << "Таблица с таким названием уже существует" << endl;
            sqlite3_close(selectedDb);
            return;
        }
    }

    string sqlRequest = "CREATE TABLE " + tableName + " (id INTEGER PRIMARY KEY AUTOINCREMENT, fullName TEXT, age INTEGER, diagnosis TEXT, location TEXT, sex TEXT)";

    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), NULL, NULL, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка создания таблицы: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Таблица " << tableName << " создана успешно....." << endl;
        tables.push_back(tableName);
    }
    
    sqlite3_close(selectedDb);
    this_thread::sleep_for(chrono::seconds(3));
    system("clear");
}

void deleteTable(vector<string>& dbNames) {
    bool found = false;
    cout << "Выберите базу данных: ";
    string databaseName;
    cin >> databaseName;
    
    // Добавляем расширение .db если его нет
    if (databaseName.length() < 3 || databaseName.substr(databaseName.length() - 3) != ".db") {
        databaseName += ".db";
    }

    sqlite3* selectedDb = nullptr;
    for (auto dbname : dbNames) {
        if (dbname == databaseName) {
            cout << "Найдена база данных " << dbname << " ...." << endl;
            reqCode = sqlite3_open(databaseName.c_str(), &selectedDb);
            if (reqCode != SQLITE_OK) {
                cout << "Ошибка открытия базы данных: " << sqlite3_errmsg(selectedDb) << endl;
                return;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "База данных не найдена...." << endl;
        return;
    }
}