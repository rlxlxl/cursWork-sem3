#include "database.hpp"
#include "addpatients.hpp"
#include "cosmetics.hpp"

#include <cstdlib>

using namespace std;


enum menu {
    WORK_WITH_TABLES = 1,
    SHOW_NONRESIDENT_PATIENTS = 2,
    ADD_PATIENT = 3,
    DELETE_PATIENT = 4,
    DELETE_NONRESIDENT_PATIENTS = 5,
    CHANGE_DIAGNOSIS = 6,
    FILTER_PATIENTS_BY_AGE = 7,
    GENERATE_RANDOM_PATIENTS = 8,
    CLEAR_CONSOLE = 9,
    EXIT = 0
};
int main() {

    printBanner("assets/banner.txt");
    showLoading(4000);


    while (true) {
        cout << "1. Работа с базой данных клиники" << endl;
        cout << "2. Вывести всех иногородних пациентов" << endl;
        cout << "3. Добавить пациента" << endl;
        cout << "4. Удалить пациента" << endl;
        cout << "5. Удалить всех иногородних пациентов" << endl;
        cout << "6. Поменять диагноз пациента" << endl;
        cout << "7. Фильтрация пациентов по возрасту" << endl;
        cout << "8. Сгенерировать 1000 случайных пациентов" << endl;
        cout << "9. Очистить консоль" << endl;
        cout << "0. Выход" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case WORK_WITH_TABLES:
                workWithTables();
                break;
            case SHOW_NONRESIDENT_PATIENTS:
                showNonresidentPatients();
                break;
            case ADD_PATIENT:
                addPatient();
                break;
            case DELETE_PATIENT:
                deletePatient();
                break;
            case DELETE_NONRESIDENT_PATIENTS:
                deleteNonresidentPatients();
                break;
            case CHANGE_DIAGNOSIS:
                changePatientDiagnosis();
                break;
            case FILTER_PATIENTS_BY_AGE:
                showPatientsByAge();
                break;
            case GENERATE_RANDOM_PATIENTS:
                addRandomPatients(1000);
                break;
            case CLEAR_CONSOLE:
                system("clear");
                break;
            case EXIT:
                exit(0);
            default:
                cout << "Неверный выбор" << endl;
                break;
        }
    }

    return 0;
}
