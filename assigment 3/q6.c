#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 100
#define FILENAME "members.dat"
#define INITIAL_CAPACITY 10

 
typedef struct {
    int studentID;
    char fullName[MAX_NAME_LENGTH];
    char batch[20];  
    char membershipType[10];   
    char registrationDate[11];   
    char dateOfBirth[11];   
    char interest[10];   
} Student;
 
Student *students = NULL;
int studentCount = 0;
int capacity = 0;
 
void initializeDatabase() {
    if (students == NULL) {
        capacity = INITIAL_CAPACITY;
        students = malloc(capacity * sizeof(Student));
        if (!students) {
            printf("ERROR: Memory allocation failed!\n");
            exit(1);
        }
    }
}

void growDatabase() {
    if (studentCount >= capacity) {
        capacity *= 2;
        Student *temp = realloc(students, capacity * sizeof(Student));
        if (!temp) {
            printf("ERROR: Memory reallocation failed!\n");
            free(students);
            exit(1);
        }
        students = temp;
    }
}

int isValidDate(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return 0;
    }
    
    int year, month, day;
    sscanf(date, "%d-%d-%d", &year, &month, &day);
    
    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    
    return 1;
}

int isStudentIDUnique(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            return 0;
        }
    }
    return 1;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

 
int loadDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return 0;   
    }
    
     
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (fileSize == 0) {
        fclose(file);
        return 1;
    }
    
    int records = fileSize / sizeof(Student);
 
    while (studentCount + records >= capacity) {
        growDatabase();
    }
    
 
    size_t readCount = fread(&students[studentCount], sizeof(Student), records, file);
    studentCount += readCount;
    
    fclose(file);
    
    if (readCount != records) {
        printf("WARNING: File may be corrupted. Some records may not have been loaded.\n");
        return 0;
    }
    
    return 1;
}

int saveDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("ERROR: Cannot open file for writing!\n");
        return 0;
    }
    
    size_t written = fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
    
    if (written != studentCount) {
        printf("ERROR: Failed to write all records to file!\n");
        return 0;
    }
    
    return 1;
}

