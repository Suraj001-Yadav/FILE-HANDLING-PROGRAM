#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void createFile();
void writeToFile();
void readFromFile();
void appendToFile();
void displayMenu();
void clearInputBuffer();
void displayFileInfo(const char *filename);

int main() {
    int choice;
    
    printf("=========================================\n");
    printf("        FILE HANDLING PROGRAM\n");
    printf("=========================================\n");
    
    do {
        displayMenu();
        printf("\nEnter your choice (1-6): ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                createFile();
                break;
            case 2:
                writeToFile();
                break;
            case 3:
                readFromFile();
                break;
            case 4:
                appendToFile();
                break;
            case 5:
                printf("\nThank you for using the File Handling Program!\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1-5.\n");
        }
        printf("\n");
    } while(choice != 5);
    
    return 0;
}

void displayMenu() {
    printf("\n-----------------------------------------\n");
    printf("               MAIN MENU\n");
    printf("-----------------------------------------\n");
    printf("1. Create a new file\n");
    printf("2. Write data to a file\n");
    printf("3. Read data from a file\n");
    printf("4. Append data to a file\n");
    printf("5. Exit\n");
    printf("-----------------------------------------\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void createFile() {
    char filename[100];
    FILE *file;
    
    printf("\nEnter filename to create: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character
    
    file = fopen(filename, "w");
    if(file == NULL) {
        printf("Error: Could not create file '%s'\n", filename);
        return;
    }
    
    printf("File '%s' created successfully!\n", filename);
    fclose(file);
    
    displayFileInfo(filename);
}

void writeToFile() {
    char filename[100];
    char content[1000];
    FILE *file;
    
    printf("\nEnter filename to write to: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    
    file = fopen(filename, "w");
    if(file == NULL) {
        printf("Error: Could not open file '%s' for writing\n", filename);
        return;
    }
    
    printf("Enter content to write (press Enter on an empty line to finish):\n");
    printf("---------------------------------------------------------------\n");
    
    // Read multiple lines until an empty line is entered
    while(1) {
        fgets(content, sizeof(content), stdin);
        if(strcmp(content, "\n") == 0) {
            break;
        }
        fputs(content, file);
    }
    
    fclose(file);
    
    printf("\nData written to '%s' successfully!\n", filename);
    displayFileInfo(filename);
}

void readFromFile() {
    char filename[100];
    char ch;
    int lineCount = 1;
    FILE *file;
    
    printf("\nEnter filename to read: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    
    file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error: Could not open file '%s' for reading\n", filename);
        return;
    }
    
    printf("\n=========================================\n");
    printf("          CONTENT OF '%s'\n", filename);
    printf("=========================================\n");
    
    // Display content with line numbers
    printf("%4d: ", lineCount);
    while((ch = fgetc(file)) != EOF) {
        putchar(ch);
        if(ch == '\n') {
            lineCount++;
            printf("%4d: ", lineCount);
        }
    }
    
    printf("\n=========================================\n");
    printf("Total lines: %d\n", lineCount);
    
    fclose(file);
    displayFileInfo(filename);
}

void appendToFile() {
    char filename[100];
    char content[1000];
    FILE *file;
    
    printf("\nEnter filename to append to: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    
    file = fopen(filename, "a");
    if(file == NULL) {
        printf("Error: Could not open file '%s' for appending\n", filename);
        return;
    }
    
    printf("Enter content to append (press Enter on an empty line to finish):\n");
    printf("-----------------------------------------------------------------\n");
    
    // Read multiple lines until an empty line is entered
    while(1) {
        fgets(content, sizeof(content), stdin);
        if(strcmp(content, "\n") == 0) {
            break;
        }
        fputs(content, file);
    }
    
    fclose(file);
    
    printf("\nData appended to '%s' successfully!\n", filename);
    displayFileInfo(filename);
}

void displayFileInfo(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);
    
    printf("File info: %s (%ld bytes)\n", filename, fileSize);
}