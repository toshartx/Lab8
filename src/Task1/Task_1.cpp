#include "Task_1.h"

int main() {
  Menu();
  return 0;
}

int numOfStructs() {
  int num = 0; 
  std::cout << "Введите число расписаний (поездов): ";
  while (!(std::cin >> num) || std::cin.peek() != '\n' || num > MAX_SCHEDULES || num < MIN_SCHEDULES) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    if (num > MAX_SCHEDULES)
      std::cout << "Число расписаний превысило допустимое (20). Повторите попытку:\n";
    if (num < MIN_SCHEDULES)
      std::cout << "Число расписаний не может быть неположительным. Повторите попытку:\n";
  }
  return num;
}

void DestinationInput(char* destination) {
  std::string line;
  std::cin.ignore(IGNORED_CHARS, '\n');
  std::getline(std::cin, line);
  strncpy(destination, line.c_str(), MAX_SIZE - 1);
  destination[MAX_SIZE - 1] = '\0'; 
}

void TimeInput(short* hours, short* minutes) {
  std::cout << "Введите время в формате Часы Минуты: ";
  while (!(std::cin >> *hours >> *minutes) || std::cin.peek() != '\n' || *hours > MAX_HOURS || *hours < MIN_HOURS ||
          *minutes > MAX_MINUTES || *minutes < MIN_MINUTES) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Время введено некорректно, повторите попытку\n";
  }
}

void TimeInput(short* minutes) {
  std::cout << "Введите время в минутах: ";
  while (!(std::cin >> *minutes) || std::cin.peek() != '\n' || *minutes < MIN_MINUTES) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Время введено некорректно, повторите попытку\n";
  }
}

void RailwayTypeInput(BelarusianRailway*& info, int i) {
  int choose;
  while (!(std::cin >> choose) || std::cin.peek() != '\n' || choose > URBAN || choose < INTERNATIONAL) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Недопустимый тип линий. Повторите попытку:\n";
  }
  info[i].lineType = (RailwayLineType)choose;
}

void DurationDefine(BelarusianRailway*& info, int i) {
  short delta;
  short minutesOfDeparture = info[i].DT.minutes + (MAX_MINUTES + 1) * info[i].DT.hours;
  short minutesOfArrival = info[i].AT.minutes + (MAX_MINUTES + 1) * info[i].AT.hours;
  if (minutesOfDeparture > minutesOfArrival) {
    delta = (MAX_HOURS + 1) * (MAX_MINUTES + 1) - (minutesOfDeparture - minutesOfArrival);   // в 24 часах 1440 минут
  } else {
    delta = minutesOfArrival - minutesOfDeparture;
  }
  if (delta > MAX_MINUTES) {
    info[i].Duration.hours = delta / (MAX_MINUTES + 1);
    info[i].flag = HOURS_FLAG;
  } else {
    info[i].Duration.minutes = delta % (MAX_MINUTES + 1);
    info[i].flag = MINUTES_FLAG;
  }
}

bool CheckSampleParameters(BelarusianRailway*& info, int& numOfSchedules, int i) {
  bool checkFlag = true;
  for (int j = 0; j < i; ++j) {
    if (info[i].AT.minutes == info[j].AT.minutes && !(strcmp(info[i].destination, info[j].destination))) {
      checkFlag = false;
      numOfSchedules = i + 1;
      info = (BelarusianRailway*)realloc(info, numOfSchedules * sizeof(BelarusianRailway));
      if (info == nullptr) {
        std::cerr << "Ошибка выделения памяти\n";
        exit(1);
      }
      break;
    }
  }
  return !checkFlag;
}

bool YesOrNoInput() {
  bool flag = false; 
  std::cout << "Введите 1 - если Да, 0 - если Нет: ";
  while (!(std::cin >> flag) || std::cin.peek() != '\n') {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Команда не распознана, повторите попытку\n";
  }
  return flag;
}

