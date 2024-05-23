#include "dice.h"

// Intent: Function to simulate rolling dice
// Pre: The focus, dice poo probability
// Post: Nothing
int dice(int focus, int dicePool, int probability) 
{
    // If the probability is greater than the maximum allowed, set it to the maximum
    if (probability > MAXPROBABILITY)
    {
        probability = MAXPROBABILITY;
    }

    // If the dice pool is less than or equal to focus, return the dice pool
    if (dicePool <= focus) 
    {
        return dicePool;
    }

    int count = 0;

    // Roll the dice
    for (int i = 0; i < dicePool - focus; i++) 
    {
        // Check if the roll falls within the probability range
        if (probability > rand() % 100) 
        {
            count++;
        }
    }

    // Return the total count of successful rolls plus the focus
    return count + focus;
}

double getExpectProbability(int focus, int diceNum, int expectNum, double probability) {
    if (expectNum > diceNum || expectNum < 0) return 0;
    if (focus > expectNum) return 0;
    if (focus > diceNum) focus = diceNum;
    if (focus < 0) focus = 0;
    if (probability > 100) probability = 100;
    if (probability < 0) probability = 0;
    if (focus == diceNum && focus == expectNum) 100;

    diceNum -= focus;
    expectNum -= focus;
    probability = probability / 100;
    double expectProbability = 1;
    for (int i = 0; i < expectNum; i++) {
        expectProbability *= probability;
    }
    for (int i = 0; i < (diceNum - expectNum); i++) {
        expectProbability *= (1 - probability);
    }
    expectProbability *= combination(diceNum, expectNum);

    //decimal 1 digital
    expectProbability *= 1000;
    expectProbability = (int)expectProbability;
    expectProbability /= 10;

    return expectProbability;
}

string formatProbability(double probability) {
    char c[10];
    sprintf(c, "%.1f%", probability);
    string str = c;
    return str;
}

int factorial(int n) {
    int arr[11] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800 };
    if (n < 11) {
        return arr[n];
    }
    else {
        return 1;
    }
}

// n C k
int combination(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}