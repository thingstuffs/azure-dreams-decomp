#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

extern u8 *beldo_actor_nodes[3];
extern u8 D_8016A36C[];
extern u8 *allocate_list_node(s32, u8 *);
extern void register_node(u8 *, u8 *);
extern void initialize_actor_sprite_and_animation(u8 *, void *, void *, s32);
extern void try_move_actor_to_valid_position(u8 *, void *, void *, u8 *);
extern s32 clear_center_tile_flags_when_enabled(void);
extern void update_actor_callbacks_and_motion(void *owner_arg, void *motion, void *data);
extern M2C_UNK D_80173980;

typedef struct S_80169D28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80169D28_0;   /* obj in create_multi_form_actor */

typedef struct S_80169D28_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    u8 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xD];
    s8 unk_AA;
    u8 pad_AB[0x1];
    s8 unk_AC;
} S_80169D28_1;   /* child in create_multi_form_actor */

typedef struct S_80169D28_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80169D28_2;   /* first in create_multi_form_actor */

u8 *create_multi_form_actor(s16 init_flags, s32 value24, s32 value25, s32 value0A) {
    u8 *result;
    s32 mode;
    u8 *obj;
    u8 *child;
    u8 *first;
    SpriteFrameState *second;
    s16 saved_init_flags;
    s16 saved_value24;
    s16 saved_value25;
    s16 saved_value0A;

    result = NULL;
    saved_value0A = value0A;
    saved_init_flags = init_flags;
    saved_value24 = value24;
    saved_value25 = value25;
    if (clear_center_tile_flags_when_enabled() == 0) {
        obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
        if (obj != NULL) {
            result = obj + 0x20;
            *beldo_actor_nodes = obj;
            ((S_80169D28_0 *)obj)->unk_10 = &update_actor_callbacks_and_motion;
            child = obj + 0x20;
            ((S_80169D28_1 *)child)->unk_13 = 0x38;
            register_node(obj, project_sprite_chain);
            first = ((S_80169D28_0 *)obj)->unk_08;
            ((S_80169D28_2 *)first)->unk_0A = saved_value0A;
            second = ((S_80169D28_0 *)obj)->unk_0C;
            mode = saved_init_flags & 3;
            second->unk_24 = saved_value24;
            second->frameTable = &D_80173980;
            second->unk_25 = saved_value25;
            if (mode == 1) {
                ((S_80169D28_1 *)child)->unk_14 = ((S_80169D28_1 *)child)->unk_14 | 0x6000;
                ((S_80169D28_1 *)child)->unk_1C = ((S_80169D28_1 *)child)->unk_1C | 0x6000;
            } else if (mode >= 2) {
                ((S_80169D28_1 *)child)->unk_14 = ((S_80169D28_1 *)child)->unk_14 | 0x2000;
                ((S_80169D28_1 *)child)->unk_1C = ((S_80169D28_1 *)child)->unk_1C | 0x2000;
            }
            ((S_80169D28_1 *)child)->unk_AC = 0;
            second->flags = second->flags | 0x400;
            initialize_actor_sprite_and_animation(obj, first, second, saved_init_flags);
            ((S_80169D28_1 *)child)->unk_9A = 0xFF;
            ((S_80169D28_1 *)child)->unk_9C = -1;
            ((S_80169D28_1 *)child)->unk_8C = D_8016A36C;
            ((S_80169D28_1 *)child)->unk_AA = 0;
            second->flags = second->flags | 0x80;
            try_move_actor_to_valid_position(child, first, second, result);
        }
    }
    return result;
}
