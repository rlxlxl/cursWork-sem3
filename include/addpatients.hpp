#pragma once

#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sqlite3.h>

using namespace std;


void addRandomPatients(int count);
string generateRandomName();
string generateRandomDiagnosisWithCode();
string generateRandomLocation();
string generateRandomGender();
int generateRandomAge();
vector<string> loadDiseasesFromFile();