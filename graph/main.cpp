#include "graph.hpp"

int main()
{
//    graph_matrix<char, int> g("ABCDE", 5);
//    g.add_edge('A', 'D', 10);
//    g.add_edge('A', 'E', 20);
//    g.add_edge('B', 'C', 10);
//    g.add_edge('B', 'D', 20);
//    g.add_edge('B', 'E', 30);
//    g.add_edge('C', 'E', 40);
//    
//    g.display();

    // 有向图
    graph_link<char, int> g("ABCDE", 5, false);
    g.add_edge('A', 'D', 10);
    g.add_edge('E', 'A', 20);
    g.add_edge('B', 'C', 10);
    g.add_edge('D', 'B', 20);
    g.add_edge('E', 'B', 30);
    g.add_edge('C', 'E', 40);
    
    g.add_edge('A', 'C', 50);
    g.add_edge('A', 'E', 50);
    
    g.display();
    
    //g.Dijkstra(0, 10000);
    //g.Dijkstra(1, 10000);
    return 0;
}

