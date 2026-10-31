#include "shared/actor_status_flags.h"
#include "engine/graphics.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"



typedef struct S_80170890_5 {
    u16 unk_00;
} S_80170890_5;   /* (u8 *)(((index + count) << 2) + (u32)table) + 6 in create_flagged_dungeon_actor_object */

extern s32 generate_random_value(void);
extern void LoadImage(void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 D_80170AE8[];
extern u8 cyclone_move_direction_frames[];
#include "dungeon/monster/cyclone.h"

extern u8 D_801764B8[];

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Cyclone with frames at D_80176460, loads a palette row from D_801764B8, and attempts tile
 * placement. */
void *create_flagged_dungeon_actor_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    ObjectNodeHeader *obj;
    void *work = 0;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *actor;
    s32 kind;
    s32 left;
    s32 right;
    s8 saved_kind_id = kind_id;
    s16 saved_spawn = spawn_value;
    s8 saved_variant = variant;

    obj = allocate_list_node(274, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_80170AE8;
        ((ActorRecord *)work)->species = MONSTER_CYCLONE;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_spawn;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_variant;
        part_b->tile_x = saved_kind_id;
        actor = work;
        part_b->frameTable = cyclone_move_direction_frames;

        if (kind == 1) {
            left = ((ActorRecord *)work)->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = ((ActorRecord *)work)->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((ActorRecord *)work)->flags14 = left;
            ((ActorRecord *)work)->flags1C = right;
        } else if (kind >= 2) {
            left = ((ActorRecord *)work)->flags14 | ACTOR_CLASS_ENABLED;
            right = ((ActorRecord *)work)->flags1C | ACTOR_PLAYER_SIDE;
            ((ActorRecord *)work)->flags14 = left;
            ((ActorRecord *)work)->flags1C = right;
        } else {
            if (((flags & ~3) << 16) == 0) {
                if (!(((ActorRecord *)work)->flags14 & ACTOR_RESIST_SLEEP)) {
                    if (generate_random_value() & 1) {
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = cyclone_direction_frames;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, (s16)flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = update_actor_animation;
        ((ActorRecord *)work)->flags1C |= 0x00040000;
        actor->unk_90.parts.high.s = -32;

        {
            u8 *cursor = (part_b->source);
            s32 count = 0;
            s32 index;
            u16 packet[4];
            u8 *table;
            s16 value;

            while (1) {
                index = count << 1;
                if (!(*cursor & 0x20)) {
                    break;
                }
                cursor += 12;
                count += 1;
            }
            table = (part_b->source);
            value = (((S_80170890_5 *)((u8 *)(((index + count) << 2) + (u32)table) + 6))->unk_00 >> 6) - 1;
            packet[1] = value;
            actor->unk_B0.halves.low.s = value << 6;
            packet[2] = 256;
            packet[0] = 0;
            packet[3] = 1;
            LoadImage(packet, D_801764B8);
            try_move_actor_to_valid_position(actor, part_a, part_b, work);
        }
    }
    return work;
}
