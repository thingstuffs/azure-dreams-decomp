#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/entity.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_80173DD4_arg0.h"

typedef struct S_80175060_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80175060_0;

typedef struct S_80175060_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80175060_1;


typedef struct S_80175060_3 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175060_3;


void func_8003DB94(void *, void *, s32);  /* extern */
s32 register_node();           /* extern */
extern void func_800478B8(void *entity);                      /* extern */
s32 rand();                                /* extern */
extern void update_radial_motion_or_complete(u16 *motion, s32 *position, u8 *object);

/* Creates an object with randomized phase and rotation and copies its initial state. */
s32 create_randomized_motion_object(Rec_func_80173DD4_arg0 *owner, EntityRec *initial_state) {
    s32 color;
    s32 four;
    s32 phase_rand;
    s32 rotation_rand;
    s32 biased_phase;
    s32 biased_rotation;
    S_80175060_1 *part;
    void *object;
    S_80175060_3 *state;

    object = func_8003FC64(0x212);
    if (object != 0) {
        ((S_80175060_0 *)object)->unk_10 = &update_radial_motion_or_complete;
        biased_phase = rand();
        phase_rand = biased_phase;
        part = object + 0x20;
        if (phase_rand < 0) {
            biased_phase = phase_rand + 0xFFF;
        }
        color = 0x606060;
        part->unk_04 = (s16) (phase_rand - ((biased_phase >> 0xC) << 0xC));
        four = 4;
        part->unk_08 = (s16) four;
        part = ((S_80175060_0 *)object)->unk_0C;
        part->unk_0C = color;
        part->unk_14 = (u16) (part->unk_14 | 0xC);
        part->unk_10 = (u16) (part->unk_10 | 0x20);
        func_8003DB94(part, &secondary_sprite, 0);
        func_800478B8(part);
        biased_rotation = rand();
        rotation_rand = biased_rotation;
        part->unk_1A = (s16) (rotation_rand % 4096);
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        register_node(object, project_sprite_chain);
        {
            s32 copy_word_1;

            state = ((S_80175060_0 *)object)->unk_08;
            *state = *(S_80175060_3 *)initial_state;
            copy_word_1 = state->unk_04;
            state->unk_0C = state->unk_00;
            state->unk_10 = copy_word_1;
        }
        state->unk_08.at02.v = owner->unk_88;
        return (s32) object;
    }
    return 0;
}

