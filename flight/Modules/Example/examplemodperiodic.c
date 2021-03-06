/**
 ******************************************************************************
 *
 * @file       examplemodperiodic.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      Example module to be used as a template for actual modules.
 *             Threaded periodic version.
 *
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/**
 * Input object: ExampleSettings
 * Output object: ExampleObject2
 *
 * This module will periodically update the value of the ExampleObject object.
 * The module settings can configure how the ExampleObject is manipulated.
 *
 * The module executes in its own thread in this example.
 *
 * UAVObjects are automatically generated by the UAVObjectGenerator from
 * the object definition XML file.
 *
 * Modules have no API, all communication to other modules is done through UAVObjects.
 * However modules may use the API exposed by shared libraries.
 * See the OpenPilot wiki for more details.
 * http://www.openpilot.org/OpenPilot_Application_Architecture
 *
 */

#include "openpilot.h"
#include "examplemodperiodic.h"
#include "exampleobject2.h"	// object that will be updated by the module
#include "examplesettings.h"	// object holding module settings

// Private constants
#define STACK_SIZE configMINIMAL_STACK_SIZE
#define TASK_PRIORITY (tskIDLE_PRIORITY+1)

// Private types

// Private variables
static xTaskHandle taskHandle;

// Private functions
static void exampleTask(void *parameters);

/**
 * Initialise the module, called on startup
 * \returns 0 on success or -1 if initialisation failed
 */
int32_t ExampleModPeriodicInitialize()
{
	// Start main task
	xTaskCreate(exampleTask, (signed char *)"ExamplePeriodic", STACK_SIZE, NULL, TASK_PRIORITY, &taskHandle);

	return 0;
}

/**
 * Module thread, should not return.
 */
static void exampleTask(void *parameters)
{
	ExampleSettingsData settings;
	ExampleObject2Data data;
	int32_t step;
	portTickType lastSysTime;

	// Main task loop
	lastSysTime = xTaskGetTickCount();
	while (1) {
		// Update settings with latest value
		ExampleSettingsGet(&settings);

		// Get the object data
		ExampleObject2Get(&data);

		// Determine how to update the data
		if (settings.StepDirection == EXAMPLESETTINGS_STEPDIRECTION_UP) {
			step = settings.StepSize;
		} else {
			step = -settings.StepSize;
		}

		// Update the data
		data.Field1 += step;
		data.Field2 += step;
		data.Field3 += step;
		data.Field4[0] += step;
		data.Field4[1] += step;

		// Update the ExampleObject, after this function is called
		// notifications to any other modules listening to that object
		// will be sent and the GCS object will be updated through the
		// telemetry link. All operations will take place asynchronously
		// and the following call will return immediately.
		ExampleObject2Set(&data);

		// Since this module executes at fixed time intervals, we need to
		// block the task until it is time for the next update.
		// The settings field is in ms, to convert to RTOS ticks we need
		// to divide by portTICK_RATE_MS.
		vTaskDelayUntil(&lastSysTime, settings.UpdatePeriod / portTICK_RATE_MS);
	}
}
