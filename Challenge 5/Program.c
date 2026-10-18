#include <stdio.h>
#include <math.h>

int main()
{
    int ch, n, i, fact;
    float a, b, c, x, d, x1, x2;

    do
    {
        printf("\n1. Linear Equation");
        printf("\n2. Factorial");
        printf("\n3. Quadratic Equation");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                printf("Enter a and b: ");
                scanf("%f%f", &a, &b);

                if(a != 0)
                {
                    x = -b / a;
                    printf("x = %.2f\n", x);
                }
                else if(b == 0)
                {
                    printf("Infinitely many solutions\n");
                }
                else
                {
                    printf("No solution\n");
                }
                break;

            case 2:
                printf("Enter a number from 0 to 12: ");
                scanf("%d", &n);

                if(n < 0 || n > 12)
                {
                    printf("Invalid number\n");
                }
                else
                {
                    fact = 1;
                    for(i = 1; i <= n; i++)
                    {
                        fact = fact * i;
                    }
                    printf("Factorial = %d\n", fact);
                }
                break;

            case 3:
                printf("Enter a, b and c: ");
                scanf("%f%f%f", &a, &b, &c);

                if(a == 0)
                {
                    printf("Not a quadratic equation\n");
                }
                else
                {
                    d = b * b - 4 * a * c;

                    if(d > 0)
                    {
                        x1 = (-b + sqrt(d)) / (2 * a);
                        x2 = (-b - sqrt(d)) / (2 * a);

                        printf("Two distinct real roots\n");
                        printf("x1 = %.2f\n", x1);
                        printf("x2 = %.2f\n", x2);
                    }
                    else if(d == 0)
                    {
                        x1 = -b / (2 * a);
                        printf("Two equal real roots\n");
                        printf("x = %.2f\n", x1);
                    }
                    else
                    {
                        printf("No real roots\n");
                    }
                }
                break;

            case 4:
                printf("Exiting program\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while(ch != 4);

    return 0;
}
