#include "shared/object_node.h"
#include "modules/dungeon_ovl_7f1ed800.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_7f1ed800.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Viper with default frames at D_8015CA7C, applies spawn flags, and attempts valid tile placement. */
void *func_80158894(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    ObjectNodeHeader *obj;
    S_80158894_2 *part_a;
    SpriteFrameState *part_b;
    S_80158894_1 *work;
    S_80158894_4 *actor;
    s32 left;
    s32 right;
    s8 held_a;
    s16 held_c;
    s8 held_b;

    work = 0;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->unk_10 = func_80158A68;
        work->unk_13 = MONSTER_VIPER;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->unk_0A = held_c;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = work;
        part_b->frameTable = D_8015CA7C;
        part_b->unk_24 = held_a;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind >= 2) {
            left = work->unk_14 | 0x2000;
            right = work->unk_1C | 0x2000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8015CAD4;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_80158E94;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
