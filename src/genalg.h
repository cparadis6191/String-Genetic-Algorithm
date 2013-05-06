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
		int evaluate(uint8_t organism) const;
		// Choose six from the previous population to mate
		void advance_six(void);
		// Crossover the first two pairs
		void crossover(void);
		// Mutate a random bit of all the organisms
		void mutate(void);

		// Overloaded operators for easy printing
		uint8_t operator[](const int nIndex) const;
		friend std::ostream& operator<<(std::ostream& os, const genalg& obj);
		

	private:
		unsigned int generation;
		int* fitness;
		uint8_t* population;
};

#endif
