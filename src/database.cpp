#include "database.hpp"

int reqCode;
char* errMsg = nullptr;
vector<string> tables;

void workWithTables() {

    int choice;

    cout << "Выберите дествие с таблицей:" << endl;
    cout << "1. Создать таблицу" << endl;
    cout << "2. Удалить таблицу" << endl;
    cout << "3. Показать таблицы" << endl;
    cout << "4. Показать информацию в таблице" << endl;
    cout << "5. Выход" << endl;

    cin >> choice;

    switch(choice) {
        case 1:
            createTable();
            break;
        case 2:
            deleteTable();
            break;
        case 3:
            showTables();
            break;
        case 4:
            showTableInfo();
            break;
        case 5:
            return;
    }
}

void initializeTables() {
    sqlite3* selectedDb;
    int rc = sqlite3_open("clinic.db", &selectedDb);
    
    if (rc != SQLITE_OK) {
        cout << "Ошибка открытия базы данных..." << endl;
        sqlite3_close(selectedDb);
        return;
    }
    
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argv[0]) {
            tables.push_back(string(argv[0]));
        }
        return 0;
    };
    
    string sqlRequest = "SELECT name FROM sqlite_master WHERE type='table'";
    char* errMsg = nullptr;
    rc = sqlite3_exec(selectedDb, sqlRequest.c_str(), callback, NULL, &errMsg);
    
    if (rc != SQLITE_OK) {
        cout << "Ошибка получения списка таблиц: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    
    sqlite3_close(selectedDb);
}

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
    
    
    string sqlRequest = "DROP TABLE " + tableName;
    
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), NULL, NULL, &errMsg);
    
    if (reqCode != SQLITE_OK) {
        cout << "Ошибка удаления таблицы: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Таблица " << tableName << " удалена успешно....." << endl;
        tables.erase(remove(tables.begin(), tables.end(), tableName), tables.end());
    }
    
    sqlite3_close(selectedDb);
    this_thread::sleep_for(chrono::seconds(3));
    system("clear");
}

void showTables() {
    int choice;
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << errMsg << endl;
        sqlite3_free(errMsg);
        return;
    } else {
        cout << "База данных клиники открыта....." << endl;
    }

    for (auto &table : tables) {
        cout << table << endl;
    }

    sqlite3_close(selectedDb);
}

void showTableInfo() {
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << sqlite3_errmsg(selectedDb) << endl;
        return;
    }

    cout << "Введите название таблицы: ";
    string tableName;
    cin >> tableName;

    cout << format("{:<10} {:<35} {:<10} {:<30} {:<30} {:<10}", "ID", "Ф.И.О", "Возраст", "Диагноз", "Место проживания", "Пол") << endl;

    cout << string(123, '-') << endl;

    // Callback для вывода данных
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        cout << format("{:<10} {:<35} {:<10} {:<30} {:<30} {:<10}", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]) << endl;
        return 0;
    };


    string sqlRequest = "SELECT * FROM " + tableName;
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), callback, NULL, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(selectedDb);
}

void showNonresidentPatients() {
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << sqlite3_errmsg(selectedDb) << endl;
        return;
    }

    cout << "Список иногородних пациентов:" << endl;
    cout << format("{:<10} {:<35} {:<10} {:<30} {:<30} {:<10}", "ID", "Ф.И.О", "Возраст", "Диагноз", "Место проживания", "Пол") << endl;

    cout << string(123, '-') << endl;

    // Callback выводит только нужные поля (id, ФИО, место проживания)
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        cout << format("{:<10} {:<35} {:<10} {:<30} {:<30} {:<10}", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]) << endl;
        return 0;
    };

    string sqlRequest = "SELECT * FROM patients WHERE location != 'Новосибирск'";
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), callback, NULL, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(selectedDb);
}

void deleteNonresidentPatients() {
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << sqlite3_errmsg(selectedDb) << endl;
        return;
    }

    string sqlRequest = "DELETE FROM patients WHERE location != 'Новосибирск'";
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), NULL, NULL, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Иногородние пациенты удалены..." << endl;
    }

    sqlite3_close(selectedDb);
}

