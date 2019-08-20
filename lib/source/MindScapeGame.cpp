#include <MindScapeGame.h>

#include <MindScape/Core/EventController.h>

using namespace MindScape;

MindScapeGame::MindScapeGame()
{
	// Initialize an instance of DemoCoreEventController
	EventController controller;
	// Start the loop on the DemoCoreEventController to start the Demo
	controller.runLoop();
}