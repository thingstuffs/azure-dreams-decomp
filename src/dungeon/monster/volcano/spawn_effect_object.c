#include "shared/actor_status_ids.h"
#include "dungeon/monster/volcano/spawn_effect_object.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/volcano/spawn_effect_object.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Volcano with default frames at D_80150510, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_effect_object(s32 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    u8 *work = 0;
    long part_b;
    long work_copy;
    ObjectNodeHeader *object;
    ObjectPosition *part_a;
    s16 flags_s16;
    s32 alloc_kind;
    ObjectNodeHeader **list_head;
    u32 flags0;
    u32 flags1;
    s32 random;

    alloc_kind = 0x112;
    list_head = &scene_object_list_anchor.next;
    object = allocate_list_node(alloc_kind, list_head);
    flags_s16 = spawn_flags;
    if (object != 0) {
        work = ((u8 *)object) + 0x20;
        *(u8 *)(work + 0x13) = 0x1C;
        register_node(object, project_sprite_chain);

        part_a = object->position;
        part_a->z.w.i = attr_c;
        part_b = (long)*(u8 * *)&object->sprite;
        ((SpriteFrameState *)part_b)->tile_x = attr_a;
        ((SpriteFrameState *)part_b)->tile_y = attr_b;
        work_copy = (long)work;

        if ((spawn_flags & 3) == 1) {
            *(ActorActionHandler *)(work + 0x8C) = func_8014CE5C;
            *(u32 *)(work + 0x14) |= 0x6000;
            *(u32 *)(work + 0x1C) |= 0x6000;
            ((SpriteFrameState *)part_b)->frameTable = volcano_frame_set;
        } else if ((spawn_flags & 3) >= 2) {
            *(ActorActionHandler *)(work + 0x8C) = func_8014CE5C;
            flags0 = *(u32 *)(work + 0x14) | 0x2000;
            flags1 = *(u32 *)(work + 0x1C) | 0x2000;
            *(u32 *)(work + 0x14) = flags0;
            *(u32 *)(work + 0x1C) = flags1;
            ((SpriteFrameState *)part_b)->frameTable = volcano_frame_set;
        } else {
            spawn_flags = (s16)(spawn_flags & -4);
            if (spawn_flags == 0) {
                if ((*(u32 *)(work + 0x14) & 0x200) == 0) {
                    if ((generate_random_value() & 1) != 0) {
                        random = generate_random_value();
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP, (random & 0x3F) | 0x20);
                        ((SpriteFrameState *)part_b)->frameTable = D_80150538;
                    }
                }
                *(ActorActionHandler *)((u8 *)work_copy + 0x8C) = func_8014CE5C;
                ((SpriteFrameState *)part_b)->frameTable = volcano_frame_set;
            } else {
                *(ActorActionHandler *)(work + 0x8C) = func_8014CE5C;
                ((SpriteFrameState *)part_b)->frameTable = volcano_frame_set;
            }
        }

        object->update_callback = func_8014CA58;
        initialize_actor_sprite_and_animation(object, part_a, (u8 *)part_b, (s16)flags_s16);

        *(u8 *)((u8 *)work_copy + 0x9A) = 0xFF;
        *(s8 *)((u8 *)work_copy + 0x9C) = -1;
        try_move_actor_to_valid_position((u8 *)work_copy, part_a, (u8 *)part_b, work);
    }
    return work;
}
