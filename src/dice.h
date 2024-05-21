#ifndef _DICE_H_
#define _DICE_H_
#include <stdlib.h>
#define maxProbability 90

int dice(int focus, int dicePool, int probability) {
	if (probability > maxProbability) {
		probability = maxProbability;
	}

	if (dicePool <= focus) {
		return dicePool;
	}

	int count = 0;

	for (int i = 0; i < dicePool - focus; i++) {
		if (probability > rand() % 100) {
			count++;
		}
	}

	return count + focus;
}

#endif // _DICE_H_
