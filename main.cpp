#include "database.hpp"
#include "addpatients.hpp"
#include "cosmetics.hpp"

#include <cstdlib>

using namespace std;

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
        cout << "9. Выход" << endl;
        cout << "10. Очистить консоль" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                workWithTables();
                break;
            case 2:
                showNonresidentPatients();
                break;
            case 3:
                addPatient();
                break;
            case 4:
                deletePatient();
                break;
            case 5:
                deleteNonresidentPatients();
                break;
            case 6:
                changePatientDiagnosis();
                break;
            case 7:
                showPatientsByAge();
                break;
            case 8:
                addRandomPatients(1000);
                break;
            case 9:
                return 0;
            case 10:
                system("clear");
        }
    }

    return 0;
}
