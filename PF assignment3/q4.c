#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int popularity;
    int lastAccessTime; // helps track least recently used
    int valid;          // flag to check if slot is occupied
} Book;

int main()
{
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    Book *shelf = (Book *)malloc(capacity * sizeof(Book));
    for (int i = 0; i < capacity; i++)
    {
        shelf[i].valid = 0; // initially empty
    }

    int currentTime = 0;

    for (int q = 0; q < Q; q++)
    {
        char op[10];
        scanf("%s", op);

        if (op[0] == 'A' && op[1] == 'D')
        { // ADD operation
            int x, y;
            scanf("%d %d", &x, &y);
            currentTime++;

            int found = -1;
            for (int i = 0; i < capacity; i++)
            {
                if (shelf[i].valid && shelf[i].id == x)
                {
                    found = i;
                    break;
                }
            }

            if (found != -1)
            {
                // Update existing book
                shelf[found].popularity = y;
                shelf[found].lastAccessTime = currentTime;
            }
            else
            {
                // Check if there is space
                int emptyIndex = -1;
                for (int i = 0; i < capacity; i++)
                {
                    if (!shelf[i].valid)
                    {
                        emptyIndex = i;
                        break;
                    }
                }

                if (emptyIndex != -1)
                {
                    // Place new book in empty slot
                    shelf[emptyIndex].id = x;
                    shelf[emptyIndex].popularity = y;
                    shelf[emptyIndex].lastAccessTime = currentTime;
                    shelf[emptyIndex].valid = 1;
                }
                else
                {
                    // Shelf full → remove least recently accessed
                    int lruIndex = 0;
                    for (int i = 1; i < capacity; i++)
                    {
                        if (shelf[i].lastAccessTime < shelf[lruIndex].lastAccessTime)
                        {
                            lruIndex = i;
                        }
                    }
                    shelf[lruIndex].id = x;
                    shelf[lruIndex].popularity = y;
                    shelf[lruIndex].lastAccessTime = currentTime;
                    shelf[lruIndex].valid = 1;
                }
            }
        }
        else if (op[0] == 'A' && op[1] == 'C')
        { // ACCESS operation
            int x;
            scanf("%d", &x);
            currentTime++;

            int found = -1;
            for (int i = 0; i < capacity; i++)
            {
                if (shelf[i].valid && shelf[i].id == x)
                {
                    found = i;
                    break;
                }
            }

            if (found != -1)
            {
                printf("%d\n", shelf[found].popularity);
                shelf[found].lastAccessTime = currentTime;
            }
            else
            {
                printf("-1\n");
            }
        }
    }

    free(shelf);
    return 0;
}