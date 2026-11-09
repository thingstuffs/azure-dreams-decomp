#include "common.h"
#include "town/scene/money.h"
#include "shared/town_event_buffer.h"
#include "town/data.h"
#include "town/scene.h"

/* Computes scene_price from town_event_records using func_800189FC in mode 1. */
s32 store_price_from_entries(void) {
    return scene_price = sum_flagged_terminated_entries(town_event_records, 1);
}
