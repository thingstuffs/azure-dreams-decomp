#include "common.h"
#include "shared/town_event_buffer.h"

extern s32 func_800189FC(void *entries, s32 value);
extern s32 scene_price;

/* Stores the result of func_800189FC for D_8001B218 in D_8001B210. */
void store_price_from_entries(void) {
    scene_price = func_800189FC(town_event_records, 1);
}
