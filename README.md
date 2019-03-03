# gezgin 
Gezgin(means traveler in Turkish) is a project where I aim to learn about heuristics for travelling salesman problem. 
It takes TSPLIB instances as an input, you can use several heuristics on the problem. For example, you can use Croes
construction heuristic then improve the solution with 2opt heuristic.
To do that(for example on instance a280.tsp):

./tsp_solver croes 2opt a280.tsp
