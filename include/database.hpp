#pragma once

#include <sqlite3.h>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <format>

using namespace std;

void workWithTables();
void initializeTables();
void createTable();
void deleteTable();
void showTables();
void showTableInfo();
void showNonresidentPatients();
void deleteNonresidentPatients();
void addPatient();
void deletePatient();
void changePatientDiagnosis();
void showPatientsByAge();