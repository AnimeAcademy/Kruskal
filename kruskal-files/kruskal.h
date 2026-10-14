#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "disjoint_sets.h"
#include "graph.h"

template <typename Vertex, typename Edge>
std::vector<Edge> kruskal(Graph<Vertex, Edge> const& g) {
    std::vector<Edge> mst;
    // ........... 

    //make sets
    DisjointSets ds(g.Size());
    for (size_t i = 0; i < g.Size(); ++i) {
        ds.Make();
    }
    //make a vector to sort all edges into
    std::vector<Edge> edges(g.GetEdges().begin(), g.GetEdges().end());
    //now sort the edges
    std::sort(edges.begin(), edges.end());

    //now pricess the edges
    for (auto const& e : edges) {
        size_t u = e.ID1();
        size_t v = e.ID2();

        if (ds[u] != ds[v]) {
            mst.push_back(e);
            ds.Join(u,v);
        }
    }

	return mst;
}

#endif
