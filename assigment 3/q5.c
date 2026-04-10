#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 500
 
char **lines = NULL;
int lineCount = 0;
int capacity = 0;

 
void growIfNeeded() {
    if (lineCount < capacity) return;

    capacity = (capacity == 0) ? 4 : capacity * 2;
    char **temp = realloc(lines, capacity * sizeof(char *));
    if (!temp) {
        printf("ERROR: Memory allocation failed.\n");
        exit(1);
    }
    lines = temp;
}

void freeAll() {
    for (int i = 0; i < lineCount; i++)
        free(lines[i]);
    free(lines);
}

 
void insertLine(int index, const char *text) {
    if (index < 1 || index > lineCount + 1) {
        printf("  Invalid index! Insert between 1 and %d.\n", lineCount + 1);
        return;
    }

    growIfNeeded();

    for (int i = lineCount; i >= index; i--) {
        lines[i] = lines[i - 1];
    }

    lines[index - 1] = malloc(strlen(text) + 1);
    strcpy(lines[index - 1], text);

    lineCount++;
    printf(" Line inserted at position %d.\n", index);
}

void deleteLine(int index) {
    if (index < 1 || index > lineCount) {
        printf(" Invalid index! Delete between 1 and %d.\n", lineCount);
        return;
    }

    free(lines[index - 1]);

    for (int i = index - 1; i < lineCount - 1; i++) {
        lines[i] = lines[i + 1];
    }

    lineCount--;
    printf(" Line %d deleted.\n", index);
}

void printAllLines() {
    if (lineCount == 0) {
        printf(" [Empty]\n");
        return;
    }

    printf("\n----- TEXT BUFFER -----\n");
    for (int i = 0; i < lineCount; i++) {
        printf("%d: %s\n", i + 1, lines[i]);
    }
    printf("------------------------\n\n");
}

 
void saveToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("  Cannot save file.\n");
        return;
    }

    for (int i = 0; i < lineCount; i++) {
        fprintf(fp, "%s\n", lines[i]);
    }

    fclose(fp);
    printf("  Saved to '%s'.\n", filename);
}

void loadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf(" Cannot open file.\n");
        return;
    }

    freeAll();
    lines = NULL;
    lineCount = 0;
    capacity = 0;

    char buffer[MAX_INPUT];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        insertLine(lineCount + 1, buffer);
    }

    fclose(fp);
    printf(" Loaded '%s'.\n", filename);
}
 
int main() {
    printf("\n========= SIMPLE TEXT EDITOR =========\n");
    printf(" Commands:\n");
    printf("  INSERT <index>   - Insert a new line\n");
    printf("  DELETE <index>   - Delete a line\n");
    printf("  PRINT            - Show all text\n");
    printf("  SAVE <file>      - Save to file\n");
    printf("  LOAD <file>      - Load from file\n");
    printf("  EXIT             - Quit\n");
 

    char command[20];
    char filename[100];
    char input[MAX_INPUT];
    int index;

    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "PRINT") == 0) {
            printAllLines();
        }

        else if (strcmp(command, "INSERT") == 0) {
            scanf("%d", &index);
            getchar();

            printf("Enter text: ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = 0;

            insertLine(index, input);
        }

        else if (strcmp(command, "DELETE") == 0) {
            scanf("%d", &index);
            deleteLine(index);
        }

        else if (strcmp(command, "SAVE") == 0) {
            scanf("%s", filename);
            saveToFile(filename);
        }

        else if (strcmp(command, "LOAD") == 0) {
            scanf("%s", filename);
            loadFromFile(filename);
        }

        else if (strcmp(command, "EXIT") == 0) {
            break;
        }

        else {
            printf(" Unknown command. Try again.\n");
        }
    }

    freeAll();
    return 0;
}

