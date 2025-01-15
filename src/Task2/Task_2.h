#ifndef TASK_2_H
#define TASK_2_H

#include <limits>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void StringInput(char*, int);
int numOfStructs();
Student* CreateStructsArray(int&);
void FillStructsArray(Student*&, int&);
void ShowStructsArray(Student*&, int&);
void AddStructsToArray(Student*&, int&);
void DeleteStruct(Student*&, int&);
void EditStruct(Student*&, int&);
void SortStructArray(Student*, int&); 
void Menu();
void DeleteStructsArray(Student*&);
Student* ReadFromFile(Student*&, int&);
void WriteInFile(Student*&, int&);

#endif