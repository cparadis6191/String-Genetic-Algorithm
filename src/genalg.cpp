#include <iostream>
#include <bitset>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include "genalg.h"


using namespace std;

int main(void) {
	uint8_t* population;

	// Seed the RNG algorithm
	srand(time(NULL));


	// Generate the initial population
	population = generate_population();

	cout << "Generation 0:" << endl;
	for (int i = 0; i < 6; i++){
		cout << bitset<8>(population[i]).to_string();
		cout << " " << eval(population[i]) << endl;
	}

	for (int j = 0; j < 1000000; j++) {
		advance_six(population);
		crossover(population);
		mutate(population);
	}

	cout << endl << "Generation 4:" << endl;
	for (int i = 0; i < 6; i++){
		cout << bitset<8>(population[i]).to_string();
		cout << " " << eval(population[i]) << endl;
	}


	return 0;
}


// Returns the number of changes in a string plus one
int eval(uint8_t organism) {
	int fitness = 0;

	for (int i = 0; i < 7; i++) {
		fitness += ((organism & (1 << i)) != ((organism & (2 << i)) >> 1))?1:0;
	}


	return (fitness + 1);
}


// Seed in the main function
uint8_t* generate_population(void) {
	uint8_t* population = (uint8_t*) calloc(6, sizeof(uint8_t));

	for (int i = 0; i < 6; i++){
		population[i] = (uint8_t) rand();
	}


	return population;
}


// Pick six to advance based on fitness
void advance_six(uint8_t* population) {
	uint8_t new_population[6];

	int fitness_sum = 0;
	double normalized_fitness[6];
	double integral_fitness[6];

	double random;

	// Pick 
	for (int i = 0; i < 6; i++) {
		fitness_sum += eval(population[i]);
	}

	//cout << "Normalized Fitness: " << endl;
	for (int i = 0; i < 6; i++) {
		normalized_fitness[i] = eval(population[i])/((double) fitness_sum);
		//cout << normalized_fitness[i] << endl;
	}

	//cout << "Integral Fitness: " << endl;
	integral_fitness[0] = normalized_fitness[0];
	for (int i = 1; i < 6; i++) {
		integral_fitness[i] = normalized_fitness[i] + integral_fitness[i - 1];
		//cout << integral_fitness[i] << endl;
	}

	// Choose the six populations to mate
	//cout << "Pick six random strings " << endl;
	for (int i = 0; i < 6; i++) {
		random = (double) rand()/(RAND_MAX);
		//cout << random << endl;

		if (random < integral_fitness[0]) {
			new_population[i] = population[0];

		} else if (random < integral_fitness[1]) {
			new_population[i] = population[1];

		} else if (random < integral_fitness[2]) {
			new_population[i] = population[2];

		} else if (random < integral_fitness[3]) {
			new_population[i] = population[3];

		} else if (random < integral_fitness[4]) {
			new_population[i] = population[4];

		} else {
			new_population[i] = population[5];

		}
	}

	for (int i = 0; i < 6; i++) {
		population[i] = new_population[i];
	}


	return;
}


void crossover(uint8_t* population) {
	// Pick a crossover point from 1 to 7
	int crossover_point0 = rand()%7 + 1;
	int crossover_point1 = rand()%7 + 1;
	int crossover_mask0 = 0;
	int crossover_mask1= 0;

	//printf("cross at: %i\n", crossover_point0);
	//printf("cross at: %i\n", crossover_point1);

	uint8_t temp0 = 0;
	uint8_t temp1 = 0;


	// Construct the crossover mask of 1s
	for (int i = 0; i < crossover_point0; i++) {
		crossover_mask0 |= (1 << i);
	}

	// Construct the crossover mask of 1s
	for (int i = 0; i < crossover_point1; i++) {
		crossover_mask1 |= (1 << i);
	}

	// Save the lower bits
	temp0 = population[0]&crossover_mask0;
	temp1 = population[1]&crossover_mask0;

	// Clear the lower bits
	population[0] &= ~crossover_mask0;
	population[1] &= ~crossover_mask0;

	// Cross the bits over
	population[0] |= temp1;
	population[1] |= temp0;


	// Save the lower bits
	temp0 = population[2]&crossover_mask1;
	temp1 = population[3]&crossover_mask1;

	// Clear the lower bits
	population[2] &= ~crossover_mask1;
	population[3] &= ~crossover_mask1;

	// Cross the bits over
	population[2] |= temp1;
	population[3] |= temp0;


	return;
}


void mutate(uint8_t* population) {
	int rand_string = rand()%6;
	int rand_bit = rand()%8;

	// Flip a random bit in a random string
	population[rand_string] ^= (1 << rand_bit);
	//cout << "Flip bit " << rand_bit << " of string " << rand_string << endl;
	

	return;
}
