#pragma once
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

extern vector<string> dbNames;
void createDatabase();
void createTable(vector<string>& dbNames);
