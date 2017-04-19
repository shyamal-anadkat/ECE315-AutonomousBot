#include "encoders.h"

// computes number of pulses required to acc. for given distance 
float encode(float inches){
	return (inches * 12.15);
}