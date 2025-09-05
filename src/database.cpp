#include "database.hpp"

int reqCode;
char* errMsg = nullptr;
vector<string> tables;


void createTable() {
    
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "База данных клиники открыта....." << endl;

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

void deleteTable() {
    
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "База данных клиники открыта....." << endl;

    }

    cout << "Введите название таблицы для удаления: ";
    string tableName;
    cin >> tableName;
    
    // Проверяем, существует ли таблица
    bool tableExists = false;
    for (auto &table : tables) {
        if (table == tableName) {
            tableExists = true;
            break;
        }
    }
    
    if (!tableExists) {
        cout << "Таблица не найдена...." << endl;
        sqlite3_close(selectedDb);
        return;
    }
    
    // SQL запрос для удаления таблицы
    string sqlRequest = "DROP TABLE " + tableName;
    
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), NULL, NULL, &errMsg);
    
    if (reqCode != SQLITE_OK) {
        cout << "Ошибка удаления таблицы: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Таблица " << tableName << " удалена успешно....." << endl;
        // Удаляем таблицу из вектора tables
        tables.erase(remove(tables.begin(), tables.end(), tableName), tables.end());
    }
    
    sqlite3_close(selectedDb);
    this_thread::sleep_for(chrono::seconds(3));
    system("clear");
}