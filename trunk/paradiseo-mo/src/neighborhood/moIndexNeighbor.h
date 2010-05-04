/*
  <moIndexNeighbor.h>
  Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

  Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

  This software is governed by the CeCILL license under French law and
  abiding by the rules of distribution of free software.  You can  use,
  modify and/ or redistribute the software under the terms of the CeCILL
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".

  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited liability.

  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,  and  that  also
  therefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and,  more generally, to use and operate it in the
  same conditions as regards security.
  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL license and that you accept its terms.

  ParadisEO WebSite : http://paradiseo.gforge.inria.fr
  Contact: paradiseo-help@lists.gforge.inria.fr
*/

#ifndef _IndexNeighbor_h
#define _IndexNeighbor_h

#include <neighborhood/moNeighbor.h>

/**
 * Index Neighbor
 */
template< class EOT >
class moIndexNeighbor : virtual public moNeighbor<EOT>
{
public:

    using moNeighbor<EOT>::fitness;

    /**
     * Default Constructor
     */
    moIndexNeighbor() : moNeighbor<EOT>(), key(0) {}

    /**
     * Copy Constructor
     */
    moIndexNeighbor(const moIndexNeighbor& _n) : moNeighbor<EOT>(_n) {
        this->key = _n.key ;
    }

    /**
     * Assignment operator
     */
    virtual moIndexNeighbor<EOT> & operator=(const moIndexNeighbor<EOT> & _source) {
        moNeighbor<EOT>::operator=(_source);
        this->key = _source.key ;
        return *this ;
    }

    /**
     * Return the class id.
     * @return the class name as a std::string
     */
    virtual std::string className() const {
        return "moIndexNeighbor";
    }

    /**
     * Getter
     * @return index of the IndexNeighbor
     */
    unsigned int index() {
        return key;
    }

    /**
     * Setter
     * @param _key index of the IndexNeighbor
     */
    void index(unsigned int _key) {
        key=_key;
    }

    /**
     * @param _neighbor a neighbor
     * @return if _neighbor and this one are equals
     */
    virtual bool equals(moIndexNeighbor<EOT>& _neighbor){
    	return (key==_neighbor.index());
    }

protected:
    // key allowing to describe the neighbor
    unsigned int key;

};

#endif