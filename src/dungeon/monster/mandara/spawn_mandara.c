/* cfail-repair: tf7-phase1-cache-v3 */
#include "dungeon/monster/mandara/spawn_api_slot_c.h"
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
extern void MoveImage(s16 *, s32, s32);
extern s32 generate_random_value(void);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern u8 D_80158B40[];
extern u8 D_80158F6C[];
extern u8 D_8015D258[];
extern u8 D_8015D298[];

void *spawn_mandara_in_slot_c(s32 input_value, s16 part_b_value, s16 part_b_value2, s16 part_a_value)

;

/* Creates a Mandara actor, initializes status and tile placement, and prepares sprite image rectangles. */
void *spawn_mandara_in_slot_c(s32 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height)
{
    void *work;
    ObjectNodeHeader *obj;
    s32 call_id;
    ObjectNodeHeader **list_head;
    SpriteFrameState *part_b;
    void *part_a;
    s16 saved_spawn_flags;
    s32 kind;
    s32 left;
    s32 right;
    s32 index;
    s32 count;
    u16 actor_value;
    s32 double_index;
    s16 values[4];
    u8 *entry;
    s16 saved_tile_x;
    s16 saved_height;
    ObjectPosition *pin_part_a;
    ActorRecord *pin_actor;

    work = 0;
    call_id = 0x112;
    saved_tile_x = tile_x;
    saved_height = spawn_height;
    list_head = &scene_object_list_anchor.next;
    obj = allocate_list_node(call_id, list_head);
    saved_spawn_flags = (s16)spawn_flags;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_80158B40;
        ((ActorRecord *)work)->species = MONSTER_MANDARA;
        register_node(obj, project_sprite_chain);

        pin_part_a = obj->position;
        pin_part_a->z.w.i = saved_height;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = tile_y;
        pin_actor = work;
        part_b->frameTable = D_8015D258;
        part_b->tile_x = saved_tile_x;
        if (kind == 1) {
            left = ((ActorRecord *)work)->flags14 | 0x6000;
            right = ((ActorRecord *)work)->flags1C | 0x6000;
            ((ActorRecord *)work)->flags14 = left;
            ((ActorRecord *)work)->flags1C = right;
        } else if (kind >= 2) {
            left = ((ActorRecord *)work)->flags14 | 0x2000;
            right = ((ActorRecord *)work)->flags1C | 0x2000;
            ((ActorRecord *)work)->flags14 = left;
            ((ActorRecord *)work)->flags1C = right;
        } else {
            if (((spawn_flags = (s16)(spawn_flags & ~3)) << 16) == 0) {
                if (!(((ActorRecord *)work)->flags14 & 0x200)) {
                    if (generate_random_value() & 1) {
                        ((ActorRecord *)work)->flags1C |= 0x200;
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) |
                                      0x20);
                        part_b->frameTable = D_8015D298;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, pin_part_a, part_b, saved_spawn_flags);
        index = 0;
        actor_value = part_b->clut;
        pin_actor->action_id.u = 0xFF;
        pin_actor->unk_9C = -1;
        pin_actor->unk_8C.address = D_80158F6C;
        pin_actor->unk_AC.halves.high.u = actor_value;

        entry = *(u8 * *)&part_b->source;
        do {
            double_index = index << 1;
            if (*entry & 0x20) {
                entry += 12;
                index += 1;
            } else {
                break;
            }
        } while (1);
        count = ((CountView *)(*(u8 * *)&part_b->source + (double_index + index) * 4))->count >> 6;
        values[0] = 0;
        values[1] = count;
        values[2] = 0x100;
        values[3] = 1;
        MoveImage(values, 0, count - 1);

        values[2] = 0x10;
        values[0] = 0x30;
        values[1] -= 1;
        do {
            MoveImage(values, values[0] - 0x30, values[1]);
            values[0] += 0x40;
        } while (values[0] < 0x100);

        try_move_actor_to_valid_position(pin_actor, pin_part_a, part_b, work);
    }
    return work;
}
