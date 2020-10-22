
#include "pch.h"
#include "Interface.h"
#include "Environment.h"


Model* environment_create(const char configfile[], const char state_file[], const char logfile[], const char messages[], unsigned int itial_time)
{
	std::ifstream config(configfile);

	if (!config.is_open())
	{
		std::cout << "Config file not found";
		//return;
	}
	std::ifstream state(state_file);

	if (!state.is_open())
	{
		std::cout << "State file not found";
		//return;
	}

	std::ofstream log(logfile);


	if (!log.is_open())
	{
		std::cout << "Log file not found";
		//return;
	}

	
	Model* ptr = new Environment(config,state,log);
	return ptr;

}

Model::~Model()
{
}
