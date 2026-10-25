#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "dungeon/monster/stealth/create_mode_configured_actor_object.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/stealth/create_mode_configured_actor_object.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Stealth with frames at D_8016DD30; a random display variant changes sprite flags and unlinks the
 * node. */
void *create_mode_configured_actor_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    s32 variant;
    void *obj_alt;
    SpriteFrameState *part_b;
    ObjectPosition *part_a;
    void *work_copy;
    ObjectNodeHeader *object;
    S_8016A854_1 *work;

    work = 0;
    variant = 1;
    object = allocate_list_node(274, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        work = (u8 *)object + 0x20;
        object->update_callback = func_8016AA8C;
        work->unk_13 = MONSTER_STEALTH;
        register_node(object, project_sprite_chain);
        part_a = *(void ** *)&object->position;
        part_a->z.w.i = attr_c;
        part_b = object->sprite;
        part_b->tile_y = attr_b;
        work_copy = work;
        part_b->frameTable = D_8016DD30;
        kind = spawn_flags & 3;
        part_b->tile_x = attr_a;
        if (kind == 1) {
            work->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            work->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            work->unk_14 |= ACTOR_CLASS_ENABLED;
            work->unk_1C |= ACTOR_PLAYER_SIDE;
        } else if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    work->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8016DD78;
                }
            }
            variant = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(object, part_a, part_b, spawn_flags);
        ((S_8016A854_4 *)work_copy)->unk_9A = 0xFF;
        ((S_8016A854_4 *)work_copy)->unk_9C = -1;
        ((S_8016A854_4 *)work_copy)->unk_8C = func_8016AF74;
        ((S_8016A854_4 *)work_copy)->unk_A4 = -1;
        if (variant != 0) {
            ((S_8016A854_4 *)work_copy)->unk_A6 = 0;
        } else {
            obj_alt = (u8 *)work_copy - 0x20;
            ((S_8016A854_4 *)work_copy)->unk_A6 = 1;
            part_b->tpage_abr = 0x60;
            part_b->flags |= 0xC;
            part_b->clut -= 0x80;
            unlink_node(obj_alt);
            retire_tracked_effect_by_id(obj_alt);
        }
        try_move_actor_to_valid_position(work_copy, part_a, part_b, work);
    }

    return work;
}
