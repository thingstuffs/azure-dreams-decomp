#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



typedef struct S_80FE1000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FE1000_1;   /* work in spawn_killer_slot_f */

typedef struct S_80FE1000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FE1000_4;   /* actor in spawn_killer_slot_f */

extern void *allocate_list_node();
extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern u8 D_8016AA7C[];
extern u8 killer_slot_f_default_frames[];
extern u8 killer_frame_set_1[];
extern u8 killer_slot_f_action_address[];

/* Creates a dungeon object and initializes its kind flags and part parameters. */
/* Creates Killer with default frames at D_8016E038, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_killer_slot_f(s16 kind_flags, s32 part_value_24, s32 part_value_25, s16 part_value_0a)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    void *work;
    S_80FE1000_4 *actor;
    s32 flags;
    s32 paired_flags;
    s16 saved_value_24;
    s16 saved_value_0a;
    s16 saved_value_25;

    work = 0;
    saved_value_24 = part_value_24;
    saved_value_0a = part_value_0a;
    saved_value_25 = part_value_25;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8016AA7C;
        ((S_80FE1000_1 *)work)->unk_13 = MONSTER_KILLER;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_value_0a;
        part_b = obj->sprite;
        kind = kind_flags & 3;
        part_b->tile_y = saved_value_25;
        actor = work;
        part_b->frameTable = killer_slot_f_default_frames;
        part_b->tile_x = saved_value_24;

        if (kind == 1) {
            flags = ((S_80FE1000_1 *)work)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            paired_flags = ((S_80FE1000_1 *)work)->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((S_80FE1000_1 *)work)->unk_14 = flags;
            ((S_80FE1000_1 *)work)->unk_1C = paired_flags;
        } else if (kind >= 2) {
            flags = ((S_80FE1000_1 *)work)->unk_14 | ACTOR_CLASS_ENABLED;
            paired_flags = ((S_80FE1000_1 *)work)->unk_1C | ACTOR_PLAYER_SIDE;
            ((S_80FE1000_1 *)work)->unk_14 = flags;
            ((S_80FE1000_1 *)work)->unk_1C = paired_flags;
        } else {
            if ((((kind_flags & ~3) << 16) == 0) &&
                !(((S_80FE1000_1 *)work)->unk_14 & ACTOR_RESIST_SLEEP)) {
                flags = generate_random_value();
                if (flags & 1) {
                    ((S_80FE1000_1 *)work)->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = killer_frame_set_1;
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &killer_slot_f_action_address;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
