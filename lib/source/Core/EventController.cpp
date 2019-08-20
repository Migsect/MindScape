#include <MindScape/Core/EventController.h>

#include <iostream>
#include <string>

using namespace MindScape;

#define APP_NAME "MindScape"

EventController::EventController() : CoreEventController(APP_NAME), m_mainRegion(*window)
{
	// Set the camera to the same as the window
	m_camera.reset(sf::FloatRect(0, 0, (float)window->getSize().x, (float)window->getSize().y));
	activeRegion = &m_mainRegion;
}

sf::Int32 EventController::getElapsedTime()
{
	return updateClock.getElapsedTime().asMilliseconds();
}

void EventController::runLoop() {
	sf::Event event;

	//Ensure window is fully opened before we do any work on it.
	while (window->isOpen() == false) {
		continue;
	}

	m_nextGameTick = getElapsedTime();
	while (window->isOpen()) {
		m_fpsCheckpoint = getElapsedTime();

		m_updateLoops = 0;
		while (getElapsedTime() > m_nextGameTick && m_updateLoops < MAX_FRAMESKIP)
		{

			// Handling input
			while (window->pollEvent(event)) {
				handleEvent(event);
			}

			// Note that we could include ticks per second here, however the update methods have access
			// to the members that can provide more information.
			update();

			// If the update loops are taking more than the SKIP_TICKS then we want to have a limit 
			// at which we break our of the loop so we don't get stuck in infinite updating.
			m_updateLoops++;

			// Updating the next time we are going to do a game update.
			m_nextGameTick += SKIP_TICKS;

			// The current tick is used to track how many updates have been done overall.
			m_currentTick++;

			// NOTE that we are not sleeping at all since we don't need to.
			// Our rendering will spin off if we don't have any updates to do.
		}
		// TODO if m_updateLopps >= MAX_FRAMESKIP then an error message should be outputted that shows how far behind we are in the loop.

		// Interpolation is a ratio of how much time has passed since we have last had a tick update.
		// This should technically always be between 0 and 1.
		float interpolation = float(SKIP_TICKS + getElapsedTime() - m_nextGameTick) / float(SKIP_TICKS);

		draw(interpolation);

		// Incrementign the frame counter
		m_framesCount++;
		// If the seconds do not match on the elapsed time and the prior checkpoint, that means we have
		// crossed over into a new second and we should report the fps.
		if ((getElapsedTime() / 1000) != (m_fpsCheckpoint / 1000))
		{
			std::cout << "fps: " << m_framesCount << " tick: " << m_currentTick << std::endl;
			m_framesCount = 0;
		}
	}

}

void EventController::update()
{
	preUpdate();
	coreUpdate();
	postUpdate();
}


void EventController::draw(float interpolation)
{
	window->clear();

	preDraw(interpolation);
	coreDraw(interpolation);
	postDraw(interpolation);

	window->display();
}

void EventController::coreDraw(float interpolation) {
	// Draw the activeRegion so it can draw its drawables.
	window->draw(*activeRegion);

	activeRegion->getGUI().draw();
}

bool EventController::handleCoreEvent(sf::Event & event)
{
	// Handle events not handled by the GUI
	switch (event.type) 
	{
		case sf::Event::Closed:
		{
			// Close the window, thus closing the game.
			window->close();
			return true;
		}
		case sf::Event::MouseMoved:
		{
			// Get the pixel position and map it to coordinates
			sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
			sf::Vector2f actualPosition = window->mapPixelToCoords(mousePos);
			// Pass the event to the active region to handle
			return true;
		}
		case sf::Event::MouseButtonPressed:
		{
			// Get the pixel position and map it to coordinates
			sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
			sf::Vector2f actualPosition = window->mapPixelToCoords(mousePos);
			// Pass the event to the active region to handle
			return true;
		}
		case sf::Event::MouseWheelScrolled:
		{
			// Pass the event to the active region to handle
			return true;
		}
		case sf::Event::KeyPressed:
		{
			// Pass the event to the active region to handle
			return true;
		}
		case sf::Event::KeyReleased:
		{
			// Pass the event to the active region to handle
			return true;
		}
		case sf::Event::Resized:
		{
			// Reset the camera to the same as the window
			m_camera.reset(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
			// Set the view on the window to be the reset camera
			window->setView(m_camera);
			// Set the view on the GUI to be the reset camera
			activeRegion->getGUI().setView(m_camera);
			return true;
		}
		default:
		{
			return false;
		}
	}
}