BelarusianRailway* CreateStructsArray(int& numOfSchedules) {
  BelarusianRailway* info = (BelarusianRailway*)malloc(sizeof(BelarusianRailway) * numOfSchedules);
  if (!info) {
    std::cout << "Ошибка выделения памяти\n";
    exit(1);
  }
  std::cout << "Расписания были успешно созданы!\n";
  return info;
}

void FillStructsArray(BelarusianRailway*& info, int& numOfSchedules) {
  short choose;
  std::cout << "Введите режим ввода структур:\n"
            "0 - ввод заранее заданного количества структур\n"
            "1 - ввод структур до появления одинакового города и времени прибытия\n"
            "2 - ввод до тех пор, пока вы не захотите закончить\n";
  while (!(std::cin >> choose) || std::cin.peek() != '\n' || choose > DIALOGUE || choose < FIXED) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Нет такого режима ввода. Повторите попытку:\n";
  }
  switch (choose) {
    case FIXED:
      for (int i = 0; i < numOfSchedules; ++i) {
        std::cout << "Введите пункт назначения:\n";
        DestinationInput(info[i].destination);
        std::cout << "Введите время отправления:\n";
        TimeInput(&info[i].DT.hours, &info[i].DT.minutes);
        std::cout << "Введите время прибытия:\n";
        TimeInput(&info[i].AT.hours, &info[i].AT.minutes);
        std::cout << "Введите тип ж/д линии\n"
                  "0 - если международные\n"
                  "1 - если межрегиональные\n"
                  "2 - если региональные\n"
                  "3 - если городские\n";
        RailwayTypeInput(info, i);
        DurationDefine(info, i);
      }
      break;
    case WITH_SPECIFED_ATTRIBUTE:
      for (int i = 0; i < numOfSchedules; ++i) {
        std::cout << "Введите пункт назначения:\n";
        DestinationInput(info[i].destination);
        std::cout << "Введите время отправления:\n";
        TimeInput(&info[i].DT.hours, &info[i].DT.minutes);
        std::cout << "Введите время прибытия:\n";
        TimeInput(&info[i].AT.hours, &info[i].AT.minutes);
        std::cout << "Введите тип ж/д линии\n"
                  "0 - если международные\n"
                  "1 - если межрегиональные\n"
                  "2 - если региональные\n"
                  "3 - если городские\n";
        RailwayTypeInput(info, i);
        DurationDefine(info, i);
        if (CheckSampleParameters(info, numOfSchedules, i)) {
          std::cout << "Были введены одинаковые параметры, ввод прекращается.\n";
          break;
        }
      }
      break;
    case DIALOGUE:
      for (int i = 0; i < numOfSchedules; ++i) {
        std::cout << "Введите пункт назначения:\n";
        DestinationInput(info[i].destination);
        std::cout << "Введите время отправления:\n";
        TimeInput(&info[i].DT.hours, &info[i].DT.minutes);
        std::cout << "Введите время прибытия:\n";
        TimeInput(&info[i].AT.hours, &info[i].AT.minutes);
        std::cout << "Введите тип ж/д линии\n"
                  "0 - если международные\n"
                  "1 - если межрегиональные\n"
                  "2 - если региональные\n"
                  "3 - если городские\n";
        RailwayTypeInput(info, i);
        DurationDefine(info, i);
        std::cout << "Вы хотите продолжить вводить расписания??\n";
        if (!YesOrNoInput()) {
          numOfSchedules = i + 1;
          info = (BelarusianRailway*)realloc(info, numOfSchedules * sizeof(BelarusianRailway));
          if (info == nullptr) {
            std::cerr << "Ошибка выделения памяти\n";
            exit(1);
          }
          break;
        }
      }
      break;
  }
}

