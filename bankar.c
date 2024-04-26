#include <stdio.h>

int main() {
    
    int n, r, i, j, k;
    n = 5; 
    r = 6; 
    int alloc[5][6] = {
        {1, 2, 3, 3, 1, 1}, 
        {3, 0, 1, 1, 0, 2}, 
        {0, 1, 0, 2, 3, 0}, 
        {2, 3, 2, 4, 1, 0}, 
        {0, 0, 3, 3, 0, 2}  
    };

    int max[5][6] = {
        {7, 6, 3, 7, 5, 4}, 
        {3, 2, 4, 8, 4, 5},  
        {8, 0, 2, 6, 4, 3},  
        {2, 1, 2, 5, 1, 4},  
        {5, 2, 3, 3, 0, 3}   
    };

    int avail[6] = {5, 8, 4, 0, 3, 6};

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][r];
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < 5; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {

                int flag = 0;
                for (j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < r; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    printf("The SAFE Sequence is as follows\n");
    for (i = 0; i < n - 1; i++)
        printf(" P%d ->", ans[i]);
    printf(" P%d\n", ans[n - 1]);

    return (0);
}
