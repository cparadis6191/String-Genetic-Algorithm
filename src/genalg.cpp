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
		// Changes + 1
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
	double probability[6];
	double integral_probability[6];

	double random_spin;


	// Find the sum of the fitnessess
	for (int i = 0; i < 6; i++) {
		fitness_sum += fitness[i];
	}

	// Calculate each probability
	for (int i = 0; i < 6; i++) {
		probability[i] = fitness[i]/((double) fitness_sum);
	}

	// Integrate to get a CDF of sorts
	integral_probability[0] = probability[0];
	for (int i = 1; i < 6; i++) {
		integral_probability[i] = probability[i] + integral_probability[i - 1];
	}

	// Choose the six organisms to mate
	for (int i = 0; i < 6; i++) {
		// Spin the roulette wheel
		random_spin = ((double) rand())/RAND_MAX;

		// Find which organism has been chosen
		if (random_spin < integral_probability[0]) {
			new_population[i] = population[0];

		} else if (random_spin < integral_probability[1]) {
			new_population[i] = population[1];

		} else if (random_spin < integral_probability[2]) {
			new_population[i] = population[2];

		} else if (random_spin < integral_probability[3]) {
			new_population[i] = population[3];

		} else if (random_spin < integral_probability[4]) {
			new_population[i] = population[4];

		} else {
			new_population[i] = population[5];

		}
	}

	// Assign the new population to the class array
	for (int i = 0; i < 6; i++) {
		population[i] = new_population[i];
	}


	return;
}


void genalg::crossover(void) {
	int crossover_point;
	int crossover_mask;
	uint8_t temp;

	// Crossover both pairs
	for (int i = 0; i < 3; i += 2) {
		// Pick a crossover point from 1 to 7
		crossover_point = (rand()%7 + 1);
		crossover_mask = 0;

		// Construct the crossover mask of 1s
		for (int j = 0; j < crossover_point; j++) {
			crossover_mask |= (1 << j);
		}

		// Save the lower bits of the first organism
		temp = population[i]&crossover_mask;

		// Clear the lower bits of the first organism
		population[i] &= ~crossover_mask;
		// Swap the lower bits of the first organism
		population[i] |= population[i + 1]&crossover_mask;

		// Clear the lower bits of the second organism
		population[i + 1] &= ~crossover_mask;
		// Swap the lower bits of the second organism
		population[i + 1] |= temp&crossover_mask;
	}


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
