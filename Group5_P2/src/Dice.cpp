#include "dice.h"

// Intent: Function to simulate rolling dice
// Pre: The focus, dice pool, and probability must be provided
// Post: Returns the count of successful rolls plus the focus
int dice(int focus, int dicePool, int probability) {
    // If the probability is greater than the maximum allowed, set it to the maximum
    probability = min(probability, MAXPROBABILITY);

    // If the dice pool is less than or equal to focus, return the dice pool
    if (dicePool <= focus) {
        return dicePool;
    }

    int count = 0;

    // Roll the dice
    for (int i = 0; i < dicePool - focus; i++) {
        // Check if the roll falls within the probability range
        if (probability > rand() % 100) {
            count++;
        }
    }

    // Return the total count of successful rolls plus the focus
    return count + focus;
}

// Intent: Calculate the expected probability of achieving a certain number of successes
// Pre: The focus, number of dice, expected number of successes, and probability must be provided
// Post: Returns the expected probability as a percentage
double getExpectProbability(int focus, int diceNum, int expectNum, double probability) {
    if (expectNum > diceNum || expectNum < 0) {
        return 0;
    }

    if (focus > expectNum) {
        return 0;
    }

    focus = min(focus, diceNum);
    focus = max(focus, 0);

    probability = min(probability, (double)100);
    probability = max(probability, (double)0);

    if (focus == diceNum && focus == expectNum) {
        return 100;
    }

    diceNum -= focus;
    expectNum -= focus;
    probability /= 100;
    double expectProbability = 1;

    for (int i = 0; i < expectNum; i++) {
        expectProbability *= probability;
    }

    for (int i = 0; i < (diceNum - expectNum); i++) {
        expectProbability *= (1 - probability);
    }

    expectProbability *= combination(diceNum, expectNum);

    return expectProbability * 100;
}

// Intent: Format a probability value as a string with a percentage sign
// Pre: Probability must be a valid double value
// Post: Returns the formatted probability string
string formatProbability(double probability) {
    char c[10];
    sprintf(c, "%.1f", probability);
    string str = c;
    return str + "%";
}

// Intent: Calculate the factorial of a given number
// Pre: n must be a non-negative integer
// Post: Returns the factorial of n
int factorial(int n) {
    int arr[11] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800 };

    if (n < 11) {
        return arr[n];
    }
    else {
        return 1;
    }
}

// Intent: Calculate the combination (n choose k)
// Pre: n and k must be non-negative integers with k <= n
// Post: Returns the number of ways to choose k elements from n elements
int combination(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}