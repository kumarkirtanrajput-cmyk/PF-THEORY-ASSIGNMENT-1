#include <stdio.h>

#define MAX_DAYS 7

/* Input and validate the festival duration. */
int getValidDays(void)
{
    int days;

    printf("Enter number of festival days (1-7): ");
    scanf("%d", &days);

    while (days < 1 || days > MAX_DAYS) {
        printf("Invalid number. Enter festival days from 1 to 7: ");
        scanf("%d", &days);
    }

    return days;
}

/* Process orders for one day and return the total sales. */
float calculateDailySales(int dayNumber)
{
    int orders, i;
    float amount;
    float total = 0.0f;
    float highest = 0.0f;

    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);

    while (orders < 1) {
        printf("Number of orders must be at least 1. Enter again: ");
        scanf("%d", &orders);
    }

    for (i = 1; i <= orders; i++) {
        printf("Enter amount for order %d (Rs. greater than 0): ", i);
        scanf("%f", &amount);

        while (amount <= 0.0f) {
            printf("Amount must be greater than 0. Enter order %d again: ", i);
            scanf("%f", &amount);
        }

        total += amount;

        if (i == 1 || amount > highest) {
            highest = amount;
        }
    }

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order amount: Rs. %.2f\n", total / orders);
    printf("Highest order amount: Rs. %.2f\n", highest);

    return total;
}

/* Return the earliest day with the highest total sales. */
int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i;
    int highestDay = 1;

    for (i = 1; i < numberOfDays; i++) {
        /* Strictly greater preserves the earliest day in a tie. */
        if (dailySales[i] > dailySales[highestDay - 1]) {
            highestDay = i + 1;
        }
    }

    return highestDay;
}

/* Print one asterisk for every complete Rs. 100 in daily sales. */
void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j;
    int stars;

    printf("\n========== DAILY SALES BAR CHART ==========\n");

    for (i = 0; i < numberOfDays; i++) {
        stars = (int)(dailySales[i] / 100.0f);

        printf("Day %d | ", i + 1);
        for (j = 0; j < stars; j++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main(void)
{
    int numberOfDays;
    int i;
    int highestDay;
    float dailySales[MAX_DAYS];
    float festivalTotal = 0.0f;

    numberOfDays = getValidDays();

    for (i = 0; i < numberOfDays; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    highestDay = findHighestSalesDay(dailySales, numberOfDays);

    printf("\n========== FESTIVAL SALES SUMMARY ==========\n");
    printf("Total sales for the festival: Rs. %.2f\n", festivalTotal);
    printf("Day with the highest total sales: Day %d\n", highestDay);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[highestDay - 1]);

    displayBarChart(dailySales, numberOfDays);

    return 0;
}