void showPatientsByAge() {
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << sqlite3_errmsg(selectedDb) << endl;
        return;
    }

    cout << "Введите возраст фильтрации: ";
    int age;
    cin >> age;

    cout << "Список пациентов с возрастом больше " << age << " лет:" << endl;
    cout << format("{:<10} {:<35} {:<10} {:<30} {:<30} {:<10}", "ID", "Ф.И.О", "Возраст", "Диагноз", "Место проживания", "Пол") << endl;

    cout << string(123, '-') << endl;

    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        cout << format("{:<10} {:<35} {:<10} {:<30} {:<30} {:<10}", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]) << endl;
        return 0;
    };
    string sqlRequest = "SELECT * FROM patients WHERE age > " + to_string(age);
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), callback, NULL, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(selectedDb);

}

void changePatientDiagnosis() {
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << sqlite3_errmsg(selectedDb) << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введите ФИО пациента: ";
    string name;
    getline(cin, name);

    bool patientExists = false;
    auto checkCallback = [](void* data, int argc, char** argv, char** azColName) -> int {
        bool* exists = static_cast<bool*>(data);
        *exists = true;
        return 0;
    };

    string checkRequest = "SELECT 1 FROM patients WHERE fullName = '" + name + "' LIMIT 1";
    reqCode = sqlite3_exec(selectedDb, checkRequest.c_str(), checkCallback, &patientExists, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(selectedDb);
        return;
    }

    if (!patientExists) {
        cout << "Пациент с Ф.И.О '" << name << "' не найден..." << endl;
        sqlite3_close(selectedDb);
        this_thread::sleep_for(chrono::seconds(3));
        system("clear");
        return;
    }

    cout << "Введите новый диагноз: ";
    string diagnosis;
    getline(cin, diagnosis);

    string sqlRequest = "UPDATE patients SET diagnosis = '" + diagnosis + "' WHERE fullName = '" + name + "'";
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), NULL, NULL, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Диагноз пациента " << name << " изменен на " << diagnosis << endl;
    }

    sqlite3_close(selectedDb);
    this_thread::sleep_for(chrono::seconds(3));
    system("clear");
}

void addPatient() {
    int choice;
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << errMsg << endl;
        sqlite3_free(errMsg);
        return;
    } else {
        cout << "База данных клиники открыта....." << endl;

    }

    cin.ignore();

    cout << "Введите Ф.И.О пациента: ";
    string name;
    getline(cin, name);

    cout << "Введите возраст пациента: ";
    int age;
    cin >> age;

    cout << "Введите диагноз пациента: ";
    string diagnosis;
    cin >> diagnosis;

    cin.ignore();

    cout << "Введите место проживания пациента: ";
    string location;
    getline(cin, location);

    cout << "Введите пол пациента (м/ж): ";
    string gender;
    cin >> gender;

    cin.ignore(1000, '\n');

    string sqlRequest = "INSERT INTO patients (fullName, age, diagnosis, location, sex) VALUES ('" + name + "', " + to_string(age) + ", '" + diagnosis + "', '" + location + "', '" + gender + "')";
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), NULL, NULL, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Пациент добавлен..." << endl;
    }

    sqlite3_close(selectedDb);
    this_thread::sleep_for(chrono::seconds(3));
    system("clear");
}

void deletePatient() {
    int choice;
    sqlite3* selectedDb;
    reqCode = sqlite3_open("clinic.db", &selectedDb);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка открытия базы данных...: " << errMsg << endl;
        sqlite3_free(errMsg);
        return;
    } else {
        cout << "База данных клиники открыта....." << endl;

    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введите фио пациента: ";
    string name;
    getline(cin, name);

    bool patientExists = false;
    auto checkCallback = [](void* data, int argc, char** argv, char** azColName) -> int {
        bool* exists = static_cast<bool*>(data);
        *exists = true;
        return 0;
    };

    string checkRequest = "SELECT 1 FROM patients WHERE fullName = '" + name + "' LIMIT 1";
    reqCode = sqlite3_exec(selectedDb, checkRequest.c_str(), checkCallback, &patientExists, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(selectedDb);
        return;
    }

    if (!patientExists) {
        cout << "Пациент с Ф.И.О '" << name << "' не найден..." << endl;
        sqlite3_close(selectedDb);
        this_thread::sleep_for(chrono::seconds(3));
        system("clear");
        return;
    }

    string sqlRequest = "DELETE FROM patients WHERE fullName = '" + name + "'";
    reqCode = sqlite3_exec(selectedDb, sqlRequest.c_str(), NULL, NULL, &errMsg);

    if (reqCode != SQLITE_OK) {
        cout << "Ошибка выполнения запроса: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Пациент удален..." << endl;
    }

    sqlite3_close(selectedDb);
    this_thread::sleep_for(chrono::seconds(3));
    system("clear");
}