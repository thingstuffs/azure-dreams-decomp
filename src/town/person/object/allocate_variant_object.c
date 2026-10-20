#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CBB68_0 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
} S_800CBB68_0;

typedef struct S_800CBB68_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800CBB68_1;

typedef struct S_800CBB68_2 {
    u8 pad_00[0x96];
    s8 unk_96;
} S_800CBB68_2;


struct IntVector3; void * create_town_effect_object(s32, struct IntVector3 *, s32, s32);
extern s16 query_lowered_transform_position();
struct Rec_D_80082E80; void initialize_record_from_table_index(void *, s32, struct Rec_D_80082E80 *);

/* Allocate and initialize an object with the given coordinates and variant. */
void allocate_variant_object(s32 variant, s32 x, s32 y) {
    s32 setup_arg;
    S_800CBB68_1 *position;
    S_800CBB68_2 *state;
    void *object;

    object = create_town_effect_object(0, 0, 0, 0);
    if (object != NULL) {
        position = ((S_800CBB68_0 *)object)->unk_08;
        setup_arg = ((S_800CBB68_0 *)object)->unk_0C;
        state = (s8 *)object + 0x20;
        position->unk_00 = (s32)(x << 0x10);
        position->unk_04 = (s32)(y << 0x10);
        position->unk_08.at00.v = 0xFF000000;
        position->unk_08.at02.v = query_lowered_transform_position(position);
        state->unk_96 = variant;
        initialize_record_from_table_index(state, (s32)(position), (struct Rec_D_80082E80 *)(setup_arg));
    }
}
