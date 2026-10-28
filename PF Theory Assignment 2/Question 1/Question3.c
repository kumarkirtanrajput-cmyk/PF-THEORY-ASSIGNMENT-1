#include <stdio.h>

#define MAX_SENSORS 100
#define MAX_HOURS 24

typedef struct {
    float total;
    float average;
    float highest;
    float lowest;
    int criticalCount;
    int warningCount;
    int longestStreak;
} SensorReport;

/* Input temperature readings for every sensor and hour. */
void inputReadings(float temp[][MAX_HOURS], int sensors, int hours)
{
    int i, j;

    for (i = 0; i < sensors; i++) {
        printf("\nSensor %d:\n", i);

        for (j = 0; j < hours; j++) {
            printf("Enter temperature for hour %d: ", j);
            scanf("%f", &temp[i][j]);
        }
    }
}

/* Analyze one sensor and return its statistics. */
SensorReport analyzeSensor(float readings[], int hours)
{
    SensorReport report;
    int i;
    int currentStreak = 0;

    report.total = 0.0f;
    report.average = 0.0f;
    report.highest = readings[0];
    report.lowest = readings[0];
    report.criticalCount = 0;
    report.warningCount = 0;
    report.longestStreak = 0;

    for (i = 0; i < hours; i++) {
        float value = readings[i];

        report.total += value;

        if (value > report.highest) {
            report.highest = value;
        }

        if (value < report.lowest) {
            report.lowest = value;
        }

        if (value >= 40.0f) {
            report.criticalCount++;
        } else if (value >= 35.0f && value <= 39.0f) {
            report.warningCount++;
        }

        if (value >= 35.0f) {
            currentStreak++;

            if (currentStreak > report.longestStreak) {
                report.longestStreak = currentStreak;
            }
        } else {
            currentStreak = 0;
        }
    }

    report.average = report.total / hours;
    return report;
}

/* Return the sensor index (starting from 0) with the highest average. */
int findHighestAverage(float temp[][MAX_HOURS], int sensors, int hours)
{
    int i;
    int highestSensor = 0;
    SensorReport current;
    SensorReport highest;

    highest = analyzeSensor(temp[0], hours);

    for (i = 1; i < sensors; i++) {
        current = analyzeSensor(temp[i], hours);

        if (current.average > highest.average) {
            highest = current;
            highestSensor = i;
        }
    }

    return highestSensor;
}

int main(void)
{
    float temp[MAX_SENSORS][MAX_HOURS];
    int sensors, hours;
    int i, highestSensor;
    SensorReport report;

    printf("Enter number of sensors (1-%d): ", MAX_SENSORS);
    scanf("%d", &sensors);

    while (sensors < 1 || sensors > MAX_SENSORS) {
        printf("Invalid number. Enter sensors from 1 to %d: ", MAX_SENSORS);
        scanf("%d", &sensors);
    }

    printf("Enter number of hourly readings (1-%d): ", MAX_HOURS);
    scanf("%d", &hours);

    while (hours < 1 || hours > MAX_HOURS) {
        printf("Invalid number. Enter readings from 1 to %d: ", MAX_HOURS);
        scanf("%d", &hours);
    }

    inputReadings(temp, sensors, hours);

    printf("\n========== SENSOR REPORTS ==========\n");

    for (i = 0; i < sensors; i++) {
        report = analyzeSensor(temp[i], hours);

        printf("\nSensor %d\n", i);
        printf("Total temperature: %.2f\n", report.total);
        printf("Average temperature: %.2f\n", report.average);
        printf("Highest temperature: %.2f\n", report.highest);
        printf("Lowest temperature: %.2f\n", report.lowest);
        printf("Critical readings (>= 40 C): %d\n", report.criticalCount);
        printf("Warning readings (35-39 C): %d\n", report.warningCount);
        printf("Longest streak (>= 35 C): %d hour(s)\n",
               report.longestStreak);
    }

    highestSensor = findHighestAverage(temp, sensors, hours);
    report = analyzeSensor(temp[highestSensor], hours);

    printf("\n========== FINAL REPORT ==========\n");
    printf("Sensor with highest average: %d\n", highestSensor);
    printf("Highest average temperature: %.2f C\n", report.average);

    return 0;
}
