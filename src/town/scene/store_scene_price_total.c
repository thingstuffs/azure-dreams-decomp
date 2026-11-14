#include "common.h"
#include "town/scene/script_hooks.h"
#include "shared/town_event_buffer.h"
#include "town/scene.h"
#include "town/data.h"

/* Computes scene_price from town_event_records using func_800189FC in mode 0. */
s32 store_scene_price_total(void) {
    return scene_price = sum_flagged_terminated_entries(town_event_records, 0);
}
