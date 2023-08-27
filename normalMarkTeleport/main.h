#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <memory>
#include "memwrapper/memwrapper.h"

enum eBlipType {
    BLIP_NONE,
    BLIP_CAR,
    BLIP_CHAR,
    BLIP_OBJECT,
    BLIP_COORD,
    BLIP_CONTACTPOINT,
    BLIP_SPOTLIGHT,
    BLIP_PICKUP,
    BLIP_AIRSTRIP
};

enum eBlipDisplay {
    BLIP_DISPLAY_NEITHER,
    BLIP_DISPLAY_MARKER_ONLY,
    BLIP_DISPLAY_BLIP_ONLY,
    BLIP_DISPLAY_BOTH
};

struct CVector {
    float x, y, z;

    CVector(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    };
};

void LoadScene(CVector* pos) {
	((void(__cdecl*)(CVector*))0x40ED80)(pos);
}

float FindGroundZForCoord(float x, float y) {
	return ((float(__cdecl*)(float, float))0x569660)(x, y);
}

void setPlayerPos(float x, float y, float z) {
    void* CPed = *(void**)(0xB6F5F0);
    void* CVehicle = *(void**)((uint32_t)CPed + 0x58C);
    CVector position(x, y, z);
    ((void(__thiscall*) (void*, CVector*))(0x4241C0))(CVehicle == nullptr ? CPed : CVehicle, &position);
}

using CRadar__SetCoordBlipPrototype = int(__cdecl*)(eBlipType, float, float, float, int, eBlipDisplay);
std::unique_ptr<memwrapper::memhook<CRadar__SetCoordBlipPrototype>> CRadarHook;

class AsiPlugin{
public:
	explicit AsiPlugin();
	virtual ~AsiPlugin();
} AsiPlugin;

#endif // !_MAIN_H_
