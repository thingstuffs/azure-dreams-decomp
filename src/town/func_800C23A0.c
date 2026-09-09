#include "common.h"

typedef struct S_800BFB00_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void);
    u8 pad_14[0xC];
    u16 unk_20;
} S_800BFB00_0;   /* temp_v0 in town_rain_in */

typedef struct S_800BFB00_1 {
    u8 pad_00[0x2];
    volatile u16 unk_02;
    volatile u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
} S_800BFB00_1;   /* temp_a0 in town_rain_in */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern u8 D_80083498[12];
extern u16 D_80083780[6];
extern void func_800BFB8C(void);

/* town_rain_in: creates a rain object with its callback, preset values, and position. */
void town_rain_in(s16 x, s16 y) {
    u16 preset_value;
    S_800BFB00_1 *state;
    void *object;

    object = func_8003FD64(2, D_80083498);
    if (object != 0) {
        ((S_800BFB00_0 *)object)->unk_10 = func_800BFB8C;
        ((S_800BFB00_0 *)object)->unk_20 = D_80083780[1];
        state = (s8 *)object + 0x20;
        state->unk_02 = D_80083780[3];
        preset_value = D_80083780[5];
        state->unk_08 = x;
        state->unk_0A = y;
        state->unk_0E = 6;
        state->unk_04 = preset_value;
    }
}
