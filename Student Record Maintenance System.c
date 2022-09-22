#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void menu();
void insert();
void display();
void search();
void modify();
void deletee();
struct student
{
    char name[20];
    char fathername[20];
    char dob[10];
    int Univrollno;
    char course[20];
    char branch[20];
};
int main()
{
    printf("<--:Student Record Management System:-->\n");
    printf("Press any key to continue....");
    getch();
    menu();
    return 0;
}
void menu()
{
    int choice;
    system("cls");
    printf("<--:MENU:-->\n");
    printf("Enter appropriate number to perform following task....");
    printf("\n1 : Add Record\n");
    printf("2 : View Record\n");
    printf("3 : Search Record\n");
    printf("4 : Modify Record\n");
    printf("5 : Delete\n");
    printf("6 : Exit\n");
    printf("Enter your choice\n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        insert();
        break;

    case 2:
        display();
        break;

    case 3:
        search();
        break;

    case 4:
        modify();
        break;

    case 5:
        deletee();
        break;

    case 6:
        exit(1);
        break;

    default:
        printf("Invalid Choice...please try again!!!");
    }
}
void insert()
{
    FILE *fp;
    struct student std;
    char another ='y';
    system("cls");

    fp = fopen("record.txt","ab+");
    if(fp == NULL){

        printf("File does not have data");
        exit(1);
    }
    fflush(stdin);
    while(another == 'y')
    {
        printf("<--:ADD RECORD:-->");
        printf("Enter details of student...\n");
        printf("Enter Name : ");
        gets(std.name);
        printf("Enter Father's name : ");
        gets(std.fathername);
        printf("Enter Date of Birth[DD/MM/YY] : ");
        gets(std.dob);
        fflush(stdin);
        printf("Enter University Roll No : ");
        scanf("%d",&std.Univrollno);
        fflush(stdin);
        printf("Enter Course : ");
        gets(std.course);
        printf("Enter Branch : ");
        gets(std.branch);
        fwrite(&std,sizeof(std),1,fp);
        printf("Want to add another record then press 'y' otherwise press 'n'\n");
        fflush(stdin);
        another = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    printf("Press any key to continue....");
    getch();
    menu();
}
void display()
{
    FILE *fp;
    int i=1,j;
    struct student std;
    system("cls");
    printf("<--:SHOWING  RECORD:-->\n");
    printf("S.No    Name of Student          Father's Name         Date of Birth   Univ Roll No    Course     Branch\n");
    printf("*********************************************************************************************************\n");
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        printf("File does not have data...\n");
        exit(1);
    }
    while(fread(&std,sizeof(std),1,fp) == 1){
        printf("%-8d%-25s%-22s%-16s%-16d%-12s%-9s\n",i,std.name,std.fathername,std.dob,std.Univrollno,std.course,std.branch);
        i++;
        j++;
    }
    fclose(fp);
    printf("Press any key to continue....");
    getch();
    menu();
}
void search()
{
    FILE *fp;
    struct student std;
    char studname[20];
    system("cls");
    printf("<--:SEARCH RECORD:-->\n");
    printf("Enter name of student to search record : ");
    fflush(stdin);
    gets(studname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        printf("File does not have data...");
        exit(1);
    }
    while(fread(&std,sizeof(std),1,fp ) == 1){
        if(strcmp(studname,std.name) == 0){
            printf("\nName : %s\n",std.name);
            printf("Father's Name : %s\n",std.fathername);
            printf("Date of Birth : %s\n",std.dob);
            printf("University Roll No : %d\n",std.Univrollno);
            printf("Course : %s\n",std.course);
            printf("Branch : %s\n",std.branch);
        }
    }
    fclose(fp);
    printf("Press any key to continue....\n");
    getch();
    menu();
}
void modify()
{
    char studname[20];
    FILE *fp;
    struct student std;
    system("cls");
    printf("<--:MODIFY RECORD:-->\n");
    printf("Enter name of student to modify: ");
    fflush(stdin);
    gets(studname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        printf("File does not have data...\n");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while(fread(&std,sizeof(std),1,fp) == 1)
    {
        if(strcmp(studname,std.name) == 0){
                printf("Enter New details of the student :\n");
            printf("Enter name: ");
            gets(std.name);
            printf("Enter Father's Name : ");
            gets(std.fathername);
            printf("Enter Date of Birth[DD/MM/YY] : ");
            gets(std.dob);
            printf("Enter University roll no : ");
            scanf("%d",&std.Univrollno);
            printf("Enter Course : ");
            fflush(stdin);
            gets(std.course);
            printf("Enter Branch : ");
            fflush(stdin);
            gets(std.branch);
            fseek(fp ,-sizeof(std),SEEK_CUR);
            fwrite(&std,sizeof(std),1,fp);
            break;
        }
    }
    fclose(fp);
    printf("Press any key to continue....");
    getch();
    menu();
}
void deletee()
{
    char studname[20];
    FILE *fp,*ft;
    struct student std;
    system("cls");
    printf("<--:DELETE RECORD:-->\n");
    printf("Enter name of student to delete record : ");
    fflush(stdin);
    gets(studname);
    fp = fopen("record.txt","rb+");
    if(fp == NULL){
        printf("File does not have data....");
        exit(1);
    }
    ft = fopen("temp.txt","wb+");
    if(ft == NULL){
        printf("File does not have data....");
        exit(1);
    }
    while(fread(&std,sizeof(std),1,fp) == 1){
        if(strcmp(studname,std.name)!=0)
            fwrite(&std,sizeof(std),1,ft);
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt","record.txt");
    printf("Press any key to continue.");
    getch();
    menu();
}
