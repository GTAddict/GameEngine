#pragma once

#define ENGINE_UNUSED(x) x

#define _CRITICAL(m)	{ std::lock_guard<std::mutex> guard(m);
#define _CRITICAL_END	}