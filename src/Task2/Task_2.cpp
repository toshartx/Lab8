#include "Task_2.h"

int main() {
  Menu();
  return 0;
}

void Menu() {
  bool restartFlag = true;
  std::cout << "Добро пожаловать в приложение:\n";
  while (restartFlag) {
    static int numOfStudents = 0;
    static Student* info = nullptr;
    std::cout << "Выберите опции:\n"
              "1 - Создать и заполнить массив структур\n"
              "2 - Просмотреть содержимое структур\n"
              "3 - Дополнить массив новыми структурами\n"
              "4 - Удаление структуры\n"
              "5 - Изменение структуры в массиве\n"
              "6 - Показать список очередности предоставления мест студентам\n"
              "7 - Выход\n"
              "8 - Чтение данных из файла\n"
              "9 - Запись данных в файл\n";
    int option;
    while (!(std::cin >> option) || std::cin.peek() != '\n' || option > FWRITE || option < CREATE) {
      std::cin.clear();
      std::cin.ignore(IGNORED_CHARS, '\n');
      std::cout << "Нет такой опции. Повторите попытку:\n";
    }
    std::cin.ignore(IGNORED_CHARS, '\n');
    switch (option) {
      case CREATE:
        if (info != nullptr) {
          std::cout << "Массив структур уже создан.\n";
          break;
        }
        numOfStudents = numOfStructs();
        info = CreateStructsArray(numOfStudents);
        FillStructsArray(info, numOfStudents);
        break;
      case SHOW:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        ShowStructsArray(info, numOfStudents);
        break;
      case ADD:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        AddStructsToArray(info, numOfStudents);
        break;
      case DELETE:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        DeleteStruct(info, numOfStudents);
        break;
      case EDIT:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        EditStruct(info, numOfStudents);
        break;
      case SORT:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        SortStructArray(info, numOfStudents);
        break;
      case EXIT:
        DeleteStructsArray(info);
        restartFlag = false;
        break;
      case FREAD:
        info = ReadFromFile(info, numOfStudents);
        break;
      case FWRITE:
        WriteInFile(info, numOfStudents);
        break;
    }
  }
}

int numOfStructs() {
  int num = 0; 
  std::cout << "Введите число студентов (1-50): ";
  while (!(std::cin >> num) || std::cin.peek() != '\n' || num > MAX_STUDENTS || num < 1) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Число студентов не может быть таким. Повторите попытку:\n";
  }
  std::cin.ignore(IGNORED_CHARS, '\n');
  return num;
}

Student* CreateStructsArray(int& numOfStudents) {
  Student* info = new Student[numOfStudents];
  std::cout << "Студент добавился успешно\n";
  return info;
}

void StringInput(char* stringInfo, int size) {
  std::string line;
  std::getline(std::cin, line);
  strncpy(stringInfo, line.c_str(), size - 1);
  stringInfo[size - 1] = '\0'; 
}

float AverageMarkInput() {
  float num = 0; 
  while (!(std::cin >> num) || std::cin.peek() != '\n' || num > MAX_AVERAGE_MARK || num < MIN_AVERAGE_MARK) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Средний балл не может быть таким. Повторите попытку:\n";
  }
  return num;
}

int ProfitInput() {
  int num = 0;
  while (!(std::cin >> num) || std::cin.peek() != '\n' || num < MIN_PROFIT || num > MAX_PROFIT) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Считается, что доход больше 500/меньше 5000. Повторите попытку:\n";
  }
  std::cin.ignore(IGNORED_CHARS, '\n');
  return num;
}

void FillStructsArray(Student*& info, int& numOfStudents) {
  for (int i = 0; i < numOfStudents; ++i) {
    std::cout << "Введите ФИО студента:\n";
    StringInput(info[i].fullName, MAX_SIZE);

    std::cout << "Введите номер группы студента (меньше 8 символов):\n";
    StringInput(info[i].groupName, MAX_GROUPNAME_SIZE);

    std::cout << "Введите средний балл студента (1-10):\n";
    info[i].averageMark = AverageMarkInput();

    std::cout << "Введите доход на члена семьи\n";
    info[i].profit = ProfitInput();

    std::cout << "Введите контакты (телефон/e-mail):\n";
    StringInput(info[i].contactInfo.email, MAX_EMAIL_SIZE);
  }
}

void ShowStructsArray(Student*& info, int& numOfStudents) {
  for (int i = 0; i < numOfStudents; ++i) {
    std::cout << "Cтудент " << i + 1 << "\n"
            "ФИО: " << info[i].fullName << "\n"
            "Группа: " << info[i].groupName << "\n"
            "Средний балл: " << info[i].averageMark << "\n"
            "Доход на члена семьи: " << info[i].profit << "\n"
            "Контакты: " << info[i].contactInfo.email << "\n";
    std::cout << "---------------------------------------------------------------------\n";
  }
}

