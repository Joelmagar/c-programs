#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

#define Employee struct emp

// ---------- Linux getch ----------
int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(0, TCSANOW, &oldt);
    return ch;
}

// ---------- pause ----------
void pause_screen()
{
    int c;
    printf("\nPress ENTER to continue...");
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---------- clear ----------
void clear_screen()
{
    printf("\033[2J\033[H");
}

// ---------- structure ----------
struct emp
{
    int id;
    char name[100];
    float sal;
    char gender[10];
    char branch[50];
};

// ---------- UI ----------
void printChar(char ch,int n)
{
    while(n--) putchar(ch);
}

void printHead()
{
    clear_screen();
    printf("\t");
    printChar('=',65);
    printf("\n\t");
    printChar('=',16);
    printf("[EMPLOYEE] [MANAGEMENT] [SYSTEM]");
    printChar('=',16);
    printf("\n\t");
    printChar('=',65);
}

void welcome()
{
    printf("\n\n\tWELCOME TO EMPLOYEE MANAGEMENT SYSTEM\n");
    pause_screen();
}

// ---------- case insensitive search ----------
int containsIgnoreCase(const char *str, const char *key)
{
    char a[300], b[100];

    strcpy(a, str);
    strcpy(b, key);

    for(int i=0;a[i];i++) a[i]=tolower(a[i]);
    for(int i=0;b[i];i++) b[i]=tolower(b[i]);

    return strstr(a,b)!=NULL;
}

// ---------- CHECK IF ID EXISTS ----------
int idExists(FILE *fp, int id)
{
    Employee temp;
    rewind(fp);

    while (fread(&temp, sizeof(temp), 1, fp))
    {
        if (temp.id == id)
            return 1;
    }
    return 0;
}

// ================= MAIN =================
int main()
{
    FILE *fp;
    Employee e;
    int option;

    fp=fopen("employeeInfo.txt","rb+");
    if(fp==NULL)
        fp=fopen("employeeInfo.txt","wb+");

    char username[20], password[20];

    printHead();
    welcome();
    printHead();

    // ---------- LOGIN ----------
    printf("\nLogin Screen\n");
    printf("Username: ");
    scanf("%19s", username);
    while(getchar()!='\n');

    printf("Password: ");
    int i=0;
    char ch;

    while(1)
    {
        ch=getch();
        if(ch=='\n' || ch=='\r') break;

        if(ch==127 || ch==8)
        {
            if(i>0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++]=ch;
            printf("*");
        }
    }
    password[i]='\0';
    printf("\n");

    if(strcmp(username,"admin")==0 && strcmp(password,"pass")==0)
    {
        while(1)
        {
            printHead();
            printf("\n1.Add  2.Delete  3.Display  4.Search  0.Exit");
            printf("\nOption: ");
            scanf("%d",&option);
            while(getchar()!='\n');

            if(option==0) break;

            switch(option)
            {
                // ---------- ADD ----------
                case 1:
                {
                    do {
                        printf("ID: ");
                        scanf("%d",&e.id);
                        while(getchar()!='\n');

                        if(idExists(fp, e.id))
                            printf("Error: ID already exists! Try again.\n");

                    } while(idExists(fp, e.id));

                    printf("Name: ");
                    fgets(e.name,100,stdin);
                    e.name[strcspn(e.name,"\n")]=0;

                    printf("Gender: ");
                    fgets(e.gender,10,stdin);
                    e.gender[strcspn(e.gender,"\n")]=0;

                    printf("Branch: ");
                    fgets(e.branch,50,stdin);
                    e.branch[strcspn(e.branch,"\n")]=0;

                    printf("Salary: ");
                    scanf("%f",&e.sal);
                    while(getchar()!='\n');

                    fseek(fp,0,SEEK_END);
                    fwrite(&e,sizeof(e),1,fp);

                    printf("Employee saved successfully!");
                    pause_screen();
                    break;
                }

                // ---------- DELETE ----------
                case 2:
                {
                    int id, found=0;
                    FILE *temp=fopen("temp.dat","wb");

                    printf("Enter ID to delete: ");
                    scanf("%d",&id);
                    while(getchar()!='\n');

                    rewind(fp);
                    while(fread(&e,sizeof(e),1,fp))
                    {
                        if(e.id==id)
                            found=1;
                        else
                            fwrite(&e,sizeof(e),1,temp);
                    }

                    fclose(fp);
                    fclose(temp);

                    remove("employeeInfo.txt");
                    rename("temp.dat","employeeInfo.txt");

                    fp=fopen("employeeInfo.txt","rb+");

                    if(found)
                        printf("Employee deleted successfully.");
                    else
                        printf("Employee not found.");

                    pause_screen();
                    break;
                }

                // ---------- DISPLAY ----------
                case 3:
                {
                    rewind(fp);
                    printf("\n\n---- Employee List ----\n");

                    while(fread(&e,sizeof(e),1,fp))
                    {
                        printf("\nID: %d", e.id);
                        printf("\nName: %s", e.name);
                        printf("\nGender: %s", e.gender);
                        printf("\nBranch: %s", e.branch);
                        printf("\nSalary: %.2f", e.sal);
                        printf("\n-----------------------");
                    }

                    pause_screen();
                    break;
                }

                // ---------- SEARCH ----------
                case 4:
                {
                    int found=0;
                    char key[100];

                    printf("Enter ID or Name: ");
                    fgets(key,100,stdin);
                    key[strcspn(key,"\n")]=0;

                    rewind(fp);

                    while(fread(&e,sizeof(e),1,fp))
                    {
                        if(atoi(key)==e.id || containsIgnoreCase(e.name,key))
                        {
                            printf("\n\nID: %d", e.id);
                            printf("\nName: %s", e.name);
                            printf("\nGender: %s", e.gender);
                            printf("\nBranch: %s", e.branch);
                            printf("\nSalary: %.2f", e.sal);
                            printf("\n-----------------------");
                            found=1;
                        }
                    }

                    if(!found)
                        printf("Employee not found.");

                    pause_screen();
                    break;
                }

                default:
                    printf("Invalid option!");
                    pause_screen();
            }
        }
    }
    else
    {
        printf("\nLogin Failed\n");
        pause_screen();
    }

    fclose(fp);
    return 0;
}