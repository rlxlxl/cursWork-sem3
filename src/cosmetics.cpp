#include "cosmetics.hpp"

void printBanner(const string& path) {
    ifstream file(path);
    if (!file) {
        cout << "Не удалось открыть файл " << path << endl;
        return;
    }

    string line;
    vector<string> lines;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    int start_row = 1;
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << lines[i] << endl;
    }
}


void showLoading(int duration_ms) {
    int total_steps = 40; // количество символов "="
    int step_time = duration_ms / total_steps;

    cout << "Загрузка: [                                        ] 0%" << flush;

    for (int i = 1; i <= total_steps; ++i) {
        // перемещаем курсор на начало прогресс-бара (после "Загрузка: [")
        cout << "\rЗагрузка: [";
        for (int j = 0; j < i; ++j) cout << "=";
        for (int j = i; j < total_steps; ++j) cout << " ";
        // вывод процентов
        int percent = i * 100 / total_steps;
        cout << "] " << percent << "%" << flush;

        this_thread::sleep_for(chrono::milliseconds(step_time));
    }
    cout << endl;
}