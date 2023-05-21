#include "main.h"

int __cdecl CRadar__SetCoordBlip(eBlipType type, float x, float y, float z, int a5, eBlipDisplay display) {
	CVector pos(x, y, z);
	LoadScene(&pos);
	float coords = FindGroundZForCoord(x, y);
	setPlayerPos(x, y, coords + 1.0f);
	return CRadarHook->call<eBlipType, float, float, float, int, eBlipDisplay>(type, x, y, z, a5, display);
}

AsiPlugin::AsiPlugin() {
	CRadarHook = std::make_unique<memwrapper::memhook<CRadar__SetCoordBlipPrototype>>(0x5775D2, &CRadar__SetCoordBlip);
	CRadarHook->install();
}

AsiPlugin::~AsiPlugin() {
	CRadarHook->remove();
}