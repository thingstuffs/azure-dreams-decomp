#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CBB68_0 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
} S_800CBB68_0;   /* temp_v0 in townAllocateVariantObject */

typedef struct S_800CBB68_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800CBB68_1;   /* temp_s0 in townAllocateVariantObject */

typedef struct S_800CBB68_2 {
    u8 pad_00[0x96];
    s8 unk_96;
} S_800CBB68_2;   /* temp_s1 in townAllocateVariantObject */


extern void *townCreateTownEffectObject();
extern s16 townQueryLoweredTransformPosition();
extern void townInitializeRecordFromTableIndex();

/* Allocate and initialize an object with the given coordinates and variant. */
void townAllocateVariantObject(s32 variant, s32 x, s32 y) {
    s32 setup_arg;
    S_800CBB68_1 *position;
    S_800CBB68_2 *state;
    void *object;

    object = townCreateTownEffectObject(0, 0, 0, 0);
    if (object != NULL) {
        position = ((S_800CBB68_0 *)object)->unk_08;
        setup_arg = ((S_800CBB68_0 *)object)->unk_0C;
        state = (s8 *)object + 0x20;
        position->unk_00 = (s32)(x << 0x10);
        position->unk_04 = (s32)(y << 0x10);
        position->unk_08.at00.v = 0xFF000000;
        position->unk_08.at02.v = townQueryLoweredTransformPosition(position);
        state->unk_96 = variant;
        townInitializeRecordFromTableIndex(state, position, setup_arg);
    }
}
