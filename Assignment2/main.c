/**@file main.c
 * main function of program
 *
 * @author	Cahira
 * @date	26.10.2013
 */
#include <stdio.h>
#include <stdlib.h>
#include "orderedIntSet.h"
#include "doublelinkedlist.h"

int main(void) {
    // Array of 10 set pointers, all starting empty
    intSet* SetsArray[10] = { NULL };
    int choice;

    do {
        // Printing the 10 menu options
        printf("\nTest Program\n");
        printf("1. Create Set\n");
        printf("2. Delete Set\n");
        printf("3. Add Elements\n");
        printf("4. Remove Elements\n");
        printf("5. Store to binary\n");
        printf("6. Load from binary\n");
        printf("7. Intersection\n");
        printf("8. Union\n");
        printf("9. Difference\n");
        printf("10. Terminate\n");
        printf("Choice: ");

        scanf("%d", &choice);

        if (choice == 1) {
            // Create empty set at index
            int idx;
            printf("Enter index (0-9): ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < 10) {
                SetsArray[idx] = createOrderSet();
            }
        }
        else if (choice == 2) {
            // Delete set and clear pointer
            int idx;
            printf("Enter index (0-9): ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < 10 && SetsArray[idx] != NULL) {
                deleteOrderSet(SetsArray[idx]);
                SetsArray[idx] = NULL;
            }
        }
        else if (choice == 3) {
            // Read until negative and then add
            int idx, val;
            printf("Enter index (0-9): ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < 10 && SetsArray[idx] != NULL) {
                printf("Enter numbers (negative to stop):\n");
                while (scanf("%d", &val) == 1 && val >= 0) {
                    if (addElement(SetsArray[idx], val) == NUMBER_ADDED) {
                        printf("NUMBER_ADDED\n");
                    } else {
                        printf("NUMBER_ALREADY_IN_SET\n");
                    }
                }
                printToStdout(SetsArray[idx]);
            }
        }
        else if (choice == 4) {
            // Read until negative and then remove
            int idx, val;
            printf("Enter index (0-9): ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < 10 && SetsArray[idx] != NULL) {
                printf("Enter numbers (negative to stop):\n");
                while (scanf("%d", &val) == 1 && val >= 0) {
                    if (removeElement(SetsArray[idx], val) == NUMBER_REMOVED) {
                        printf("NUMBER_REMOVED\n");
                    } else {
                        printf("NUMBER_NOT_IN_SET\n");
                    }
                }
                printToStdout(SetsArray[idx]);
            }
        }
        else if (choice == 5) {
            // Save to binary file
            FILE *f = fopen("SetsArrayFile.bin", "wb");
            if (f) {
                fwrite(SetsArray, sizeof(intSet*), 10, f);
                fclose(f);
                printf("Saved to binary file.\n");
            }
        }
        else if (choice == 6) {
            // Load from binary file
            FILE *f = fopen("SetsArrayFile.bin", "rb");
            if (f) {
                fread(SetsArray, sizeof(intSet*), 10, f);
                fclose(f);
                printf("Loaded from binary file.\n");
            }
        }
        else if (choice == 7) {
            // Intersection of i1 and i2, store in i3
            int i1, i2, i3;
            printf("Enter 3 indices: ");
            scanf("%d %d %d", &i1, &i2, &i3);

            // Delete old set at i3 first
            if (SetsArray[i3] != NULL) deleteOrderSet(SetsArray[i3]);

            SetsArray[i3] = setIntersection(SetsArray[i1], SetsArray[i2]);
            printToStdout(SetsArray[i3]);
        }
        else if (choice == 8) {
            // Union of i1 and i2, store in i3
            int i1, i2, i3;
            printf("Enter 3 indices: ");
            scanf("%d %d %d", &i1, &i2, &i3);

            // Delete old set at i3 first
            if (SetsArray[i3] != NULL) deleteOrderSet(SetsArray[i3]);

            SetsArray[i3] = setUnion(SetsArray[i1], SetsArray[i2]);
            printToStdout(SetsArray[i3]);
        }
        else if (choice == 9) {
            // Difference of i1 and i2, store in i3
            int i1, i2, i3;
            printf("Enter 3 indices: ");
            scanf("%d %d %d", &i1, &i2, &i3);

            // Delete old set at i3 first
            if (SetsArray[i3] != NULL) deleteOrderSet(SetsArray[i3]);

            SetsArray[i3] = setDifference(SetsArray[i1], SetsArray[i2]);
            printToStdout(SetsArray[i3]);
        }
        else if (choice == 10) {
            // Exit the program
            printf("Terminating program.\n");
        }

    } while (choice != 10);

    return 0;
}
