
#include <pybind11/pybind11.h>
#include"Environment.h"
#include "pch.h"


//Environment create_model(std::string& configfile, std::string& state_file, std::string& logfile, std::string& messages, unsigned int itial_time)
//{
//	std::ifstream config(configfile, std::ios_base::in);
//
//	if (!config.is_open())
//	{
//		std::cout << "Config file not found";
//		//return;
//	}
//
//	std::ifstream state(state_file, std::ios_base::in);
//
//	if (state.rdstate() == std::ios_base::failbit)
//	{
//		std::cout << "State file not found";
//	}
//
//	if (!state.is_open())
//	{
//		std::cout << "State file not found";
//		//return;
//	}
//
//	std::ofstream log(logfile);
//
//
//	if (!log.is_open())
//	{
//		std::cout << "Log file not found";
//		//return;
//	}
//
//	return Environment::Environment(config, state, log, std::cout, 0);
//}

class Py_Model
{
public:
	Py_Model(std::string& configfile, std::string& state_file, std::string& logfile, std::string& messages, unsigned int intial_time);
	~Py_Model();

	void time_shift(unsigned int time);//сдвинуть время модели
	void do_step_till_machine(unsigned int mch_ID);//моделировать до машины ID
	void do_step();//моделировать до коца
	void do_step(unsigned int n);//сделать n шагов моделирования
	void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0);//вставить в очередь машины партию
	void add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0);
	//вставить в очередь машины несколько партий
	void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID);//замена очереди, не заменяет нулевой элемент

	void test();
private:
	Environment* env_ptr;
};

Py_Model::Py_Model(std::string& configfile, std::string& state_file, std::string& logfile, std::string& messages, unsigned int intial_time)
{

	try
	{
		this->env_ptr = new Environment(configfile, state_file, logfile, messages, intial_time);
	}
	catch (pybind11::error_already_set& )
	{

	}
	
}

void Py_Model::test()
{
	std::cout << this->env_ptr;
}

Py_Model::~Py_Model()
{
	delete this->env_ptr;
}


void Py_Model::time_shift(unsigned int time)
{
	env_ptr->time_shift(time);
}


namespace py = pybind11;

PYBIND11_MODULE(Model_python, m)
{
	py::class_<Environment>(m, "Model")
		.def(py::init<>())
		.def(py::init<std::string&, std::string&, std::string&, std::string&, unsigned int>())
		.def("time_shift", &Environment::time_shift)
		.def("do_step_till_machine", &Environment::do_step_till_machine)
		.def("do_step", py::overload_cast<>(&Environment::do_step))
		.def("do_step", py::overload_cast<unsigned int>(&Environment::do_step))
		.def("add_batch", py::overload_cast<unsigned int, unsigned int, unsigned int> (&Environment::add_batch))
		.def("add_batch", py::overload_cast<std::vector<unsigned int>, unsigned int, unsigned int> (&Environment::add_batch))
		.def("replace_queue", &Environment::replace_queue)

		#if DEBUG
			.def("print_env", &Environment::print_env)
		#endif // DEBUG
		;

	py::class_<Py_Model>(m, "Model2")
		.def(py::init<std::string&, std::string&, std::string&, std::string&, unsigned int>())
		.def("test", &Py_Model::test)
		;
	//m.def("create_model", &create_model);
}


