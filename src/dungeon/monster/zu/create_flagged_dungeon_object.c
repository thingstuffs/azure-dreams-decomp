#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



typedef struct S_80FA5000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FA5000_1;   /* work in create_flagged_dungeon_object */

typedef struct S_80FA5000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x3];
    s16 unk_A0;
} S_80FA5000_4;   /* actor in create_flagged_dungeon_object */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value(void); /* Retail RNG reads no argument registers. */
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern u8 D_80152A70[];
extern u8 D_80156AD4[];
extern u8 D_80156AFC[];
extern u8 D_80153138[];

void *create_flagged_dungeon_object(s16, s16, s16, s16)
#ifdef __mips__
#endif
;

/* Creates a Zu actor at the supplied tile and height, then initializes mode flags, status, and callbacks. */
void *create_flagged_dungeon_object(s16 mask, s16 value_24, s16 value_25, s16 value_0A)
{
    s32 kind;
    void *work = 0;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    S_80FA5000_4 *actor;
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;

    saved_arg1 = value_24;
    saved_arg3 = value_0A;
    saved_arg2 = value_25;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->unk_10 = D_80152A70;
        ((S_80FA5000_1 *)work)->unk_13 = MONSTER_ZU;
        register_node(obj, project_sprite_chain);

        part_a = *(void ** *)&obj->position;
        part_a->z.w.i = saved_arg3;
        part_b = *(void ** *)&obj->sprite;
        kind = mask & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->frameTable = D_80156AD4;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = ((S_80FA5000_1 *)work)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = ((S_80FA5000_1 *)work)->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((S_80FA5000_1 *)work)->unk_14 = left;
            ((S_80FA5000_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_80FA5000_1 *)work)->unk_14 | ACTOR_CLASS_ENABLED;
            right = ((S_80FA5000_1 *)work)->unk_1C | ACTOR_PLAYER_SIDE;
            ((S_80FA5000_1 *)work)->unk_14 = left;
            ((S_80FA5000_1 *)work)->unk_1C = right;
        } else {
            if (((mask & ~3) << 16) == 0) {
                if (!(((S_80FA5000_1 *)work)->unk_14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        ((S_80FA5000_1 *)work)->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_80156AFC;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, mask);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_80153138;
        ((S_80FA5000_1 *)work)->unk_1C |= 0x40000;
        actor->unk_A0 = 0;
        actor->unk_92 = -0x30;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
