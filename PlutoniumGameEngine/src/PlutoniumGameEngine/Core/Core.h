#pragma once

#ifdef PGE_PLATFORM_WINDOWS
#if PGE_DYNAMIC_LINK

	#ifdef PGE_BUILD_DLL
		#define PGE_API __declspec(dllexport)
	#else
		#define PGE_API __declspec(dllimport)

	#endif

#else
	#define PGE_API
#endif
#else
	#error Plutonium is supported only by windows!
#endif // PGE_PLATFORM_WINDOWS

#ifdef PGE_DEBUG
	#define PGE_ENABLE_ASSERTS

#endif // PGE_DEBUG


#ifdef PGE_ENABLE_ASSERTS
#define PGE_ASSERT(x, ...) { if(!(x)) { PGE_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define PGE_CORE_ASSERT(x, ...) { if(!(x)) { PGE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else
#define PGE_ASSERT(x, ...)
#define PGE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define PGE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
