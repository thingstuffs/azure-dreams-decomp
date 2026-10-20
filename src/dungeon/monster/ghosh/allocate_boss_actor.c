#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 D_8016F2E0[];
extern M2C_UNK D_8016F78C;
extern u8 D_80174A2C[];
extern void *D_80174CD8;

typedef struct S_8016F160_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016F160_0;   /* obj in allocate_boss_actor */

typedef struct S_8016F160_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016F160_1;   /* work in allocate_boss_actor */

typedef struct S_8016F160_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016F160_2;   /* part_a in allocate_boss_actor */

typedef struct S_8016F160_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    s8 unk_9C;
    u8 pad_9D[0x13];
    s16 unk_B0;
} S_8016F160_4;   /* tail_ptr in allocate_boss_actor */

/* Allocate an actor, initialize its parts and mode flags, and return its work area. */
void *allocate_boss_actor(s16 mode, s16 config_24, s16 config_25, s16 config_0a)
{
    s16 mode_kind;
    void *obj;
    S_8016F160_2 *part_a;
    SpriteFrameState *part_b;
    void *work;
    s16 saved_mode;
    s8 saved_config_24;
    s16 saved_config_0a;
    s8 saved_config_25;
    void *actor;
    void *actor_state;

    work = 0;
    saved_config_24 = config_24;
    saved_config_0a = config_0a;
    saved_config_25 = config_25;
    obj = allocate_list_node(0x112, ((s32 *)&D_80083498.next));
    saved_mode = mode;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        D_80174CD8 = obj;
        ((S_8016F160_0 *)obj)->unk_10 = D_8016F2E0;
        ((S_8016F160_1 *)work)->unk_13 = 0x32;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8016F160_0 *)obj)->unk_08;
        part_a->unk_0A = saved_config_0a;
        part_b = ((S_8016F160_0 *)obj)->unk_0C;
        mode_kind = mode & 3;
        part_b->frameTable = D_80174A2C;
        part_b->unk_25 = saved_config_25;
        actor = work;
        part_b->unk_24 = saved_config_24;

        if (mode_kind == 1) {
            ((S_8016F160_1 *)work)->unk_14 |= 0x6000;
            ((S_8016F160_1 *)work)->unk_1C |= 0x6000;
        } else if (mode_kind >= 2) {
            ((S_8016F160_1 *)work)->unk_14 |= 0x2000;
            ((S_8016F160_1 *)work)->unk_1C |= 0x2000;
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, saved_mode);
        actor_state = actor;
        ((S_8016F160_4 *)actor_state)->unk_9A = 0xFF;
        ((S_8016F160_4 *)actor_state)->unk_9C = -1;
        ((S_8016F160_4 *)actor_state)->unk_8C = &D_8016F78C;
        ((S_8016F160_4 *)actor_state)->unk_9B = 0;
        ((S_8016F160_4 *)actor_state)->unk_B0 = 0;
        part_b->flags |= 0x80;
        try_move_actor_to_valid_position(actor_state, part_a, part_b, work);
    }
    return work;
}
