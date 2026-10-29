#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/service.h"


/* Invokes the callback with values 2 and 13 and two zero arguments. */
void call_scene_service_220_d_2(void) {
    ((void (*) (s32, s32, s32, s32))town_scene_root->services->callback_220)(2, 0xD, 0, 0);
}
