# dijkstra
c++ program incorporates the dijkstra algorithm to find the shortest path between two nodes 


Summary
Since the price that is charged to you on your Tokyo Metro card is based on the number of stops you past, I decided to run this
program on the Tokyo Metro Train routes in order to find the shortest path from one major
station to the next.

Applying the trains.txt file to the code and specifying a source and destination provides
the number of stops a commuter will have to take, in turn saving the commuter both time and
money. The program also specifies the specific station names and in the order they will need
to be taken to achieve the shortest path. For example, Asakusa does not have a direct train line
access to Shinjuku. However, if one travels from Asakusa station to Shibuya station and then
from there to Shinjuku station, that would be the shortest path with a commuter passing 18
stations in total. I found my results to accurate as I checked them with the route map of the
Tokyo Metro. This would be very beneficial to an unfamiliar commuter or tourist, such as
myself.

**Some optimizations I performed within my code could be the change from my
initial use of double arrays to the use of vectors. This improved my code because every
instance the matrix needed to be used in a function, I only needed to pass it by
reference, which in turn allowed me to save memory and increase performance.