void ShowStruct(BelarusianRailway*& info, int& numOfSchedules, int i) {
  std::cout << "Расписание " << i + 1 << "\n"
            "Пункт назначения: " << info[i].destination << "\n"
            "Время отправления: " << info[i].DT.hours << ":" << info[i].DT.minutes << "\n"
            "Время прибытия: " << info[i].AT.hours << ":" << info[i].AT.minutes << "\n"
            "Тип ж/д линии: ";
  switch (info[i].lineType) {
    case INTERNATIONAL:
      std::cout << "International\n";
      break;
    case INTERREGIONAL:
      std::cout << "Interregional\n";
      break;
    case REGIONAL:
      std::cout << "Regional\n";
      break;
    case URBAN:
      std::cout << "Urban\n";
      break;
  }
  std::cout << "Длительность поездки: ";
  if (info[i].flag == HOURS_FLAG) {
    std::cout << "~" << info[i].Duration.hours << " часа\n";
  } else {
    std::cout << info[i].Duration.minutes << " минут\n";
  }
}

void ShowStructsArray(BelarusianRailway*& info, int& numOfSchedules) {
  for (int i = 0; i < numOfSchedules; ++i) {
    ShowStruct(info, numOfSchedules, i);
  }
}

void AddStructsToArray(BelarusianRailway*& info, int& numOfSchedules) {
  numOfSchedules++;
  info = (BelarusianRailway*)realloc(info, numOfSchedules * sizeof(BelarusianRailway));
  if (info == nullptr) {
    std::cerr << "Ошибка выделения памяти\n";
    exit(1);
  }
  int addedStructIndex = numOfSchedules - 1;
  std::cout << "Введите данные о новом расписании!\n";
  std::cout << "Введите пункт назначения:\n";
  DestinationInput(info[addedStructIndex].destination);
  std::cout << "Введите время отправления:\n";
  TimeInput(&info[addedStructIndex].DT.hours, &info[addedStructIndex].DT.minutes);
  std::cout << "Введите время прибытия:\n";
  TimeInput(&info[addedStructIndex].AT.hours, &info[addedStructIndex].AT.minutes);
  std::cout << "Введите тип ж/д линии\n"
            "0 - если международные\n"
            "1 - если межрегиональные\n"
            "2 - если региональные\n"
            "3 - если городские\n";
  RailwayTypeInput(info, addedStructIndex);
  DurationDefine(info, addedStructIndex);
}

void DeleteStruct(BelarusianRailway*& info, int& numOfSchedules) {
  int index;
  std::cout << "Введите номер структуры (1 - " << numOfSchedules << ")\n";
  while (!(std::cin >> index) || std::cin.peek() != '\n' || index < MIN_SCHEDULES || index > numOfSchedules) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Структуры с таким индексом нет. Повторите попытку:\n";
  }
  for (int i = index - 1; i < numOfSchedules - 1; ++i) {
    info[i] = info[i + 1];
  }
  numOfSchedules--;
  info = (BelarusianRailway*)realloc(info, numOfSchedules * sizeof(BelarusianRailway));
  if (info == nullptr) {
    std::cerr << "Ошибка выделения памяти\n";
    exit(1);
  }
  std::cout << "Структура " << index << " успешно удалена\n";
}

