#include "shared/actor_status_flags.h"
#include "dungeon/monster/kraken.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/node/registration.h"
#include "shared/monster_ids.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/position_views.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"
#include "engine/graphics.h"
#include "engine/node/allocation.h"
#include "engine/texture.h"
#include "dungeon/data.h"
#include "dungeon/monster/kraken_frames.h"

   /* obj in update_actor_action_controller */


   /* part_a in update_actor_action_controller */

typedef struct S_8017086C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x90];
    u32 unk_98;
} S_8017086C_6;   /* child in update_actor_action_controller */


extern s32 generate_random_value(void); /* Retail RNG reads no argument registers. */
extern void initialize_actor_sprite_and_animation();

extern u8 kraken_action_resume_address[];

/* Creates a Kraken actor with a linked display object and initializes its status and tile placement. */
void *update_actor_action_controller(s16 mode, s16 value_24, s16 value_25, s16 value_0A)
{
    s32 kind;
    ActorRecord *work;
    s8 saved_value_24;
    s8 saved_value_25;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    ActorRecord *actor;
    s32 left;
    s32 right;
    s16 saved_mode;
    void *current;
    ActorRecord *base;
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
    saved_value_25 = value_25;
    saved_mode = mode;
    obj = allocate_list_node(0x112, (saved_value_24 = value_24, &scene_object_list_anchor.next));
    if (obj != 0) {
        work = NODE_BODY(obj);
        obj->update_callback = update_actor_callbacks_movement_and_terrain;
        work->species = MONSTER_KRAKEN;
        register_node(obj, project_sprite_chain);
        actor = work;

        part_a = obj->position;
        part_a->z.w.i = value_0A;
        part_b = obj->sprite;
        kind = mode & 3;
        part_b->frameTable = kraken_frame_set_1;
        part_b->tile_x = saved_value_24;
        part_b->tile_y = saved_value_25;

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
            if (((mode & ~3) << 16) == 0) {
                if (!(work->flags14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        work->flags1C |= ACTOR_ASLEEP;
                        right = generate_random_value();
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP, (right & 0x3F) | 0x20);
                        part_b->frameTable = kraken_frame_set_2;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, saved_mode);

        actor->action_id = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C.address = kraken_action_resume_address;
        work->flags1C |= 0x00040000;
        actor->unk_90.parts.high = -16;
        flags = actor->action_state_flags;
        actor->unk_A8 = 0;
        actor->unk_9E = 1;
        actor->action_state_flags = flags | 0x4000;

        current = actor;
        count = 0;
        do {
            child_obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
            ((ActorRecord *)current)->unk_A4.address = child_obj;
            if (child_obj != 0) {
                S_8017086C_6 *child;

                child = (S_8017086C_6 *)NODE_BODY(child_obj);

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

                    elem->clut = part_b->clut - 128;
                    elem->color.word = ((u32)(0x00C0C0C0));
                    ((ObjectNodeHeader *)base->unk_A4.address)->update_callback = child_object_update_address;

                    select_sprite_entry(elem, 39, 0);
                    elem_offset += 48;
                    i++;
                    child->unk_06 = 0;
                    texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(part_b, child_texture_entries, 0);
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
