#include <stdint.h>


int eval(uint8_t organism);
uint8_t* generate_population(void);
void advance_six(uint8_t* population);
void crossover(uint8_t* population);
void mutate(uint8_t* population);
