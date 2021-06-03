from simulationpy import Station
from random import random
import numpy as np

U = lambda : random()
Exp = lambda lmbda: -1.0*np.log(U())/lmbda

def call_event_type_list(event_type_list,t):
	events = []
	for event in event_type_list:
		events.append(event(t))
	return events

arrival_processes = [
	lambda t: Exp(0.0012),
	lambda t: Exp(0.011)
]

service_time = [
	lambda t: Exp(0.14),
	lambda t: Exp(0.13)
]
patience_time = [
	lambda t: 5.0,
	lambda t: 5.0	
]

station = Station(10,10,service_time,2,patience_time)

discrete_events = 0
arriving_customer = 0
t = 0.0

ta = call_event_type_list(service_time,t)
priority = 0

while discrete_events < 100:

	t = np.min([station.find_min_td()]+ta)

	station.server_updates(t)

	if t == np.min(ta):

		# arrival happening
		priority = np.argmin(ta)
		station.add_customer_to_station(t, [priority,arriving_customer],True,arrival_processes,ta)
		arriving_customer += 1
		ta[priority] = t + arrival_processes[priority](t)
	else:
		station.departure_updates(t)
	# print(station.get_counter_variable())
	station.print_station_status(t)
	discrete_events += 1

# Simulation output in output.txt