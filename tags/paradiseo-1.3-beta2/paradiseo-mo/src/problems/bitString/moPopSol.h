/*
<moPopSol.h>
Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software.  You can  ue,
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

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

#ifndef _moPopSol_h
#define _moPopSol_h

#include <EO.h>
#include <eoPop.h>

template <class EOT>
class moPopSol : public EO<double>, public std::vector<EOT>{
public:
	typedef typename EO<double>::Fitness Fitness;
	using EO<double>::invalidate;

	  virtual void printOn(std::ostream& _os) const
	  {
	        _os << (*this).size() << " " << (*this).fitness() << '\n';
	        for(unsigned int i=0; i<(*this).size(); i++)
	        	_os << (*this).operator[](i) << std::endl;
	  }

};

#endif
