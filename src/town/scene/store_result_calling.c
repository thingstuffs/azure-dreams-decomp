#include "common.h"
#include "town/scene/script_hooks.h"
#include "shared/town_event_buffer.h"
#include "town/scene.h"
#include "town/data.h"

extern s32 sum_flagged_terminated_entries(void *, s32);

/* Computes scene_price from town_event_records using func_800189FC in mode 0. */
s32 store_result_calling(void) {
    return scene_price = sum_flagged_terminated_entries(town_event_records, 0);
}
