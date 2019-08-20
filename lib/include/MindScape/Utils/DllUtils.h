#pragma once

#ifdef _WIN32

	//MINDSCAPEDLL_EXPORTS
	#ifdef MindScape_EXPORTS 
		#define libMindScape __declspec(dllexport)
	#else
		#define libMindScape __declspec(dllimport)
	#endif
	#ifdef debugDefines
		#ifdef MindScape_EXPORTS 
			#define libPvtMindScape __declspec(dllexport)
		#else
			#define libPvtMindScape __declspec(dllimport)
		#endif
	#else
		#define libPvtMindScape
	#endif
#else
	#define libMindScape
	#define libPvtMindScape
#endif
