#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
typedef struct { u8 pad[6]; u16 count; } CountView;
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(void);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern void MoveImage(s16 *, s32, s32);

extern u8 D_8016AB40[];
extern u8 D_8016AF6C[];
extern u8 D_8016F258[];
extern u8 D_8016F298[];

void *create_mandara_actor_with_parts(s32 spawn_flags, s16 pos_x, s16 pos_y, s16 part_a_value)

;

/* Creates a dungeon actor and initializes its parts, flags, and image regions. */
/* Creates Mandara with frames at D_8016F258, copies its palette row and four strips, and attempts tile
 * placement. */
void *create_mandara_actor_with_parts(s32 spawn_flags, s16 pos_x, s16 pos_y, s16 part_a_value)
{
    void *work;
    ObjectNodeHeader *obj;
    s32 object_type;
    ObjectNodeHeader **list_head;
    SpriteFrameState *part_b;
    void *part_a;
    s16 saved_flags;
    s32 kind;
    s32 primary_flags;
    s32 secondary_flags;
    u32 entry_index;
    s32 entry_count;
    u16 actor_value;
    s32 twice_index;
    s16 rect[4];
    u8 *entry;
    s16 saved_part_value;
    ObjectPosition *pin_part_a;
    ActorRecord *pin_actor;

    work = 0;
    object_type = 0x112;
    saved_part_value = part_a_value;
    list_head = &scene_object_list_anchor.next;
    obj = allocate_list_node(object_type, list_head);
    saved_flags = (s16)spawn_flags;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8016AB40;
        ((ActorRecord *)work)->species = MONSTER_MANDARA;
        register_node(obj, project_sprite_chain);

        pin_part_a = obj->position;
        pin_part_a->z.w.i = saved_part_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = pos_y;
        pin_actor = work;
        part_b->frameTable = D_8016F258;
        part_b->tile_x = pos_x;

        if (kind == 1) {
            primary_flags = ((ActorRecord *)work)->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            secondary_flags = ((ActorRecord *)work)->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((ActorRecord *)work)->flags14 = primary_flags;
            ((ActorRecord *)work)->flags1C = secondary_flags;
        } else if (kind >= 2) {
            primary_flags = ((ActorRecord *)work)->flags14 | ACTOR_CLASS_ENABLED;
            secondary_flags = ((ActorRecord *)work)->flags1C | ACTOR_PLAYER_SIDE;
            ((ActorRecord *)work)->flags14 = primary_flags;
            ((ActorRecord *)work)->flags1C = secondary_flags;
        } else {
            {
                s32 non_kind_mask;
                non_kind_mask = -4;
                if (((spawn_flags = (s16)(spawn_flags & non_kind_mask)) << 16) == 0) {
                    if (!(((ActorRecord *)work)->flags14 & ACTOR_RESIST_SLEEP)) {
                        if (generate_random_value() & 1) {
                            ((ActorRecord *)work)->flags1C |= ACTOR_ASLEEP;
                            set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                          (generate_random_value() & 0x3F) |
                                          0x20);
                            part_b->frameTable = D_8016F298;
                        }
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, pin_part_a, part_b, saved_flags);

        entry_index = 0;
        actor_value = part_b->clut;
        pin_actor->action_id.u = 0xFF;
        pin_actor->unk_9C = -1;
        pin_actor->unk_8C.address = D_8016AF6C;
        pin_actor->unk_AC.halves.high.u = actor_value;

        entry = *(u8 * *)&part_b->source;
        while (1) {
            twice_index = entry_index << 1;
            if (!(*entry & 0x20)) {
                break;
            }
            entry += 12;
            entry_index += 1;
        }

        entry_count = ((CountView *)(*(u8 * *)&part_b->source + (twice_index + entry_index) * 4))->count >> 6;
        rect[0] = 0;
        rect[1] = entry_count;
        rect[2] = 0x100;
        rect[3] = 1;
        MoveImage(rect, 0, entry_count - 1);

        rect[2] = 0x10;
        rect[0] = 0x30;
        rect[1] -= 1;
        do {
            {
                MoveImage(rect, rect[0] - 0x30, rect[1]);
                rect[0] += 0x40;
            }
        } while (rect[0] < 0x100);

        try_move_actor_to_valid_position(pin_actor, pin_part_a, part_b, work);
    }
    return work;
}

#if 0
#endif
