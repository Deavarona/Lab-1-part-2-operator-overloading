#pragma once
#include <iostream>
#include <conio.h>
#include "Matrix.h"
using namespace std;

const int SIZE_OF_MATRIX = 15;
const int RAND_INTERVAL = 30;

int inputNaturalNumber();
void fillingMatrixMenu(Matrix&);

void showMenuOperationsWithMatrix();
void operationsWithMatrix(Matrix matrix);

void unionSets(Matrix first_matrix);