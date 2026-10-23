#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BF654_2 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800BF654_2;   /* setup in spawn_effect_object_with_packet */

extern void register_node(void *entry, void *registration_id);
extern void configure_the_set_mode_n_1(void *record, void *setup_value, void *setup_param);

extern u8 lit_mesh_renderer_address[];
extern u8 D_800BF4CC[];
extern u8 D_800D2348[];
extern s32 D_800D2360;

/* Initialize an object and its packet, then set the caller and global flags. */
void spawn_effect_object_with_packet(void *caller_data)
{
    ObjectNodeHeader *obj;
    SpriteFrameState *part;
    void *setup;
    s32 *packet;

    obj = allocate_flagged_object_node(0x136);
    if (obj != NULL) {
        register_node(obj, lit_mesh_renderer_address);
        obj->update_callback = D_800BF4CC;
        part = obj->sprite;
        part->scale_x = 0x1000;
        part->scale_y = 0x1000;
        part->offset_x = 0x1000;
        part->color.word = 0x808080;
        setup = (u8 *)obj + 0x20;
        part->angle_z = 0;
        part->source = 0x60;
        packet = *(s32 * *)&obj->position;
        packet[0] = 0x05400000;
        packet[1] = 0x02300000;
        packet[2] = 0;
        ((S_800BF654_2 *)setup)->unk_48 = D_800D2360;
        configure_the_set_mode_n_1(setup, packet, D_800D2348);
    }
    (*(u16 *)((u8 *)caller_data + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
