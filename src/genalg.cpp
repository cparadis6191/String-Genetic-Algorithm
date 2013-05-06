#include <iostream>
#include <bitset>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "genalg.h"


using namespace std;

int main(int argc, char* argv[]) {
	// Seed the RNG algorithm
	srand(time(NULL));


	// Generate the initial population
	genalg population;

	// Print the population
	cout << population;

	// Step through generations
	for (int j = 0; j < atoi(argv[1]); j++) {
		population.step();
	}

	// Print the population
	cout << population;


	return 0;
}


// TODO Put these definitions in another file
genalg::genalg() {
	generation = 0;
	fitness = new int[6]();
	population = new uint8_t[6];

	// Create the initial random population
	for (int i = 0; i < 6; i++) {
		// Not the best method to generate random bits
		population[i] = (uint8_t) rand();
	}

	// Evaluate the initial fitness
	evaluate();


	return;
}


genalg::~genalg() {
	delete[] fitness;
	delete[] population;


	return;
}


// Calculates the fitness values for each organism this generation
void genalg::evaluate(void) {
	average_fitness = 0;

	// For each organism
	for (int i = 0; i < 6; i++) {
		fitness[i] = 1;

		// Compare each bit to the previous bit
		for (int j = 0; j < 7; j++) {
			// If current bit doesn't equal next bit return 1, else 0
			fitness[i] += (((population[i]&(1 << j)) != ((population[i]&(2 << j)) >> 1))?1:0);
		}

		average_fitness += fitness[i];
	}

	average_fitness /= 6;


	return;
}


// Pick six to advance based on fitness
void genalg::advance_six(void) {
	uint8_t new_population[6];

	int fitness_sum = 0;
	double normalized_fitness[6];
	double integral_fitness[6];

	double random;

	for (int i = 0; i < 6; i++) {
		fitness_sum += fitness[i];
	}

	for (int i = 0; i < 6; i++) {
		normalized_fitness[i] = fitness[i]/((double) fitness_sum);
	}

	integral_fitness[0] = normalized_fitness[0];
	for (int i = 1; i < 6; i++) {
		integral_fitness[i] = normalized_fitness[i] + integral_fitness[i - 1];
	}

	// Choose the six populations to mate
	for (int i = 0; i < 6; i++) {
		random = (double) rand()/(RAND_MAX);

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


void genalg::crossover(void) {
	// Pick a crossover point from 1 to 7
	int crossover_point0 = rand()%7 + 1;
	int crossover_point1 = rand()%7 + 1;
	int crossover_mask0 = 0;
	int crossover_mask1= 0;

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


void genalg::mutate(void) {
	int rand_string = rand()%6;
	int rand_bit = rand()%8;

	// Flip a random bit in a random string
	population[rand_string] ^= (1 << rand_bit);
	

	return;
}


// Apply all the rules for creating a new generation
void genalg::step(void) {
	advance_six();
	crossover();
	mutate();
	evaluate();

	generation++;

	return;
}


ostream& operator<<(ostream& os, const genalg& population) {
	cout << "Generation " << population.generation << ": " << endl;
	cout << "Average Fitness of: " << population.average_fitness << endl;

	for (int i = 0; i < 6; i++){
		cout << bitset<8>(population.population[i]).to_string();
		cout << " " << population.fitness[i] << endl;
	} 

	
	return os;
}


uint8_t genalg::operator[](const int i) const { return population[i]; }
