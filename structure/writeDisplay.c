// wap to take name , age , marks , grades of 2 students from user using
// structure

#include <stdio.h>
#include <string.h>
struct student {
  char name[20];
  int age;
  float marks;
  char grade[5];
};

int main() {
  struct student studentData[2];

  for (int i = 0; i < 2; i++) {
    printf("Enter name : ");
    fgets(studentData[i].name, sizeof(studentData[i].name), stdin);
    studentData[i].name[strcspn(studentData[i].name, "\n")] = '\0';
    printf("Enter age : ");
    scanf("%d", &studentData[i].age);
    printf("Enter marks: ");
    scanf("%f", &studentData[i].marks);
    printf("Enter grade: ");
    scanf("%s", studentData[i].grade);
    printf("------------------------------\n");

    getchar();
  }
  for (int i = 0; i < 2; i++) {
    printf("Name is : %s \nAge is : %d \nMarks is : %.2f \nGrade is : %s \n",
           studentData[i].name, studentData[i].age, studentData[i].marks,
           studentData[i].grade);

    printf("\n ------------------------------ \n");
  }
  return 0;
}
