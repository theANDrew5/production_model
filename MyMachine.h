// This header represents description of Machine clases
//Machines can process queue simultaneously, step-by-step and using different chambers
// Class Machines is a base class
// Class MachinePool represets implementation of simultaneous processing
// Class MachineFlow represets implementation of step-by-step proc
// Class MachineChamber represetns implementation of chambers 




#ifndef _MY_MACHINE_HEADER_

#define _MY_MACHINE_HEADER_


#include <string>
#include <list>
#include "Batch.h"
#include "Recipe.h"
#include "Event.h"
#include <vector>



class Machine
{

public:

	//		Default constructor
	Machine(); 

	//		Main constructor
	Machine(int Id, std::string Type, bool state, std::list <Batch*> queue = std::list<Batch*>{});

	//		Copy constructor
	Machine( const Machine &ref);


	//		Protected Variables Setters

	void setId(int Id);

	void setProcType(std::string Type);

	void setQueue(std::list <Batch*> queue);

	void setState(bool newState);


	//		Protected Variables Getters
	int getId();

	std::string getProcType();

	std::list <Batch*> getQueue();

	bool getState();
	

	//		Add new items to queue
	void addQueue(std::list <Batch*> Bachces);

	//		Indicates if the object contains trivial variables (except Queue)
	bool isTrivial(); 

	//		
	Event generateEvent();


	//		Virtual destructor
	virtual ~Machine();

protected:
	
	//		Machie Id with respect to DB 
	int Id;

	//		Proc Type
	std::string procType;

	//		Queue (Why do not use std::queue?) for machine
	std::list <Batch*> queue;

	//		Indicates if Machine is broken
	bool state; 

};



#endif // !MyMachineClass