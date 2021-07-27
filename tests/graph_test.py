from queuesimpy import QNetwork,Station,INF
import numpy as np
from random import random
import time


U = lambda : random()
Exp = lambda lmbda: -1.0*np.log(U())/lmbda

def call_event_type_list(event_type_list,t):
    events = []
    for event in event_type_list:
        events.append(event(t))
    return events

Station_list = \
[
# 0
 Station(5,5,[lambda t: Exp(0.14),lambda t: Exp(0.13)],2,[lambda t: INF,lambda t: INF]),
 # 1
 Station(20,20,[lambda t: Exp(0.5),lambda t: Exp(0.6)],2,[lambda t: INF,lambda t: INF]),
 # 2
 Station(10,10,[lambda t: Exp(0.25),lambda t: Exp(0.3)],2,[lambda t: INF,lambda t: INF]),
 # 3
 Station(5,5,[lambda t: Exp(0.14),lambda t: Exp(0.13)],2,[lambda t: INF,lambda t: INF])
]

arrival_processes = [
    lambda t: Exp(0.0012),
    lambda t: Exp(0.011)
]

patience_time = [
    lambda t: INF,
    lambda t: INF
]

network = [
           [(1,0.5),(2,0.3),(3,0.2)],
           [(2,1)],
           [(3,1)],
           []
]

System = QNetwork(0,0,network,Station_list,patience_time)

discrete_events = 0
arriving_customer = 0
t = 0.0

ta = call_event_type_list(arrival_processes,t)

waiting_time = []
System.initialize_CSV("./graph",False)


System.logger(t)
start = time.time()

while discrete_events < 100000:
    least_station_index,least_dep_time = System.find_least_dep_time()

    t = np.min( [least_dep_time] + ta )
    System.server_updates(t)

    if t == np.min(ta):

        # arrival happening
        priority = np.argmin(ta)
        # System.add_customer_to_graph(t, [priority,arriving_customer])
        System.add_customer_to_graph_vir(t, [priority,arriving_customer],True,arrival_processes,ta)
        arriving_customer += 1
        ta[priority] = t + arrival_processes[priority](t)
    else:
        System.departure_updates(least_station_index,t)
    if discrete_events%1000 == 0:
        System.dump_counter_variable_memory("./graph",True,False)
    discrete_events += 1

end = time.time()
print(end - start)