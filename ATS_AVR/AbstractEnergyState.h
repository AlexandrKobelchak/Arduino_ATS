#pragma once

enum energyState { ENERGY_LINE, GENERATOR_STARTING, ENERGY_GENERATOR, ERROR_STATE };

class AbstractEnergyState
{
public:
	virtual void BeginEnergyFault() = 0;
	virtual void EndEnergyFault() = 0;
	virtual void BeginStartGenerator() = 0;
	virtual void EndStartGenerator() = 0;
	virtual void BeginGeneratorEnergy() = 0;
	virtual void EndGeneratorEnergy() = 0;
	virtual void BeginError() = 0;
};

class EnergyLineState : public AbstractEnergyState {

public:

	void BeginEnergyFault() override {
	}
	void EndEnergyFault() override {
	}
	void BeginStartGenerator() override {
	}
	void EndStartGenerator() override {
	}
	void BeginGeneratorEnergy() override {
	}
	void EndGeneratorEnergy() override {
	}
	void BeginError() override {
	}
};

class GeneratorState : public AbstractEnergyState {
public:

	void BeginEnergyFault() override {
	}
	void EndEnergyFault() override {
	}
	void BeginStartGenerator() override {
	}
	void EndStartGenerator() override {
	}
	void BeginGeneratorEnergy() override {
	}
	void EndGeneratorEnergy() override {
	}
	void BeginError() override {
	}

};

class ErrorState : public AbstractEnergyState {
public:

	void BeginEnergyFault() override {
	}
	void EndEnergyFault() override {
	}
	void BeginStartGenerator() override {
	}
	void EndStartGenerator() override {
	}
	void BeginGeneratorEnergy() override {
	}
	void EndGeneratorEnergy() override {
	}
	void BeginError() override {
	}

};

class EnergyStateUnit
{
private:
	static AbstractEnergyState* states[];

public:
	static AbstractEnergyState& GetEnergyState(energyState state)
	{
		return *(states[(int)state]);
	}
};

AbstractEnergyState* EnergyStateUnit::states[] = {
		new EnergyLineState,
		new GeneratorState,
		new ErrorState 
};