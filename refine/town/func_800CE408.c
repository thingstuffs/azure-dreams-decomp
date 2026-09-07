#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CBB68_0 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
} S_800CBB68_0;   /* temp_v0 in func_800CBB68 */

typedef struct S_800CBB68_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800CBB68_1;   /* temp_s0 in func_800CBB68 */

typedef struct S_800CBB68_2 {
    u8 pad_00[0x96];
    s8 unk_96;
} S_800CBB68_2;   /* temp_s1 in func_800CBB68 */


extern void *func_8009C390();
extern s16 func_800C2AE8();
extern M2C_UNK func_800CBAE0();

/* Allocate and initialize an object with the given coordinates and variant. */
void func_800CBB68(s32 variant, s32 x, s32 y) {
    s32 setup_arg;
    S_800CBB68_1 *position;
    S_800CBB68_2 *state;
    void *object;

    object = func_8009C390(0, 0, 0, 0);
    if (object != NULL) {
        position = ((S_800CBB68_0 *)object)->unk_08;
        setup_arg = ((S_800CBB68_0 *)object)->unk_0C;
        state = (s8 *)object + 0x20;
        position->unk_00 = (s32)(x << 0x10);
        position->unk_04 = (s32)(y << 0x10);
        position->unk_08.at00.v = 0xFF000000;
        position->unk_08.at02.v = func_800C2AE8(position);
        state->unk_96 = variant;
        func_800CBAE0(state, position, setup_arg);
    }
}