void SearchStruct(BelarusianRailway*& info, int& numOfSchedules) {
  int index;
  std::cout << "Введите элемент структуры из следующих:\n"
            "1 - название пункта назначения\n"
            "2 - время отправления\n"
            "3 - время прибытия\n"
            "4 - длительность поездки\n"
            "5 - флаг поездки с определенной длительностью ((</>) часа)\n";
  std::cin.ignore(IGNORED_CHARS, '\n');
  while (!(std::cin >> index) || std::cin.peek() != '\n' || index > RIGHT || index < LEFT) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Такого элемента в структуре нет. Повторите попытку:\n";
  }
  switch (index) {
    case 1: {
      char searchDestination[MAX_SIZE];
      DestinationInput(searchDestination);
      for (int i = 0; i < numOfSchedules; ++i) {
        if (!(strcmp(info[i].destination, searchDestination))) {
          ShowStruct(info, numOfSchedules, i);
        }
      }
      break;
    }
    case 2: {
      short searchDTHours, searchDTMinutes;
      TimeInput(&searchDTHours, &searchDTMinutes);
      for (int i = 0; i < numOfSchedules; ++i) {
        if (searchDTHours == info[i].DT.hours && searchDTMinutes == info[i].DT.minutes) {
          ShowStruct(info, numOfSchedules, i);
        }
      }
      break;
    }
    case 3: {
      short searchATHours, searchATMinutes;
      TimeInput(&searchATHours, &searchATMinutes);
      for (int i = 0; i < numOfSchedules; ++i) {
        if (searchATHours == info[i].AT.hours && searchATMinutes == info[i].AT.minutes) {
          ShowStruct(info, numOfSchedules, i);
        }
      }
      break;
    }
    case 4: {
      short searchDuration;
      bool checkFlag;
      std::cout << "Введите длительность поездки в минутах:\n";
      TimeInput(&searchDuration);
      if (searchDuration > MAX_MINUTES) {
        checkFlag = HOURS_FLAG;
        searchDuration /= (MAX_MINUTES + 1);
      } else {
        checkFlag = MINUTES_FLAG;
      }
      for (int i = 0; i < numOfSchedules; ++i) {
        if (checkFlag == info[i].flag && searchDuration == info[i].Duration.hours) {
          ShowStruct(info, numOfSchedules, i);
        }
      }
      break;
    }
    case 5: {
      short searchDuration;
      bool checkFlag;
      std::cout << "Введите длительность поездки в минутах:\n";
      TimeInput(&searchDuration);
      if (searchDuration > MAX_MINUTES) {
        checkFlag = HOURS_FLAG;
      } else {
        checkFlag = MINUTES_FLAG;
      }
      for (int i = 0; i < numOfSchedules; ++i) {
        if (checkFlag == info[i].flag) {
          ShowStruct(info, numOfSchedules, i);
        }
      }
      break;
    }
  }
}

void EditStruct(BelarusianRailway*& info, int& numOfSchedules) {
  int index;
  std::cout << "Введите номер структуры (1 - " << numOfSchedules << ")\n";
  while (!(std::cin >> index) || std::cin.peek() != '\n' || index < MIN_SCHEDULES || index > numOfSchedules) {
    std::cin.clear();
    std::cin.ignore(IGNORED_CHARS, '\n');
    std::cout << "Структуры с таким индексом нет. Повторите попытку:\n";
  }
  std::cout << "Обновите данные существующего расписания!\n";
  std::cout << "Введите пункт назначения:\n";
  DestinationInput(info[index - 1].destination);
  std::cout << "Введите время отправления:\n";
  TimeInput(&info[index - 1].DT.hours, &info[index - 1].DT.minutes);
  std::cout << "Введите время прибытия:\n";
  TimeInput(&info[index - 1].AT.hours, &info[index - 1].AT.minutes);
  std::cout << "Введите тип ж/д линии\n"
            "0 - если международные\n"
            "1 - если межрегиональные\n"
            "2 - если региональные\n"
            "3 - если городские\n";
  RailwayTypeInput(info, index);
  DurationDefine(info, index);
  std::cout << "Расписание было обновлено!\n";
}

void SortStructArray(BelarusianRailway*& info, int& numOfSchedules) {
  std::cout << "Отсортированные расписания по длительности поездки (по убыванию):\n";
  for (int i = 1; i < numOfSchedules; ++i) {
    BelarusianRailway tempStruct = info[i];
    int j = i - 1;
    int tempDuration = tempStruct.flag == HOURS_FLAG ? tempStruct.Duration.hours * 60 : tempStruct.Duration.minutes;
    while (j >= 0) {
      int currentDuration = info[j].flag == HOURS_FLAG ? info[j].Duration.hours * 60 : info[j].Duration.minutes;
      if (currentDuration < tempDuration) {
        info[j + 1] = info[j];
        j--;
      } else {
        break;
      }
    }
    info[j + 1] = tempStruct;
  }
  ShowStructsArray(info, numOfSchedules);
}

