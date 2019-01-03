#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <fstream>
using namespace std;



// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void fapu(vector<vector<int> > g,int u, int d, bool visited[],
                            int **paths,int path[], int &path_index,int *k,int n,vector<int>  &f)
{
    // Mark the current node and store it in path[]

    visited[u] = true;
    path[path_index] = u;
    path_index++;
    /*for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
      {//std::cout << "asdasdasdasdasdasdasd" << '\n';
        cout<<paths[i][j]<<" ";
      }
      cout<<endl;
    }*/
    // If current vertex is same as destination, then print
    // current path[]

    if (u == d)
    {//paths[k].push_back(0);

      int y=*k;
        for (int i = 1; i<path_index; i++){

            int pp=path[i];
          paths[y][i]=pp;  cout <<"aaaaa:  "<< paths[y][i] << " "; }
        cout << endl;y=y+1;
        *k = y;std::cout << y << '\n';

    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        for (int i = 1; i <n; ++i)
            if (g[u][i]>0 & visited[i]==false){
                fapu(g,i, d, visited,paths, path, path_index,k,n,f);

              }

    }

    // Remove current vertex from path[] and mark it as unvisited

    path_index--;
    visited[u] = false;
    f[0]=10;
}

void fap(vector<vector<int> > g,int s, int d,int **paths,int n,vector<int>  &f)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[n];

    // Create an array to store paths
    int *path = new int[n];
    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 1; i < n; i++)
        visited[i] = false;
    int k=0;
    // Call the recursive helper function to print all paths
    fapu(g,s, d, visited, paths,path, path_index,&k,n,f);
    std::cout << "kakakakakaka" << '\n';
    for(int i=1;i<n*2-2;i++)
    {
      for(int j=1;j<n*2-2;j++)
      {//std::cout << "asdasdasdasdasdasdasd" << '\n';
        cout<<paths[i][j]<<" ";
      }
      cout<<endl;
    }
}
/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */

// Driver program to test above functions

vector<int> av_paths(int **paths,int n,int s,int d,int *lro,int *lre,int cts)
{
  int ctp;int oc,ec;vector<int> ap;int c=0;oc=0;ec=0;
  for(int i=1;i<2*n-2;i++)
  {ctp=cts;cout<<i<<"|||"<<endl;oc=0;ec=0;
    if(paths[i][1]!=0)
    {std::cout << "m0" << '\n';
      for(int j=1;(j<2*n-2)&&(paths[i][j]!=0);j++)
      {std::cout << "ctp:"<<ctp << '\n';
        if((ctp+1)%2)
        { std::cout << "m1" << '\n';
          for(int k=0;lro[k]!=0;k++)
          {std::cout << lro[k] << ' ';
            if(paths[i][j]==lro[k])
            {std::cout << "m11" << '\n';
                oc=1;
                break;
            }
          }
        }
        else
        {std::cout << "m2" << '\n';
          for(int k=0;lre[k]!=0;k++)
          {
            if(paths[i][j]==lre[k])
            {
                ec=1;
                break;
            }
          }
        }
        if((oc==1)||(ec==1)){std::cout << oc<<"/* message */"<<ec << '\n';break;}
        ctp++;
      }
      cout<<i<<"+++"<<endl;
      if((oc==0)&&(ec==0))
      {
        cout<<i<<"---"<<endl;std::cout <<c<< "mmm" << '\n';
        ap.push_back(i);std::cout << ap.front() << '\n';
      }
    }

  }
  std::cout << c<<"alalal" << '\n';
  for(int l=0;l<ap.size();l++){cout<<ap[l]<<" ";}
  std::cout << "alalal" << '\n';
  return ap;
}



int main()
{
  int ammo,sr,kr,br;
  int nor,noar;
  int a,b,c,d;
  ifstream input("the3inp.txt");
  vector<int> f;f.resize(5);
  input>>ammo;
  input>>nor;
  input>>br;
  input>>kr;
  input>>sr;
  int lro[nor];
  int lre[nor];

  input>>a;cout<<a<<endl;for(int i=0;i<nor;i++){if(i<a){input>>lro[i];}else{lro[i]=0;}}
  input>>a;cout<<a<<endl;for(int i=0;i<nor;i++){if(i<a){input>>lre[i];}else{lre[i]=0;}}
  std::cout << "/* message */" << '\n';
for(int i=0;i<a;i++){cout<<lre[i]<<endl;}
std::cout << "/* message */" << '\n';
  cout<<ammo<<"$"<<nor<<"$"<<br<<"$"<<kr<<"$"<<sr<<"$"<<endl;
  vector<vector< int > > graph;
  graph.resize(nor+1);
  for(int i=0;i<nor+1;i++){graph[i].resize(nor+1);}
  //vector<vector< int > > p;
  //p.resize(nor+1);

  int **p=new int*[2*nor];
  for(int i=0;i<2*nor;i++)
  {
    p[i]=new int[2*nor];
  }
  std::cout << "iyiyiyiyiyiyi" << '\n';
  for(int i=0;i<2*nor;i++)
  {
    for(int j=0;j<2*nor;j++)
    {//std::cout << "asdasdasdasdasdasdasd" << '\n';
      cout<<p[i][j]<<" ";
    }
    cout<<endl;
  }
  //for(int i=0;i<nor+1;i++){p[i].resize(nor+1);}
  input>>d;

  for(int i=0;i<d;i++)
  {
    input>>a>>b>>c;

    graph[a][b]=c;
    graph[b][a]=c;
    std::cout << "check" << '\n';
  }
  for(int i=0;i<nor+1;i++)
  {
    for(int j=0;j<nor+1;j++)
    {
      std::cout << graph[i][j];
    }
    cout<<endl;
  }
  input>>noar;

  int ar[noar+1];
  for(int i=0;i<noar;i++)
  {std::cout << "/* message */" << '\n';
    input>>a>>b;
    ar[a]=b;

  }
  int u,v;int o=0;
  /*int parent[nor+1];
  bool *visited = new bool[nor+1];

  // Create an array to store paths
  int *path = new int[nor+1];*/
  int path_index = 0; // Initialize path[] as empty
  int k=0;
  // Initialize all vertices as not visited
  /*for (int i = 1; i < nor+1; i++)
      visited[i] = false;
  *///fap(graph,1,6,p,nor+1,f);
  vector<int> ap;int cts=0;
  fap(graph,1, 7,  p,nor+1,f);
  ap=av_paths(p,nor+1,1,7,lro,lre,cts);
  std::cout << "/* message */" << '\n';
  for(int t=0;t<ap.size();t++){std::cout << ap[t]<<" ";}cout<<endl;
  for(int i=0;i<5;i++){cout<<f[i]<<" ";}
  cout<<endl;

  for(int i=1;i<2*nor;i++)
  {
    for(int j=1;j<2*nor;j++)
    {//std::cout << "asdasdasdasdasdasdasd" << '\n';
      cout<<p[i][j]<<" ";
    }
    cout<<endl;
  }





    return 0;
}
