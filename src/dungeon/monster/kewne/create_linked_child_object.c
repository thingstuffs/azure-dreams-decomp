#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "engine/node/allocation.h"

typedef struct Pair {
    s32 first;
    s32 second;
} Pair;

extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern void draw_textured_ellipse();
extern u8 D_80175B1C[12];
extern u8 D_80175FA8[12];
extern u8 D_80175FB4[12];

typedef struct S_80175D7C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80175D7C_0;

typedef struct S_80175D7C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s16 unk_0C;
} S_80175D7C_2;

typedef struct S_80175D7C_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175D7C_3;   /* arg0 in create_linked_child_object */

/* Creates and initializes a child object linked to its parent state. */
void create_linked_child_object(void *parent_state) {
    void *allocation_head_address;
    ObjectNodeHeader **allocation_head;
    Pair pair;
    s32 pair_first;
    s32 pair_second;
    Pair *pair_ptr;
    ObjectNodeHeader *child;
    SpriteFrameState *visual;
    S_80175D7C_2 *child_state;

    allocation_head_address = (u8 *)parent_state - 0x20;
    allocation_head = allocation_head_address;
    child = allocate_list_node(514,allocation_head);
    if (child != 0) {
        child->update_callback = D_80175B1C;
        register_node(child, project_sprite_chain);
        pair_first = 0x01000340;
        pair_second = 0x200020;
        pair_ptr = &pair;
        visual = child->sprite;
        visual->source = D_80175FA8;
        visual->scale_x = 0x1000;
        visual->scale_y = 0x800;
        child_state = (u8 *)child + 0x20;
        ((S_80175D7C_0 *)child)->unk_20 = parent_state;
        child_state->unk_0A = ((S_80175D7C_3 *)parent_state)->unk_2A;
        child_state->unk_0C = 0x30;
        pair.second = pair_second;
        pair.first = pair_first;
        draw_textured_ellipse(D_80175FB4, pair_ptr, 1, 0);
    }
}

/* MECHANISM: The Pair stack object plus long-lived arg0/result locals produces the retail 0x28 frame
   and s1/s0 save contract. */
