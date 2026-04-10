#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int lastAccessed;    
};

int findBook(struct Book shelf[], int capacity, int id) {
    for (int i = 0; i < capacity; i++) {
        if (shelf[i].id == id) return i;
    }
    return -1;
}

int findEmptySlot(struct Book shelf[], int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (shelf[i].id == -1) return i;
    }
    return -1;
}

int findLeastRecent(struct Book shelf[], int capacity) {
    int index = -1, minAccess = 999999;
    for (int i = 0; i < capacity; i++) {
        if (shelf[i].lastAccessed < minAccess) {
            minAccess = shelf[i].lastAccessed;
            index = i;
        }
    }
    return index;
}

int main() {
    int capacity, Q;
    printf("Enter shelf capacity and number of operations: ");
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];
    for (int i = 0; i < capacity; i++) {
        shelf[i].id = -1;
        shelf[i].popularity = 0;
        shelf[i].lastAccessed = 0;
    }

    printf("\nInstructions:\n");
    printf("1. ADD 'book_id' 'popularity'\n");
    printf("2. ACCESS <book_id>\n");
    printf("Commands are case-insensitive.\n\n");

    char op[20];
    int id, popularity;
    int timer = 1;

    for (int i = 1; i <= Q; i++) {
        printf("Enter operation #%d: ", i);
        scanf("%s", op);
 
        for (int k = 0; op[k]; k++) {
            if (op[k] >= 'a' && op[k] <= 'z') op[k] -= 32;
        }

        if (strcmp(op, "ADD") == 0) {

            scanf("%d %d", &id, &popularity);

            int pos = findBook(shelf, capacity, id);

            if (pos != -1) {
                shelf[pos].popularity = popularity;
                shelf[pos].lastAccessed = timer++;
                printf("Updated existing book (ID=%d) with popularity %d.\n", id, popularity);
            } else {
                int empty = findEmptySlot(shelf, capacity);

                if (empty != -1) {
                    shelf[empty].id = id;
                    shelf[empty].popularity = popularity;
                    shelf[empty].lastAccessed = timer++;
                    printf("Added new book ID=%d.\n", id);
                } else {
                    int removeIndex = findLeastRecent(shelf, capacity);
                    printf("Shelf full → Removing least recently accessed book ID=%d.\n",
                           shelf[removeIndex].id);

                    shelf[removeIndex].id = id;
                    shelf[removeIndex].popularity = popularity;
                    shelf[removeIndex].lastAccessed = timer++;
                    printf("Added new book ID=%d.\n", id);
                }
            }

        }
        else if (strcmp(op, "ACCESS") == 0) {

            scanf("%d", &id);

            int pos = findBook(shelf, capacity, id);

            if (pos == -1) {
                printf("Book ID=%d not found. ACCESS result: -1\n\n", id);
            } else {
                shelf[pos].lastAccessed = timer++;
                printf("Book ID=%d found. Popularity=%d\n\n", id, shelf[pos].popularity);
            }

        } else {
            printf("Invalid operation: %s\n\n", op);
        }
    }

    return 0;
}



