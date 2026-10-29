#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "dungeon/monster/kraken/create_actor_child_display_c.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/kraken/create_actor_child_display_c.h"
#include "dungeon/effect/sprite.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Kraken with frames at D_8016218C and a gray child display using frame 39 and an adjusted
 * palette. */
void *create_actor_child_display_c(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    void *work;
    s8 held_a;
    s8 held_b;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    S_8015E86C_4 *actor;
    s32 left;
    s32 right;
    s16 held_flags;
    void *current;
    S_8015E86C_8 *base;
    void *child_obj;
    SpriteFrameState *elem;
    s32 count;
    register s32 i;
    u32 elem_offset;
    s32 child_arg;
    u16 flags;
    u16 child_flags;
    u16 elem_flags;

    work = 0;
    held_b = attr_b;
    held_flags = spawn_flags;
    obj = allocate_list_node(0x112, (held_a = attr_a, &scene_object_list_anchor.next));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = func_8015EB64;
        ((S_8015E86C_1 *)work)->unk_13 = MONSTER_KRAKEN;
        register_node(obj, project_sprite_chain);
        actor = work;

        part_a = obj->position;
        part_a->z.w.i = attr_c;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->frameTable = D_8016218C;
        part_b->tile_x = held_a;
        part_b->tile_y = held_b;

        if (kind == 1) {
            left = ((S_8015E86C_1 *)work)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = ((S_8015E86C_1 *)work)->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((S_8015E86C_1 *)work)->unk_14 = left;
            ((S_8015E86C_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_8015E86C_1 *)work)->unk_14 | ACTOR_CLASS_ENABLED;
            right = ((S_8015E86C_1 *)work)->unk_1C | ACTOR_PLAYER_SIDE;
            ((S_8015E86C_1 *)work)->unk_14 = left;
            ((S_8015E86C_1 *)work)->unk_1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((S_8015E86C_1 *)work)->unk_14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        ((S_8015E86C_1 *)work)->unk_1C |= ACTOR_ASLEEP;
                        right = generate_random_value();
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP, (right & 0x3F) | 0x20);
                        part_b->frameTable = D_801621CC;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, held_flags);

        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = func_8015F1A4;
        ((S_8015E86C_1 *)work)->unk_1C |= 0x00040000;
        actor->unk_92 = -16;
        flags = actor->unk_98;
        actor->unk_A8 = 0;
        actor->unk_9E = 1;
        actor->unk_98 = flags | 0x4000;

        current = actor;
        count = 0;
        do {
            child_obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
            ((S_8015E86C_5 *)current)->unk_A4 = child_obj;
            if (child_obj != 0) {
                S_8015E86C_6 *child;

                child = (S_8015E86C_6 *)((u8 *)child_obj + 0x20);

                child->unk_02 = 1;
                i = 0;
                base = current;
                elem_offset = 8;
                while (i < child->unk_02) {
                    elem = (u8 *)child + elem_offset;
                    child_flags = child->unk_04;
                    child->unk_04 = child_flags | 0x8000;
                    child_arg = part_b->animation_resource;
                    elem_flags = elem->flags;
                    elem->tpage_abr = 96;
                    elem->animation_resource = child_arg;
                    elem->flags = elem_flags | 0xC;

                    elem->clut = *(s16 *)&part_b->clut - 128;
                    elem->color.word = ((u32)(0x00C0C0C0));
                    ((ObjectNodeHeader *)base->unk_A4)->update_callback = process_effect_block_entries;

                    select_sprite_entry(elem, 39, 0);
                    elem_offset += 48;
                    i++;
                    child->unk_06 = 0;
                    texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(part_b, draw_sprite_effect_quads, 0);
                    child->unk_98 = (u8 *)obj + 30;
                }
            }
            current = (u8 *)current + 4;
            count++;
        } while (count < actor->unk_9E);
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
