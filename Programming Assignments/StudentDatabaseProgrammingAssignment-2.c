#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void createFile(void);
void loadFile(void);
void displayMainMenu(void);
void displayUpdateMenu(void);
void createRecord(void);
void inputStuID(int studentIndex);
void inputStuName(int studentIndex);
void inputStuEmail(int studentIndex);
void addCourse (int studentIndex);
void removeCourse(int studentIndex);
void removeRecord(void);
void writeNewFile(void);
void displayContents(int start, int finish);
int seekRecord(void);
void updateContents(void);

FILE *ofp, *ifp;
char outfilename[20], infilename[20];

/*
    Define structures to form the database. The database consists of students,
    and within each student record is an array of courses.
*/


struct courseID
{
    char subject[15];
    int num[10];
    float grade;
};
    
struct student
{
    char studentID[20];
    char firstName[20];
    char lastName[20];
    char email[30];
    int coursesTaken;               
    struct courseID courses[50];
};

/* 
    Create a database array of students
*/

int totalStudents = 0;              // to keep track of the number of students
struct student database[100];       // allows the database to house up to 100 students
struct student empty;               // used for clearing the database

/* 
    The following program creates a database of student school records. Information is
    stored in memory until output to a formatted binary file. Formatted files can be 
    loaded into memory through the appropriate menu selection.

    Individual records can be created, displayed on screen, updated, and deleted.

    Author: Michael Kuby for TRU COMP 2131 Assignment #2
    Date: Fri april 8, 2022
*/

int main ()
{   
    char c;

    do
    {
        displayMainMenu();
        do
        {        
            printf("\n\t\tPlease enter your choice ... ");
            fflush(stdin);
            scanf(" %c", &c);
        } while(c > '9' || !isdigit(c));

        switch (c)
        {
            case '1':
                createFile();
                writeNewFile();
                break;
            case '2':
                createRecord();
                break;
            case '3':
                displayContents(0, totalStudents);
                break;
            case '4':
                seekRecord();
                break;
            case '5':
                updateContents();
                break;
            case '6':
                removeRecord();
                break;
            case '7':
                loadFile();
                break;
            case '8':
                {
                    if (strlen(outfilename) > 1)
                    {
                        writeNewFile();
                        exit(0);
                    }
                    else
                    {
                        printf("\nNo output file specified. Please create a file.");
                        createFile();
                        writeNewFile();
                        printf("\n");
                        exit(0);
                    }

                }
            case '9':
                {
                    printf("\n");
                    exit(0);
                }
        }
    } while (1);
}

/* 
    Displays the main menu
*/

void displayMainMenu(void)
{
    char *menu[10] = {
                        "\n\n\t\tM A I N  M E N U",
                        "\t1. Create binary file from working database",
                        "\t2. Write new Student Record to working database",
                        "\t3. Display contents of working database",
                        "\t4. Seek specific record in working database",
                        "\t5. Update specific record in working database",
                        "\t6. Delete a record for a specific name",
                        "\t7. Load database from file",
                        "\t8. Save File and Exit",
                        "\t9. Exit without Save"
                    };
    
    for (int i = 0; i < sizeof(menu)/sizeof(menu[0]); i++)
    {
        puts(menu[i]);
    }
}

/* 
    Prompts the user to name and create an empty file 
*/

void createFile(void)
{
    extern FILE *ofp;
    ofp = NULL;
    extern char outfilename[20];
    char *file;
    
    printf("\nName of the file: ");
    fflush(stdin);
    fgets(outfilename, sizeof(outfilename), stdin);
    file = strtok(outfilename, "\n");
    ofp = fopen(file, "wb");
    if (ofp != NULL)
        printf("\n... File created succesfully");
    fclose(ofp);
}

/* 
    Prompts the user to load the information from a formatted file into memory 
*/

void loadFile(void)
{
    char c;

    // warn the user that loading a file overwrites the working memory

    do
    {
        printf("\nLoading a file will overwrite the working database. "
                            "Save to file before continuing is recommended. ");
        printf("Continue (Y/N)? ");
        fflush(stdin);
        scanf("%c", &c);

        if (toupper(c) == 'Y')
            continue;
        if (toupper(c) == 'N')
            return;
        c = ' ';

    } while (toupper(c) != 'Y' && toupper(c) != 'N');
    
    extern FILE *ifp;
    ifp = NULL;
    extern char infilename[20];
    char *file;
    
    // Get name of file from user

    printf("\nName of the file: ");
    fflush(stdin);
    fgets(infilename, sizeof(infilename), stdin);
    file = strtok(infilename, "\n");
    ifp = fopen(file, "rb");

    // Check if the specified file was found

    if (ifp == NULL)
        {
            printf("\n... Unable to find file");
            return;
        }
    else 
        printf("\n... File found.");

    // Clear the working database

    for (int i = 0; i < totalStudents; i++)
        database[i] = empty;
    
    // Read data from the file and load into the working database

    fscanf(ifp, "%d", &totalStudents);

    for (int i = 0; i < totalStudents; i++)
    {
        fscanf(ifp, " %s %s %s %s %d", database[i].studentID, database[i].firstName, 
                    database[i].lastName, database[i].email, &database[i].coursesTaken);
        for (int j = 0; j < database[i].coursesTaken; j++)
            fscanf(ifp, "%s %d %f", database[i].courses[j].subject, 
                                        database[i].courses[j].num, 
                                            &database[i].courses[j].grade);
    }

    if (ferror(ifp))
    {
        fprintf(stderr, "error in reading from file : %s", file);
    }
    
    // Set outfilename to loaded file so that on save and exit the proper outfile is set

    strcpy(outfilename, infilename);
    printf("\n... Information loaded.");
}

