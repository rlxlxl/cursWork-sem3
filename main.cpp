#include "database.hpp"
#include "filesystem.hpp"

using namespace std;


int main() {

    while (true) {
        cout << "1. Создать таблицу" << endl;
        cout << "2. Удалить таблицу" << endl;
        cout << "3. Выход" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            createTable();
        } else if (choice == 2) {
            deleteTable();
        } else {
            break;
        }
    }

    return 0;
}
