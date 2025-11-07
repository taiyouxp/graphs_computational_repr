// graphs implementation (graph_impl)
#include "graph.h++"
using namespace std;

int main () {
        cout << R"( ⡎⠑ ⡀⣀ ⢀⣀ ⣀⡀ ⣇⡀ ⢀⣀   ⡇ ⣀⣀  ⣀⡀ ⡇  
 ⠣⠝ ⠏  ⠣⠼ ⡧⠜ ⠇⠸ ⠭⠕   ⠇ ⠇⠇⠇ ⡧⠜ ⠣ ⠶)" << "\n\n";    

    int V = 5;

    // --- create the graph object in LIST mode ---
    // best for "sparse" => (few edges) graphs
    Graphs g_list(V, GraphMode::List);
    g_list.addEdge(0,1);
    g_list.addEdge(0,4);
    g_list.addEdge(1,2);
    g_list.addEdge(2,2); // self-loop ('laço')
    g_list.addEdge(3,4);
    
    cout << g_list.ToString() << endl;
    cout << "---------------------------------\n" << 
    "Max degree ('grau máximo'): " << g_list.maxDegree() << endl <<
    "Self-loops ('laços'): " << g_list.numLoops() << endl <<
    "---------------------------------\n";

    // --- create the graph on MATRIX mode ---
    Graphs g_matrix(V, GraphMode::Matrix);
    g_matrix.addEdge(0,1);
    g_matrix.addEdge(0,4);
    g_matrix.addEdge(1,2);
    g_matrix.addEdge(2,2); // self-loop
    g_matrix.addEdge(3,4);
    cout << g_matrix.ToString() << endl;
    cout << "---------------------------------\n" << 
    "Max degree ('grau máximo'): " << g_matrix.maxDegree() << endl <<
    "Self-loops ('laços'): " << g_matrix.numLoops() << endl <<
    "---------------------------------\n";
}