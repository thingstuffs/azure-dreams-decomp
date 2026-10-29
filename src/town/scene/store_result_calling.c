#include "common.h"
#include "town/scene/script_hooks.h"
#include "shared/town_event_buffer.h"
#include "town/scene.h"

extern s32 func_800189FC(void *, s32);
extern s32 scene_price;

/* Computes scene_price from town_event_records using func_800189FC in mode 0. */
s32 store_result_calling(void) {
    return scene_price = func_800189FC(town_event_records, 0);
}
