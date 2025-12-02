//
//  grafos.h
//  Grafos
//
//  Created by Isabel Vaca on 12/11/25.
//
#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
        int edgesList;
        int edgesMat;
        int nodes;
    vector<int> *adjList;
        int *adjMatrix;


public:
        Graph(int);
        Graph();
        void addEdgeAdjList(int, int);
        void addEdgeAdjMatrix(int, int);
        string printAdjList();
        string printAdjMat();
        string printAdjMat_clean();
        string DFS(int, int);
        string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&, int );
        string BFS(int, int);
        string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&,int);
        string print_visited(list<int>);
        string print_path(vector<vector<int>>&,int ,int);
        bool contains(list<int>, int);
        void sortAdjList();
        void loadGraphList( string, int );
        void loadGraphMat(string, int,int);

};


void Graph::loadGraphList( string name,int n  ){
    adjList = new vector<int>[n];
     nodes = n;
     

     stringstream ss(name);
     string edge;
     
     while (ss >> edge) {

         int u, v;
         char discard;
         stringstream s(edge);
         s >> discard; // (
         s >> u;
         s >> discard; // ,
         s >> v;
         s >> discard; // )
         
         addEdgeAdjList(u, v);
     }
     sortAdjList();
 }
void Graph::loadGraphMat(string name, int n, int m){
    adjMatrix = new int [n*m];
    nodes = n;
    for (int i = 0; i < n*m; i++)
        adjMatrix[i] = 0;
    stringstream ss(name);
    string edge;
        
        while (ss >> edge) {
         
            int u, v;
            char discard;
            stringstream s(edge);
            s >> discard; //(
            s >> u;
            s >> discard; // ,
            s >> v;
            s >> discard; // )
            
            addEdgeAdjMatrix(u, v);
        }
        
}


Graph::Graph() {
    edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int>[nodes];
    adjMatrix = new int [nodes*nodes];
    for (int i = 0; i < nodes*nodes; i++)
        adjMatrix[i] = 0;
    edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){//
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;//contador externo
}

void Graph::addEdgeAdjMatrix(int u, int v){
    adjMatrix[u*nodes+v] = 1;
    adjMatrix[v*nodes+u] = 1;
    edgesMat++;
}

string Graph::printAdjList(){
      stringstream aux;
        for (int i = 0; i < nodes; i++){
            aux << "vertex "
                 << i << " :";
            for (int j = 0; j < adjList[i].size(); j ++){
                             aux << " " << adjList[i][j];
                    }
            aux << " ";
    }
        return aux.str();

}

void Graph::sortAdjList(){
    for (int i = 0; i < nodes; i++)
        sort(adjList[i].begin(),adjList[i].end());
}

string Graph::printAdjMat(){
    stringstream aux;
    for (int i = 0; i < nodes; i++){
       for (int j = 0; j < nodes; j++){
             aux << adjMatrix[i*nodes+j] << " ";
         }
  }
    return aux.str();
}


string Graph::DFS(int start, int goal){
    stack<int> st;
    list<int> visited;
    vector<vector<int>> paths(nodes);
    st.push(start);
    
    return depthHelper(start,goal,st,visited,paths,start);
}

string Graph::depthHelper(int current,int goal,stack<int> &st,list<int> &visited,
                          vector<vector<int>> &paths, int start){
    if(st.empty()){
        return "not found";
    }
    current = st.top();
    st.pop();
    
    if(current == goal){
        visited.push_back(current);
        return print_visited(visited) + print_path(paths, start, goal);
    }
    
    
    if(!contains(visited, current)){
        visited.push_back(current);
        for(int i = 0; i< adjList[current].size(); i++){ //itera en adj list(osea los hijos de current)
            if(!contains(visited, adjList[current][i])){
                st.push(adjList[current][i]);
                if (paths[adjList[current][i]].empty()) {
                    paths[adjList[current][i]].push_back(current);
                }
            }
        }
    }
    return depthHelper(current, goal, st, visited, paths,start);
        
  
    
    
    
    
   
}


string Graph::BFS(int start, int goal){
    queue<int> qu;
    list<int> visited;
    vector<vector<int>> paths(nodes);
    qu.push(start);
    
    
    return breadthHelper(start,goal,qu,visited,paths,start);
}

string Graph::breadthHelper(int current,int goal,queue<int> &qu,
                            list<int> &visited,
                            vector<vector<int>> &paths, int start){
    if(qu.empty()){
        return "not found";
    }
    current = qu.front();
    qu.pop();
    
    if(current == goal){
        visited.push_back(current);
        return print_visited(visited) + print_path(paths, start, goal);
    }
    
    
    if (!contains(visited, current)) {
        visited.push_back(current);
        
        for(int i = 0; i< adjList[current].size(); i++){
            if(!contains(visited, adjList[current][i])){
                qu.push(adjList[current][i]);
                if (paths[adjList[current][i]].empty()) {
                    paths[adjList[current][i]].push_back(current);
                }
            }
        }
    }
    return breadthHelper(current, goal, qu, visited, paths,start);
   
                                                           

        
}


bool Graph::contains(list<int> ls, int node){
        list<int>::iterator it;
        it = find(ls.begin(), ls.end(), node);
        if(it != ls.end())
            return true;
        else
            return false;
}

string Graph::print_visited(list<int> q){
    stringstream aux;
    aux << "visited: ";
    while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
    return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
    if (path[goal].empty() || path[goal][0] == -1) {
            return "path: no path";
    }
    int node =  path[goal][0];
    stack<int> reverse;
    reverse.push(goal);
    stringstream aux;
    aux  << "path:";
    while (node != start) {
        reverse.push(node);
    node = path[node][0];
  }
    reverse.push(start);
    while (!reverse.empty()) {
        aux << " " << reverse.top() ;
        reverse.pop();
  }
    return aux.str();
}
#endif /* Graph_H_ */
