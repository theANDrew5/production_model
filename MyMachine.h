// This header represents description of Machine clases
// Machines can process queue simultaneously, step-by-step and using different chambers
// Class Machines is a base class
// Class MachinePool represets implementation of simultaneous processing
// Class MachineFlow represets implementation of step-by-step proc
// Class MachineChamber represetns implementation of chambers 




#ifndef MYMACHINE_HEADER

#define MYMACHINE_HEADER


#include <string>
#include <list>
#include "Batch.h"
#include "Recipe.h"
//#include "Event.h"
#include <vector>



class Machine
{

public:

	//		Default constructor
	Machine(); 

	//		Main constructor
	Machine(int Id, std::string Type, bool state, std::list <Batch*> queue = {}, std::vector<Recipe> recipes = {}, const unsigned int bufSize = 1);

	//		Copy constructor
	Machine( const Machine &ref);


	//		Protected Variables Setters

	void setId(int Id);

	void setProcType(std::string Type);

	void setQueue(std::list <Batch*> queue);

	void setState(bool newState);

	void setResipes(std::vector<Recipe> newRecipes);


	//		Protected Variables Getters
	int getId();

	std::string getProcType();

	std::list<Batch*> getQueue();

	bool getState();

	std::vector<Recipe> getRecipes();
	

	//		Add new items to queue
	void addQueue(std::list <Batch*> Bachces);

	//		Indicates if the object contains trivial variables (except Queue)
	bool isTrivial(); 

	//		If currentRecipe equels to newResipe Returns true, else - false
	bool checkCurRecipe(Recipe newRecipe);

	//		Set new current recipe
	void setNewCurRecipe(Recipe newRecipe);

	//		true if recipe is in set of Machine recipes, else - false
	bool isRecInMachRecSet(Recipe recipe);
	//		Generates an Event for Model
	//Event generateEvent();


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

	//		Recipes that could be processed by Machine
	std::vector<Recipe> recipes;

	//		The recipe executing at machine
	Recipe currentRecipe;

	//		Maximum amount of batches that could be proceed per working cicle
	const unsigned int bufferSize;

	//		Indicates if current recipe is changed
	bool recipeChanged;

};



#endif // _MY_MACHINE_HEADER_