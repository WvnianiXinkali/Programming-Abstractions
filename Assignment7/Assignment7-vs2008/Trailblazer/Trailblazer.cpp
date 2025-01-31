/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "hashmap.h"
#include "hashset.h"
#include "grid.h"
#include "random.h"
using namespace std;


void assembleRoad(HashMap<Loc, Loc>& parents, Vector<Loc>& answ, Loc temp){
	if(parents.containsKey(temp)){
		assembleRoad(parents, answ, parents.get(temp));
		answ.add(parents.get(temp));
	}
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {

	TrailblazerPQueue<Loc> pqueue;  // I use priority queue to determine next node to examine;
	pqueue.enqueue(start, heuristic(start, end, world));

	HashSet<Loc> usedLocs; // I use HashSet because it has really fast contains method so it helps when we need to check already examined nodes;

	HashMap<Loc, Loc> parents;  // Here I use Hashmap because it connects 2 things fastest, in this case it saves the road connects next node to its ancestor;

	HashMap<Loc, double> distSoFar; // Here I save distance price for every node so far and use hashmap for same purpose as before;

	distSoFar[start] = 0;
	
	while(!pqueue.isEmpty()){
		Loc curr = pqueue.dequeueMin();
		colorCell(world, curr, GREEN);
		usedLocs.add(curr);

		if(curr == end){
			break;
		}

		for(int i = -1; i < 2; i ++){
			for(int j = -1; j < 2; j++){
				Loc neighbour = makeLoc(curr.row + i, curr.col + j);
				if(world.inBounds(neighbour.row, neighbour.col)){
					if(!usedLocs.contains(neighbour)){
						usedLocs.add(neighbour);
						colorCell(world, neighbour, YELLOW);
						parents[neighbour] = curr;
						double dist = costFn(curr, neighbour, world);
						distSoFar[neighbour] = distSoFar.get(curr) + dist;
						pqueue.enqueue(neighbour, distSoFar.get(neighbour) + heuristic(neighbour, end, world));
					} else if(distSoFar.get(curr) + costFn(curr, neighbour, world) < distSoFar.get(neighbour)){
						distSoFar[neighbour] = distSoFar.get(curr) + costFn(curr, neighbour, world);
						parents[neighbour] = curr;
						pqueue.decreaseKey(neighbour, distSoFar.get(neighbour) + heuristic(neighbour, end, world));
					}
				}
			}
		}
	}
	
	Vector<Loc> answ;
	answ.add(start);
	Loc temp = end;
	assembleRoad(parents, answ, temp);
	answ.add(end);
	
    return answ;
}

Set<Edge> createMaze(int numRows, int numCols) {
	int claster = numRows * numCols; // Program starts with this many clasters;
	Grid<int> maze(numRows, numCols); // Grid is keeper of board it keeps clasters and fastly checks if clasters are coliding;

	HashMap<int, HashSet<Loc>> clasters;  // Here I needed something to keep all clasters in my hands so again Hashmap and HashSet is the way to go because Hash function gives fast access;
	
	TrailblazerPQueue<Edge> pqueue; // And priority queue once again to determine which edge needs to go first based on its randomly generated price;

	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j ++){
			Loc newLoc = makeLoc(i, j);

			maze[i][j] = numCols * i + j;
			clasters[numCols * i + j].add(newLoc);

			if(maze.inBounds(i + 1, j)){
				Loc right = makeLoc(i + 1, j);
				Edge newEdge = makeEdge(newLoc, right);
				double price = randomReal(1, 20);
				pqueue.enqueue(newEdge, price);
			}

			if(maze.inBounds(i, j + 1)){
				Loc top = makeLoc(i, j + 1);
				Edge newEdge = makeEdge(newLoc, top);
				double price = randomReal(1, 20);
				pqueue.enqueue(newEdge, price);
			}
		}
	}

	Set<Edge> answ;
	while(claster > 1){ // If 1 claster is left its over;
		Edge curr = pqueue.dequeueMin();
		if(maze[curr.start.row][curr.start.col] != maze[curr.end.row][curr.end.col]){ 
			foreach(Loc m in clasters.get(maze[curr.start.row][curr.start.col])){
				maze[m.row][m.col] = maze[curr.end.row][curr.end.col];
				clasters[maze[curr.end.row][curr.end.col]].add(m);
			}	
			answ.add(curr);
			claster--;
		}
	}

    return answ;
}


