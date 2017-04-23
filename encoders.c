#include "encoders.h"

// computes number of pulses required to acc. for given distance 
float encode(float inches){
	return (inches * 12.15);
}

int pulse_to_inches(int pulse){
	return (pulse / 12.15);
}