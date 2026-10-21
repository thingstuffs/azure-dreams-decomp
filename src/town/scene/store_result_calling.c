#include "common.h"
#include "shared/town_event_buffer.h"

extern s32 func_800189FC(void *, s32);
extern s32 scene_price;

/* Store the result of calling func_800189FC with D_8001B218 and zero. */
void store_result_calling(void) {
    scene_price = func_800189FC(town_event_records, 0);
}
