#pragma once
#include <iostream>
#include <vector>
#include <sstream> // to use the method ToString()
using namespace std;

// to let choose the 
enum class GraphMode {
    List,
    Matrix
};

class Graphs {
private: 
    int V_quant; // number of vertices 
    int A_quant; // number of edges (arestas)

    // choosing the type of representation (adjacency list or matrix)
    GraphMode mode; 

    // declare both but only initialize one
    vector<vector<int>> adj_list;
    vector<vector<int>> adj_matrix;

    // colors for better visual on output
    const string GREEN = "\033[32m";
    const string RED = "\033[31m";
    const string RESET = "\033[0m";

public:
    // graph class constructor
    Graphs(int V, GraphMode rep_mode) {
        this->V_quant = V;
        this->A_quant = 0;
        this->mode = rep_mode;

        // checking the data structure type to initialize only the choosen
        if(mode == GraphMode::List) {
            cout << GREEN << R"( ⡇  ⠄ ⢀⣀ ⣰⡀   ⣀⣀  ⢀⡀ ⢀⣸ ⢀⡀ 
 ⠧⠤ ⠇ ⠭⠕ ⠘⠤   ⠇⠇⠇ ⠣⠜ ⠣⠼ ⠣⠭:)" << RESET << endl;


            cout << "Creating graph with " << V << " vertices\n";
            adj_list.resize(V_quant);
        } else if (mode == GraphMode::Matrix){
            cout << RED << R"( ⡷⢾ ⢀⣀ ⣰⡀ ⡀⣀ ⠄ ⡀⢀   ⣀⣀  ⢀⡀ ⢀⣸ ⢀⡀ 
 ⠇⠸ ⠣⠼ ⠘⠤ ⠏  ⠇ ⠜⠣   ⠇⠇⠇ ⠣⠜ ⠣⠼ ⠣⠭:)" << RESET << endl; 

            cout << "Creating graph with " << V << " vertices\n";       
            adj_matrix.resize(V_quant, vector<int>(V_quant, 0));
        }
    }
    // --- core graphs methods --- 
    int getV() const {return V_quant;}
    int getA() const {return A_quant;}

    // to undirected (two-way) edges between v and w
    void addEdge(int v, int w) {
        // LIST LOGIC
        if (mode == GraphMode::List) {
            adj_list[v].push_back(w);
            adj_list[w].push_back(v);
            // MATRIX LOGIC
        } else {
            // checking if edges alrady exists to avoid double counting edges
            if(adj_matrix[v][w] == 0) {
                adj_matrix[v][w] = 1;
                adj_matrix[w][v] = 1;
            }

            if(v == w) {
                adj_matrix[v][v] = 1;
            }
        }
        A_quant++;
    }

    // methods of processing 
    // to check the degree of a vertex ('vertice')
    int degree(int v) {
        // LIST LOGIC 
        // to find the degree of a vertex ('vertice') is to just return
        // the number of its 'neighbors'.
        // if v=w, addEdge(v,v) adds 'v' to its own list twice, 
        // so .size() correctly counts degree as 2  
        if(mode == GraphMode::List) { 
            return adj_list[v].size();
        } else {
            // MATRIX LOGIC
            int count = 0;
            for(int i=0; i < V_quant; ++i) {
                if(adj_matrix[v][i] == 1) count++;
            }
            // add the self-loop a sec time to count it as 2 degrees
            if(adj_matrix[v][v] == 1) count++;
            
            return count;
        }
    }
    // to find the 'vertice' with the max degree (grau)
    int maxDegree() {
        int max = 0;
        for(int v = 0; v < V_quant; ++v) {
            int dg = degree(v);
            if(dg>max) max = dg;
        } 
        return max;
    }
    
    // couting the number of self-loops ('laços')
    int numLoops() {
        int count = 0;
        // LIST LOGIC
        if(mode == GraphMode::List) {
            for(int v=0; v < V_quant; ++v) {
                for(int w : adj_list[v]) {
                    if(v==w) count++;
                }
            }
            // because addEdge(v,v) adds the edge twice (undirected), it has to be divided by 2
            return count / 2;
        
        // MATRIX LOGIC
        } else {
            // checking only the diagonal of the matrix
            for(int v = 0; v < V_quant; ++v) {
                if(adj_matrix[v][v] == 1) count ++;
            }
            return count;
        }
    }
    // returning a string representation of the graph 
    string ToString() {
        stringstream s_stream;
        s_stream << V_quant << " vertexes ('vertices'), " << A_quant << " edges ('arestas')\n";

        // LIST LOGIC
        if(mode == GraphMode::List) {
            s_stream << GREEN << "[Adjacency List]\n\n" << RESET;
            for(int v = 0; v < V_quant; ++v) {
                s_stream << GREEN << v << ": " << RESET;
                for (int w : adj_list[v]) {
                    s_stream << w << " ";
                } 
                s_stream << endl;
            }
        // MATRIX LOGIC
        } else {
            s_stream << RED << "[Adjacency Matrix]\n\n" << RESET;
            // priting header
            s_stream << "  ";
            for(int i = 0; i < V_quant; ++i) s_stream << RED << i << " ";
            s_stream << "\n";
            // printing rows
            for(int v = 0; v < V_quant; ++v) {
                s_stream << RED << v << " " << RESET;
                for(int w = 0; w < V_quant; ++w) {
                    s_stream << adj_matrix[v][w] << " ";
                }
                s_stream << endl;
            }
        }
        return s_stream.str();
    }
};