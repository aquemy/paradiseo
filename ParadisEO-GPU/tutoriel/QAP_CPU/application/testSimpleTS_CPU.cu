#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int * a;
int * b;
int n;

// The general include for eo
#include <eo>
#include <ga.h>
// Fitness function
#include <QapEval.h>
// Cuda Fitness function
#include <QapIncrEval.h>
// QAP solution
#include <eoVector.h>
#include <eoInt.h>
//To compute execution time
#include <performance/moCudaTimer.h>
//QAP neighbor
#include <problems/permutation/moIndexedSwapNeighbor.h>
//QAP neighborhood 
//#include <problems/permutation/moSwapNeighborhood.h>
#include <neighborhood/moOrderNeighborhood.h>
//QAP data
#include <Problem.h>
// The Solution and neighbor comparator
#include <comparator/moNeighborComparator.h>
#include <comparator/moSolNeighborComparator.h>
// The Iter continuator
#include <continuator/moIterContinuator.h>
// Local search algorithm
#include <algo/moLocalSearch.h>
// The Tabou Search algorithm explorer
//#include <explorer/moTSexplorer.h>
//Algorithm and its components
#include <algo/moTS.h>
//Tabu list
//#include <memory/moNeighborVectorTabuList.h>
#include <memory/moIndexedVectorTabuList.h>
//Memories
#include <memory/moDummyIntensification.h>
#include <memory/moDummyDiversification.h>
#include <memory/moBestImprAspiration.h>
//#include <time.h>



typedef eoInt<eoMinimizingFitness> solution;
//typedef moSwapNeighbor<solution> Neighbor;
typedef moIndexedSwapNeighbor<solution> Neighbor;
//typedef moSwapNeighborhood<solution> Neighborhood;
typedef moOrderNeighborhood<Neighbor> Neighborhood;

int main(int argc, char **argv)
{

 /* =========================================================
   *
   * Parameters
   *
   * ========================================================= */

    // First define a parser from the command-line arguments
  eoParser parser(argc, argv);

  // For each parameter, define Parameter, read it through the parser,
  // and assign the value to the variable

  // seed
  eoValueParam<uint32_t> seedParam(time(0), "seed", "Random number seed", 'S');
  parser.processParam( seedParam );
  unsigned seed = seedParam.value();

  // Iteration number
  eoValueParam<unsigned int> nbIterationParam(1, "nbIteration", "TS Iteration number", 'I');
  parser.processParam( nbIterationParam, "TS Iteration number" );
  unsigned nbIteration = nbIterationParam.value();

  // size tabu list
  eoValueParam<unsigned int> sizeTabuListParam(7, "sizeTabuList", "size of the tabu list", 'T');
  parser.processParam( sizeTabuListParam, "Search Parameters" );
  unsigned sizeTabuList = sizeTabuListParam.value();

 // duration tabu list
  eoValueParam<unsigned int> durationParam(7, "duration", "duration of the tabu list", 'D');
  parser.processParam( durationParam, "Search Parameters" );
  unsigned duration = durationParam.value();


  // the name of the "status" file where all actual parameter values will be saved
  string str_status = parser.ProgramName() + ".status"; // default value
  eoValueParam<string> statusParam(str_status.c_str(), "status", "Status file");
  parser.processParam( statusParam, "Persistence" );

  // do the following AFTER ALL PARAMETERS HAVE BEEN PROCESSED
  // i.e. in case you need parameters somewhere else, postpone these
  if (parser.userNeedsHelp()) {
    parser.printHelp(cout);
    exit(1);
  }
  if (statusParam.value() != "") {
    ofstream os(statusParam.value().c_str());
    os << parser;// and you can use that file as parameter file
  }
  /* =========================================================
   *
   * Random seed
   *
   * ========================================================= */

  //reproducible random seed: if you don't change SEED above,
  // you'll aways get the same result, NOT a random run
//  rng.reseed(seed);
  srand(seed);
  
  /* =========================================================
   *
   * Initilisation of QAP data
   *
   * ========================================================= */

   load(argv[1]);

  /* =========================================================
   *
   * Initilisation of the solution
   *
   * ========================================================= */

   solution sol(n);
   create<solution>(sol);

  /*=========================================================
   *
   * Evaluation of a solution neighbor's
   *
   * ========================================================= */

   QapEval<solution> eval;
   QapIncrEval<Neighbor> incr_eval;

  /* =========================================================
   *
   * Comparator of solutions and neighbors
   *
   * ========================================================= */

      moNeighborComparator<Neighbor> comparator;
      moSolNeighborComparator<Neighbor> solComparator;

  /* =========================================================
   *
   * a solution neighborhood
   *
   * ========================================================= */
 
      Neighborhood neighborhood(n*(n-1)/2);

  /* =========================================================
   *
   * continuator
   *
   * ========================================================= */

     moIterContinuator <Neighbor> continuator(nbIteration);

  /*=========================================================
   *
   * Tabu list
   *
   * ========================================================= */

    sizeTabuList=(n*(n-1))/2;
    duration=sizeTabuList/8;
    // tabu list
    moIndexedVectorTabuList<Neighbor> tl(sizeTabuList,duration);

  /* =========================================================
   *
   * Memories
   *
   * ========================================================= */

    moDummyIntensification<Neighbor> inten;
    moDummyDiversification<Neighbor> div;
    moBestImprAspiration<Neighbor> asp;

  /* =========================================================
   *
   * the Tabu search algorithm  
   *
   * ========================================================= */

    //General Constructor
    moTS<Neighbor> tabuSearch(neighborhood, eval, incr_eval, comparator, solComparator, continuator, tl, inten, div, asp);  

  /* =========================================================
   *
   * Execute the Tabu search from random sollution
   *
   * ========================================================= */
 
  //Can be eval here, else it will be done at the beginning of the localSearch
  eval(sol);

  std::cout << "initial: " << sol<< std::endl;
 // Create timer for timing CUDA calculation
  moCudaTimer timer;
  timer.start();
  tabuSearch(sol);
  timer.stop();
  std::cout << "final:   " << sol << std::endl;
  printf("CUDA execution time = %f ms\n",timer.getTime());
  timer.deleteTimer();
 
  delete[] a;
  delete[] b;    


return 0;
}