void Menu() {
  bool restartFlag = true;
  std::cout << "Добро пожаловать в приложение белорусской железной дороги:\n";
  while (restartFlag) {
    static BelarusianRailway* info = nullptr;
    static int numOfSchedules = 0;
    std::cout << "Выберите опции:\n"
              "1 - Создать и заполнить массив структур\n"
              "2 - Просмотреть содержимое структур\n"
              "3 - Дополнить массив новыми структурами\n"
              "4 - Поиск и вывод структур с заданным значением параметра\n"
              "5 - Удаление структуры\n"
              "6 - Изменение структуры в массиве\n"
              "7 - Сортировка расписаний по времени (по убыванию)\n"
              "8 - Выход\n"
              "9 - Чтение из бинарного файла\n"
              "10 - Запись в бинарный файл\n";
    int option;
    while (!(std::cin >> option) || std::cin.peek() != '\n' || option > FWRITE || option < CREATE) {
      std::cin.clear();
      std::cin.ignore(IGNORED_CHARS, '\n');
      std::cout << "Нет такой опции. Повторите попытку:\n";
    }
    switch (option) {
      case CREATE:
        if (info != nullptr) {
          std::cout << "Массив структур уже создан.\n";
          break;
        }
        numOfSchedules = numOfStructs();
        info = CreateStructsArray(numOfSchedules);
        FillStructsArray(info, numOfSchedules);
        break;
      case SHOW:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        ShowStructsArray(info, numOfSchedules);
        break;
      case ADD:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        AddStructsToArray(info, numOfSchedules);
        break;
      case SEARCH:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        SearchStruct(info, numOfSchedules);
        break;
      case DELETE:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        DeleteStruct(info, numOfSchedules);
        break;
      case EDIT:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        EditStruct(info, numOfSchedules);
        break;
      case SORT:
        if (info == nullptr) {
          std::cout << "Массив структур не создан.\n";
          break;
        }
        SortStructArray(info, numOfSchedules);
        break;
      case EXIT:
        DeleteStructsArray(info);
        restartFlag = false;
        break;
      case FREAD:
        info = ReadFromFile(info, numOfSchedules);
        break;
      case FWRITE:
        WriteInFile(info, numOfSchedules);
        break;
    }
  }
}

void DeleteStructsArray(BelarusianRailway*& info) {
  free(info);
}

BelarusianRailway* ReadFromFile(BelarusianRailway*& info, int& numOfSchedules) {
  std::fstream fs("schedules.bin", std::ios::in | std::ios::binary);
  if (!fs.is_open()) {
    std::cerr << "Файл не был открыт!\n";
    return nullptr;
  }
  
  fs.seekg(0, std::ios::end);
  int size = fs.tellg() / sizeof(BelarusianRailway);
  fs.seekg(0, std::ios::beg);

  if (info == nullptr) {
    info = CreateStructsArray(size);
  } else {
    info = (BelarusianRailway*)realloc(info, sizeof((numOfSchedules+size)*sizeof(BelarusianRailway)));
  }
  for (int i = 0; i < size; ++i) {
    fs.read((char*)&info[numOfSchedules + i], sizeof(BelarusianRailway));
  }
  numOfSchedules += size;
  fs.close();
  std::cout << "Чтение успешно!\n";
  return info;
}

void WriteInFile(BelarusianRailway*& info, int& numOfSchedules) {
  std::fstream fs("schedules.bin", std::ios::out | std::ios::binary | std::ios::app);
  for (int i = 0; i < numOfSchedules; ++i) {
    fs.write((char*)&info[i], sizeof(BelarusianRailway));
  }
  fs.close();
  std::cout << "Данные были успешно записаны!\n";
}