/* 
    Prompts the user to add a new student record to the database 
*/

void createRecord(void)
{
    extern int totalStudents;

    inputStuID(totalStudents);
    inputStuName(totalStudents);
    inputStuEmail(totalStudents);

    char addGrade;
    
    do
    {
        printf("\nAdd a course and grade to the record (Y/N)? ");
        fflush(stdin);
        scanf("%c", &addGrade);

        if (toupper(addGrade) == 'Y')
            addCourse (totalStudents);
        if (toupper(addGrade) == 'N')
            break;
        addGrade = ' ';

    } while (toupper(addGrade) != 'Y' && toupper(addGrade) != 'N');

    totalStudents++;
}

/* 
    Prompts the user to input user ID. Used for new records and updates.
    Param: the student index in database
*/

void inputStuID(int studentIndex)
{
    printf("\nInput the Student ID number: ");
    fflush(stdin);
    scanf(" %s", database[studentIndex].studentID);
}

/* 
    Prompts the user to input user name. Used for new records and updates. 
    Param: the student index in database
*/

void inputStuName(int studentIndex)
{
    printf("Input the student's first name: ");
    scanf(" %[^\n]s", database[studentIndex].firstName);
    printf("Input the student's last name: ");
    scanf(" %[^\n]s", database[studentIndex].lastName);
}

/* 
    Prompts the user to input user email. Used for new records and updates.
    Param: the student index in database
*/

void inputStuEmail(int studentIndex)
{
    printf("Input the associated email address: ");
    fflush(stdin);
    scanf(" %s", database[studentIndex].email);
}

/*  
    Prompts the user to add a course and grade to a student as specified by
    the given parameter. Used for new records and updates.
    Param: the student index in database
*/

void addCourse(int studentIndex)
{
    printf("\nYou will have a chance to input the course subject, "
                    "then the course number. Please do so one at a time. ");
    printf("\nInput the course subject: ");
    fflush(stdin);
    scanf(" %[^\n]s", database[studentIndex].courses[database[studentIndex].coursesTaken].subject);
    
    // The following ensures that the input is the first word only. If the user inputs two words,
    // file formatting on save would be incorrect, ruining the load process.

    char *saveptr;
    const char s[2] = " ";
    *database[studentIndex].courses[database[studentIndex].coursesTaken].subject = 
        *strtok_r(database[studentIndex].courses[database[studentIndex].coursesTaken].subject, s, &saveptr);

    printf("Input the course number: ");
    fflush(stdin);
    scanf(" %d", database[studentIndex].courses[database[studentIndex].coursesTaken].num);

    double num;
    do
    {
        printf("Input the course grade [0 - 100]: ");
        fflush(stdin);
        scanf(" %f", &database[studentIndex].courses[database[studentIndex].coursesTaken].grade);

    } while (database[studentIndex].courses[database[studentIndex].coursesTaken].grade < (double) 0 || 
                database[studentIndex].courses[database[studentIndex].coursesTaken].grade > (double) 100);

    database[studentIndex].coursesTaken++;
}

/*  
    Prompts the user to remove a course and grade to a student as specified by
    the given parameter. Used for new records and updates. 
    Param: the student index in database
*/

void removeCourse(int studentIndex)
{
    char remove[15];
    int number;

    printf("What is the course subject for which you would like to remove? ");
    fflush(stdin);
    scanf(" %[^\n]s", remove);

    printf("What is the course number? ");
    fflush(stdin);
    scanf(" %d", &number);

    // Search through the courses taken by the student to find a matching 
    // subject and course number.

    int j = 0;
    while (j < database[studentIndex].coursesTaken && 
            strcmp(database[studentIndex].courses[j].subject, remove) != 0 && 
                (*database[studentIndex].courses[j].num != number))
        j++;
    
    // if found, remove the course by simply overwriting it with any courses
    // that come after it in the students database.

    if (strcmp(database[studentIndex].courses[j].subject, remove) == 0 && 
            (*database[studentIndex].courses[j].num == number) && 
                j < database[studentIndex].coursesTaken)
        {
            for (int i = j; i < database[studentIndex].coursesTaken; i++)
                database[studentIndex].courses[i] = database[studentIndex].courses[i+1];
            database[studentIndex].coursesTaken--;
        }
    else
        printf("\nCourse not found.");
}

