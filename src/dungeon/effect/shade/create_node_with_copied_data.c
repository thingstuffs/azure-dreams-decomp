#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

typedef struct S_818C2E40_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818C2E40_0;   /* node in func_818C2E40 */

typedef struct S_818C2E40_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s8 unk_0A;
} S_818C2E40_1;   /* fields in func_818C2E40 */

typedef struct {
    s32 word[6];
} Copy24;

extern void register_node(void *entry, void *registration_id);
extern u8 D_800240C0[9];
extern u8 D_800241D4[9];

/* Allocate and initialize a node with the supplied value and 24 bytes of data. */
void *create_motion_copy_sprite(s32 node_value, void *initial_data)
{
    ObjectNodeHeader *node;
    S_818C2E40_1 *fields;
    SpriteFrameState *display;
    void *node_data;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {

        node->unk_10 = D_800240C0;
        register_node(node, D_800241D4);
        fields = (u8 *)node + 0x20;
        ((S_818C2E40_0 *)node)->unk_20 = node_value;
        fields->unk_04 = 0;
        fields->unk_06 = 0;
        fields->unk_08 = 0x7DCF;
        fields->unk_0A = 0;

        display = node->sprite;
        display->scale_y = 0x1000;
        display->scale_x = 0x1000;

        node_data = node->position;
        *(Copy24 *)node_data = *(Copy24 *)initial_data;
        return node;
    }
    return 0;
}

/* MECHANISM: The 0x20 frame follows from node/node_value/initial_data held in s0/s1/s2 and
   the 24-byte struct assignment emits retail's grouped six-word copy.
   The early `return 0;` on the null edge is retail's `j <epilogue>` with `move v0,zero`
   in its delay slot (true base 0x80024640, target row+0xB4 = the `lw ra` epilogue). */
