#pragma once

#include <MindScape/Utils/DllUtils.h>
#include <MindScape/Core/TemplateRegion.h>

#include <GameBackbone/Core/CoreEventController.h>

namespace MindScape
{

	using Ulong = unsigned long ;

	class libMindScape EventController : public GB::CoreEventController <EventController>
	{
	public:
		// Constructors
		EventController();
		EventController(const EventController& other) = delete;
		EventController(EventController&& other) = default;
		EventController& operator=(const EventController& other) = delete;
		EventController& operator=(EventController&& other) = default;
		virtual ~EventController() = default;

		void runLoop();

		void update();
		void preUpdate() {};
		void coreUpdate() {};
		void postUpdate() {};

		void draw(float interpolation);
		void preDraw(float interpolation) {};
		void coreDraw(float interpolation);
		void postDraw(float interpolation) {};

		// PAIN POINT
		// CoreEventController should not force us to use a preDraw, coreDraw, and postDraw system.
		// This only matters because it is casting up to the child, expecting the child to actually have 
		// the correct methods.
		void draw() {};
		void preDraw() {};
		void coreDraw() {};
		void postDraw() {};

		// Event handling
		bool handleCoreEvent(sf::Event& event);

	private:
		const sf::Int32 TICKS_PER_SECOND = 60;
		const sf::Int32 SKIP_TICKS = 1000 / TICKS_PER_SECOND;
		const sf::Int32 MAX_FRAMESKIP = 10;

		sf::Int32 m_nextGameTick;
		/**Used for updates which may base themselves on how many ticks have passed. */
		Ulong m_currentTick = 0;
		size_t m_updateLoops = 0;
		Ulong m_sleepTime = 0;

		// Used for tracking frames per second
		sf::Int32 m_fpsCheckpoint = 0;
		Ulong m_framesCount = 0;
		

		sf::View m_camera;

		TemplateRegion m_mainRegion;

		sf::Int32 getElapsedTime();
	};
}
