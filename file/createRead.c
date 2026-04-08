// wap to add name roll and marks of five students in a  STUDENT.txt file and
// display students with more than 400 marks and students with name starting
// with letter a
#include <stdio.h>
#include <string.h>
struct student {

  int roll;
  char name[30];
  float marks;
};

int main() {
  struct student s[2];
  FILE *fp;
  fp = fopen("STUDENT.txt", "wb");
  if (fp == NULL) {
    printf("Something went wrong while accessing the file.");
    return 0;
  }
  // step:1 To store data of 5 students
  for (int i = 0; i < 2; i++) {

    printf("Enter the name of student no. %d \t", i + 1);
    fgets(s[i].name, 30, stdin);
    s[i].name[strcspn(s[i].name, "\n")] = '\0';
    printf("Enter the roll number of student  no. %d \t", i + 1);
    scanf("%d", &s[i].roll);

    printf("Enter the marks of student no. %d\t", i + 1);
    scanf("%f", &s[i].marks);
    getchar();

    // fprintf(fp, "%s %d %f\n", s[i].name, s[i].roll, s[i].marks);
    fwrite(&s[i], sizeof(s[i]), 1, fp);
  }
  fclose(fp);
  // step: 2 To display the student data with more than 400 marks
  fp = fopen("STUDENT.txt", "rb");
  printf("List of students with marks greater than 400");
  // while (fscanf(fp, "%[^\n] %d %f", s[0].name, &s[0].roll, &s[0].marks) !=
  //        EOF) {
  while (fread(&s[0], sizeof(s[0]), 1, fp)) {
    // if (s[0].name[0] == 'a' || s[0].name[0] == 'A')
    if (s[0].marks >= 400) {
      printf("\nName is %s , roll is %d , marks is %.2f ", s[0].name, s[0].roll,
             s[0].marks);
    }
  }
  fclose(fp);

  return 0;
}
