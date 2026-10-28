#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"

typedef s32 M2C_UNK;




extern s32 generate_random_value(void);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 ifrit_object_callback_3[];
extern u8 D_80162820[];
extern u8 D_80162860[];
extern M2C_UNK D_8015EE84;

/* The row begins with a 132-byte data bank; the executable body follows it. */

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Ifrit with default frames at D_80162820, applies spawn flags, and attempts valid tile placement. */
void *queue_linked_render_packets(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 left;
    s32 right;
    s8 held_a;
    s16 held_c;
    s8 held_b;

    work = 0;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = ifrit_object_callback_3;
        work->species = MONSTER_IFRIT;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = held_c;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = held_b;
        actor = work;
        part_b->frameTable = D_80162820;
        part_b->tile_x = held_a;

        if (kind == 1) {
            left = work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->flags14 = left;
            work->flags1C = right;
        } else if (kind >= 2) {
            left = work->flags14 | ACTOR_CLASS_ENABLED;
            right = work->flags1C | ACTOR_PLAYER_SIDE;
            work->flags14 = left;
            work->flags1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        work->flags1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_80162860;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &D_8015EE84;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
