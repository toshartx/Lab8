#ifndef BCH_H
#define BCH_H

enum {
  MAX_SIZE = 124,
  MAX_HOURS = 23,
  MIN_HOURS = 0,
  MAX_MINUTES = 59,
  MIN_MINUTES = 0,
  MAX_SCHEDULES = 20,
  MIN_SCHEDULES = 1,
  MAX_SEATS = 100,
  IGNORED_CHARS = 1000,
};

enum Options {
  CREATE = 1,
  SHOW,
  ADD,
  SEARCH,
  DELETE,
  EDIT,
  SORT,
  EXIT,
  FREAD,
  FWRITE,
};

enum Fields {
  LEFT = 1,
  RIGHT = 5,
};

enum InputModes {
  FIXED,
  WITH_SPECIFED_ATTRIBUTE,
  DIALOGUE,
};

enum RailwayLineType {
  INTERNATIONAL,
  INTERREGIONAL,
  REGIONAL,
  URBAN,
};

enum UnionFlag {
  HOURS_FLAG,
  MINUTES_FLAG,
};

struct BelarusianRailway {
  char destination[MAX_SIZE];
  struct {
    short hours;
    short minutes;
  } DT; 
  struct {
    short hours;
    short minutes;
  } AT; 
  RailwayLineType lineType;
  union {
    int hours;
    int minutes;
  } Duration;
  UnionFlag flag;
};

#endif 
