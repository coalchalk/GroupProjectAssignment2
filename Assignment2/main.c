/**@file main.c
 * To test the program and displays the menu calls the fuctions
 *
 * @author	Cahira
 * @date	27.11.2026
 */
#include <stdio.h>
#include <stdlib.h>
#include "orderedIntSet.h"
#include "doublelinkedlist.h"

int main(void) {
    // Array of 10 set pointers all starting empty
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

        /**
         * @brief Creates an empty set at the chosen index.
         * Prompts user for an index (0 to 9) and calls createOrderSet().
         */
        if (choice == 1) {
            int idx;
            printf("Enter index (0-9): ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < 10) {
                SetsArray[idx] = createOrderSet(); // changed to match teammate's spelling
            }
        }

        /**
         * @brief Deletes the set at the chosen index.
         * Shows the user for an index and calls deleteOrderSet() and then clears the pointer.
         */
        else if (choice == 2) {
            int idx;
            printf("Enter index (0-9): ");
            scanf("%d", &idx);
            if (idx >= 0 && idx < 10 && SetsArray[idx] != NULL) {
                deleteOrderSet(SetsArray[idx]); // changed to match teammate's spelling
                SetsArray[idx] = NULL;
            }
        }

        /**
         * @brief Add elements to the chosen set.
         * Reads numbers until negative then calls addElement().
         */
        else if (choice == 3) {
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

        /**
         * @brief Remove elements from the chosen set.
         * Reads numbers until negative then calls removeElement().
         */
        else if (choice == 4) {
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

        /**
         * @brief Stores the entire array to a binary file.
         * Opens SetsArrayFile.bin and then writes the 10 pointers.
         */
        else if (choice == 5) {
            FILE *f = fopen("SetsArrayFile.bin", "wb");
            if (f) {
                fwrite(SetsArray, sizeof(intSet*), 10, f);
                fclose(f);
                printf("Saved to binary file.\n");
            }
        }

        /**
         * @brief Loads the array from the binary file.
         * Opens the SetsarrayFile.bin and then reads the 10 pointers back.
         */
        else if (choice == 6) {
            FILE *f = fopen("SetsArrayFile.bin", "rb");
            if (f) {
                fread(SetsArray, sizeof(intSet*), 10, f);
                fclose(f);
                printf("Loaded from binary file.\n");
            }
        }

        /**
         * @brief Calculates the intersection of two sets.
         * Prompts for i1, i2, i3 and stores the result in i3.
         */
        else if (choice == 7) {
            int i1, i2, i3;
            printf("Enter 3 indices: ");
            scanf("%d %d %d", &i1, &i2, &i3);

            // Delete old set at i3 first
            if (SetsArray[i3] != NULL) deleteOrderSet(SetsArray[i3]);

            SetsArray[i3] = setIntersection(SetsArray[i1], SetsArray[i2]);
            printToStdout(SetsArray[i3]);
        }

        /**
         * @brief Calculates the union of two sets.
         * Prompts for i1, i2, i3 and stores the result in i3.
         */
        else if (choice == 8) {
            int i1, i2, i3;
            printf("Enter 3 indices: ");
            scanf("%d %d %d", &i1, &i2, &i3);

            // Delete old set at i3 first
            if (SetsArray[i3] != NULL) deleteOrderSet(SetsArray[i3]);

            SetsArray[i3] = setUnion(SetsArray[i1], SetsArray[i2]);
            printToStdout(SetsArray[i3]);
        }

        /**
         * @brief Calculates the difference of two sets whcih is (i1 - i2).
         * Shows for i1, i2, i3 and then stores the result in i3.
         */
        else if (choice == 9) {
            int i1, i2, i3;
            printf("Enter 3 indices: ");
            scanf("%d %d %d", &i1, &i2, &i3);

            // Delete old set at i3 first
            if (SetsArray[i3] != NULL) deleteOrderSet(SetsArray[i3]);

            SetsArray[i3] = setDifference(SetsArray[i1], SetsArray[i2]);
            printToStdout(SetsArray[i3]);
        }

        /**
         * @brief Terminates the program
         */
        else if (choice == 10) {
            printf("Terminating program.\n");
        }

    } while (choice != 10);

    return 0;
}

