#include "shared/object_node.h"
#include "common.h"


typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern void register_node(void *, void *);

extern u8 linked_sprite_renderer_address[];
extern Copy12 D_80077818;
extern u8 D_8016ABC8[];


typedef struct S_8016AD00_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016AD00_0;   /* part1 in allocate_type_12_object */

typedef struct S_8016AD00_1 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8016AD00_1;   /* part2 in allocate_type_12_object */

/* Allocate a type 0x12 object and initialize its state and default data. */
/* Creates a zero-sized black sprite at the origin with a copied 12-byte entry from D_80077818 and its
 * update callbacks. */
void allocate_type_12_object(void)
{
    ObjectNodeHeader * object;
    S_8016AD00_0 *primary_state;
    S_8016AD00_1 *secondary_state;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->unk_10) = D_8016ABC8;
        register_node(object, linked_sprite_renderer_address);

        primary_state = (object->position);
        primary_state->unk_0A = 0;
        primary_state->unk_06 = 0;
        primary_state->unk_02 = 0;

        secondary_state = (object->sprite);
        secondary_state->unk_1E = 0;
        secondary_state->unk_1C = 0;
        secondary_state->unk_0E = 0;
        secondary_state->unk_0D = 0;
        secondary_state->unk_0C = 0;

        (*(Copy12 *)((u8 *)object + 0x4C)) = D_80077818;
        secondary_state->unk_08 = (u8 *)object + 0x4C;
    }
}
