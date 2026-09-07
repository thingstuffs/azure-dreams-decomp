#include "common.h"

typedef struct S_80174DA0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80174DA0_0;   /* obj in func_80174DA0 */

typedef struct S_80174DA0_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174DA0_1;   /* arg0 in func_80174DA0 */

typedef struct S_80174DA0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80174DA0_2;   /* dst in func_80174DA0 */

typedef struct S_80174DA0_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80174DA0_3;   /* aux in func_80174DA0 */

typedef struct S_80174DA0_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 * unk_10;
    u8 pad_14[0x2];
    u8 unk_16;
    u8 pad_17[0x5];
    void * unk_1C;
} S_80174DA0_4;   /* tail in func_80174DA0 */

typedef struct S_80174DA0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174DA0_5;   /* ((S_80174DA0_1 *)arg0)->unk_08 in func_80174DA0 */



extern void *func_8003FD64();
extern u8 D_80174AD4[9];
extern u8 D_80175F90[9];

/* Creates an effect at the parent position and initializes its display and state. */
void func_80174DA0(S_80174DA0_1 *parent, s32 effect_param, u8 *effect_data)
{
    void *effect;
    S_80174DA0_2 *position;
    S_80174DA0_3 *display;
    S_80174DA0_4 *state;
    void *parent_position;
    u16 coordinate;

    effect = func_8003FD64(0x12, parent);
    if (effect != 0) {
        ((S_80174DA0_0 *)effect)->unk_10 = D_80174AD4;
        position = ((S_80174DA0_0 *)effect)->unk_08;

        coordinate = ((S_80174DA0_5 *)(parent->unk_08))->unk_02;
        position->unk_0E = coordinate;
        position->unk_02 = coordinate;

        coordinate = ((S_80174DA0_5 *)(parent->unk_08))->unk_06;
        position->unk_12 = coordinate;
        position->unk_06 = coordinate;

        coordinate = ((S_80174DA0_5 *)(parent->unk_08))->unk_0A;
        position->unk_16 = coordinate;
        position->unk_0A = coordinate;

        display = ((S_80174DA0_0 *)effect)->unk_0C;
        display->unk_08 = D_80175F90;
        display->unk_1E = 0x1000;
        display->unk_1C = 0x1000;
        display->unk_0C = 0;
        display->unk_06 = 8;

        parent_position = parent->unk_08;
        state = (u8 *)effect + 0x20;
        state->unk_0C = effect_param;
        state->unk_10 = effect_data;
        state->unk_1C = parent_position;
        state->unk_16 = *effect_data;
        ((S_80174DA0_0 *)effect)->unk_20 = 0x40;
        state->unk_04 = 0;
    }
}
