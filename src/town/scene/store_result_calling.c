#include "common.h"
#include "shared/town_event_buffer.h"

extern s32 func_800189FC(void *, s32);
extern s32 scene_price;

/* Computes scene_price from town_event_records using func_800189FC in mode 0. */
void store_result_calling(void) {
    scene_price = func_800189FC(town_event_records, 0);
}
