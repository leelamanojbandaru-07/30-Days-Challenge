#include <stdio.h>

#define ZONES 5
#define DAYS 7

char *zoneNames[ZONES] = {
    "Academic Block", "Hostel", "Library",
    "Cafeteria", "Sports Area"
};

void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS]);
void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES]);
void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], int riskDays[ZONES]);
void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], float greenIndex[ZONES]);
void displayRanking(float greenIndex[ZONES]);
void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], int riskDays[ZONES]);

int main()
{
    float temp[ZONES][DAYS], humidity[ZONES][DAYS];
    int aqi[ZONES][DAYS];
    float avgTemp[ZONES], avgHumidity[ZONES], avgAQI[ZONES];
    float greenIndex[ZONES];
    int riskDays[ZONES];
    int choice, dataReady = 0;

    do
    {
        printf("\n===== CAMPUS ENVIRONMENT MONITOR =====\n");
        printf("1. Input / Update Data\n");
        printf("2. Display Data\n");
        printf("3. Zone-wise Averages\n");
        printf("4. Detect Risk Days\n");
        printf("5. Green Index and Ranking\n");
        printf("6. Recommendations\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                inputData(temp, humidity, aqi);
                dataReady = 1;
                break;

            case 2:
                if(dataReady)
                    displayData(temp, humidity, aqi);
                else
                    printf("Please enter data first.\n");
                break;

            case 3:
                if(dataReady)
                {
                    calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);

                    for(int i = 0; i < ZONES; i++)
                    {
                        printf("\n%s\n", zoneNames[i]);
                        printf("Average Temperature: %.2f\n", avgTemp[i]);
                        printf("Average Humidity: %.2f\n", avgHumidity[i]);
                        printf("Average AQI: %.2f\n", avgAQI[i]);
                    }
                }
                else
                    printf("Please enter data first.\n");
                break;

            case 4:
                if(dataReady)
                    detectRiskZones(temp, humidity, aqi, riskDays);
                else
                    printf("Please enter data first.\n");
                break;

            case 5:
                if(dataReady)
                {
                    calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
                    computeGreenIndex(avgTemp, avgHumidity, avgAQI, greenIndex);
                    displayRanking(greenIndex);
                }
                else
                    printf("Please enter data first.\n");
                break;

            case 6:
                if(dataReady)
                {
                    calculateAverages(temp, humidity, aqi, avgTemp, avgHumidity, avgAQI);
                    detectRiskZones(temp, humidity, aqi, riskDays);
                    displayRecommendations(avgTemp, avgHumidity, avgAQI, riskDays);
                }
                else
                    printf("Please enter data first.\n");
                break;

            case 7:
                printf("Program exited successfully.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while(choice != 7);

    return 0;
}

void inputData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS])
{
    int i, j;

    printf("\nEnter seven-day readings for all zones.\n");
    printf("Use authorised measurements or clearly labelled simulated data.\n");

    for(i = 0; i < ZONES; i++)
    {
        printf("\n--- %s ---\n", zoneNames[i]);

        for(j = 0; j < DAYS; j++)
        {
            do
            {
                printf("Day %d Temperature (10-50): ", j + 1);
                scanf("%f", &temp[i][j]);

                if(temp[i][j] < 10 || temp[i][j] > 50)
                    printf("Invalid temperature. Enter again.\n");

            } while(temp[i][j] < 10 || temp[i][j] > 50);

            do
            {
                printf("Day %d Humidity (0-100): ", j + 1);
                scanf("%f", &humidity[i][j]);

                if(humidity[i][j] < 0 || humidity[i][j] > 100)
                    printf("Invalid humidity. Enter again.\n");

            } while(humidity[i][j] < 0 || humidity[i][j] > 100);

            do
            {
                printf("Day %d AQI (0-500): ", j + 1);
                scanf("%d", &aqi[i][j]);

                if(aqi[i][j] < 0 || aqi[i][j] > 500)
                    printf("Invalid AQI. Enter again.\n");

            } while(aqi[i][j] < 0 || aqi[i][j] > 500);
        }
    }

    printf("\nAll readings entered successfully.\n");
}

