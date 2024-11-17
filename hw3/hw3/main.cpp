#include "problem.hpp"
#include "ILP.hpp"
#include "checker.hpp"

#include <iostream>
#include <cstdlib>

int main( int argc, char* argv[] )
{
  if ( argc != 2 )
  {
    std::cerr << "[e] Missing input filename." << std::endl;
    std::cout << "Usage: ./hw3 <filename>" << std::endl;
    return -1;
  }

  std::cout << "[i] Writing ILP constraints for testcase " << argv[1] << " into `scheduling.lp`...\n";
  Problem problem( argv[1] );
  //problem.print(); /* Uncomment this line to see the sequencing graph in a (maybe) more comprehensive way. */
  ILP lp( problem );
  lp.dump_lp();
  std::cout << "[i] ILP problem written in `scheduling.lp`:\n";
  std::system( "cat scheduling.lp" );
  //std::system( "lp_solve scheduling.lp" ); /* Uncomment this line to solve with lp_solve. */

#if 0 /* Change this line to #if 1 to run the grading system. */
  std::cout << "[i] Solving with lp_solve and writing results into `solution.txt`...\n";
  std::system( "lp_solve scheduling.lp > solution.txt" );
  Checker checker( problem );
  checker.check( "solution.txt" );
  //checker.print_schedule(); /* Uncomment this line to see the scheduling result in a (maybe) more comprehensive way. */
#endif

  return 0;
}
