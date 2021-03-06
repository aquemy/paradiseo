/*
* <moeoSelectFromPopAndArch.h>
* Copyright (C) DOLPHIN Project-Team, INRIA Futurs, 2006-2007
* (C) OPAC Team, LIFL, 2002-2007
*
* Arnaud Liefooghe
*
* This software is governed by the CeCILL license under French law and
* abiding by the rules of distribution of free software.  You can  use,
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info".
*
* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited liability.
*
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or
* data to be ensured and,  more generally, to use and operate it in the
* same conditions as regards security.
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*
* ParadisEO WebSite : http://paradiseo.gforge.inria.fr
* Contact: paradiseo-help@lists.gforge.inria.fr
*
*/
//-----------------------------------------------------------------------------

#ifndef MOEOSELECTONEFROMPOPANDARCH_H_
#define MOEOSELECTONEFROMPOPANDARCH_H_

#include <eoPop.h>
#include <utils/eoRNG.h>
#include <archive/moeoArchive.h>
#include <selection/moeoSelectOne.h>
#include <selection/moeoRandomSelect.h>

/**
 * Elitist selection process that consists in choosing individuals in the archive as well as in the current population.
 */
template < class MOEOT >
class moeoSelectFromPopAndArch : public moeoSelectOne < MOEOT >
  {
  public:

    /**
     * Ctor
     * @param _popSelectOne the population's selection operator
     * @param _archSelectOne the archive's selection operator
     * @param _arch the archive
     * @param _ratioFromPop the ratio of selected individuals from the population
     */
    moeoSelectFromPopAndArch (moeoSelectOne < MOEOT > & _popSelectOne, moeoSelectOne < MOEOT > & _archSelectOne, moeoArchive < MOEOT > & _arch, double _ratioFromPop=0.5)
        : popSelectOne(_popSelectOne), archSelectOne(_archSelectOne), arch(_arch), ratioFromPop(_ratioFromPop)
    {}


    /**
     * Defaulr ctor - the archive's selection operator is a random selector
     * @param _popSelectOne the population's selection operator	
     * @param _arch the archive
     * @param _ratioFromPop the ratio of selected individuals from the population
     */
    moeoSelectFromPopAndArch (moeoSelectOne < MOEOT > & _popSelectOne, moeoArchive < MOEOT > & _arch, double _ratioFromPop=0.5)
        : popSelectOne(_popSelectOne), archSelectOne(randomSelectOne), arch(_arch), ratioFromPop(_ratioFromPop)
    {}


    /**
     * The selection process
     */
    virtual const MOEOT & operator () (const eoPop < MOEOT > & pop)
    {
      if (arch.size() > 0)
        if (rng.flip(ratioFromPop)){
          return popSelectOne(pop);
        }
        else{
          return archSelectOne(arch);
        }
      else{
        return popSelectOne(pop);
      }
    }


    /**
     * Setups some population stats
     */
    virtual void setup (const eoPop < MOEOT > & _pop)
    {
      popSelectOne.setup(_pop);
    }


  private:

    /** The population's selection operator */
    moeoSelectOne < MOEOT > & popSelectOne;
    /** The archive's selection operator */
    moeoSelectOne < MOEOT > & archSelectOne;
    /** The archive */
    moeoArchive < MOEOT > & arch;
    /** The ratio of selected individuals from the population*/
    double ratioFromPop;
    /** A random selection operator (used as default for archSelectOne) */
    moeoRandomSelect < MOEOT > randomSelectOne;

  };

#endif /*MOEOSELECTONEFROMPOPANDARCH_H_*/
