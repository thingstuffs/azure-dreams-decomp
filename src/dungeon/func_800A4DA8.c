#include "common.h"

extern s32 D_80083460;

/* Sets the entity state to 3, clears its progress, and increments the global counter. */
void func_800AA508(void *entity) {
    u16 *update_count;
    s8 *state_bytes;
    s32 *global_state;

    do {
        *(s8 *)((s8 *)entity + 0x9A) = 3;
        *(s32 *)((s8 *)entity + 0x8C) = (*(s8 *)((s8 *)entity - -0x9B) = 0);
        global_state = &D_80083460;
        state_bytes = (s8 *)global_state;
        update_count = (u16 *)(state_bytes + 0xA);
        *(s16 *)((s8 *)entity + 0x96) = 4;
    } while (0);

    *update_count = (u16)(*(u16 *)(state_bytes - -0xA) + 1);
}
