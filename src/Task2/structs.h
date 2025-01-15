#ifndef STRUCTS_H
#define STRUCTS_H

enum {
  MAX_SIZE = 128,
  MAX_EMAIL_SIZE = 32,
  MAX_PHONE_SIZE = 16,
  MAX_GROUPNAME_SIZE = 8,
  MIN_AVERAGE_MARK = 1,
  MAX_AVERAGE_MARK = 10,
  MIN_PROFIT = 500,
  MAX_PROFIT = 5000,
  MAX_STUDENTS = 50,
  IGNORED_CHARS = 1000,
};

enum Options {
  CREATE = 1,
  SHOW,
  ADD,
  DELETE,
  EDIT,
  SORT,
  EXIT,
  FREAD,
  FWRITE
};

struct Student {
  char fullName[MAX_SIZE];
  char groupName[MAX_GROUPNAME_SIZE];
  float averageMark;
  int profit;
  union {
    char phone[MAX_PHONE_SIZE];
    char email[MAX_EMAIL_SIZE];
  } contactInfo;
};

#endif