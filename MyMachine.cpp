
#include "MyMachine.h"

Machine::Machine(): 
	Id(-1), procType(""), state(false)
{

}


Machine::Machine(int Id, std::string Type, bool state, std::list <Batch*> queue) :
	Id(Id), procType(Type), queue(queue), state(state)
{

}


Machine::Machine(const Machine &ref) :
	Id(ref.Id), procType(ref.procType), queue(ref.queue), state(ref.state)
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


bool Machine::isTrivial()
{
	if (state == false || Id == -1 || procType == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}


Event Machine::generateEvent()
{
	return Event();
}


void Machine::addQueue(std::list <Batch *> addList)
{
	for(std::list<Batch *>::iterator iter = addList.begin(); iter != addList.end();  iter++)
	{
		queue.push_back(*iter);
	}
	
}
