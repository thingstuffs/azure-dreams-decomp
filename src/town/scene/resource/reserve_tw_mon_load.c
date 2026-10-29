#include "common.h"
#include "town/scene/resource.h"

extern s32 town_resource_request;

/* reserve_tw_mon_load: store the town monster load reservation value. */
void reserve_tw_mon_load(s32 reservation_value) {
    town_resource_request = reservation_value;
}
