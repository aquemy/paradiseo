// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

// "comm.h"

// (c) OPAC Team, LIFL, August 2005

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
   
   Contact: paradiseo-help@lists.gforge.inria.fr
*/

#ifndef __comm_mpi_h
#define __comm_mpi_h

#include "../../core/communicable.h"
#include "../../core/reac_thread.h"

class Communicator : public ReactiveThread {

public :
  
  /* Ctor */
  Communicator (int * __argc, char * * * __argv);

  void start ();
};

extern void initCommunication ();

extern void waitNodeInitialization ();

extern void wakeUpCommunicator ();

#endif