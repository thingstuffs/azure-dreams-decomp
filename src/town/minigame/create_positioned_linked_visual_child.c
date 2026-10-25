#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "records/Rec_func_8008F074_arg0.h"
#include "shared/vector.h"

typedef struct S_800BF9E4_0_pre {
    u8 * unk_00;
    u8 pad_04[0xC];
} S_800BF9E4_0_pre;   /* the 0x10 bytes before arg0 in create_positioned_linked_visual_child, addressed as arg0[-1] */

   /* arg1 in create_positioned_linked_visual_child */

typedef struct S_800BF9E4_5 {
    u8 pad_00[0xA0];
    void * unk_A0;
} S_800BF9E4_5;
struct Dst;
struct Elem;
void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern void configure_the_set_mode_n_1();

extern u8 sprite_chain_projector_address[];
extern u8 lit_mesh_renderer_address[];
extern u8 D_800BF72C[];
extern u8 D_800BF8DC[];
extern u8 D_800D2364[];
extern s32 D_800D237C[];
extern u8 D_800F9F78[];

/* Initialize the object and create a positioned visual child linked to it. */
void create_positioned_linked_visual_child(void *object, IntVector3 *position, s32 resource_context) {
    ObjectNodeHeader *child;
    S_800BF9E4_5 *child_data;
    SpriteFrameState *child_visual;
    ObjectPosition *child_position;

    ((S_800BF9E4_0_pre *)object)[-1].unk_00 = &D_800BF8DC[0];
    ((Rec_func_8008F074_arg0 *)object)->unk_50 = 0;
    register_node(object - 0x20, &sprite_chain_projector_address[0]);
    position->x = 0x0F200000;
    position->y = 0x02600000;
    position->z = 0;
    configure_the_set_mode_n_1(object, position, &D_800D2364[0]);
    select_record_entry_and_value(resource_context, &D_800F9F78[0], 0);
    ((Rec_func_8008F074_arg0 *)object)->unk_48 = D_800D237C[0];
    child = allocate_flagged_object_node(0x136);
    if (child != 0) {
        child_data = ((void *)child) + 0x20;
        register_node(child, &lit_mesh_renderer_address[0]);
        child_visual = child->sprite;
        child->update_callback = &D_800BF72C[0];
        child_visual->scale_x = 0x1000;
        child_visual->scale_y = 0x1000;
        child_visual->offset_x = 0x1000;
        child_visual->angle_z = 0;
        child_visual->color.word = 0x808080;
        child_visual->source = 0x75;
        child_position = child->position;
        child_position->x.v = 0x0FA00000;
        child_position->y.v = 0x02300000;
        child_position->z.v = 0;
        child_data->unk_A0 = object;
    }
}

/* MECHANISM: Natural argument liveness gives the 0x20 frame and s2/s0/s1 save order. This restores the
   0xA0(v0) store and its upstream branch displacement; aligned residue is zero. */
