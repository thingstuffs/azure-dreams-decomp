#include "shared/entity.h"
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
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"

typedef struct ActionState ActionState;
typedef struct ActorSprite ActorSprite;
typedef struct CreatureState CreatureState;

typedef struct S_81029000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_81029000_1;   /* work in spawn_garuda_slot_a */


typedef struct S_81029000_4 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_81029000_4;   /* actor in spawn_garuda_slot_a */

s16 set_or_clear_actor_status_slot();
s32 generate_random_value(void);
void func_8014CA78(void *obj, void *input_motion, void *input_part);
void func_8014D058(ActionState *actor, void *context, ActorSprite *sprite_arg, CreatureState *creature);
extern M2C_UNK D_80150880;
extern M2C_UNK D_801508E0;

void *spawn_garuda_slot_a(s16, s16, s16, s16)

;

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
/* Creates Garuda with default frames at D_80150880, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_garuda_slot_a(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c) {
    s32 kind;
    s16 final_arg0;
    s32 left;
    S_81029000_1 *work = NULL;
    ObjectNodeHeader *obj;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    S_81029000_4 *actor;
    s8 held_a;
    s16 held_c;
    s8 held_b;

    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = allocate_list_node(0x112, &scene_object_list_anchor.next);
    final_arg0 = spawn_flags;
    if (obj != NULL) {
        work = ((void *)obj) + 0x20;
        obj->update_callback = &func_8014CA78;
        work->unk_13 = MONSTER_GARUDA;
        register_node(obj, project_sprite_chain);
        part_a = obj->position;
        part_a->z.w.i = held_c;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = held_b;
        actor = work;
        part_b->frameTable = &D_80150880;
        part_b->tile_x = held_a;
        if (kind == 1) {
            work->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            work->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            work->unk_14 |= ACTOR_CLASS_ENABLED;
            work->unk_1C |= ACTOR_PLAYER_SIDE;
        } else {
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                    left = generate_random_value();
                    if (left & 1) {
                        work->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = &D_801508E0;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, final_arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_8014D058;
        work->unk_1C |= 0x40000;
        actor->unk_92 = -0x18;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
