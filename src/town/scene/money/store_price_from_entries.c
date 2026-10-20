#include "common.h"
#include "shared/town_event_buffer.h"

extern s32 func_800189FC(void *entries, s32 value);
extern s32 D_8001B210;

/* Stores the result of func_800189FC for D_8001B218 in D_8001B210. */
void store_price_from_entries(void) {
    D_8001B210 = func_800189FC(D_8001B218, 1);
}
