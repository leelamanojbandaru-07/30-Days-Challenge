#include <stdio.h>
#define ROWS 5
#define COLS 8

void initializeSeats(int seats[ROWS][COLS]);
void displaySeats(int seats[ROWS][COLS]);
int bookSeat(int seats[ROWS][COLS], int row, int col);
int cancelSeat(int seats[ROWS][COLS], int row, int col);
int reserveGroup(int seats[ROWS][COLS], int groupSize);
void displayReport(int seats[ROWS][COLS]);

int main()
{
    int seats[ROWS][COLS];
    int choice, row, col, size;

    initializeSeats(seats);

    do
    {
        printf("\n===== SEATSMART =====\n");
        printf("1. Display Seats\n");
        printf("2. Book One Seat\n");
        printf("3. Cancel Booking\n");
        printf("4. Group Reservation\n");
        printf("5. Occupancy Report\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displaySeats(seats);
                break;

            case 2:
                printf("Enter row (1-5): ");
                scanf("%d", &row);

                printf("Enter seat (1-8): ");
                scanf("%d", &col);

                if(bookSeat(seats, row, col))
                {
                    printf("Seat booked successfully!\n");
                    displaySeats(seats);
                }
                else
                {
                    printf("Invalid or already booked seat.\n");
                }
                break;

            case 3:
                printf("Enter row (1-5): ");
                scanf("%d", &row);

                printf("Enter seat (1-8): ");
                scanf("%d", &col);

                if(cancelSeat(seats, row, col))
                {
                    printf("Booking cancelled successfully!\n");
                    displaySeats(seats);
                }
                else
                {
                    printf("Invalid seat or seat is not booked.\n");
                }
                break;

            case 4:
                printf("Enter group size (2-8): ");
                scanf("%d", &size);

                if(reserveGroup(seats, size))
                {
                    printf("Group reservation successful!\n");
                    displaySeats(seats);
                }
                else
                {
                    printf("No suitable consecutive seats available.\n");
                }
                break;

            case 5:
                displayReport(seats);
                break;

            case 6:
                printf("Thank you for using SEATSMART!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while(choice != 6);

    return 0;
}
void initializeSeats(int seats[ROWS][COLS])
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            seats[i][j] = 0;
        }
    }
}
void displaySeats(int seats[ROWS][COLS])
{
    int i, j;

    printf("\n----- SEATING ARRANGEMENT -----\n");
    printf("0 = Available, 1 = Booked\n\n");

    for(i = 0; i < ROWS; i++)
    {
        printf("Row %d: ", i + 1);

        for(j = 0; j < COLS; j++)
        {
            printf("%d ", seats[i][j]);
        }

        printf("\n");
    }
}


int bookSeat(int seats[ROWS][COLS], int row, int col)
{
    if(row < 1 || row > ROWS || col < 1 || col > COLS)
        return 0;

    row--;
    col--;

    if(seats[row][col] == 1)
        return 0;

    seats[row][col] = 1;

    return 1;
}
int cancelSeat(int seats[ROWS][COLS], int row, int col)
{
    if(row < 1 || row > ROWS || col < 1 || col > COLS)
        return 0;

    row--;
    col--;

    if(seats[row][col] == 0)
        return 0;

    seats[row][col] = 0;

    return 1;
}
int reserveGroup(int seats[ROWS][COLS], int groupSize)
{
    int i, j, k, free;

    if(groupSize < 2 || groupSize > 8)
        return 0;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j <= COLS - groupSize; j++)
        {
            free = 1;

            for(k = 0; k < groupSize; k++)
            {
                if(seats[i][j + k] == 1)
                {
                    free = 0;
                    break;
                }
            }

            if(free == 1)
            {
                for(k = 0; k < groupSize; k++)
                {
                    seats[i][j + k] = 1;
                }

                printf("Allocated Row: %d\n", i + 1);
                printf("First Seat: %d\n", j + 1);

                return 1;
            }
        }
    }

    return 0;
}
void displayReport(int seats[ROWS][COLS])
{
    int i, j, booked = 0, available;
    int count, highest = 0;

    for(i = 0; i < ROWS; i++)
    {
        count = 0;

        for(j = 0; j < COLS; j++)
        {
            if(seats[i][j] == 1)
            {
                booked++;
                count++;
            }
        }

        if(count > highest)
        {
            highest = count;
        }
    }

    available = ROWS * COLS - booked;

    printf("\n----- OCCUPANCY REPORT -----\n");
    printf("Booked Seats: %d\n", booked);
    printf("Available Seats: %d\n", available);
    printf("Occupancy Percentage: %.2f%%\n",
           (booked * 100.0) / 40);

    printf("Busiest Row(s): ");

    for(i = 0; i < ROWS; i++)
    {
        count = 0;

        for(j = 0; j < COLS; j++)
        {
            if(seats[i][j] == 1)
                count++;
        }

        if(count == highest)
        {
            printf("%d ", i + 1);
        }
    }

    printf("\nHighest Bookings in a Row: %d\n", highest);
}

