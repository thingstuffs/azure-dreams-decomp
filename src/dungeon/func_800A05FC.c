#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 D_800814A0[3];

void func_800A5D5C(void *arg0) {
    u16 temp_v0;
    u16 *state;

    temp_v0 = *(u16 *)arg0 + 1;
    *(u16 *)arg0 = temp_v0;
    if ((s16)temp_v0 >= 0x10) {
        state = (u16 *)&D_80083460;
        state[5]--;
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
