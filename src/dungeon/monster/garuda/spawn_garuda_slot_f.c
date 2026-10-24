#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_8100B000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8100B000_1;   /* work in spawn_garuda_slot_f */

typedef struct S_8100B000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8100B000_2;   /* part_a in spawn_garuda_slot_f */

typedef struct S_8100B000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8100B000_4;   /* actor in spawn_garuda_slot_f */

void *allocate_list_node();
s32 register_node();
s16 set_or_clear_actor_status_slot();
s32 generate_random_value();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
extern M2C_UNK D_8016AA78;
extern M2C_UNK garuda_slot_f_action_callback;
extern M2C_UNK D_8016E880;
extern M2C_UNK D_8016E8E0;

void *spawn_garuda_slot_f(s16, s16, s16, s16)

;

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Garuda with default frames at D_8016E880, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_garuda_slot_f(s16 flags, s16 kind_id, s16 variant, s16 spawn_value) {
    s32 kind;
    s16 final_arg0;
    s32 left;
    S_8100B000_1 *work = NULL;
    ObjectNodeHeader *obj;
    S_8100B000_2 *part_a;
    SpriteFrameState *part_b;
    S_8100B000_4 *actor;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;

    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((void *)&scene_object_list_anchor.next));
    final_arg0 = flags;
    if (obj != NULL) {
        work = ((void *)obj) + 0x20;
        obj->update_callback = &D_8016AA78;
        work->unk_13 = MONSTER_GARUDA;
        register_node(obj, project_sprite_chain);
        part_a = obj->position;
        part_a->unk_0A = saved_spawn;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_variant;
        actor = work;
        part_b->frameTable = &D_8016E880;
        part_b->tile_x = saved_kind_id;
        if (kind == 1) {
            work->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            work->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            work->unk_14 |= ACTOR_CLASS_ENABLED;
            work->unk_1C |= ACTOR_PLAYER_SIDE;
        } else {
            if (((flags & ~3) << 16) == 0) {
                if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        work->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = &D_8016E8E0;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, final_arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &garuda_slot_f_action_callback;
        work->unk_1C |= 0x40000;
        actor->unk_92 = -0x18;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
