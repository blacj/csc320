/* Do not change NMAX or Hamilton Path/Cycle routines will not work!
 * You can assume NMAX is already big enough for any problem you 
 * want to solve.
 * 
 * IMPORTANT NOTE:
 * The adjacency matrix of the graph must be symmetric.
 * If you want to add an edge (u, v) you should use the
 * TWO statements:
 *
 * G[u][v]= 1;
 * G[v][u]= 1;
 *
 */
#include <stdio.h>
#include <stdlib.h>
#define NMAX 100
int read_graph(int *n, int G[NMAX][NMAX]);
int print_graph(int n, int G[NMAX][NMAX]);
int new_hamilton_path(int n, int G[NMAX][NMAX]);
int new_hamilton_cycle(int n, int G[NMAX][NMAX]);
int hamilton_path(int n, int G[NMAX][NMAX]);
int hamilton_cycle(int n, int G[NMAX][NMAX]);
int hamuv(int n, int G[NMAX][NMAX], int nv, int u, int v, int mask[]);
main()
{
   int n;
   int G[NMAX][NMAX];
   char answer[2][4];
   int count;
 
   int hp, hc, hp_new, hc_new;
   
   answer[0][0]= 'N'; answer[0][1]= 'O'; answer[0][2]= ' '; answer[0][3]= '\0';
   answer[1][0]= 'Y'; answer[1][1]= 'E'; answer[1][2]= 'S'; answer[1][3]= '\0';

   count=0;
   while (read_graph(&n, G))
   {
       count++;
       printf("Input graph: %0d\n", count);
       print_graph(n, G);

       printf("\n");
       hp    = hamilton_path(n, G);
       hp_new= new_hamilton_path(n, G);
       if (hp!= hp_new)
       {
          printf("Error- new HP routine disagrees with old one.\n");
       }

       hc    = hamilton_cycle(n, G);
       hc_new= new_hamilton_cycle(n, G);
       if (hc!= hc_new)
       {
          printf("Error- new HC routine disagrees with old one.\n");
       }

       printf("Hamilton Path :  Correct answer: %s   Your answer: %s\n", answer[hp], answer[hp_new]);
       printf("Hamilton Cycle:  Correct answer: %s   Your answer: %s\n", answer[hc], answer[hc_new]);
       printf("\n");
   }
}
int read_graph(int *n, int G[NMAX][NMAX])
/* 
 *  Read in n, the number of vertices followed by an upper triangular
 *  adjacency matrix and store as adjacency matrix in G.
 */
{
   int i, j;

   if (scanf("%d", n)!=1) return(0);
   if (*n < 1 || *n > NMAX)
   {
      printf("*** Error- Number of vertices %d not in range 1-NMAX (%d)\n", *n, NMAX); 
      return(0);
   }

   for (i=0; i < *n; i++)
   {
      G[i][i]=0;
      for (j=i+1; j < *n; j++)
      {
          if (scanf("%1d", &G[i][j])!= 1) return(0);
          G[j][i]= G[i][j];
      }
   }
   return(1);
}
/* 
 *  Print the graph G in adjacency list format. 
 */
int print_graph(int n, int G[NMAX][NMAX])
{
   int i, j;

   for (i=0; i <n; i++)
   {
      printf("%2d : ", i);
      for (j=0; j <n; j++)
      {
          if (G[i][j])
          {
             printf("%2d ", j);
          }
      }
      printf("\n");
   }
}
