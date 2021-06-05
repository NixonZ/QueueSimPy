#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include "station.h"
#include "includes.h"
#include "tandem.h"
#include "queue_graphv2.h"
namespace py = pybind11;

// int add(int i, int j=2) {
//     return i + j;
// }

PYBIND11_MODULE(simulationpy, m) {
    m.doc() = "Simulation for delay prediction.\n We follow a object oriented approach for creating a general Queueing System and getting simulated wait time data."; // optional module docstring

    // m.def("add", &add, "A function which adds two numbers",py::arg("i"),py::arg("j")=2);

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
        .def(py::init<long,C_type,event_type_list,int,float,priority_type,float,int>(),
                py::arg("init_mxN"),
                py::arg("C_para"),
                py::arg("dept_para"),
                py::arg("init_num_class") = 0,
                py::arg("PatienceTimes_para") = 0,
                py::arg("priority_type_para") = std::vector<priority_type>(1,[]() -> int {return int(0);})[0],
                py::arg("t") = 0,
                py::arg("init_n") =0
                )
        .def(py::init<long,C_type,float,int,event_type_list,priority_type,float,int>(),
                py::arg("init_mxN"),
                py::arg("C_para"),
                py::arg("init_dept"),
                py::arg("init_num_class") = 0,
                py::arg("PatienceTimes_para") = event_type_list( 1 , [](float t) -> float { return (0.0); }  ),
                py::arg("priority_type_para") = std::vector<priority_type>(1,[]() -> int {return int(0);})[0],
                py::arg("t") = 0,
                py::arg("init_n") =0
                )
        .def(py::init<long,int,float,int,event_type_list,priority_type,float,int>(),
                py::arg("init_mxN"),
                py::arg("init_C"),
                py::arg("init_dept"),
                py::arg("init_num_class") = 0,
                py::arg("PatienceTimes_para") = event_type_list( 1 , [](float t) -> float { return (0.0); }  ),
                py::arg("priority_type_para") = std::vector<priority_type>(1,[]() -> int {return int(0);})[0],
                py::arg("t") = 0,
                py::arg("init_n") =0
                )
        .def(py::init<long,int,event_type_list,int,event_type_list,priority_type,float,int>(),
                py::arg("init_mxN"),
                py::arg("init_C"),
                py::arg("dept_para"),
                py::arg("init_num_class") = 0,
                py::arg("PatienceTimes_para") = event_type_list( 1 , [](float t) -> float { return (0.0); }  ),
                py::arg("priority_type_para") = std::vector<priority_type>(1,[]() -> int {return int(0);})[0],
                py::arg("t") = 0,
                py::arg("init_n") =0
                )
        .def(py::init<long,int,event_type,int,event_type_list,priority_type,float,int>(),
                py::arg("init_mxN"),
                py::arg("init_C"),
                py::arg("init_dept"),
                py::arg("init_num_class") = 0,
                py::arg("PatienceTimes_para") = event_type_list( 1 , [](float t) -> float { return (0.0); }  ),
                py::arg("priority_type_para") = std::vector<priority_type>(1,[]() -> int {return int(0);})[0],
                py::arg("t") = 0,
                py::arg("init_n") =0
                )
        .def(py::init<long,C_type,event_type,int,event_type_list,priority_type,float,int>(),
                py::arg("init_mxN"),
                py::arg("C_para"),
                py::arg("init_dept"),
                py::arg("init_num_class") = 0,
                py::arg("PatienceTimes_para") = event_type_list( 1 , [](float t) -> float { return (0.0); }  ),
                py::arg("priority_type_para") = std::vector<priority_type>(1,[]() -> int {return int(0);})[0],
                py::arg("t") = 0,
                py::arg("init_n") =0
                )
        .def(py::init<const station>(),py::arg("copy"))
        .def("print_station_status",&station::print_station_status,py::arg("t"))
        .def("find_min_k",&station::find_min_k)
        .def("find_min_td",&station::find_min_td)
        .def("server_updates",&station::server_updates,py::arg("t"))
        .def("departure_updates",&station::departure_updates,py::arg("t"))
        .def("add_customer_to_station",&station::add_customer_to_station,
                py::arg("t"),
                py::arg("curr_customer"),
                py::arg("keep_virtual") = false,
                py::arg("arrival_process") = event_type_list(1, [](float t)-> float{return 0;} ),
                py::arg("ta") = std::vector<float>(1,0.0) )
        .def("write_to_csv",&station::write_to_csv,py::arg("file_name"))
        .def("get_counter_variable",&station::get_counter_variable)
        .def("find_queue_len",&station::find_queue_len)
        .def("logger",py::overload_cast<int,float>(&station::logger),py::arg("station_id"),py::arg("t"))
        .def("logger",py::overload_cast<std::string,float>(&station::logger),py::arg("station_id"),py::arg("t"))
        .def("reset_queue",&station::reset_queue,py::arg("t"))
        .def("minimum_residual_time",&station::minimum_residual_time,py::arg("t"))
        .def("access_system_state",&station::access_system_state,py::arg("t"))
        .def("initialize_CSV",&station::initialize_CSV,py::arg("file_name"))
        .def("dump_counter_variable_memory",py::overload_cast<std::string>(&station::dump_counter_variable_memory),py::arg("file_name"))
        .def("dump_counter_variable_memory",py::overload_cast<>(&station::dump_counter_variable_memory));

    py::class_<tandem>(m,"Tandem")
        .def(py::init<std::vector<station>,event_type_list,int>(),
                py::arg("temp"),
                py::arg("PatienceTimes_para") = event_type_list( 1 , [](float t) -> float { return (0.0); }  ),
                py::arg("num_class_para") = 0)
        .def(py::init<const tandem>(),py::arg("copy"))
        .def("find_least_dep_time",&tandem::find_least_dep_time)
        .def("print_system_status",&tandem::print_system_status,py::arg("t"))
        .def("add_customer_to_system",&tandem::add_customer_to_system,
                py::arg("t"),
                py::arg("curr_customer"),
                py::arg("keep_virtual") = false,
                py::arg("arrival_process") = event_type_list(1, [](float t)-> float{return 0;} ),
                py::arg("ta") = std::vector<float>(1,0.0))
        .def("departure_updates",&tandem::departure_updates,py::arg("station_index"),py::arg("t"))
        .def("server_updates",&tandem::server_updates,py::arg("t"))
        .def("write_to_csv",&tandem::write_to_csv,py::arg("tandem_name"))
        .def("logger",&tandem::logger,py::arg("t"))
        .def("initialize_CSV",&tandem::initialize_CSV,py::arg("file_name"))
        .def("dump_counter_variable_memory",&tandem::dump_counter_variable_memory,py::arg("file_name"))
        .def("num_classes",&tandem::num_classes);

    py::class_<graphv2>(m,"QNetwork")
        .def(py::init<const graphv2>(),py::arg("copy"))
        .def(py::init<int,int,std::vector<std::vector<std::pair<int, float>>>,std::vector<station>,event_type_list>(),
                py::arg("init_N"),
                py::arg("init_max_queue_len"),
                py::arg("init_network"),
                py::arg("temp"),
                py::arg("PatienceTimes"))
        .def("find_least_dep_time",&graphv2::find_least_dep_time)
        .def("add_customer_to_graph",&graphv2::add_customer_to_graph,py::arg("t"),py::arg("customer_id"))
        .def("departure_updates",&graphv2::departure_updates,py::arg("station_index"),py::arg("t"))
        .def("server_updates",&graphv2::server_updates,py::arg("t"))
        .def("write_to_csv",&graphv2::write_to_csv,py::arg("file_name"))
        .def("initialize_CSV",&graphv2::initialize_CSV,py::arg("file_name"))
        .def("dump_counter_variable_memory",&graphv2::dump_counter_variable_memory,py::arg("file_name"))
        .def("logger",&graphv2::logger,py::arg("t"))
        .def("num_classes",&graphv2::num_classes)
        .def("add_customer_to_graph_vir",&graphv2::add_customer_to_graph_vir,
                py::arg("t"),
                py::arg("curr_customer"),
                py::arg("keep_virtual"),
                py::arg("arrival_process") = event_type_list(1, [](float t)-> float{return 0;} ),
                py::arg("ta") = std::vector<float>(1,0.0));
}

// c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) ./src/main.cpp ./src/station.cpp ./src/tandem.cpp ./src/queue_graphv2.cpp  -o simulationpy$(python3-config --extension-suffix)