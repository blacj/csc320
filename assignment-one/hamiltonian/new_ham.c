// CSC 320 Spring 2014
// Assignment 1, Questions 7-10
//
// Jaimee Blackwood
// V00755181

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0
#define PRINT 0
#define NMAX 100

int new_hamilton_path(int n, int G[NMAX][NMAX]);
int new_hamilton_cycle(int n, int G[NMAX][NMAX]);
int hamilton_path(int n, int G[NMAX][NMAX]);
int hamilton_cycle(int n, int G[NMAX][NMAX]);

static int hp = 0;
static int hc = 0;

/*
   These first two routines are of type int and return
   0 if there is no Hamilton path/cycle and
   1 if there is a Hamilton path/cycle 

   The new_hamilton_path routine can make a polynomial number
   of calls to hamilton_cycle. The syntax:
   int answer;
   answer= hamilton_cycle(G);

   The new_hamilton_cycle routine can make a polynomial number
   of calls to hamilton_path. The syntax:
   int answer;
   answer= hamilton_path(G);
*/
int new_hamilton_path(int n, int G[NMAX][NMAX])
{	
	//a one vertex graph will always have a path of 1.
	if(n==1)
	{
		return 1;
	}
	//a two vertex graph has a path if the two vertices are connected
	//only one edge required
	if(n==2 && G[0][1] == 1)
	{
		return 1;
	}
	
	//if the graph has a cycle, then it has a path
    int answer;
	answer = hamilton_cycle(n, G);
	if(answer == 1)
	{
		return(answer);
	}
	
	//this loop goes through the entire graph
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(G[i][j]==0) //checks for an edge that doesn't exist
			{	
				//and adds it to see if it creates a cycle
				G[i][j]=1;
				G[j][i]=1;
				if(hamilton_cycle(n,G) == 1)
				{
					//if it does, then a path exists
					return 1;
				}
				//otherwise it has to take the edge away before continuing through the loop
				G[i][j] = 0;
				G[j][i] = 0;
			}
		}
	}
	//if none of those conditions are met, there is no path
	return 0;
}

int new_hamilton_cycle(int n, int G[NMAX][NMAX])
{
	//it isnt possible for a 1 or 2 vertice graph to contain a cycle
	if(n==1 || n==2)
	{
		return 0;
	}

	//this loop goes through the entire graph
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(G[i][j]==1) //checks for an that exists
			{	
				//and removes it to see if a path exists without it
				G[i][j]=0;
				G[j][i]=0;
				if(hamilton_path(n,G) == 1)
				{
					//if a hamiltonian path exists without the edge removed
					//then with the edge, a cycle may exist. 
					return 1;
				}
				//otherwise it has to take the edge away before continuing through the loop
				G[i][j] = 1;
				G[j][i] = 1;
			}
		}
	}
	//if none of those conditions are met, there is no path
	return 0;
}
