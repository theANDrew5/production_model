// MicronModel.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <fstream>
#include <string>
#include "Environment.h"
/*
#include "production_model\Machine.h"
#include "production_model\Batch.h"
#include <list>
#include <vector>
#include <mysqlx\xdevapi.h>
#include "production_model\Recipe.h"
*/
/*
using ::std::cout;
using ::std::endl;
using namespace mysqlx;
int main(int argc, const char* argv[])
try {
	cout << "Creating session "
		<< " ..." << endl;

	std::string databaseName = "sosable_v0.6";

	Session sess("localhost", 33060, "root", "Track_100");

	cout << "Connected!" << endl;


	sess.sql("use `" + databaseName + "`;").execute();

	//int machinesAmount = sess.sql("SELECT COUNT(*) FROM machines;").execute().fetchOne().get(0);

	auto Result = sess.sql("CALL `getMachineData`();").execute();

	//===================		Creating machine objects from DB		===============================

	std::vector<M_flow> machineFlow = {};
	std::vector<M_group> machineGroup = {};
	std::vector<M_stack> machineStack = {};

	Machine* machine = nullptr;

	int tmpId = -1;

	for (auto iter = Result.begin(); iter != Result.end(); ++iter)
	{
		int Id = (*iter).get(0);

		if (Id != tmpId)
		{
			int state = (*iter).get(3);
			int type = (*iter).get(4);
			unsigned int recipeId = (*iter).get(1);
			unsigned int recipeTime = (*iter).get(2);

			switch (type)
			{
			case 0:

				machineFlow.push_back(M_flow(Id, { Recipe(recipeId, recipeTime) }, state));
				machine = &machineFlow.back();

				break;
			case 1:

				machineGroup.push_back((M_group(Id, { Recipe(recipeId, recipeTime) }, state)));
				machine = &machineGroup.back();

				break;

			case 2:

				machineStack.push_back((M_stack(Id, { Recipe(recipeId, recipeTime) }, state)));
				machine = &machineStack.back();

				break;

			default:
				break;
			}

			tmpId = Id;
		}
		else
		{
			machine->addRecipe(Recipe((*iter).get(1), (*iter).get(2)));
		}

	}

	//================	base class pionters for polymorthism		=====================

	std::vector<Machine*> machinesSet;

	int machinesAmount = machineFlow.size() + machineGroup.size() + machineStack.size();

	machinesSet.resize(machinesAmount);

	for (auto iter = machineFlow.begin(); iter != machineFlow.end(); ++iter)
	{
		machinesSet[iter->get_ID() - 1] = &(*iter);
	}

	for (auto iter = machineGroup.begin(); iter != machineGroup.end(); ++iter)
	{
		machinesSet[iter->get_ID() - 1] = &(*iter);
	}

	for (auto iter = machineStack.begin(); iter != machineStack.end(); ++iter)
	{
		machinesSet[iter->get_ID() - 1] = &(*iter);
	}



	return 0;
}

catch (const mysqlx::Error &err)
{
	cout << "ERROR: " << err << endl;
	return 1;
}

catch (std::exception &ex)
{
	cout << "STD EXCEPTION: " << ex.what() << endl;
	return 1;
}
catch (const char *ex)
{
	cout << "EXCEPTION: " << ex << endl;
	return 1;
}


<<<<<<< HEAD
=======

*/
int main()
{
    std::ifstream config ("ConfigFile.txt");
    std::ifstream state ("StateFile.txt");
    std::ofstream log("LOG.txt");
    Environment ev(config,state,log);
    //ev.do_step();
    std::vector<unsigned int>IDs{5,6,7};
    ev.replace_queue(IDs,3);
    //ev.add_batch(1,1,0);
    //ev.add_batch(3,1,0);
    std::cout<<ev<<'\n';
	ev.add_batch(IDs, 3, 0);
	ev.do_step(2);
	
    //std::cout<<ev;


    return 0;

}
//>>>>>>> b1ead0d283727d772de77b6a099414a3d51877f6
