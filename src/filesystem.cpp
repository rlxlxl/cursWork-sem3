#include "filesystem.hpp"


void getDbFiles(vector<string>& dbFiles) {
    for (const auto& entry : filesystem::directory_iterator(".")) {
        if (entry.path().extension() == ".db") {
            dbFiles.push_back(entry.path().filename().string());
        }
    }
}