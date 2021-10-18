/*
 * esmini - Environment Simulator Minimalistic
 * https://github.com/esmini/esmini
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) partners of Simulation Scenarios
 * https://sites.google.com/view/simulationscenarios
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CommonMini.hpp"
#include "ScenarioGateway.hpp"
#include "Server.hpp"
#include "UDP.hpp"

using namespace scenarioengine;

// #define SWAP_BYTE_ORDER_ESMINI  // Set when Ego state is sent from non Intel platforms, such as dSPACE

enum { SERV_NOT_STARTED, SERV_RUNNING, SERV_STOP, SERV_STOPPED };

static int state = SERV_NOT_STARTED;
static SE_Thread thread;
static SE_Mutex mutex;
static ScenarioGateway *scenarioGateway = 0;

namespace scenarioengine
{
	void ServerThread(void *args)
	{
		static unsigned short int iPortIn = ESMINI_DEFAULT_INPORT;   // Port for incoming packages
		EgoStateBuffer_t buf;

		state = SERV_NOT_STARTED;
		UDPServer *udpServer = new UDPServer(ESMINI_DEFAULT_INPORT);

		double x_old = 0.0;
		double y_old = 0.0;
		double wheel_rot = 0.0;

		while (state == SERV_RUNNING)
		{
			int ret = udpServer->Receive((char*)&buf, sizeof(EgoStateBuffer_t));


#ifdef SWAP_BYTE_ORDER_ESMINI
			SwapByteOrder((unsigned char*)&buf, 4, sizeof(buf));
#endif

			// Find out wheel rotation from x, y displacement
			double ds = GetLengthOfLine2D(buf.x, buf.y, x_old, y_old);
			wheel_rot += SIGN(buf.speed) * fmod(ds / 0.35, 2 * M_PI); // wheel radius = 0.35 m
			x_old = buf.x;
			y_old = buf.y;

			if (ret >= 0)
			{
				printf("Server: Received Ego pos (%.2f, %.2f, %.2f) rot: (%.2f, %.2f, %.2f) speed: %.2f (%.2f km/h) wheel_angle: %.2f (%.2f deg)\n",
					buf.x, buf.y, buf.z, buf.h, buf.p, buf.r, buf.speed, 3.6 * buf.speed, buf.wheel_angle, 180 * buf.wheel_angle / M_PI);

				// Update Ego state
				mutex.Lock();

				OSCBoundingBox bbox = {0, 0, 0, 0, 0, 0}; // dummy bariable just to feed into the function

				scenarioGateway->reportObject(0, "Ego", static_cast<int>(Object::Type::VEHICLE), static_cast<int>(Vehicle::Category::CAR), 0, 1, bbox,
					static_cast<int>(EntityScaleMode::NONE), 0.0, buf.speed, buf.wheel_angle, wheel_rot,  buf.x, buf.y, buf.z, buf.h, buf.p, buf.r);

				mutex.Unlock();
			}

		}

		delete udpServer;

		state = SERV_STOPPED;
	}

	void StartServer(ScenarioEngine *scenarioEngine)
	{
		// Fetch ScenarioGateway
		scenarioGateway = scenarioEngine->getScenarioGateway();

		thread.Start(ServerThread, NULL);
	}

	void StopServer()
	{
		// Flag time to stop
		if (state == SERV_RUNNING)
		{
			state = SERV_STOP;
		}
		else
		{
			state = SERV_STOPPED;
		}

		// Wait/block until UDP server closed gracefully
		thread.Wait();
	}
}