void displayData(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS])
{
    int i, j;

    printf("\nTEMPERATURE MATRIX\n");
    for(i = 0; i < ZONES; i++)
    {
        printf("%s: ", zoneNames[i]);
        for(j = 0; j < DAYS; j++)
            printf("%.1f ", temp[i][j]);
        printf("\n");
    }

    printf("\nHUMIDITY MATRIX\n");
    for(i = 0; i < ZONES; i++)
    {
        printf("%s: ", zoneNames[i]);
        for(j = 0; j < DAYS; j++)
            printf("%.1f ", humidity[i][j]);
        printf("\n");
    }

    printf("\nAQI MATRIX\n");
    for(i = 0; i < ZONES; i++)
    {
        printf("%s: ", zoneNames[i]);
        for(j = 0; j < DAYS; j++)
            printf("%d ", aqi[i][j]);
        printf("\n");
    }
}

void calculateAverages(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES])
{
    int i, j;
    float t, h, a;

    for(i = 0; i < ZONES; i++)
    {
        t = 0;
        h = 0;
        a = 0;

        for(j = 0; j < DAYS; j++)
        {
            t = t + temp[i][j];
            h = h + humidity[i][j];
            a = a + aqi[i][j];
        }

        avgTemp[i] = t / DAYS;
        avgHumidity[i] = h / DAYS;
        avgAQI[i] = a / DAYS;
    }
}

void detectRiskZones(float temp[ZONES][DAYS], float humidity[ZONES][DAYS], int aqi[ZONES][DAYS], int riskDays[ZONES])
{
    int i, j, found;

    printf("\n===== RISK DAY REPORT =====\n");

    for(i = 0; i < ZONES; i++)
    {
        riskDays[i] = 0;
        found = 0;

        printf("\n%s: ", zoneNames[i]);

        for(j = 0; j < DAYS; j++)
        {
            if(aqi[i][j] > 150 || temp[i][j] > 35 || humidity[i][j] > 80)
            {
                riskDays[i]++;
                printf("Day %d ", j + 1);
                found = 1;
            }
        }

        if(found == 0)
            printf("No risk days");

        printf("\nTotal risk days: %d\n", riskDays[i]);
    }
}

void computeGreenIndex(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], float greenIndex[ZONES])
{
    int i;
    float a, t, h, diff;

    for(i = 0; i < ZONES; i++)
    {
        a = 100 - (avgAQI[i] / 5);

        diff = avgTemp[i] - 25;
        if(diff < 0)
            diff = -diff;
        t = 100 - (4 * diff);

        diff = avgHumidity[i] - 50;
        if(diff < 0)
            diff = -diff;
        h = 100 - (2 * diff);

        if(a < 0)
            a = 0;
        if(t < 0)
            t = 0;
        if(h < 0)
            h = 0;

        greenIndex[i] = (0.4 * a) + (0.3 * t) + (0.3 * h);
    }
}

void displayRanking(float greenIndex[ZONES])
{
    int i, j, rank[ZONES];

    for(i = 0; i < ZONES; i++)
    {
        rank[i] = 1;

        for(j = 0; j < ZONES; j++)
        {
            if(greenIndex[j] > greenIndex[i])
                rank[i]++;
        }
    }

    printf("\n===== GREEN INDEX RANKING =====\n");

    for(i = 1; i <= ZONES; i++)
    {
        for(j = 0; j < ZONES; j++)
        {
            if(rank[j] == i)
            {
                printf("Rank %d - %s : %.2f\n", rank[j], zoneNames[j], greenIndex[j]);
            }
        }
    }
}

void displayRecommendations(float avgTemp[ZONES], float avgHumidity[ZONES], float avgAQI[ZONES], int riskDays[ZONES])
{
    int i, found;

    printf("\n===== ENVIRONMENTAL RECOMMENDATIONS =====\n");

    for(i = 0; i < ZONES; i++)
    {
        printf("\n%s:\n", zoneNames[i]);
        found = 0;

        if(avgAQI[i] > 150)
        {
            printf("- Reduce vehicle idling or improve ventilation.\n");
            found = 1;
        }

        if(avgTemp[i] > 35)
        {
            printf("- Provide shade and increase green cover.\n");
            found = 1;
        }

        if(avgHumidity[i] > 80)
        {
            printf("- Improve ventilation and check stagnant water.\n");
            found = 1;
        }

        if(found == 0 && riskDays[i] > 0)
        {
            printf("- Review the flagged days and monitor those conditions.\n");
            found = 1;
        }

        if(found == 0)
            printf("- No major risk detected. Continue regular monitoring.\n");
    }
}

