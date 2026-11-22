#include <stdio.h>

#define ZONES 5
#define DAYS 7

char *zoneName[ZONES] = {
    "Academic Block",
    "Hostel",
    "Library",
    "Cafeteria",
    "Sports Complex"
};

void inputWaterData(int usage[ZONES][DAYS], int dailyTarget[ZONES]);
void displayWaterData(int usage[ZONES][DAYS], int dailyTarget[ZONES]);

void calculateZoneStats(int *zoneUsage, int *total,
                        float *average, int *peakUsage, int *peakDay);

void detectWaterAlerts(int *zoneUsage, int dailyTarget,
                       int *overLimitDays, int *totalExcess,
                       int *spikeDays, int *alertDays);

void generateAuditReport(int usage[ZONES][DAYS],
                         int dailyTarget[ZONES],
                         int excessByZone[ZONES],
                         int overLimitByZone[ZONES],
                         int spikeByZone[ZONES],
                         int alertByZone[ZONES]);

void rankZones(int excessByZone[ZONES]);

void displayConservationActions(int overLimitByZone[ZONES],
                                int spikeByZone[ZONES],
                                int excessByZone[ZONES]);

int main()
{
    int usage[ZONES][DAYS];
    int dailyTarget[ZONES];

    int excessByZone[ZONES] = {0};
    int overLimitByZone[ZONES] = {0};
    int spikeByZone[ZONES] = {0};
    int alertByZone[ZONES] = {0};

    int choice, reportDone = 0;

    printf("========== WATERWISE ==========\n");
    printf("Campus Water Consumption Analysis\n");

    inputWaterData(usage, dailyTarget);

    do
    {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Display Water Data\n");
        printf("2. Generate Audit Report\n");
        printf("3. Rank Zones by Excess\n");
        printf("4. Conservation Actions\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displayWaterData(usage, dailyTarget);
                break;

            case 2:
                generateAuditReport(usage, dailyTarget,
                                    excessByZone, overLimitByZone,
                                    spikeByZone, alertByZone);
                reportDone = 1;
                break;

            case 3:
                if(reportDone == 1)
                    rankZones(excessByZone);
                else
                    printf("Generate audit report first.\n");
                break;

            case 4:
                if(reportDone == 1)
                    displayConservationActions(overLimitByZone,
                                               spikeByZone,
                                               excessByZone);
                else
                    printf("Generate audit report first.\n");
                break;

            case 5:
                printf("Thank you for using WATERWISE!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while(choice != 5);

    return 0;
}

void inputWaterData(int usage[ZONES][DAYS], int dailyTarget[ZONES])
{
    int i, j;

    printf("\nEnter daily water targets:\n");

    for(i = 0; i < ZONES; i++)
    {
        do
        {
            printf("%s target: ", zoneName[i]);
            scanf("%d", &dailyTarget[i]);

            if(dailyTarget[i] < 100 || dailyTarget[i] > 50000)
                printf("Invalid target! Enter 100 to 50000.\n");

        } while(dailyTarget[i] < 100 || dailyTarget[i] > 50000);
    }

    printf("\nEnter water consumption readings (litres):\n");

    for(i = 0; i < ZONES; i++)
    {
        printf("\n%s\n", zoneName[i]);

        for(j = 0; j < DAYS; j++)
        {
            do
            {
                printf("Day %d: ", j + 1);
                scanf("%d", &usage[i][j]);

                if(usage[i][j] < 0 || usage[i][j] > 50000)
                    printf("Invalid reading! Enter 0 to 50000.\n");

            } while(usage[i][j] < 0 || usage[i][j] > 50000);
        }
    }
}

void displayWaterData(int usage[ZONES][DAYS], int dailyTarget[ZONES])
{
    int i, j;

    printf("\n========== WATER DATA ==========\n");

    printf("%-18s", "Zone");

    for(j = 0; j < DAYS; j++)
        printf("Day%-5d", j + 1);

    printf("Target\n");

    for(i = 0; i < ZONES; i++)
    {
        printf("%-18s", zoneName[i]);

        for(j = 0; j < DAYS; j++)
            printf("%-8d", usage[i][j]);

        printf("%d\n", dailyTarget[i]);
    }
}

void calculateZoneStats(int *zoneUsage, int *total,
                        float *average, int *peakUsage, int *peakDay)
{
    int i, sum = 0;

    *peakUsage = *zoneUsage;
    *peakDay = 1;

    for(i = 0; i < DAYS; i++)
    {
        sum = sum + *(zoneUsage + i);

        if(*(zoneUsage + i) > *peakUsage)
        {
            *peakUsage = *(zoneUsage + i);
            *peakDay = i + 1;
        }
    }

    *total = sum;
    *average = (float)sum / DAYS;
}

void detectWaterAlerts(int *zoneUsage, int dailyTarget,
                       int *overLimitDays, int *totalExcess,
                       int *spikeDays, int *alertDays)
{
    int i;
    int over, spike;

    *overLimitDays = 0;
    *totalExcess = 0;
    *spikeDays = 0;
    *alertDays = 0;

    for(i = 0; i < DAYS; i++)
    {
        over = 0;
        spike = 0;

        if(*(zoneUsage + i) > dailyTarget)
        {
            (*overLimitDays)++;

            *totalExcess = *totalExcess +
                           (*(zoneUsage + i) - dailyTarget);

            over = 1;
        }

        if(i > 0 &&
           *(zoneUsage + i) > *(zoneUsage + i - 1) * 1.40)
        {
            (*spikeDays)++;
            spike = 1;
        }

        if(over == 1 || spike == 1)
            (*alertDays)++;
    }
}

void generateAuditReport(int usage[ZONES][DAYS],
                         int dailyTarget[ZONES],
                         int excessByZone[ZONES],
                         int overLimitByZone[ZONES],
                         int spikeByZone[ZONES],
                         int alertByZone[ZONES])
{
    int i, total, peak, peakDay;
    float average;

    int over, excess, spike, alert;

    printf("\n========== WATER AUDIT REPORT ==========\n");

    for(i = 0; i < ZONES; i++)
    {
        calculateZoneStats(&usage[i][0], &total,
                           &average, &peak, &peakDay);

        detectWaterAlerts(&usage[i][0], dailyTarget[i],
                          &over, &excess, &spike, &alert);

        excessByZone[i] = excess;
        overLimitByZone[i] = over;
        spikeByZone[i] = spike;
        alertByZone[i] = alert;

        printf("\nZone: %s\n", zoneName[i]);
        printf("Weekly Total: %d litres\n", total);
        printf("Daily Average: %.2f litres\n", average);
        printf("Highest Usage: %d litres\n", peak);
        printf("Peak Day: Day %d\n", peakDay);
        printf("Over-limit Days: %d\n", over);
        printf("Total Excess: %d litres\n", excess);
        printf("Sudden Spikes: %d\n", spike);
        printf("Unique Alert Days: %d\n", alert);
    }
}

void rankZones(int excessByZone[ZONES])
{
    int i, j, rank;

    printf("\n========== ZONE RANKING ==========\n");

    for(i = 0; i < ZONES; i++)
    {
        rank = 1;

        for(j = 0; j < ZONES; j++)
        {
            if(excessByZone[j] > excessByZone[i])
                rank++;
        }

        printf("Rank %d : %-18s %d litres excess\n",
               rank, zoneName[i], excessByZone[i]);
    }
}

void displayConservationActions(int overLimitByZone[ZONES],
                                int spikeByZone[ZONES],
                                int excessByZone[ZONES])
{
    int i;

    printf("\n========== CONSERVATION ACTIONS ==========\n");

    for(i = 0; i < ZONES; i++)
    {
        printf("\n%s\n", zoneName[i]);

        if(spikeByZone[i] > 0)
            printf("- Check for leaks or unexpected usage around spike days.\n");

        if(overLimitByZone[i] >= 3)
            printf("- Prioritise a water audit and reduction plan.\n");

        else if(overLimitByZone[i] == 1 || overLimitByZone[i] == 2)
            printf("- Monitor excess days and inspect taps or valves.\n");

        if(overLimitByZone[i] == 0 && spikeByZone[i] == 0)
            printf("- Maintain current good water-saving practices.\n");

        printf("Total excess: %d litres\n", excessByZone[i]);
    }
}
