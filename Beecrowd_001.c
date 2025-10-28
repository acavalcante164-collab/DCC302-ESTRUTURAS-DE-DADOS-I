#include <stdio.h>

int main() {
    int N, M; // N = cashiers, M = clients
    scanf("%d %d", &N, &M);

    int cashier_speeds[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &cashier_speeds[i]);
    }

    // This array will store the timestamp when each cashier becomes free.
    // We use 'long long' to avoid any potential overflow with large inputs.
    long long cashier_finish_times[N];
    for (int i = 0; i < N; i++) {
        cashier_finish_times[i] = 0; // All cashiers are free at time 0.
    }

    // Process each client one by one
    for (int j = 0; j < M; j++) {
        int client_items;
        scanf("%d", &client_items);

        // Find the cashier who is free the earliest (lowest finish time).
        // The one with the lowest ID is the tie-breaker.
        int best_cashier_idx = 0;
        for (int i = 1; i < N; i++) {
            if (cashier_finish_times[i] < cashier_finish_times[best_cashier_idx]) {
                best_cashier_idx = i;
            }
        }

        // Calculate the service time for this client with the chosen cashier.
        long long service_time = (long long)cashier_speeds[best_cashier_idx] * client_items;

        // Update the finish time for the chosen cashier.
        cashier_finish_times[best_cashier_idx] += service_time;
    }

    // The total time is the time the last cashier finishes.
    // So, we find the maximum finish time among all cashiers.
    long long total_time = 0;
    for (int i = 0; i < N; i++) {
        if (cashier_finish_times[i] > total_time) {
            total_time = cashier_finish_times[i];
        }
    }

    printf("%lld\n", total_time);

    return 0;
}