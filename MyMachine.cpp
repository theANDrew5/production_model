
#include "MyMachine.h"

Machine::Machine(): 
	Id(-1), procType(""), queue({}), state(false), recipes({}), bufferSize(1)
{

}


Machine::Machine(int Id, std::string Type, bool state, std::list <Batch*> queue, std::vector<Recipe> recipes, const unsigned int bufSize) :
	Id(Id), procType(Type), queue(queue), state(state), recipes(recipes), bufferSize(bufSize)
{

}


Machine::Machine(const Machine &ref) :
	Id(ref.Id), procType(ref.procType), queue(ref.queue), state(ref.state), recipes(ref.recipes), bufferSize(ref.bufferSize)
{

}


Machine::~Machine()
{
	
}


void Machine::setId(int Id) 
{
	this-> Id = Id;
}


void Machine::setProcType(std::string Type)
{
	this->procType = Type;
}


void Machine::setQueue(std::list<Batch*> newQueue) 
{
	this->queue = newQueue;
}


void Machine::setState(bool newState) 
{
	this->state = newState;
}


void Machine::setResipes(std::vector<Recipe> newRecipes)
{
	this->recipes = newRecipes;
}


int Machine::getId()
{
	return this->Id;
}


std::string Machine::getProcType()
{
	return this->procType;
}


std::list<Batch*> Machine::getQueue()
{
	return this->queue;
}


bool Machine::getState()
{
	return this->state;
}


std::vector<Recipe> Machine::getRecipes()
{
	return this->recipes;
}


bool Machine::isTrivial()
{
	if (this->state == false || this->Id == -1 || this->procType == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Machine::addQueue(std::list <Batch *> addList)
{
	for(std::list<Batch *>::iterator iter = addList.begin(); iter != addList.end();  iter++)
	{
		this->queue.push_back(*iter);
	}
	
}


bool Machine::checkCurRecipe(Recipe recipe)
{
	if (this->currentRecipe.get_name() == recipe.get_name() &&
		this->currentRecipe.get_time() == recipe.get_time())
	{
		return true;
	}
	else 
	{
		return false;
	}
}


void Machine::setNewCurRecipe(Recipe newResipe)
{
	this->currentRecipe = newResipe;

	this->recipeChanged = true;
}

bool Machine::isRecInMachRecSet(Recipe recipe)
{
	for (size_t iter = 0; iter < this->recipes.size(); iter++)
	{
		if (recipe == this->recipes[iter]) 
		{
			return true;
		}
	}

	return false;
}