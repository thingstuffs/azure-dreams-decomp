#include "common.h"

short SD_Call(int flags);
extern s32 D_800D0460;

/* Triggers event 0x519 at interval multiples when enabled. */
void trigger_event_hex_519_interval_multiples_enabled(s32 count, s32 interval) {
    if (((count % interval) == 0) && (D_800D0460 != 0)) {
        SD_Call(0x519);
    }
}
