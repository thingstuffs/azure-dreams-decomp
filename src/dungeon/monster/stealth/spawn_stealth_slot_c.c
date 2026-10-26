#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/stealth/spawn_variant_slot_c.h"
#include "modules/dungeon_ovl_7f217800.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_7f217800.h"

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select, then finish through the mode branch that either zeroes or arms the actor's 0xA6 state. */
/* Creates Stealth with frames at D_8015BD30; a random display variant changes sprite flags and unlinks the
 * node. */
void *spawn_variant_monster_slot_c(s16 flags, s16 tile_x, s16 tile_y, s16 spawn_height)
{
    s32 kind;
    s32 mode;
    void *object_base;
    SpriteFrameState *part1;
    ObjectPosition *part0;
    void *actor;
    ObjectNodeHeader *object;
    S_80158854_1 *result;

    result = 0;
    mode = 1;
    object = allocate_list_node(274, &scene_object_list_anchor.next);
    if (object != 0) {
        result = (u8 *)object + 0x20;
        object->update_callback = func_80158A8C;
        result->unk_13 = MONSTER_STEALTH;
        register_node(object, project_sprite_chain);
        part0 = *(void ** *)&object->position;
        part0->z.w.i = spawn_height;
        part1 = object->sprite;
        part1->tile_y = tile_y;
        actor = result;
        part1->frameTable = D_8015BD30;
        kind = flags & 3;
        part1->tile_x = tile_x;
        if (kind == 1) {
            result->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            result->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            result->unk_14 |= ACTOR_CLASS_ENABLED;
            result->unk_1C |= ACTOR_PLAYER_SIDE;
        } else if (((flags & ~3) << 16) == 0) {
            if (!(result->unk_14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    result->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    part1->frameTable = D_8015BD78;
                }
            }
            mode = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(object, part0, part1, flags);
        ((S_80158854_4 *)actor)->unk_9A = 0xFF;
        ((S_80158854_4 *)actor)->unk_9C = -1;
        ((S_80158854_4 *)actor)->unk_8C = func_80158F74;
        ((S_80158854_4 *)actor)->unk_A4 = -1;
        if (mode != 0) {
            ((S_80158854_4 *)actor)->unk_A6 = 0;
        } else {
            object_base = (u8 *)actor - 0x20;
            ((S_80158854_4 *)actor)->unk_A6 = 1;
            part1->tpage_abr = 0x60;
            part1->flags |= 0xC;
            part1->clut -= 0x80;
            unlink_node(object_base);
            retire_tracked_effect_by_id(object_base);
        }
        try_move_actor_to_valid_position(actor, part0, part1, result);
    }

    return result;
}
