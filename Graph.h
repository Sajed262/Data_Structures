// https://github.com/Sajed262
//
//

#ifndef GRAPH
#define GRAPH
// the graph is represented as an adjacency list

#include <iostream>
#include "DynamicArray.h"
#include "List.h"
#include <vector>

using std::vector;

class Edge
{
public:
    int src;
    int dest;
    int weight;

    Edge(int from, int to, int w = 1) : src(from), dest(to), weight(w) {}

    ~Edge() = default;

    Edge(const Edge &e) = default;

    Edge &operator=(const Edge &e) = default;
};

class Graph
{
private:
    int num_of_vertices;
    bool is_directed;

    // we will represent the graph as dynamic array of vertices.
    // the index of the array represents a vertex and each element is a list of edges, i.e.,
    // the list contains other vertices that form an edge with that vertex. the key will be the other vertices,
    // and the data will be the weight
    DynamicArray<List<int>> edges;     // if the graph is direct each cell in the array will be vector that contains the out edges
    DynamicArray<List<int>> in_edges; // will be used only if the graph is directed.
    // e.g., if we have an edge 1->2, then in the in_edges at index 2 we will add 1,
    // and in the edges at index 1 we will add 2.
    vector<Edge> weighted_edges;

public:
    // can be used as a none-parameter constructor, but as default the graph will be directed.
    // and can be used a one parameter constructor.
    explicit Graph(bool directed = true) : is_directed(directed), num_of_vertices(0), edges(), in_edges(), weighted_edges() {}

    // it is your job to fill the vector with edges
    Graph(int vertices, bool is_directed, vector<Edge> ed) : num_of_vertices(vertices), is_directed(is_directed),
                                                             edges(num_of_vertices), in_edges(num_of_vertices), weighted_edges(ed)
    {
        for (int i = 0; i < ed.size(); i++)
            addEdge(ed[i].src, ed[i].dest, ed[i].weight);
    }

    Graph(const Graph &gr) = default;

    Graph &operator=(const Graph &gr) = default;

    ~Graph() = default;

    // when adding a vertex the vertex will take the current num_of_vertices, and we will add one to the num_of_vertices.
    int addVertex() // returns the index of the added vertex.
    {
        List<int> tmp;
        edges.insert(tmp);
        if (is_directed)
            in_edges.insert(tmp);
        return num_of_vertices++;
    }
    // there is no remove function for the vertices.

    // in case of directed graph, from will be the vertex that the edge comes out of,
    // and to will be the vertex that the edge points to
    // we dont add the same edge more than once. lets say we have 1->2 and 2->1 in the directed graph and we want the undirected graph of it,
    // in this case we add 1-2 once in each index. we dont need parallel edges.
    // and in case of 2->2, we add 2-2 once.
    void addEdge(int from, int to, int wei = 1)
    {
        if (from < 0 || to < 0 || from >= num_of_vertices || to >= num_of_vertices)
            return;
        if (edges[from].getElement(to)) // the case of parallel edges.
            return;

        edges[from].addElement(to, wei);
        if (is_directed)
            in_edges[to].addElement(from, wei);

        else // the graph is undirected
        {
            if (from == to) // the case of 2->2.
                return;
            edges[to].addElement(from, wei);
        }

        Edge tmp(from, to, wei);
        weighted_edges.push_back(tmp);
    }

    void removeEdge(int from, int to)
    {
        if (from < 0 || to < 0 || from >= num_of_vertices || to >= num_of_vertices)
            return;
        edges[from].removeElement(to);
        if (is_directed)
            in_edges[to].removeElement(from);
        else // the graph is undirected
            edges[to].removeElement(from);
    }

    void removeAllEdgesForVertex(int index) // remove all the edges that the vertex number index is at either sides of the edge.
    {
        if (index < 0 || index >= num_of_vertices)
            return;
        for (int i = 0; i < num_of_vertices; i++)
        { // delete the vertex number index from the vectors in the other vertices that form an edge with index.
            if (i == index)
            {
                while (edges[index].first)
                    edges[index].removeLast();
                while (in_edges[index].first)
                    in_edges[index].removeLast();
                continue;
            }
            edges[i].removeElement(index);
            if (is_directed)
                in_edges[i].removeElement(index);
        }
    }

    void clear() // the clear func erases the whole graph.
    {
        num_of_vertices = 0;
        edges.clear();
        if (is_directed)
            in_edges.clear();
    }

    Graph theUndirectedGraph() // if the edges have weights then the weights in the undirected graph wont be correct.
    {
        if (is_directed)
        {
            Graph undirected(num_of_vertices, false, weighted_edges);
            return undirected;
        }
        else // the graph is already undirected
            return *this;
    }

    bool isDirected()
    {
        return is_directed;
    }

    int numOfVertices() { return num_of_vertices; }
};

#endif // GRAPH