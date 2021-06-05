#pragma once

#ifndef GRAPHV2_H
#define GRAPHV2_H

#include "station.h"
#include "tandem.h"
// Directed Graphs only station_list[0] -> entry station_list[N-1] -> exit[Every unconnected node is exit]
class graphv2
{
    int num_nodes;
    int N ; //Number of custmer in system
    int max_queue_len;
    std::vector< std::vector< std::pair<int,float> > > network ; // { adjacent node,probability of that edge }
    std::vector<station> station_list; // 0 : Entry to system , -1 : Exit to station
    std::vector<int> exit_stations;
    std::vector<graph_data> system_counter_variable;
    event_type_list PatienceTimes;
    /* 
    0 - Customer
    1 - Time of arrival
    2 - Number of people in system at arrival
    3 - Service times at last station
    4 - Departure times of system
    */
public:
    graphv2( const graphv2 &copy)
    {
        this->num_nodes = copy.num_nodes;
        this->N = copy.N;
        this->max_queue_len = copy.max_queue_len;
        this->network = copy.network;
        this->station_list = copy.station_list;
        this->exit_stations = copy.exit_stations;
        this->system_counter_variable = copy.system_counter_variable;
        this->PatienceTimes = copy.PatienceTimes;
    }
    graphv2(int init_N, int init_max_queue_len, std::vector<std::vector<std::pair<int, float>>> init_network, std::vector<station> temp, event_type_list PatienceTimes);
    // void calculate_distance();
    std::tuple<int, float> find_least_dep_time();
    void add_customer_to_graph(float t, customer customer_id);
    customer departure_updates(int station_index, float t);
    void server_updates(float t);
    void write_to_csv(std::string file_name);
    void initialize_CSV(std::string file_name);
    void dump_counter_variable_memory(std::string file_name);
    void logger(float t);
    int num_classes();
    void add_customer_to_graph_vir(float t,customer curr_customer,bool keep_virtual = false, event_type_list arrival_processes = { [](float t)-> float{return 0;} },std::vector<float> ta = {0.0});
};
#endif