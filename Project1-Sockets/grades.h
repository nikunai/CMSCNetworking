#ifndef GRADES_H
#define GRADES_H
struct Grades{
  char _semester[10]; //HOWTO: All caps for semester, 4 digit year code
                      //       SPRING2024, AUGUST2024, FALL2024, WINTER2024
  char _subject[4];   //enter the 4 letter code: CMSC, JPNS,.. or 3 letter code
  char _grade[1];     //enter letter grade: A, B, C, D ,F, W, D
  char _creditHour[2];//Enter credit hours. No decimals. So for 3 credit hours,
                      //enter 30. for 3.5->35. Backend will do e+1 or e-1.
};
#endif
