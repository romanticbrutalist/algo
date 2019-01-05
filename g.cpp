#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <fstream>
#include <math.h>
using namespace std;



// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void fapu(vector<vector<int> > g,int u, int d, bool visited[],
                            int **paths,int path[], int &path_index,int *k,int n,vector<int>  &f)
{
    // Mark the current node and store it in path[]
    //if(path_index>(4)){return;}
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
            //cout<<y<<"|"<<path_index<<"|"<<pow(n-1,3)<<endl;
            int pp=path[i];
          paths[y][i+1]=pp;  /*cout <<"aaaaa:  "<< paths[y][i] << " ";*/ }
        y=y+1;
        *k = y;//std::cout << y << '\n';

    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        for (int i = 1; i <n; ++i)
            if (g[u][i]!=0 & visited[i]==false){
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
    int k=1;
    // Call the recursive helper function to print all paths
    fapu(g,s, d, visited, paths,path, path_index,&k,n,f);
    //std::cout << "kakakakakaka" << '\n';
    for(int i=1;i<pow(n-1,3);i++)
    {

        if(paths[i][2]!=0){paths[i][1]=s;}

      //cout<<endl;
    }
}
/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */

// Driver program to test above functions

vector<int> av_paths(int **paths,int n,int s,int d,int *lro,int *lre,int cts,int src,int brc,int sr,int br)
{
  int ctp;int oc,rc,ec;vector<int> ap;int c=0;rc=0;oc=0;ec=0;
  for(int i=1;i<pow(n-1,3);i++)
  {ctp=cts;oc=0;ec=0;rc=0;
    if(paths[i][1]!=0)
    {//std::cout << "m0" << '\n';
      for(int j=1;(j<2*n-2)&&(paths[i][j]!=0);j++)
      {
        if(ctp%2)
        {// std::cout << "m1" << '\n';
          for(int k=0;lro[k]!=0;k++)
          {
            if(paths[i][j]==lro[k])
            {//std::cout <<ctp<<":::"<<lro[k]<< "m11" << '\n';
                oc=1;
                break;
            }
          }
        }
        else
        {//std::cout << "m2" << '\n';
          for(int k=0;lre[k]!=0;k++)
          {
            if(paths[i][j]==lre[k])
            {
                ec=1;
                break;
            }
          }
        }
        if(src)
        {

            if((paths[i][j+1]!=0)&&(paths[i][j]==sr))
            {
                rc=1;
                break;
            }

        }
        if(brc)
        {
          if((paths[i][j+1]!=0)&&(paths[i][j]==br))
          {
              rc=1;
              break;
          }
        }
        if((rc==1)||(oc==1)||(ec==1)){break;}
        ctp++;
      }

      if((rc==0)&&(oc==0)&&(ec==0))
      {

        ap.push_back(i);
      }
    }

  }
  //std::cout << c<<"alalal" << '\n';
  //for(int l=0;l<ap.size();l++){cout<<ap[l]<<" ";}
  //std::cout << "alalal" << '\n';
  return ap;
}

vector<int> mp(vector<vector<int> > g,int **paths,vector<int> ap,int n,int *cts,int *ar)
{int mv,mi,r,s;mv=99999;mi=0;r=0;int ai=0;int ac=0;int aic=0;int aicc=0;
  vector<vector<int> > ara;ara.resize(ap.size());
  for(int i=0;i<ap.size();i++)
  {s=0;r=0;ac=0;
    for(int j=1;paths[ap[i]][j]!=0;j++)
    {//cout<<"papij:"<<paths[ap[i]][j]<<" ";
      if(ar[paths[ap[i]][j+1]]>0)
      {
        //cout<<"ac"<<paths[ap[i]][j+1]<<" ";
      s-=ar[paths[ap[i]][j+1]];ac=1;aic=paths[ap[i]][j+1];ara[i].push_back(paths[ap[i]][j+1]);
      }
      s+=g[paths[ap[i]][j]][paths[ap[i]][j+1]];r++;
    }
    //cout<<i<<"+++"<<s<<endl;
    if(s<mv){*cts+=r;mv=s;mi=i;if(ac==1){ai=i;aicc=aic;}}
  }
  if(mi==ai)
  {
    for(int q=0;q<ara[mi].size();q++)
    {//std::cout <<ara[mi][q]<< "c1c1c1" << '\n';
      ar[ara[mi][q]]=0;
      //std::cout << "c2c2c2" << '\n';
    }
  }
  vector<int> res;
  res.push_back(-mv);
  for(int i = 1;paths[ap[mi]][i]!=0;i++)
  {
    res.push_back(paths[ap[mi]][i]);
  }
  return res;
}

