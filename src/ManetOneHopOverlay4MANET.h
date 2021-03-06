//
// Copyright (C) 2006 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

/**
 * @file ManetOneHopOverlay4MANET.h
 * @author Frank Ockenfeld
 */

#ifndef __MANETONEHOPOVERLAY4MANET_H_
#define __MANETEONEHOPOVERLAY4MANET_H_

#include <BaseOverlay.h>
#include <OneHopOverlay4MANET.h>

#include "OneHopOverlay4MANETCache.h"
#include "OneHopOverlay4MANETMessage_m.h"

#include "IPv4Route.h"
#include "INotifiable.h"

/**
 * ManetOneHopOverlay4MANET overlay module
 *
 * Minor changes from OneHopOverlay4MANET module: node registers itself to bootstraplist during INIT state.
 *
 *
 * @see BaseOverlay, OneHopOverlay4MANET, OneHopOverlay4MANETFingerTable
 */
class ManetOneHopOverlay4MANET : public oversim::OneHopOverlay4MANET
{


protected:

    /**
     * changes node state
     *
     * @param toState state to change to
     */
    virtual void changeState(int toState);


};

#endif
