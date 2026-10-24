#include <stdio.h>

int main() {
    int a[12], n, i, j, k, temp, r, d;
    int sum = 0, min, max, second = -1;
    int peaks = 0, run = 1, longest = 1, count = 0;

    do {
        printf("Enter N (5 to 12): ");
        scanf("%d", &n);
    } while (n < 5 || n > 12);

    for (i = 0; i < n; i++) {
        do {
            printf("Enter reading (0 to 1000): ");
            scanf("%d", &a[i]);
        } while (a[i] < 0 || a[i] > 1000);
    }

    min = max = a[0];

    printf("\nOriginal readings: ");
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
        sum += a[i];

        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];

        if (i > 0 && a[i] > a[i - 1])
            run++;
        else
            run = 1;

        if (run > longest)
            longest = run;
    }

    for (i = 0; i < n; i++)
        if (a[i] < max && (second == -1 || a[i] > second))
            second = a[i];

    for (i = 1; i < n - 1; i++)
        if (a[i] > a[i - 1] && a[i] > a[i + 1])
            peaks++;

    printf("\nSum = %d", sum);
    printf("\nAverage = %.2f", (float)sum / n);
    printf("\nMinimum = %d", min);
    printf("\nMaximum = %d", max);
if (second == -1)
        printf("\nNo second-largest distinct value");
    else
        printf("\nSecond largest = %d", second);

    printf("\nLocal peaks = %d", peaks);
    printf("\nLongest increasing run = %d", longest);

    printf("\nEnter K (rotation): ");
    scanf("%d", &k);

    k = ((k % n) + n) % n;

    for (i = 0; i < k; i++) {
        temp = a[n - 1];
        for (j = n - 1; j > 0; j--)
            a[j] = a[j - 1];
        a[0] = temp;
    }

    printf("Rotated readings: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    do {
        printf("\nEnter last two registration digits (0 to 99): ");
        scanf("%d", &r);
    } while (r < 0 || r > 99);

    d = (r % 9) + 1;

    for (i = 0; i < n; i++)
        if (a[i] % d == 0)
            count++;

    printf("\nD = %d", d);
    printf("\nDivisible count = %d\n", count);

    return 0;
}
