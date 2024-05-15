#ifndef _DICE_H_
#define _DICE_H_
#include <stdlib.h>
#define maxProbability 90

int dise(int fourse, int dicePool, int probability) {
	if (probability > maxProbability) {
		probability = maxProbability;
	}

	if (dicePool <= fourse) {
		return dicePool;
	}

	int count = 0;

	for (int i = 0; i < dicePool - fourse; i++) {
		if (probability > rand() % 100) {
			count++;
		}
	}

	return count + fourse;
}

#endif // _DICE_H_
