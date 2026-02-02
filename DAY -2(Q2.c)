#include <stdio.h>

int main() {
    int n, target;
    
    // Read size of array
    scanf("%d", &n);
    
    int nums[n];
    
    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    
    // Read target
    scanf("%d", &target);
    
    // Find two indices such that nums[i] + nums[j] == target
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                // Print indices (0-based)
                printf("%d %d\n", i, j);
                return 0; // exit after finding the solution
            }
        }
    }
    
    // If no solution found (though problem guarantees one)
    printf("No solution\n");
    return 0;
}
