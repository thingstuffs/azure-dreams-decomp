#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct PackedVec3 {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec3;

extern void register_node(void *, void *);

extern u8 D_80044BB0[];
extern u8 D_8016F99C[];
extern u8 D_80173B1C[];
extern u8 D_80173B28[];
extern u8 D_80170000[];

typedef struct S_8016FAFC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
} S_8016FAFC_0;   /* part in create_encounter_overlay */

typedef struct S_8016FAFC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016FAFC_1;   /* sprite in create_encounter_overlay */

typedef struct S_8016FAFC_3 {
    u8 pad_00[0x5D58];
    void * unk_5D58;
    void * unk_5D5C;
} S_8016FAFC_3;   /* store_page in create_encounter_overlay */

/* Creates a sprite object with the selected vector preset and stores its global pointer. */
void create_encounter_overlay(s32 variant)
{
    ObjectNodeHeader *obj;
    u8 *part;
    u8 *call_obj;
    u8 *sprite;
    u8 *copy_src;
    u8 *sprite_vector;
    ObjectPosition *coords;

    obj = allocate_flagged_object_node(0x12);
    if (obj != NULL) {
        call_obj = obj;
        part = ((u8 *)obj) + 0x20;
        ((S_8016FAFC_0 *)part)->unk_18 = 0;
        ((S_8016FAFC_0 *)part)->unk_1C = variant;
        (obj->unk_10) = D_8016F99C;
        register_node(call_obj, D_80044BB0);

        sprite = (*(u8 * *)&obj->sprite);
        ((S_8016FAFC_1 *)sprite)->unk_14 &= 0xFFF3;

        coords = (*(u8 * *)&obj->position);
        coords->x.w.i = 0xA0;
        coords->y.w.i = 0xA;
        coords->z.w.i = 2;

        sprite = (*(u8 * *)&obj->sprite);
        ((S_8016FAFC_1 *)sprite)->unk_1E = 0x1000;
        ((S_8016FAFC_1 *)sprite)->unk_1C = 0x1000;
        ((S_8016FAFC_1 *)sprite)->unk_0E = 0x80;
        ((S_8016FAFC_1 *)sprite)->unk_0D = 0x80;
        ((S_8016FAFC_1 *)sprite)->unk_0C = 0x80;

        if (variant == 0) {

            copy_src = D_80173B1C;
            (*(PackedVec3 *)((u8 *)obj + 0x48)) =
                (*(PackedVec3 *)((u8 *)copy_src + 0));
            ((S_8016FAFC_3 *)D_80170000)->unk_5D58 = obj;
        } else {

            copy_src = D_80173B28;
            (*(PackedVec3 *)((u8 *)obj + 0x48)) =
                (*(PackedVec3 *)((u8 *)copy_src + 0));
            ((S_8016FAFC_3 *)D_80170000)->unk_5D5C = obj;
        }
        sprite_vector = part + 0x28;
        ((S_8016FAFC_1 *)sprite)->unk_08 = sprite_vector;
    }
}

/* MECHANISM: The true-space body uses a local join, not a phantom call at 0x8016FC28.
   A 0x20 frame holds variant, obj, and obj+0x20 in s2/s0/s1; packed 12-byte
   assignments reproduce the two unaligned vector-copy arms. */