int addStudentToFile(Student s, const char *filename) {
    FILE *file = fopen(filename, "ab");
    if (!file) {
        printf("ERROR: Cannot open file for appending!\n");
        return 0;
    }
    
    size_t written = fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
    
    return (written == 1);
}

 
void registerStudent() {
    if (studentCount >= capacity) {
        growDatabase();
    }
    
    Student newStudent;
    
    printf("\n=== REGISTER NEW STUDENT ===\n");
    
   
    while (1) {
        printf("Enter Student ID: ");
        if (scanf("%d", &newStudent.studentID) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        
        if (!isStudentIDUnique(newStudent.studentID)) {
            printf("Student ID already exists! Please use a different ID.\n");
            continue;
        }
        break;
    }
    clearInputBuffer();
    
     
    printf("Enter Full Name: ");
    fgets(newStudent.fullName, MAX_NAME_LENGTH, stdin);
    newStudent.fullName[strcspn(newStudent.fullName, "\n")] = 0;
  
    while (1) {
        printf("Enter Batch (CS/SE/Cyber Security/AI): ");
        fgets(newStudent.batch, sizeof(newStudent.batch), stdin);
        newStudent.batch[strcspn(newStudent.batch, "\n")] = 0;
        
        if (strcmp(newStudent.batch, "CS") == 0 || strcmp(newStudent.batch, "SE") == 0 ||
            strcmp(newStudent.batch, "Cyber Security") == 0 || strcmp(newStudent.batch, "AI") == 0) {
            break;
        }
        printf("Invalid batch! Please choose from: CS, SE, Cyber Security, AI\n");
    }
     
    while (1) {
        printf("Enter Membership Type (IEEE/ACM): ");
        fgets(newStudent.membershipType, sizeof(newStudent.membershipType), stdin);
        newStudent.membershipType[strcspn(newStudent.membershipType, "\n")] = 0;
        
        if (strcmp(newStudent.membershipType, "IEEE") == 0 || 
            strcmp(newStudent.membershipType, "ACM") == 0) {
            break;
        }
        printf("Invalid membership type! Please choose: IEEE or ACM\n");
    }
    
     
    while (1) {
        printf("Enter Registration Date (YYYY-MM-DD): ");
        fgets(newStudent.registrationDate, sizeof(newStudent.registrationDate), stdin);
        newStudent.registrationDate[strcspn(newStudent.registrationDate, "\n")] = 0;
        
        if (isValidDate(newStudent.registrationDate)) {
            break;
        }
        printf("Invalid date format! Please use YYYY-MM-DD format.\n");
    }
    
  
    while (1) {
        printf("Enter Date of Birth (YYYY-MM-DD): ");
        fgets(newStudent.dateOfBirth, sizeof(newStudent.dateOfBirth), stdin);
        newStudent.dateOfBirth[strcspn(newStudent.dateOfBirth, "\n")] = 0;
        
        if (isValidDate(newStudent.dateOfBirth)) {
            break;
        }
        printf("Invalid date format! Please use YYYY-MM-DD format.\n");
    }
    
     
    while (1) {
        printf("Enter Interest (IEEE/ACM/Both): ");
        fgets(newStudent.interest, sizeof(newStudent.interest), stdin);
        newStudent.interest[strcspn(newStudent.interest, "\n")] = 0;
        
        if (strcmp(newStudent.interest, "IEEE") == 0 || 
            strcmp(newStudent.interest, "ACM") == 0 || 
            strcmp(newStudent.interest, "Both") == 0) {
            break;
        }
        printf("Invalid interest! Please choose: IEEE, ACM, or Both\n");
    }
    
     
    students[studentCount] = newStudent;
    studentCount++;
    
    if (addStudentToFile(newStudent, FILENAME)) {
        printf("\nStudent registered successfully!\n");
    } else {
        printf("\nFailed to save student to file!\n");
    }
}

void updateStudent(int studentID) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            found = 1;
            
            printf("\n=== UPDATE STUDENT %d ===\n", studentID);
            printf("Current Batch: %s\n", students[i].batch);
            printf("Current Membership Type: %s\n", students[i].membershipType);
            
            
            while (1) {
                printf("Enter New Batch (CS/SE/Cyber Security/AI): ");
                fgets(students[i].batch, sizeof(students[i].batch), stdin);
                students[i].batch[strcspn(students[i].batch, "\n")] = 0;
                
                if (strcmp(students[i].batch, "CS") == 0 || strcmp(students[i].batch, "SE") == 0 ||
                    strcmp(students[i].batch, "Cyber Security") == 0 || strcmp(students[i].batch, "AI") == 0) {
                    break;
                }
                printf("Invalid batch! Please choose from: CS, SE, Cyber Security, AI\n");
            }
             
            while (1) {
                printf("Enter New Membership Type (IEEE/ACM): ");
                fgets(students[i].membershipType, sizeof(students[i].membershipType), stdin);
                students[i].membershipType[strcspn(students[i].membershipType, "\n")] = 0;
                
                if (strcmp(students[i].membershipType, "IEEE") == 0 || 
                    strcmp(students[i].membershipType, "ACM") == 0) {
                    break;
                }
                printf("Invalid membership type! Please choose: IEEE or ACM\n");
            }
            
            if (saveDatabase(FILENAME)) {
                printf("Student updated successfully!\n");
            } else {
                printf("Failed to save changes to file!\n");
            }
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found!\n", studentID);
    }
}

void deleteStudent(int studentID) {
    int found = 0;
    int index = -1;
    
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            found = 1;
            index = i;
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found!\n", studentID);
        return;
    }
    
     FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("ERROR: Cannot create temporary file!\n");
        return;
    }
     
    for (int i = 0; i < studentCount; i++) {
        if (i != index) {
            fwrite(&students[i], sizeof(Student), 1, tempFile);
        }
    }
    
    fclose(tempFile);
    
    
    if (remove(FILENAME) != 0) {
        printf("ERROR: Cannot remove original file!\n");
        remove("temp.dat");
        return;
    }
    
    if (rename("temp.dat", FILENAME) != 0) {
        printf("ERROR: Cannot rename temporary file!\n");
        return;
    }
    
    
    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    
    printf(" Student with ID %d deleted successfully!\n", studentID);
}

void viewAllRegistrations() {
    if (studentCount == 0) {
        printf("\nNo student registrations found.\n");
        return;
    }
    
    printf("\n=== ALL STUDENT REGISTRATIONS ===\n");
 
    printf("│   ID    │         Name           │      Batch       │ Membership   │  Reg. Date     │    DOB         │ Interest │\n");
    
    
    for (int i = 0; i < studentCount; i++) {
        printf("│ %-7d │ %-22s │ %-16s │ %-12s │ %-14s │ %-14s │ %-8s │\n",
               students[i].studentID,
               students[i].fullName,
               students[i].batch,
               students[i].membershipType,
               students[i].registrationDate,
               students[i].dateOfBirth,
               students[i].interest);
    }
     
    printf("Total Students: %d\n", studentCount);
}

void generateBatchReport() {
    char batch[20];
    
    printf("\nEnter Batch to generate report (CS/SE/Cyber Security/AI): ");
    fgets(batch, sizeof(batch), stdin);
    batch[strcspn(batch, "\n")] = 0;
    
    printf("\n=== BATCH REPORT: %s ===\n", batch);
    printf("│   ID    │         Name           │ Membership   │ Interest │\n");
 
    
    int count = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            printf("│ %-7d │ %-22s │ %-12s │ %-8s │\n",
                   students[i].studentID,
                   students[i].fullName,
                   students[i].membershipType,
                   students[i].interest);
            count++;
        }
    }
 
    printf("Total students in %s batch: %d\n", batch, count);
}

