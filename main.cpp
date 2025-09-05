#include "database.hpp"
#include "filesystem.hpp"

using namespace std;


int main() {

    while (true) {
        cout << "1. Создать таблицу" << endl;
        cout << "2. Удалить таблицу" << endl;
        cout << "3. Показать таблицы" << endl;
        cout << "4. Показать информацию в таблице" << endl;
        cout << "5. Выход" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
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
                return 0;
            default:
                cout << "Неверный выбор" << endl;
        }
    }

    return 0;
}
