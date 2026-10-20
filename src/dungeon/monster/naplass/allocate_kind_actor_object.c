#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_8016A870_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016A870_0;   /* obj in allocate_kind_actor_object */

typedef struct S_8016A870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A870_1;   /* work in allocate_kind_actor_object */

typedef struct S_8016A870_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A870_2;   /* part_a in allocate_kind_actor_object */

typedef struct S_8016A870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A870_4;   /* actor in allocate_kind_actor_object */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_8016AA3C[];
extern s32 D_8016AE68;
extern u8 D_8016E194[];
extern u8 D_8016E1DC[];

/* Allocate an actor object and initialize its parts and flags for the requested kind. */
void *allocate_kind_actor_object(s16 spawn_flags, s16 part_b_value_24, s16 part_b_value_25, s16 part_a_value)
{
    s32 kind;
    void *obj;
    S_8016A870_2 *part_a;
    SpriteFrameState *part_b;
    S_8016A870_1 *work;
    S_8016A870_4 *actor;
    register s32 flags_14;
    register s32 flags_1c;
    s8 saved_value_24;
    register s16 saved_part_value;
    s8 saved_value_25;

    work = 0;
    saved_value_24 = part_b_value_24;
    saved_part_value = part_a_value;
    saved_value_25 = part_b_value_25;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8016A870_0 *)obj)->unk_10 = D_8016AA3C;
        work->unk_13 = 0x25;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8016A870_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_value;
        part_b = ((S_8016A870_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_value_25;
        actor = work;
        part_b->frameTable = D_8016E194;
        part_b->unk_24 = saved_value_24;

        if (kind == 1) {
            flags_14 = work->unk_14 | 0x6000;
            flags_1c = work->unk_1C | 0x6000;
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else if (kind >= 2) {
            flags_14 = work->unk_14 | 0x2000;
            flags_1c = work->unk_1C | 0x2000;
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else {
            if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                work->unk_1C |= 0x200;
                set_or_clear_actor_status_slot(work, 1,
                              (generate_random_value() & 0x3F) | 0x20);
                part_b->frameTable = D_8016E1DC;
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AE68;
        part_b->flags |= 0xC;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