void AddStructsToArray(Student*& info, int& numOfStudents) {
  std::cout << "Введите количество добавляемых структур:\n";
  int add = numOfStructs();

  Student* temp = new Student[numOfStudents];
  for (int i = 0; i < numOfStudents; ++i) {
    temp[i] = info[i];
  }
  delete[] info;

  info = temp;
  delete[] temp;
  temp = nullptr;

  for (int i = numOfStudents; i < numOfStudents + add; ++i) {
    std::cout << "Введите ФИО студента:\n";
    StringInput(info[i].fullName, MAX_SIZE);
    std::cout << "Введите номер группы студента (меньше 8 символов):\n";
    StringInput(info[i].groupName, MAX_GROUPNAME_SIZE);
    std::cout << "Введите средний балл студента (1-10):\n";
    info[i].averageMark = AverageMarkInput();
    std::cout << "Введите доход на члена семьи\n";
    info[i].profit = ProfitInput();
    std::cout << "Введите контакты (телефон/e-mail):\n";
    StringInput(info[i].contactInfo.email, MAX_EMAIL_SIZE);
  }
  numOfStudents += add;
}

void DeleteStruct(Student*& info, int& numOfStudents) {
  int index;
  std::cout << "Введите номер удаляемой структуры (1 - " << numOfStudents << ")\n";
  while (!(std::cin >> index) || std::cin.peek() != '\n' || index < 1 || index > numOfStudents) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Структуры с таким индексом нет. Повторите попытку:\n";
  }
  for (int i = index - 1; i < numOfStudents - 1; ++i) {
    info[i] = info[i + 1];
  }
  Student* temp = new Student[numOfStudents - 1];
  for (int i = 0; i < numOfStudents - 1; ++i) {
    temp[i] = info[i];
  }
  delete[] info;
  info = temp;
  numOfStudents--;
  
  std::cout << "Структура " << index << " успешно удалена\n";
}

void EditStruct(Student*& info, int& numOfStudents) {
  int index;
  std::cout << "Введите номер структуры (1 - " << numOfStudents << ")\n";
  while (!(std::cin >> index) || std::cin.peek() != '\n' || index < 1 || index > numOfStudents) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Структуры с таким индексом нет. Повторите попытку:\n";
  }
  std::cin.ignore(IGNORED_CHARS, '\n');
  int i = index - 1;
  std::cout << "Обновите данные существующего студента!\n";
  std::cout << "Введите ФИО студента:\n";
  StringInput(info[i].fullName, MAX_SIZE);

  std::cout << "Введите номер группы студента (меньше 8 символов):\n";
  StringInput(info[i].groupName, MAX_GROUPNAME_SIZE);

  std::cout << "Введите средний балл студента (1-10):\n";
  info[i].averageMark = AverageMarkInput();

  std::cout << "Введите доход на члена семьи\n";
  info[i].profit = ProfitInput();

  std::cout << "Введите контакты (телефон/e-mail):\n";
  StringInput(info[i].contactInfo.email, MAX_EMAIL_SIZE);

  std::cout << "Данные успешно обновлены!\n";
}

void SortStructArray(Student* info, int& numOfStudents) {
  for (int i = 1; i < numOfStudents; ++i) {
    Student key = info[i];
    int j = i - 1;
    while (j >= 0) {
      if (info[j].profit < 2 * MIN_PROFIT && key.profit >= 2 * MIN_PROFIT) {
        break;
      }
      if (info[j].profit >= 2 * MIN_PROFIT && key.profit < 2 * MIN_PROFIT) {
        info[j + 1] = info[j];
        --j;
        continue;
      }
      if (info[j].averageMark < key.averageMark) {
        break;
      }
      info[j + 1] = info[j];
      --j;
    }
    info[j + 1] = key;
  }
}

void DeleteStructsArray(Student*& info) {
  delete[] info;
  info = nullptr;
}

Student* ReadFromFile(Student*& info, int& numOfStudents) {
  std::fstream fs("students.txt", std::ios::in);
  if (!fs.is_open()) {
    std::cerr << "Файл не был открыт!\n";
    return nullptr;
  }

  int count = 0;
  std::string line;
  while (std::getline(fs, line)) {
      count++;
  }
  fs.clear();
  fs.seekg(0, std::ios::beg);

  if (info == nullptr) {
    info = CreateStructsArray(count);
  } else {
    Student* temp = new Student[numOfStudents + count];
    for (int i = 0; i < numOfStudents + count; ++i) {
      temp[i] = info[i];
    }
    delete[] info;
    info = temp;
  }

  for (int i = numOfStudents; i < numOfStudents + count; ++i) {
    fs >> info[i].fullName >> info[i].groupName >> info[i].averageMark >> info[i].profit >> info[i].contactInfo.email;
    fs.ignore(); 
  }

  numOfStudents += count;
  fs.close();
  return info;
}

void WriteInFile(Student*& info, int& numOfStudents) {
  std::fstream fs("students.txt", std::ios::out | std::ios::app);
  for (int i = 0; i < numOfStudents; ++i) {
    fs << info[i].fullName << " " << info[i].groupName << " " << info[i].averageMark << " " << info[i].profit << " " << info[i].contactInfo.email << '\n';
  }
  fs.close();
  std::cout << "Данные были успешно записаны!\n";
}