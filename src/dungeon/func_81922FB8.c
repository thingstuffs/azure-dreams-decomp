#include "common.h"
#include "records/Rec_func_800247B8_arg0.h"
#include "records/Rec_func_800247B8_arg1.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800247B8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_18;   /* overlapping accesses */
    s32 unk_1C;
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    union { s16 s; u16 u; } unk_22;   /* accessed as both */
    union { s16 s; u16 u; } unk_24;   /* accessed as both */
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[0x22];
    s16 unk_5A;
    s16 unk_5C;
} S_800247B8_0;   /* work in func_800247B8 */

typedef struct S_800247B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800247B8_1;   /* obj in func_800247B8 */

typedef struct S_800247B8_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800247B8_2;   /* part in func_800247B8 */


typedef struct S_800247B8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800247B8_4;   /* dest in func_800247B8 */




extern s32 func_8002406C(s32);
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand();
extern M2C_UNK D_80024670[];
extern M2C_UNK D_800246C4[];

/* Creates an effect at the supplied position with randomized color and radial offsets. */
void func_800247B8(Rec_func_800247B8_arg0 *source, Rec_func_800247B8_arg1 *origin)
{
    s32 elevation;
    s32 planar_radius;
    s32 azimuth;
    s32 random_value;
    void *effect;
    S_800247B8_0 *state;
    S_800247B8_2 *sprite;
    S_800247B8_4 *position;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        state = effect + 0x20;
        state->unk_5A = 10;
        state->unk_5C = 10;
        random_value = func_8002406C(8);
        state->unk_18.at00.v = 0x303030;
        if (random_value & 1) {
            state->unk_18.at00u.v = 0x90;
        }
        if (random_value & 2) {
            state->unk_18.at01.v = 0x90;
        }
        if (random_value & 4) {
            state->unk_18.at02.v = 0x90;
        }
        state->unk_10 = 0;
        state->unk_14 = 0;
        state->unk_1C = state->unk_18.at00.v;
        ((S_800247B8_1 *)effect)->unk_20 = state->unk_10;
        state->unk_04 = state->unk_14;
        state->unk_08 = state->unk_18.at00.v;
        state->unk_0C = state->unk_1C;
        ((S_800247B8_1 *)effect)->unk_10 = D_800246C4;
        func_8004491C(effect, D_80024670);

        sprite = ((S_800247B8_1 *)effect)->unk_0C;
        sprite->unk_10 = 0x20;
        sprite->unk_14 |= 0xC;
        elevation = rand(sprite) & 0xFFF;
        planar_radius = (source->unk_56 * func_80064584(elevation)) >> 12;
        state->unk_24.s = (source->unk_56 * func_800644B8(elevation)) >> 12;
        azimuth = rand() & 0xFFF;
        state->unk_20.s = ((s16)planar_radius * func_80064584(azimuth)) >> 12;
        state->unk_22.s = ((s16)planar_radius * func_800644B8(azimuth)) >> 12;

        state->unk_26 = state->unk_20.u + func_8002406C(0x10) - 8;
        state->unk_28 = state->unk_22.u + func_8002406C(0x10) - 8;
        random_value = func_8002406C(0x10);
        state->unk_36 = 0;
        state->unk_34 = 0;
        state->unk_32 = 0;
        state->unk_30 = 0;
        state->unk_2E = 0;
        state->unk_2C = 0;
        state->unk_2A = state->unk_24.u + random_value - 8;

        position = ((S_800247B8_1 *)effect)->unk_08;
        position->unk_02 = origin->unk_02;
        position->unk_06 = origin->unk_06;
        position->unk_0A = origin->unk_0A;

        sprite = ((S_800247B8_1 *)effect)->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
    }
}
