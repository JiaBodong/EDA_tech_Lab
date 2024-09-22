#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
namespace hw0
{

class Graph
{
public:
  Graph( uint32_t num_nodes )
    : neighbors_for_nodes( num_nodes ), nodes_in_degree( num_nodes ) /* Constructs neighbors_for_nodes with `num_nodes` size */
  {
    /* The constructor of the `Graph` class. */
    // Init
    for (auto& neighbors : neighbors_for_nodes) {
      neighbors.clear();
    }
    for (auto& in_degree : nodes_in_degree) {
      in_degree.clear();
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
        neighbors_for_nodes[from].push_back(to);//just store out degree
        nodes_in_degree[to].push_back(from);//store in degree
    } else{
      return;
    }



  }

  uint32_t num_degree_k( uint32_t k ) const
  {
    /* TODO: Count the number of nodes with degree `k`. out degree and in degree */

    uint32_t num = 0;
    for (size_t i = 0; i < neighbors_for_nodes.size(); ++i) {
        // Total degree is the sum of out-degree and in-degree
        uint32_t total_degree = neighbors_for_nodes[i].size() + nodes_in_degree[i].size();
        
        if (total_degree == k) {
            num++;
        }
    }
    return num;
  }

  uint32_t num_out_degree_k( uint32_t k ) const
  {

    uint32_t num = 0;
    for(auto& neighbors : neighbors_for_nodes) {
      if(neighbors.size() == k) {
        num++;
      }
    }
    return num;
  }

  uint32_t num_in_degree_k( uint32_t k ) const
  {
    uint32_t num = 0;
    //count in degree
    for(auto& in_degree: nodes_in_degree) {
      if(in_degree.size() == k) {
        num++;
      }
    }
    
    return num;
    
  }

private:
  /* Possible data structure: each node (index) as a vector of neighbors */
  std::vector<std::vector<uint32_t>> neighbors_for_nodes;
  std::vector<std::vector<uint32_t>> nodes_in_degree;
};

} // namespace hw0