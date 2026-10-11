#include <stdio.h>

int main() {
    double purchase_amount;
    int customer_type;
    double delivery_distance;
    double discount_percent = 0.0;
    double discount_amount = 0.0;
    double amount_after_discount = 0.0;
    double delivery_charge = 0.0;
    double final_payable_amount = 0.0;
    printf("Enter purchase amount: ");
    scanf("%lf", &purchase_amount);

    printf("Enter customer type (1=Student, 2=Regular Customer): ");
    scanf("%d", &customer_type);

    printf("Enter delivery distance in km: ");
    scanf("%lf", &delivery_distance);

    if (customer_type == 1) {
        if (purchase_amount >= 2000) {
            discount_percent = 15.0;
        } else {
            discount_percent = 10.0;
        }
    }
    else if (customer_type == 2) {
        if (purchase_amount >= 3000) {
            discount_percent = 8.0;
        } else {
            discount_percent = 0.0;
        }
    }
    else {
        printf("\nInvalid customer type entered. Assuming 0%% discount.\n");
        discount_percent = 0.0;
    }

    discount_amount = (discount_percent / 100.0) * purchase_amount;
    amount_after_discount = purchase_amount - discount_amount;
    if (delivery_distance <= 5.0) {
        delivery_charge = 40.0;
    }
    else if (delivery_distance > 5.0 && delivery_distance <= 15.0) {
        delivery_charge = 70.0;
    }
    else {
        delivery_charge = 100.0;
    }
    final_payable_amount = amount_after_discount + delivery_charge;

    printf("\n=============================\n");
    printf("       BILLING DETAILS       \n");
    printf("=============================\n");
    printf("Purchase Amount:       %.2f\n", purchase_amount);
    printf("Discount Amount:       %.2f (%.0f%%)\n", discount_amount, discount_percent);
    printf("Amount After Discount: %.2f\n", amount_after_discount);
    printf("Delivery Charge:       %.2f\n", delivery_charge);
    printf("-----------------------------\n");
    printf("Final Payable Amount:  %.2f\n", final_payable_amount);
    printf("=============================\n");

    return 0;
}



