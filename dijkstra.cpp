#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <new>
#include <vector>
#include <map>
#include <climits>

using namespace std;

vector<string> split(const string s, char delim)
{
  stringstream ss(s);
  string item;
  vector<string> tokens;

  while (getline(ss, item, delim))
    {
      tokens.push_back(item);
    }
return tokens;
}

// create matrix                                                                
double** createMatrix(int n)
{
  double** matrix=new double* [n];
  for(int row=0; row<n; row++)
    {
      matrix[row]=new double[n];
    }
  return matrix;
}

// initialize matrix                                                            
void initMatrix(double** matrix, int n)
{
  for(int row=0; row<n; row++)
    {
      for(int col=0; col<n; col++)
        {
          matrix[row][col]=0.0;
        }
    }
}

// clean matrix                                                                 
void cleanMatrix(double** matrix, int n)
{
  for(int row=0; row<n; row++)
    {
      delete[] matrix[row];
    }
  delete[] matrix;
}

int minDist(vector<double>& dist, vector<bool>& vSet)
{
  double min=(double)INT_MAX;
  int idx=-1;

  for(unsigned int v=0; v<dist.size(); v++)
    {
      if(vSet[v] == false && dist[v] <= min)
        {
          min = dist[v];
          idx=v;
        }
    }

  return idx;
}

// testing purposes                                                             
void printMap(map<string, int> &vtx)
{
  map<string, int>::iterator itr;
  for(itr=vtx.begin(); itr!=vtx.end(); ++itr)
    {
      cout << itr->first << " " << itr->second << endl;
    }
}

void printShortestPath(vector<int>& parent, int src, int dst, map<string, int> \
&labels)
{
  vector<int> v1, v2;
  int k=0, current=dst;

  while(current!=src)
    {
      v1.push_back(current);
      current=parent[current];
    }
  v1.push_back(src);
  vector<int>::reverse_iterator rit = v1.rbegin();
  for(; rit!=v1.rend();++rit)
    {
      v2.push_back(*rit);
    }

  map<int, string>tmp;
  for(auto k: labels)
    {
      tmp.insert(pair<int, string>(k.second, k.first));
    }
vector<int>::iterator it;
  for (it=v2.begin(); it!=v2.end(); ++it)
    {
      cout << tmp.at(*it) << " ";
    }
  cout << endl;
}



void djk(map<string, int> &labels, double **M, int n, int src, int dest)
{
  vector<double> dist(n,INT_MAX);
  vector<bool> vSet(n, false);
  vector<int> parent(n, -1);


  dist[src]=0.0;

  for(int j=0; j < n-1; j++)
    {
      int u=minDist(dist, vSet);
      vSet[u]=true;
      for(int k=0; k < n; k++)
        {
          if(!vSet[k] && M[u][k] && dist[u] != INT_MAX && dist[u] + M[u][k] < dist[k])
            {
              parent[k]=u;
              dist[k]=dist[u]+M[u][k];
            }
        }
    }
  cout << dist[dest] << endl;
  printShortestPath(parent, src, dest, labels);
}


int main(int argc, char ** argv)
{
  int n;
  ifstream inFile;
  string line;
  map<string, int> vtxNames;

  inFile.open(argv[1]);
  getline(inFile, line);
  stringstream(line) >> n;

  string srcLabel=argv[2];
  string dstLabel=argv[3];

  vtxNames.insert(pair<string, int>(srcLabel,0));

  // create matrix                                                                                               
  double** M=createMatrix(n);

  //initialize matrix                                                                                            
  initMatrix(M, n);

  vector<string> vect;
  string key;
  int x, y, size, ndx;
  double weight;
  int vtxIndex=1;
  while (getline(inFile, line))
    {
      ndx=0;
      vect=split(line, ' ');

      key=vect[ndx];
      // first value should be a label                                                                           
      if(vtxNames.count(key) == 0)
        {
          vtxNames.insert(pair<string, int>(key, vtxIndex));
          x=vtxIndex;
          vtxIndex++;
        }
      else
        {
          x=vtxNames.at(key);
        }
      ndx++;
      
      // second value should be a label                                                                          
      key=vect[ndx];
      if(vtxNames.count(key) == 0)
        {
          vtxNames.insert(pair<string, int>(key, vtxIndex));
          y=vtxIndex;
          vtxIndex++;
        }
      else
        {
          y=vtxNames.at(key);
        }
        
      // third value should be a weight                                                                          
      ndx++;
      weight=atof(vect[ndx].c_str());
      M[x][y]=weight;
      M[y][x]=weight;
      ndx++;
      
      // we expect a pair of values for each vertice                                                             
      size=vect.size() -3;
      while(size>=2)
        {
          // next value should be a label                                                                        
          key=vect[ndx];
          if(vtxNames.count(key) == 0)
            {
              vtxNames.insert(pair<string, int>(key,vtxIndex));
              y=vtxIndex;
              vtxIndex++;
            }
          else
            {
              y=vtxNames.at(key);
            }
          // next should be a weight                                                                             
          ndx++;
          weight = atof(vect[ndx].c_str());
          M[x][y]=weight;
          M[y][x]=weight;
          ndx++;

          size-=2;
        }
    }

  int src = vtxNames.at(srcLabel.c_str());
  int dest = vtxNames.at(dstLabel.c_str());

  djk(vtxNames, M, n, src, dest);

  // clean matrix                                                                                                
  cleanMatrix(M,n);
  inFile.close();
  
}

