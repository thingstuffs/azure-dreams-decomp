#include "common.h"

extern s32 D_8002D690[4];
extern s32 D_8002D6A0[3];

/* Initialize entry pointers, per-entry defaults, and shared state defaults. */
void func_8001BDF0(void *state, s32 entry_count) {
    s32 entry_index;

    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        *(u8 **) ((u8 *) state + 0x68C + entry_index * 4) = (u8 *) state + 0x6A4 + entry_index * 0x10;
        *(s32 *) ((u8 *) state + 0x704 + entry_index * 0x10) = D_8002D690[0];
        *(s32 *) ((u8 *) state + 0x708 + entry_index * 0x10) = D_8002D690[1];
        *(s32 *) ((u8 *) state + 0x70C + entry_index * 0x10) = D_8002D690[2];
        *(s32 *) ((u8 *) state + 0x710 + entry_index * 0x10) = D_8002D690[3];
        *(s32 *) ((u8 *) state + 0x6A8 + entry_index * 0x10) = (s32) ((u8 *) state + 0x704 + entry_index * 0x10);
        *(u8 **) ((u8 *) state + 0x6AC + entry_index * 0x10) = (u8 *) state + 0x670;
    }
    *(s32 *) ((u8 *) state + 0x670) = D_8002D6A0[0];
    *(s32 *) ((u8 *) state + 0x674) = D_8002D6A0[1];
    *(s32 *) ((u8 *) state + 0x678) = D_8002D6A0[2];
}
