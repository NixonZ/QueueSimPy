from queuesimpy import Station

x = Station(10,10,[lambda t:10.0,lambda t:15.0],2,[lambda t: 0.0,lambda t: 0.0])
x.add_customer_to_station(1.0,[0,0])
x.print_station_status(1.0)
x.add_customer_to_station(2.0,[1,1])
x.print_station_status(2.0)

# help(Station)

temp = x.get_counter_variable()
print(temp)