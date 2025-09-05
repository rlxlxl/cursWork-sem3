#pragma once
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <algorithm>
using namespace std;

extern vector<string> dbNames;

void createTable();
void deleteTable();
void showTables();
void showTableInfo();