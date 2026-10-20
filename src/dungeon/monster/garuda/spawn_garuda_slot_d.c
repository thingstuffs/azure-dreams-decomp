/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct ActionState ActionState;
typedef struct ActorSprite ActorSprite;
typedef struct CreatureState CreatureState;

typedef struct S_81017000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_81017000_0;   /* obj in spawn_garuda_slot_d */

typedef struct S_81017000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_81017000_1;   /* work in spawn_garuda_slot_d */

typedef struct S_81017000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_81017000_2;   /* part_a in spawn_garuda_slot_d */

typedef struct S_81017000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_81017000_4;   /* actor in spawn_garuda_slot_d */

void *allocate_list_node();
s32 register_node();
s16 set_or_clear_actor_status_slot();
s32 generate_random_value();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
void func_8015EA78(void *obj, void *input_motion, void *input_part);
void func_8015F058(ActionState *actor, void *context, ActorSprite *sprite_arg, CreatureState *creature);
extern M2C_UNK D_80162880;
extern M2C_UNK D_801628E0;

void *spawn_garuda_slot_d(s16, s16, s16, s16)

;

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *spawn_garuda_slot_d(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c) {
    s32 kind;
    s16 final_arg0;
    s32 left;
    S_81017000_1 *work = NULL;
    void *obj;
    S_81017000_2 *part_a;
    SpriteFrameState *part_b;
    S_81017000_4 *actor;
    s8 held_a;
    s16 held_c;
    s8 held_b;

    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = allocate_list_node(0x112, ((void *)&D_80083498.next));
    final_arg0 = spawn_flags;
    if (obj != NULL) {
        work = obj + 0x20;
        ((S_81017000_0 *)obj)->unk_10 = &func_8015EA78;
        work->unk_13 = 0x29;
        register_node(obj, project_sprite_chain);
        part_a = ((S_81017000_0 *)obj)->unk_08;
        part_a->unk_0A = held_c;
        part_b = ((S_81017000_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = work;
        part_b->frameTable = &D_80162880;
        part_b->unk_24 = held_a;
        if (kind == 1) {
            work->unk_14 |= 0x6000;
            work->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            work->unk_14 |= 0x2000;
            work->unk_1C |= 0x2000;
        } else {
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(work->unk_14 & 0x200)) {
                    left = generate_random_value();
                    if (left & 1) {
                        work->unk_1C |= 0x200;
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = &D_801628E0;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, final_arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_8015F058;
        work->unk_1C |= 0x40000;
        actor->unk_92 = -0x18;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
