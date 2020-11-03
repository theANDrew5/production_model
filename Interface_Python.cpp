#include"Interface_Python.h"
#include "pch.h"


void PyModel::time_shift(unsigned int time) 
{
	PYBIND11_OVERRIDE_PURE(
		void,
		Model,
		time_shift
	);
}

void PyModel::do_step_till_machine(unsigned int mch_ID) 
{
	PYBIND11_OVERRIDE_PURE(
		void,
		Model,
		do_step_till_machine
	);
}

void PyModel::do_step() 
{
	PYBIND11_OVERRIDE_PURE(
		void,
		Model,
		do_step
	);
}

void PyModel::do_step(unsigned int n)
{
	PYBIND11_OVERRIDE_PURE(
		void,
		Model,
		do_step
	);
}

void PyModel::add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos)
{
	PYBIND11_OVERRIDE_PURE(
		void,
		Model,
		add_batch
	);
}

void PyModel::add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos)
{
	PYBIND11_OVERRIDE_PURE(
		void,
		Model,
		add_batch
	);
}

void PyModel::replace_queue(std::vector<unsigned int> btc_IDs, unsigned int mch_ID)
{
	PYBIND11_OVERRIDE_PURE(
		void,
		Model,
		replace_queue
	);
}

namespace py = pybind11;

PYBIND11_MODULE(Model_python, m)
{
	py::class_<Model, PyModel>(m, "Model")
		.def("time_shift", &Model::time_shift)
		.def("do_step_till_machine", &Model::do_step_till_machine)
		.def("do_step", py::overload_cast<>(&Model::do_step))
		.def("do_step", py::overload_cast<unsigned int>(&Model::do_step))
		.def("add_batch", py::overload_cast<unsigned int, unsigned int, unsigned int> (&Model::add_batch))
		.def("add_batch", py::overload_cast<std::vector<unsigned int>, unsigned int, unsigned int> (&Model::add_batch))
		.def("replace_queue", &Model::replace_queue)
		;
}

