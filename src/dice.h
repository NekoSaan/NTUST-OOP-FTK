#pragma once
#include <stdlib.h>
#define maxProbability 90
int dise(int fourse,int amount,int probability) {
	if (probability > maxProbability) {
		probability = maxProbability;
	}
	if (amount <= fourse)
		return amount;
	int count = 0;
	for (int i = 0; i < amount - fourse; i++) {
		if (probability > rand() % 100) {
			count++;
		}
	}
	return count + fourse;
}