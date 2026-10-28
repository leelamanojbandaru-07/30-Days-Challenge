#include <stdio.h>
int main() {
    int n, a[15];
    int missing = 0, duplicate = 0;
    int i, j, count;
    int missingCount = 0, duplicateCount = 0;
    int r, target, total = 0;
    int invalidRange = 0;

    printf("Enter N: ");
    scanf("%d", &n);

    if (n < 5 || n > 15) {
        printf("Invalid range\n");
        invalidRange = 1;
    } else {
        printf("Enter ticket IDs: ");

        for (i = 0; i < n; i++) {
            scanf("%d", &a[i]);

            if (a[i] < 1 || a[i] > n) {
                invalidRange = 1;
            }
        }

        if (invalidRange == 1) {
            printf("Invalid range\n");
        } else {
            for (i = 1; i <= n; i++) {
                count = 0;

                for (j = 0; j < n; j++) {
                    if (a[j] == i) {
                        count++;
                    }
                }

                if (count == 0) {
                    missing = i;
                    missingCount++;
                }

                if (count > 1) {
                    duplicate = i;
                    duplicateCount++;
                }
            }

            if (missingCount != 1 || duplicateCount != 1) {
                printf("Invalid scan log\n");
            } else {
                printf("Missing ID: %d\n", missing);
                printf("Duplicate ID: %d\n", duplicate);

                count = 0;

                for (i = 0; i < n; i++) {
                    for (j = i + 1; j < n; j++) {
                        if (a[i] > a[j]) {
                            count++;
                        }
                    }
                }

                printf("Out of order pairs: %d\n", count);

                printf("Enter R: ");
                scanf("%d", &r);

                target = (r % n) + 1;

                printf("Target: %d\n", target);
                printf("Matching positions: ");

                for (i = 0; i < n; i++) {
                    if (a[i] == target) {
                        printf("%d ", i + 1);
                        total++;
                    }
                }

                printf("\nCount: %d\n", total);
            }
        }
    }

    return 0;
}