int main()
{
  int ammo,sr,kr,br;int src,brc;src=1;brc=1;
  int nor,noar;
  int a,b,c,d;
  ifstream input("the3.inp");
  vector<int> f;f.resize(5);
  input>>ammo;
  input>>nor;
  input>>br;
  input>>kr;
  input>>sr;
  int lro[nor];
  int lre[nor];

  input>>a;for(int i=0;i<nor;i++){if(i<a){input>>lro[i];}else{lro[i]=0;}}
  input>>a;for(int i=0;i<nor;i++){if(i<a){input>>lre[i];}else{lre[i]=0;}}
//for(int i=0;i<a;i++){cout<<lre[i]<<endl;}
  vector<vector< int > > graph;
  graph.resize(nor+1);
  for(int i=0;i<nor+1;i++){graph[i].resize(nor+1);}
  //vector<vector< int > > p;
  //p.resize(nor+1);
int ff=pow(nor,3);
  int **p=new int*[ff];
  for(int i=0;i<pow(nor,3);i++)
  {
    p[i]=new int[2*nor];
  }
  //std::cout << "iyiyiyiyiyiyi" << '\n';
  /*for(int i=0;i<100*nor;i++)
  {
    for(int j=0;j<100*nor;j++)
    {//std::cout << "asdasdasdasdasdasdasd" << '\n';
      cout<<p[i][j]<<" ";
    }
    cout<<endl;
  }*/
  //for(int i=0;i<nor+1;i++){p[i].resize(nor+1);}
  input>>d;

  for(int i=0;i<d;i++)
  {
    input>>a>>b>>c;

    graph[a][b]=c;
    graph[b][a]=c;
    //std::cout << "check" << '\n';
  }
  for(int i=0;i<nor+1;i++)
  {
    for(int j=0;j<nor+1;j++)
    {
      //std::cout << graph[i][j];
    }
    //cout<<endl;
  }
  input>>noar;

  int ar[nor+1];
  for(int i=0;i<nor+1;i++){ar[i]=0;}
  for(int i=0;i<noar;i++)
  {//std::cout << "/* message */aaaarrrr" << '\n';
    input>>a>>b;
    ar[a]=b;
    /*for(int j=1;j<nor+1;j++)
    {
      if(graph[j][a]!=0)
      {
      graph[j][a]=graph[j][a]-b;
      }
    }*/

  }
  //for(int i=0;i<nor+1;i++){for(int j=0;j<nor+1;j++){cout<<graph[i][j]<<" ";}cout<<endl;}
  int u,v;int o=0;
  /*int parent[nor+1];
  bool *visited = new bool[nor+1];

  // Create an array to store paths
  int *path = new int[nor+1];*/
  int path_index = 0; // Initialize path[] as empty
  int k,lc;k=0;lc=0;
  // Initialize all vertices as not visited
  /*for (int i = 1; i < nor+1; i++)
      visited[i] = false;
  *///fap(graph,1,6,p,nor+1,f);
  vector<int> ap;int cts=0;
  vector<int> temp,res;
  //std::cout << "/* phase0 */" << '\n';
  fap(graph,1, kr,  p,nor+1,f);
  ap=av_paths(p,nor+1,1,kr,lro,lre,cts,src,brc,sr,br);
  /*for(int i=1;i<100*nor;i++)
  {
    for(int j=1;j<100*nor;j++)
    {//std::cout << "asdasdasdasdasdasdasd" << '\n';
      cout<<p[i][j]<<" ";
    }
    cout<<endl;
  }*/
  src=0;
  //for(int i=0;i<nor+1;i++){cout<<ar[i]<<' ';}cout<<endl;
  temp=mp(graph,p,ap,nor+1,&cts,ar);
  for(int i=0;i<temp.size();i++)
  {
    if(i==0){ammo+=temp[0];}
    else{res.push_back(temp[i]);}
  }
  //for(int i=0;i<nor+1;i++){cout<<ar[i]<<' ';}cout<<endl;
  //std::cout << "ap0" << '\n';
  //for(int t=0;t<ap.size();t++){std::cout << ap[t]<<" ";}cout<<endl;
  for(int i=1;i<pow(nor,3);i++){if(p[i][1]==0){break;}for(int j=1;j<2*nor;j++){p[i][j]=0;}}
  //cout<<"CTS:"<<cts<<endl;









  //std::cout << "/* phase1 */" << '\n';

  fap(graph,kr, sr,  p,nor+1,f);
  ap=av_paths(p,nor+1,kr,sr,lro,lre,cts,src,brc,sr,br);
  /*for(int i=1;i<100*nor;i++)
  {
    for(int j=1;j<100*nor;j++)
    {//std::cout << "asdasdasdasdasdasdasd" << '\n';
      cout<<p[i][j]<<" ";
    }
    cout<<endl;
  }*/
  //for(int i=0;i<nor+1;i++){cout<<ar[i]<<' ';}cout<<endl;
  temp=mp(graph,p,ap,nor+1,&cts,ar);
  for(int i=0;i<temp.size();i++)
  {
    if(i==0){ammo+=temp[0];}
    else if(i==1){continue;}

    else{res.push_back(temp[i]);}
  }
  //for(int i=0;i<nor+1;i++){cout<<ar[i]<<' ';}cout<<endl;

  //std::cout << "ap1" << '\n';
  //for(int t=0;t<ap.size();t++){std::cout << ap[t]<<" ";}cout<<endl;

  brc=0;
  //cout<<"CTS:"<<cts<<endl;

  //std::cout << "/* phase2 */" << '\n';

  for(int i=1;i<pow(nor,3);i++){if(p[i][1]==0){break;}for(int j=1;j<2*nor;j++){p[i][j]=0;}}
  fap(graph,sr, br,  p,nor+1,f);
  ap=av_paths(p,nor+1,sr,br,lro,lre,cts,src,brc,sr,br);
  temp=mp(graph,p,ap,nor+1,&cts,ar);
  for(int i=0;i<temp.size();i++)
  {
    if(i==0){ammo+=temp[0];}
    else if(i==1){continue;}
    else{res.push_back(temp[i]);}
  }
  //for(int i=0;i<nor+1;i++){cout<<ar[i]<<' ';}cout<<endl;

  //std::cout << "ap2" << '\n';

  //for(int t=0;t<ap.size();t++){std::cout << ap[t]<<" ";}cout<<endl;
  ofstream myf;
  myf.open ("the3.out");
  myf << ammo <<"\n";
  myf << res.size()<<endl;

  for(int i=0;i<res.size();i++)
  {
    //cout<<res[i]<<" ";
    myf<<res[i]<<" ";
  }
  myf<<endl;
  std::cout << ammo << '\n';
  myf.close();
  /*for(int i=1;i<100*nor;i++)
  {
    for(int j=1;j<100*nor;j++)
    {//std::cout << "asdasdasdasdasdasdasd" << '\n';
      cout<<p[i][j]<<" ";
    }
    cout<<endl;
  }*/





    return 0;
}
