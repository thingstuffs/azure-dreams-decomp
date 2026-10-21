#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_8017088C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017088C_0;   /* obj in create_configured_actor_effect */

typedef struct S_8017088C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8017088C_1;   /* work in create_configured_actor_effect */

typedef struct S_8017088C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8017088C_2;   /* part_a in create_configured_actor_effect */

typedef struct S_8017088C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8017088C_4;   /* actor in create_configured_actor_effect */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_80170A78[];
void update_creature_animation_action(void *actor, void *context, void *sprite_arg, void *creature);
extern u8 D_80174880[];
extern u8 D_801748E0[];

void *create_configured_actor_effect(s16 mask, s16 value_24, s16 value_25, s16 value_0A)
{
    s32 kind;
    void *obj;
    S_8017088C_2 *part_a;
    SpriteFrameState *part_b;
    S_8017088C_1 *work;
    S_8017088C_4 *actor;
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;
    void *call_a1;

    work = 0;
    saved_arg1 = value_24;
    saved_arg3 = value_0A;
    saved_arg2 = value_25;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8017088C_0 *)obj)->unk_10 = D_80170A78;
        work->unk_13 = 0x29;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8017088C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_8017088C_0 *)obj)->unk_0C;
        kind = mask & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->frameTable = D_80174880;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind > 1) {
            left = work->unk_14 | 0x2000;
            right = work->unk_1C | 0x2000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (((mask & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_801748E0;
                }
            }
        }
        initialize_actor_sprite_and_animation(((void *)(obj)), part_a, part_b, mask);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &update_creature_animation_action;
        work->unk_1C |= 0x40000;
        actor->unk_92 = -0x18;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
