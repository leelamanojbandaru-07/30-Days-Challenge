#include <stdio.h>

int main() {
    int count_small = 0, count_medium = 0, count_large = 0, count_valid = 0;
    float total_small = 0.0, total_medium = 0.0, total_large = 0.0, total_valid = 0.0;
    float amount;

    printf("--- LOOPLAB: Daily Expense Analyser ---\n");
    printf("Enter expense amounts (Enter 0 to stop):\n\n");

    while (1) {
        printf("Enter expense amount (₹): ");
        scanf("%f", &amount);

        if (amount == 0) {
            break;
        }

        if (amount < 0) {
            printf("Error: Invalid amount. Expenses cannot be negative.\n");
            continue;
        }

        if (amount < 100.0) {
            count_small++;
            total_small += amount;
    }

    printf("\n================ SUMMARY ================\n");
    if (count_valid > 0) {
        float average_valid = total_valid / count_valid;

        printf("Small Expenses (< ₹100)   : Count = %d, Total = ₹%.2f\n", count_small, total_small);
        printf("Medium Expenses (< ₹500)  : Count = %d, Total = ₹%.2f\n", count_medium, total_medium);
        printf("Large Expenses (>= ₹500)  : Count = %d, Total = ₹%.2f\n", count_large, total_large);
        printf("-----------------------------------------\n");
        printf("Total Valid Expenses      : %d\n", count_valid);
        printf("Grand Total Expense       : ₹%.2f\n", total_valid);
        printf("Average Valid Expense     : ₹%.2f\n", average_valid);
    } else {
        printf("No valid expenses were entered.\n");
    }
    printf("=========================================\n");

    return 0;
}
