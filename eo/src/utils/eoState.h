// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

//-----------------------------------------------------------------------------
// eoState.h
// (c) Marc Schoenauer, Maarten Keijzer and GeNeura Team, 2000
/* 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact: todos@geneura.ugr.es, http://geneura.ugr.es
             Marc.Schoenauer@polytechnique.fr
             mkeijzer@dhi.dk
 */
//-----------------------------------------------------------------------------

#ifndef eoState_h
#define eoState_h

#include <stdexcept>
#include <string>
#include <map>

class eoObject;
class eoPersistent;

/**
* eoState can be used to register derivants of eoPersistent. It will
* then in turn implement the persistence framework through members load
* and save, that will call readFrom and printOn for the registrated objects.
*/
class eoState 
{
public :

    /**
    * Object registration function, note that it does not take ownership!
    */
    void registerObject(eoPersistent& registrant);
    
    /**
    * Loading error thrown when nothing seems to work.
    */
    struct loading_error : public std::runtime_error
    {
        loading_error(std::string huh = "Error while loading") : std::runtime_error(huh) {}
    };

    std::string getCommentString(void) const { return "#"; }

    /**
    * Reads the file specified
    *
    *   @param _filename    the name of the file to load from
    */
    void load(const std::string& _filename);
    
    /**
    * Saves the state in file specified
    *
    *   @param _filename    the name of the file to save into
    */
    void save(const std::string& _filename);

private :
    std::string createObjectName(eoObject* obj);

    // first is Persistent, second is the raw data associated with it.
    typedef std::map<std::string, eoPersistent*> ObjectMap;
    
    ObjectMap objectMap;
};

#endif //eoState_h
