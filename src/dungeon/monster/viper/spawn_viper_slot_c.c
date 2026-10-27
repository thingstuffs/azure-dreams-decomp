#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/viper/spawn_factory_slot_c.h"
#include "modules/dungeon_ovl_7f1ed800.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_7f1ed800.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Viper with default frames at D_8015CA7C, applies spawn flags, and attempts valid tile placement. */
void *spawn_mode_configured_monster_slot_c(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height)
{
    s32 kind;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *work;
    ActorRecord *actor;
    s32 left;
    s32 right;
    s8 saved_tile_x;
    s16 saved_height;
    s8 saved_tile_y;

    work = 0;
    saved_tile_x = tile_x;
    saved_height = spawn_height;
    saved_tile_y = tile_y;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (obj != 0) {
        work = (ActorRecord *)(obj + 1);
        obj->update_callback = func_80158A68;
        work->species = MONSTER_VIPER;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->z.w.i = saved_height;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_tile_y;
        actor = work;
        part_b->frameTable = D_8015CA7C;
        part_b->tile_x = saved_tile_x;

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
            if (((spawn_flags & ~3) << 16) == 0 && !(work->flags14 & ACTOR_RESIST_SLEEP)) {
                left = generate_random_value();
                if (left & 1) {
                    work->flags1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = viper_frame_set_7;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->action_id.u = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = &func_80158E94;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
