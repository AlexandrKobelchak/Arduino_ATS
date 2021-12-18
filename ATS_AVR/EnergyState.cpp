#include "EnergyState.h"



AbstractEnergyState* EnergyStateUnit::states[] = {
		new EnergyLineState,
		new GeneratorState,
		new ErrorState
};
