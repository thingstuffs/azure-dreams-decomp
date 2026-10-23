#include "dungeon/actor.h"

extern s32 town_resource_request;
/* Stores value in town_resource_request. */
void reserve_tw_mon_load(s32 value) { town_resource_request = value; }