/*  
    Prompts the user to remove a students entire record from the database.
*/

void removeRecord(void)
{
    char c;

    printf("\nHelp identify the record you would like to remove.");
    int i = seekRecord();
    
    if(i == -1)
    {
        printf(" Nothing to remove.");
        return;
    }

    do
    {
        printf("\nAre you sure (Y/N)?");
        scanf(" %c", &c);
    } while (toupper(c) != 'N' && toupper(c) != 'Y');
    
    if (toupper(c) == 'N')
        return;
    
    for (; i < totalStudents; i++)
        database[i] = database[i + 1];
    
    totalStudents--;
}

/*  
    Writes the database information loaded into memory to the outfile currently pointed to.
    Outfile pointed to is either 
        a) outfile created using menu option 1
        b) the file loaded from memory
*/

void writeNewFile(void)
{
    printf("\n");
    ofp = fopen(outfilename, "wb");
    fprintf (ofp, "%d\n", totalStudents);
    int i = 0, j = 0;
    for (i = 0; i < totalStudents; i++)
    {
        fprintf(ofp, "%s \t %s %s \t %s \t %d \n", database[i].studentID, database[i].firstName, 
                                    database[i].lastName, database[i].email, database[i].coursesTaken);
        for (j = 0; j < database[i].coursesTaken; j++)
            fprintf(ofp, "%s %d %.2f \n", database[i].courses[j].subject, 
                                    *database[i].courses[j].num, database[i].courses[j].grade);
        fprintf(ofp, "\n");
    }
    fclose(ofp);
}

/*  
    Displays the requested contents that are currently loaded into memory
    Param: the start index and end index
*/

void displayContents(int start, int finish)
{
    int i, j = 0;

    for (i = start; i < finish; i++)
    {
        printf("\n\nStudent ID: %s \t Student Name: %s %s \t Student Email: %s \t Courses taken: %d \n", 
                        database[i].studentID, database[i].firstName, database[i].lastName, 
                                                database[i].email, database[i].coursesTaken);
        for (j = 0; j < database[i].coursesTaken; j++)
            {
                printf("{Course ID: %s %d    Course grade: %.2f} \n", database[i].courses[j].subject, 
                                    *database[i].courses[j].num, database[i].courses[j].grade);
            }
            
    }
}

/*  
    Seeks through the database by either name or ID number to find the given student record.
    Returns an integer value representing the index of the student in the database records.
    Returns -1 if student not found.
*/

int seekRecord(void)
{
    char c;

    do
    {        
        printf("\nSearch by Name or ID (N/I)? ");
        fflush(stdin);
        scanf(" %c", &c);
    } while(toupper(c) != 'N' && toupper(c) != 'I');

    if (c == 'N')
    {
        // Search by name

        char first[20], last[20];

        printf("\nFirst name of the person on record: ");
        scanf(" %[^\n]s", first);
        printf("Last name of the person on record: ");
        scanf(" %[^\n]s", last);

        int i = 0;
        while (i < totalStudents && strcmp(database[i].firstName, first) != 0 && 
                                            strcmp(database[i].lastName, last) != 0)
            i++;

        i < totalStudents ? displayContents(i, i + 1) : (printf("Student not found in database."), i = -1);

        return i;
    }
    else
    {
        // Search by student ID

        char ID[20];

        printf("\nID number of the person on record: ");
        scanf(" %s", ID);

        int i = 0;
        while (i < totalStudents && strcmp(database[i].studentID, ID) != 0)
            i++;

        i < totalStudents ? displayContents(i, i + 1) : (printf("Student not found in database."), i = -1);

        return i;
    }
}

/*  
    Displays the menu for update options with regards to a specific file
*/

void displayUpdateMenu(void)
{
    char *menu2[7] = {
                        " \n",
                        "\t1. Update ID",
                        "\t2. Update Name",
                        "\t3. Update Email",
                        "\t4. Add Course",
                        "\t5. Remove Course",
                        "\t6. Exit"
                    };
    
    for (int i = 0; i < sizeof(menu2)/sizeof(menu2[0]); i++)
    {
        puts(menu2[i]);
    }
}

/*  
    Navigates the user process for updating the contents of a specific user record.
*/

void updateContents(void)
{
    printf("\nHelp identify the record you would like to update.");
    int i = seekRecord();
    
    if (i > totalStudents)
        return;
    else if(i == -1)
    {
        printf(" Nothing to update.");
        return;
    }

    char c;

    do
    {
        do
        {        
            displayUpdateMenu();
            printf("\n\nWhat would you like to update? ");
            fflush(stdin);
            scanf(" %c", &c);
        } while(c > '6' || !isdigit(c));

        switch (c)
        {
            case '1':
                inputStuID(i);
                break;
            case '2':
                inputStuName(i);
                break;
            case '3':
                inputStuEmail(i);
                break;
            case '4':
                addCourse(i);
                break;
            case '5':
                removeCourse(i);
                break;
            case '6':
                printf("\n");
                return;
        }
        displayContents(i, i + 1);
    } while (1);
}