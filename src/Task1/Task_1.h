#ifndef TASK_1_H
#define TASK_1_H

#include <limits>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "BCH.h"

void DestinationInput(char*);
void TimeInput(short*, short*);
void RailwayTypeInput(BelarusianRailway*&, int);
void DurationDefine(BelarusianRailway*&, int);
bool CheckSampleParameters(BelarusianRailway*&, int&, int);
bool YesOrNoInput();
int numOfStructs();
BelarusianRailway* CreateStructsArray(int&);
void FillStructsArray(BelarusianRailway*&, int&);
void ShowStructsArray(BelarusianRailway*&, int&);
void AddStructsToArray(BelarusianRailway*&, int&);
void SearchStruct(BelarusianRailway*&, int&);
void DeleteStruct(BelarusianRailway*&, int&);
void EditStruct(BelarusianRailway*&, int&);
void SortStructArray(BelarusianRailway*&, int&); // Сортировка вставкой по убыванию
void Menu();
void DeleteStructsArray(BelarusianRailway*&);
BelarusianRailway* ReadFromFile(BelarusianRailway*&, int&);
void WriteInFile(BelarusianRailway*&, int&);

#endif // TASK_1_H
