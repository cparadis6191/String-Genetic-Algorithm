#ifndef _GENALG_H__
#define _GENALG_H__

#include <stdint.h>


class genalg {
	public:
		genalg();
		~genalg();

		// Step forward a generation
		void step(void);

		// Evaluate the fitness of the organisms
		void evaluate(void);
		// Choose six from the previous population to mate
		void advance_six(void);
		// Crossover the first two pairs
		void crossover(void);
		// Mutate a random bit of all the organisms
		void mutate(void);

		// Overloaded operator for easy printing
		friend std::ostream& operator<<(std::ostream& os, const genalg& obj);
		

	private:
		unsigned int generation;
		double average_fitness;
		int* fitness;
		uint8_t* population;
};

#endif
