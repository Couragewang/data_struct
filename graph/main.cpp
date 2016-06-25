#include "graph.hpp"

int main()
{
    graph_matrix<char, int> g("ABCDE", 5);
    g.add_edge('A', 'D', 10);
    g.add_edge('A', 'E', 20);
    g.add_edge('B', 'C', 10);
    g.add_edge('B', 'D', 20);
    g.add_edge('B', 'E', 30);
    g.add_edge('C', 'E', 40);
    
    g.display();
    return 0;
}

