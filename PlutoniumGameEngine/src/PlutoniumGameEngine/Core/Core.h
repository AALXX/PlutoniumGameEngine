#pragma once

#ifdef PGE_PLATFORM_WINDOWS

	#ifdef PGE_BUILD_DLL
		#define PGE_API __declspec(dllexport)
	#else
		#define PGE_API __declspec(dllimport)

	#endif
#else
	#error Plutonium is supported only by windows!
#endif // PGE_PLATFORM_WINDOWS

#define BIT(x) (1<<x)
