from simulationpy import Station

x = Station(100,lambda t:100,[lambda t:10.0])
x.add_customer_to_station(1.0,[0,0])
x.print_station_status(1.0)