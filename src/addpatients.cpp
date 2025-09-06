#include "addpatients.hpp"

// Глобальные генераторы
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> ageDist(1, 100);
uniform_int_distribution<> nameDist(0, 99);
uniform_int_distribution<> diagDist(0, 29); // 30 заболеваний
uniform_int_distribution<> locDist(0, 9);
uniform_int_distribution<> genderDist(0, 1);

vector<string> firstNames = {"Иван", "Петр", "Алексей", "Сергей", "Михаил", "Дмитрий", "Андрей", "Александр", "Владимир", "Николай",
                                       "Мария", "Анна", "Елена", "Ольга", "Наталья", "Ирина", "Татьяна", "Светлана", "Юлия", "Ксения"};
vector<string> lastNames = {"Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов", "Попов", "Лебедев", "Козлов", "Новиков", "Морозов"};
vector<string> middleNames = {"Иванович", "Петрович", "Алексеевич", "Сергеевич", "Михайлович", "Дмитриевич", "Андреевич", "Александрович", "Владимирович", "Николаевич"};
vector<string> locations = {"Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург", "Казань", "Нижний Новгород", "Челябинск", "Самара", "Омск", "Ростов-на-Дону"};

vector<string> diseases;

vector<string> loadDiseasesFromFile() {
    vector<string> diseasesList;
    ifstream file("assets/illnesses.txt");
    
    if (!file.is_open()) {
        cout << "Ошибка открытия файла diseases.txt" << endl;
        return diseasesList;
    }
    
    string line;
    while (getline(file, line)) {
        diseasesList.push_back(line);
    }
    
    file.close();
    return diseasesList;
}

string generateRandomName() {
    string lastName = lastNames[nameDist(gen) % lastNames.size()];
    string firstName = firstNames[nameDist(gen) % firstNames.size()];
    string middleName = middleNames[nameDist(gen) % middleNames.size()];
    return lastName + " " + firstName + " " + middleName;
}

string generateRandomDiagnosisWithCode() {
    if (diseases.empty()) {
        diseases = loadDiseasesFromFile();
    }
    
    if (!diseases.empty()) {
        return diseases[diagDist(gen) % diseases.size()];
    }
    return "0001-Грипп";
}

string generateRandomLocation() {
    return locations[locDist(gen) % locations.size()];
}

string generateRandomGender() {
    return genderDist(gen) == 0 ? "м" : "ж";
}

int generateRandomAge() {
    return ageDist(gen);
}

void addRandomPatients(int count) {
    sqlite3* selectedDb;
    int rc = sqlite3_open("clinic.db", &selectedDb);
    
    if (rc != SQLITE_OK) {
        cout << "Ошибка открытия базы данных..." << endl;
        sqlite3_close(selectedDb);
        return;
    }

    // Загружаем заболевания один раз
    if (diseases.empty()) {
        diseases = loadDiseasesFromFile();
    }
    
    if (diseases.empty()) {
        cout << "Не удалось загрузить заболевания из файла" << endl;
        sqlite3_close(selectedDb);
        return;
    }

    // Начинаем транзакцию для ускорения вставки
    sqlite3_exec(selectedDb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    for (int i = 0; i < count; ++i) {
        string fullName = generateRandomName();
        int age = generateRandomAge();
        string diagnosis = generateRandomDiagnosisWithCode();
        string location = generateRandomLocation();
        string gender = generateRandomGender();
        
        string sql = "INSERT INTO patients (fullName, age, diagnosis, location, sex) VALUES ('" + 
                          fullName + "', " + to_string(age) + ", '" + diagnosis + "', '" + 
                          location + "', '" + gender + "')";
        
        char* errMsg = nullptr;
        rc = sqlite3_exec(selectedDb, sql.c_str(), NULL, NULL, &errMsg);
        
        if (rc != SQLITE_OK) {
            cout << "Ошибка добавления пациента: " << errMsg << endl;
            sqlite3_free(errMsg);
        }
    }
    
    // Завершаем транзакцию
    sqlite3_exec(selectedDb, "COMMIT;", NULL, NULL, NULL);
    
    cout << "Добавлено " << count << " случайных пациентов." << endl;
    sqlite3_close(selectedDb);
}