//
// Copyright (C) 2008 Institut fuer Telematik, Universitaet Karlsruhe (TH)
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
 * @file ZeroChurn.cc
 * @author Ingmar Baumgart
 */

#include <TransportAddress.h>
#include <UnderlayConfigurator.h>
#include <UnderlayConfiguratorAccess.h>

#include "ZeroChurn.h"

Define_Module(ZeroChurn);

void ZeroChurn::initialize(int stage)
{
    // because of IPvXAddressResolver, we need to wait until interfaces are registered,
    // address auto-assignment takes place etc.
    if (stage != MAX_STAGE_UNDERLAY)
        return;
    underlayConfigurator = UnderlayConfiguratorAccess().get();

    terminalCount = 0;
    init = true;

    updateDisplayString();
    WATCH(terminalCount);

    initializeChurn();
}

void ZeroChurn::initializeChurn()
{
    Enter_Method_Silent();

    initialMean = 0;//par("initPhaseCreationInterval");
    initialDeviation = 0;//initialMean / 3;
    targetOverlayTerminalNum = 0;//par("targetOverlayTerminalNum");

    initAddMoreTerminals = false;

    mobilityTimer = new cMessage("mobilityTimer");
    scheduleAt(simTime(), mobilityTimer);
}

void ZeroChurn::handleMessage(cMessage* msg)
{
    if (!msg->isSelfMessage()) {
        throw cRuntimeError("ZeroChurn::handleMessage(): "
                                "Unknown message received!");
        delete msg;
        return;
    }

    if (msg == mobilityTimer) {
        if (terminalCount < targetOverlayTerminalNum) {
            TransportAddress* ta = underlayConfigurator->createNode(type);
            delete ta; // Address not needed in this churn model
        }

        if (terminalCount >= targetOverlayTerminalNum) {
            initAddMoreTerminals = false;
            underlayConfigurator->initFinished();
        } else {
            scheduleAt(simTime()
                       + truncnormal(initialMean, initialDeviation), msg);
        }
    }
}

void ZeroChurn::updateDisplayString()
{
    char buf[80];
    sprintf(buf, "Zero churn");
    getDisplayString().setTagArg("t", 0, buf);
}

ZeroChurn::~ZeroChurn() {
    // destroy self timer messages
    cancelAndDelete(mobilityTimer);
}

