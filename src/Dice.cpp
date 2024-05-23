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