#pragma once

#include <iostream>
#include <stdint.h>

namespace AEC {
	using GameObject = uint32_t;

	///gInfo - gameobject information
	struct gInfo {
		gInfo(uint32_t _id, bool _active) : id(_id), active(_active) {}
		gInfo(const gInfo& ga) : id(ga.id), active(ga.active) {}
		uint32_t id;
		bool active;
	};
}