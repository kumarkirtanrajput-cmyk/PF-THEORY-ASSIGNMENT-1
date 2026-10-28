#include <stdio.h>

int main(void)
{
    int rows, seats;
    int i, j;
    int totalAvailable = 0;
    int k;
    int middle, distance;
    int allocated = 0;
    int allocatedRow = -1;
    int startSeat = -1;
    int endRow, row;
    int availableInRow;
    int consecutive;
    int found = 0;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of seats per row: ");
    scanf("%d", &seats);

    if (rows <= 0 || seats <= 0) {
        printf("Rows and seats must both be greater than zero.\\n");
        return 0;
    }

    int seating[rows][seats];

    printf("\\nEnter seating status (0 = available, 1 = booked):\\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < seats; j++) {
            do {
                printf("Row %d, Seat %d: ", i, j);
                scanf("%d", &seating[i][j]);

                if (seating[i][j] != 0 && seating[i][j] != 1) {
                    printf("Invalid input. Enter 0 or 1.\\n");
                }
            } while (seating[i][j] != 0 && seating[i][j] != 1);
        }
    }

    printf("\\nCurrent Seating Arrangement\\n");
    printf("      ");
    for (j = 0; j < seats; j++) {
        printf("%d ", j);
    }
    printf("\\n");

    for (i = 0; i < rows; i++) {
        printf("Row %d: ", i);
        for (j = 0; j < seats; j++) {
            if (seating[i][j] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\\n");
    }

    printf("\\nSeat Availability Report\\n");
    for (i = 0; i < rows; i++) {
        availableInRow = 0;
        for (j = 0; j < seats; j++) {
            if (seating[i][j] == 0) {
                availableInRow++;
            }
        }
        printf("Row %d: %d available seat(s)\\n", i, availableInRow);
        totalAvailable += availableInRow;
    }
    printf("Total available seats: %d\\n", totalAvailable);

    printf("\\nEnter number of customers to seat together (k): ");
    scanf("%d", &k);

    if (k <= 0 || k > seats) {
        printf("Invalid group size. It must be greater than 0 and no more than %d.\\n", seats);
        return 0;
    }

    middle = rows / 2;

    /*
       Search rows by increasing distance from the middle.
       At equal distance, check the smaller row number first.
    */
    for (distance = 0; distance < rows && !found; distance++) {
        int lowerRow = middle - distance;
        int upperRow = middle + distance;

        if (lowerRow >= 0) {
            consecutive = 0;
            for (j = 0; j < seats; j++) {
                if (seating[lowerRow][j] == 0) {
                    consecutive++;
                    if (consecutive == k) {
                        allocatedRow = lowerRow;
                        startSeat = j - k + 1;
                        found = 1;
                        break;
                    }
                } else {
                    consecutive = 0;
                }
            }
        }

        if (!found && distance > 0 && upperRow < rows) {
            consecutive = 0;
            for (j = 0; j < seats; j++) {
                if (seating[upperRow][j] == 0) {
                    consecutive++;
                    if (consecutive == k) {
                        allocatedRow = upperRow;
                        startSeat = j - k + 1;
                        found = 1;
                        break;
                    }
                } else {
                    consecutive = 0;
                }
            }
        }
    }

    if (found) {
        endRow = startSeat + k - 1;

        for (j = startSeat; j <= endRow; j++) {
            seating[allocatedRow][j] = 1;
        }

        printf("\\nBooking successful!\\n");
        printf("Allocated row: %d\\n", allocatedRow);
        printf("Allocated seat numbers: ");
        for (j = startSeat; j <= endRow; j++) {
            printf("%d ", j);
        }
        printf("\\n");

        printf("\\nUpdated Seating Arrangement\\n");
        printf("      ");
        for (j = 0; j < seats; j++) {
            printf("%d ", j);
        }
        printf("\\n");

        totalAvailable = 0;
        for (i = 0; i < rows; i++) {
            printf("Row %d: ", i);
            for (j = 0; j < seats; j++) {
                if (seating[i][j] == 0) {
                    printf("_ ");
                    totalAvailable++;
                } else {
                    printf("X ");
                }
            }
            printf("\\n");
        }
        printf("Remaining available seats: %d\\n", totalAvailable);
    } else {
        printf("\\nBooking unsuccessful: no row has %d consecutive available seats.\\n", k);
        printf("The seating plan remains unchanged.\\n");
    }

    return 0;
}