void freeMemory() {
    if (students != NULL) {
        free(students);
        students = NULL;
    }
    studentCount = 0;
    capacity = 0;
}

 
void stressTest() {
    printf("\n=== RUNNING STRESS TEST ===\n");
    
    
    char *names[] = {"Ali Khan", "Sara Ahmed", "Mohammad Bilal", "Fatima Noor", "Ahmed Raza",
                    "Ayesha Malik", "Usman Ghani", "Zainab Kareem", "Bilal Hussain", "Hina Shah",
                    "Omar Farooq", "Rabia Tariq", "Kamran Ali", "Sadia Iqbal", "Faisal Mahmood",
                    "Nadia Sheikh", "Tariq Javed", "Saima Rehman", "Waqas Ahmed", "Maria Khan"};
    
    char *batches[] = {"CS", "SE", "Cyber Security", "AI"};
    char *memberships[] = {"IEEE", "ACM"};
    char *interests[] = {"IEEE", "ACM", "Both"};
    
     
    printf("Adding 25 students...\n");
    for (int i = 1; i <= 25; i++) {
        Student testStudent;
        testStudent.studentID = 1000 + i;
        strcpy(testStudent.fullName, names[i % 20]);
        strcpy(testStudent.batch, batches[i % 4]);
        strcpy(testStudent.membershipType, memberships[i % 2]);
        strcpy(testStudent.registrationDate, "2024-03-15");
        strcpy(testStudent.dateOfBirth, "2000-01-01");
        strcpy(testStudent.interest, interests[i % 3]);
        
        if (studentCount >= capacity) growDatabase();
        students[studentCount++] = testStudent;
    }
    saveDatabase(FILENAME);
    printf("Added 25 students\n");
    
    
    printf("Deleting 5 random students...\n");
    int deleteIDs[] = {1005, 1010, 1015, 1020, 1025};
    for (int i = 0; i < 5; i++) {
        deleteStudent(deleteIDs[i]);
    }
    printf(" Deleted 5 students\n");
    
    
    printf("Updating 5 random students...\n");
    int updateIDs[] = {1001, 1007, 1012, 1018, 1022};
    for (int i = 0; i < 5; i++) {
         
        for (int j = 0; j < studentCount; j++) {
            if (students[j].studentID == updateIDs[i]) {
                strcpy(students[j].batch, batches[(i + 1) % 4]);
                strcpy(students[j].membershipType, memberships[(i + 1) % 2]);
                break;
            }
        }
    }
    saveDatabase(FILENAME);
    printf("Updated 5 students\n");
    
    printf("Stress test completed successfully!\n");
}

 
void displayMenu() {
    printf("\n========= STUDENT MEMBERSHIP MANAGEMENT SYSTEM =========\n");
    printf("1. Register New Student\n");
    printf("2. Update Student Information\n");
    printf("3. Delete Student Registration\n");
    printf("4. View All Registrations\n");
    printf("5. Generate Batch Report\n");
    printf("6. Run Stress Test\n");
    printf("7. Exit\n");
     
    printf("Enter your choice (1-7): ");
}

int main() {
    initializeDatabase();
    
    
    if (loadDatabase(FILENAME)) {
        printf("Database loaded successfully! (%d students)\n", studentCount);
    } else {
        printf("  No existing database found. Starting fresh.\n");
    }
    
    int choice;
    int studentID;
    
    while (1) {
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                registerStudent();
                break;
                
            case 2:
                printf("Enter Student ID to update: ");
                if (scanf("%d", &studentID) == 1) {
                    clearInputBuffer();
                    updateStudent(studentID);
                } else {
                    printf("Invalid Student ID!\n");
                    clearInputBuffer();
                }
                break;
                
            case 3:
                printf("Enter Student ID to delete: ");
                if (scanf("%d", &studentID) == 1) {
                    clearInputBuffer();
                    deleteStudent(studentID);
                } else {
                    printf("Invalid Student ID!\n");
                    clearInputBuffer();
                }
                break;
                
            case 4:
                viewAllRegistrations();
                break;
                
            case 5:
                generateBatchReport();
                break;
                
            case 6:
                stressTest();
                break;
                
            case 7:
                 
                if (saveDatabase(FILENAME)) {
                    printf("Database saved successfully!\n");
                }
                freeMemory();
                printf(" Thank you for using Student Membership Management System!\n");
                exit(0);
                
            default:
                printf(" Invalid choice! Please enter 1-7.\n");
        }
    }
    
    return 0;

}
