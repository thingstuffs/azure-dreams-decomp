#include "shared/entity.h"
#include "engine/node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/status.h"
#include "dungeon/effect/screen.h"


/* cfail-repair: tf7-phase1-cache-v3 */
s32 generate_random_value(void);                          /* extern */
extern M2C_UNK D_8014CA8C;
extern M2C_UNK D_8014CF74;
extern M2C_UNK D_8014FD30;
extern M2C_UNK D_8014FD78;

void *spawn_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Stealth with frames at D_8014FD30; a random display variant changes sprite flags and unlinks the
 * node. */
void *spawn_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c) {
    s32 unksp20;
    s32 kind;
    s32 variant;
    void *obj_alt;
    SpriteFrameState *part_b;
    ObjectPosition *part_a;
    void *work_copy;
    ObjectNodeHeader *object;
    ActorRecord *work;

    unksp20 = (s32) *(s8 *)-0x149C;
    work = NULL;
    variant = 1;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != NULL) {
        work = ((void *)object) + 0x20;
        object->update_callback = &D_8014CA8C;
        work->species = MONSTER_STEALTH;
        register_node(object, project_sprite_chain);
        part_a = object->position;
        part_a->z.w.i = attr_c;
        part_b = object->sprite;
        part_b->tile_y = attr_b;
        work_copy = work;
        part_b->frameTable = &D_8014FD30;
        kind = spawn_flags & 3;
        part_b->tile_x = attr_a;
        if (kind == 1) {
            work->flags14 = (s32) (work->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER));
            work->flags1C = (s32) (work->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER));
        } else if (kind >= 2) {
            work->flags14 = (s32) (work->flags14 | ACTOR_CLASS_ENABLED);
            work->flags1C = (s32) (work->flags1C | ACTOR_PLAYER_SIDE);
        } else if (((spawn_flags & ~3) << 0x10) == 0) {
            if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    work->flags1C = (s32) (work->flags1C | ACTOR_ASLEEP);
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = &D_8014FD78;
                }
            }
            variant = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(object, part_a, part_b, spawn_flags);
        ((ActorRecord *)work_copy)->action_id.u = 0xFF;
        ((ActorRecord *)work_copy)->unk_9C = -1;
        ((ActorRecord *)work_copy)->unk_8C.address = &D_8014CF74;
        ((ActorRecord *)work_copy)->unk_A4.halves.low.s = -1;
        if (variant != 0) {
            ((ActorRecord *)work_copy)->unk_A4.halves.high.s = 0;
        } else {
            obj_alt = work_copy - 0x20;
            ((ActorRecord *)work_copy)->unk_A4.halves.high.s = 1;
            part_b->tpage_abr = 0x60;
            part_b->flags = (u16) (part_b->flags | 0xC);
            part_b->clut = (u16) (part_b->clut - 0x80);
            unlink_node(obj_alt);
            retire_tracked_effect_by_id(obj_alt);
        }
        try_move_actor_to_valid_position(work_copy, part_a, part_b, work);
    }
    return work;
}
