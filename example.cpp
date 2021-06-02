#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include "../simulation/components/station.h"
#include "../simulation/includes.h"
namespace py = pybind11;

int add(int i, int j=2) {
    return i + j;
}

PYBIND11_MODULE(simulationpy, m) {
    m.doc() = "Simulation for delay prediction.\n We follow a object oriented approach for creating a general Queueing System and getting simulated wait time data."; // optional module docstring

    m.def("add", &add, "A function which adds two numbers",py::arg("i"),py::arg("j")=2);

    py::class_<station>(m,"Station")
        .def(py::init<long,C_type,event_type_list,int,event_type_list,priority_type,float,int>(),
                py::arg("init_mxN"),
                py::arg("C_para"),
                py::arg("dept_para"),
                py::arg("init_num_class") = 0,
                py::arg("PatienceTimes_para") = event_type_list( 1 , [](float t) -> float { return (0.0); }  ),
                py::arg("priority_type_para") = std::vector<priority_type>(1,[]() -> int {return int(0);})[0],
                py::arg("t") = 0,
                py::arg("init_n") =0
                )
        .def("add_customer_to_station",&station::add_customer_to_station,
                py::arg("t"),
                py::arg("curr_customer"),
                py::arg("keep_virtual") = false,
                py::arg("arrival_process") = event_type_list(1, [](float t)-> float{return 0;} ),
                py::arg("ta") = std::vector<float>(1,0.0) )
        .def("print_station_status",&station::print_station_status,py::arg("t"));
}

// c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) example.cpp ../simulation/components/station.cpp  -o example$(python3-config --extension-suffix)