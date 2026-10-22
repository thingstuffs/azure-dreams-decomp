#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#include "shared/entity.h"

typedef struct S_80170AF4_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170AF4_1;   /* work in spawn_picket */

typedef struct S_80170AF4_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170AF4_2;   /* part_a in spawn_picket */

typedef struct S_80170AF4_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170AF4_4;   /* actor in spawn_picket */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_80170CC8[];
extern void update_dungeon_actor_behavior_facing_animation_state(void *actor, void *context, void *sprite, ActorRecord *entity);
extern u8 D_80174F00[];
extern u8 D_80174F48[];

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Picket with default frames at D_80174F00, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_picket(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    S_80170AF4_2 *part_a;
    SpriteFrameState *part_b;
    S_80170AF4_1 *work;
    S_80170AF4_4 *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    void *call_a1;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->unk_10 = D_80170CC8;
        work->unk_13 = MONSTER_PICKET;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->unk_0A = saved_spawn;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->frameTable = D_80174F00;
        part_b->unk_24 = saved_kind_id;

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
            call_a1 = obj;
            if (((flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = generate_random_value();
                call_a1 = obj;
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_80174F48;
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &update_dungeon_actor_behavior_facing_animation_state;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

/* MECHANISM: Preserve the seed's exact 0x38 frame, s0-s7 holds, CFG, and true-base name.
   The sole residue was part_b's saved_kind_id byte field at 0x20 versus retail offset 0x24.
   part_b->unk_24 closes the substitution at emitted word 32. */
