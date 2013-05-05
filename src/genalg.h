#ifndef _GENALG_H__
#define _GENALG_H__

#include <stdint.h>


class genalg {
	public:
		genalg();
		~genalg();

		// Evaluate the fitness of the organisms
		int eval(uint8_t organism) const;

		// Apply the rules
		void step(void);
		void advance_six(void);
		void crossover(void);
		void mutate(void);

		uint8_t operator[](const int nIndex) const;
		friend std::ostream& operator<<(std::ostream& os, const genalg& obj);
		

	private:
		uint8_t* population;
		unsigned int generation;
};

#endif
