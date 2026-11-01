#include <stdio.h>
int main() {
    int a[6][6],n,t,i,j,s,mr=0,mc=0,d1=0,d2=0,b=0,c=0,h=0,max;
    scanf("%d",&n);
    while(n<3||n>6) scanf("%d",&n);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++) {
            scanf("%d",&a[i][j]);
            while(a[i][j]<0||a[i][j]>100) scanf("%d",&a[i][j]);
        }

    scanf("%d",&t);
    while(t<1||t>100) scanf("%d",&t);
    max=a[0][0];

    for(i=0;i<n;i++) {
        s=0;
        for(j=0;j<n;j++) {
            s+=a[i][j];
            if(a[i][j]>max) max=a[i][j];
            if(a[i][j]>=t)c++;
            if(i==0||j==0||i==n-1||j==n-1)b+=a[i][j];
        }
        if(s>mr)mr=s;
    }

    for(j=0;j<n;j++) {
        s=0;
        for(i=0;i<n;i++)s+=a[i][j];
        if(s>mc)mc=s;
    }

    for(i=0;i<n;i++) {
        d1+=a[i][i]; d2+=a[i][n-1-i];
    }

    printf("Highest risk: %d\n",max);
    printf("Risky cells: %d\n",c);
    printf("Diagonal sums: %d %d\n",d1,d2);
    printf("Boundary total: %d\n",b);
    printf("Highest row total: %d\n",mr);
    printf("Highest column total: %d\n",mc);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++) {
            if(a[i][j]==max)printf("Max at (%d,%d)\n",i+1,j+1);
            if(i>0&&j>0&&i<n-1&&j<n-1&&a[i][j]>=t&&
            a[i][j]>a[i-1][j]&&a[i][j]>a[i+1][j]&&
            a[i][j]>a[i][j-1]&&a[i][j]>a[i][j+1]) {
                printf("Hotspot (%d,%d)\n",i+1,j+1); h++;
            }
        }

    if(d1==d2)printf("Diagonals balanced\n");
    if(h)printf("CRITICAL\n");
    else if(c>=n)printf("WARNING\n");
    else printf("NORMAL\n");
    if(!h)printf("No hotspots\n");
    return 0;
}

