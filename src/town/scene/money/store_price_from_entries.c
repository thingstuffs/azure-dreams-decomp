#include "common.h"
#include "town/scene/money.h"
#include "shared/town_event_buffer.h"

extern s32 func_800189FC(void *entries, s32 value);
extern s32 scene_price;

/* Computes scene_price from town_event_records using func_800189FC in mode 1. */
s32 store_price_from_entries(void) {
    return scene_price = func_800189FC(town_event_records, 1);
}
