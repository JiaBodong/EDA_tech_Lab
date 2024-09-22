#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
namespace hw0
{

class Graph
{
public:
  Graph( uint32_t num_nodes )
    : neighbors_for_nodes( num_nodes ) /* Constructs neighbors_for_nodes with `num_nodes` size */
  {
    /* The constructor of the `Graph` class. */
    // Init
    for (auto& neighbors : neighbors_for_nodes) {
      neighbors.clear();
    }
  }

  ~Graph()
  {
    /* The destructor of the `Graph` class. */

  }

  void add_edge( uint32_t from, uint32_t to )
  {
    /* TODO: Add a new edge in your data structure.  */
    if(from == to) { // ignore self-loop
      return;
    }
    // find algorithm
    if(std::find(neighbors_for_nodes[from].begin(), neighbors_for_nodes[from].end(), to) == neighbors_for_nodes[from].end()) {
        neighbors_for_nodes[from].push_back(to);
        neighbors_for_nodes[to].push_back(from);
    } else{
      return;
    }



  }

  uint32_t num_degree_k( uint32_t k ) const
  {
    /* TODO: Count the number of nodes with degree `k`. */

    uint32_t num = 0;
    for(auto& neighbors : neighbors_for_nodes) {
      if(neighbors.size() == k) {
        num++;
      }
    }
    return num;

  }

private:
  /* Possible data structure: each node (index) as a vector of neighbors */
  std::vector<std::vector<uint32_t>> neighbors_for_nodes;
};

} // namespace hw0