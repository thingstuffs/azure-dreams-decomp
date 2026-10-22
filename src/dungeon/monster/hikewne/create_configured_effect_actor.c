#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80170BB0_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x7E];
    s16 unk_9E;
} S_80170BB0_1;   /* actor in create_configured_effect_actor */

typedef struct S_80170BB0_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170BB0_2;   /* part_a in create_configured_effect_actor */

typedef struct S_80170BB0_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170BB0_4;   /* actor2 in create_configured_effect_actor */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 D_80170DA8[16];
extern u8 D_801714D4[16];
extern u8 D_801740E0[16];
extern u8 D_80174158[16];

/* Creates a Hikewne actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_configured_effect_actor(s16 mask, s16 value_at_24, s16 value_at_25, s32 value_at_0A)
{
    s32 kind;
    s32 flags14;
    s32 flags1c;
    ObjectNodeHeader *object;
    S_80170BB0_2 *part_a;
    SpriteFrameState *part_b;
    void *handler;
    S_80170BB0_1 *actor;
    S_80170BB0_4 *actor2;

    actor = 0;
    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        actor = object;
        actor = (S_80170BB0_1 *)((u8 *)actor + 0x20);
        object->unk_10 = D_80170DA8;
        actor->unk_13 = MONSTER_HIKEWNE;
        register_node(object, project_sprite_chain);

        part_a = object->position;
        handler = D_801740E0;
        part_a->unk_0A = value_at_0A;
        part_b = object->sprite;
        kind = mask & 3;
        part_b->unk_25 = value_at_25;
        actor2 = actor;
        part_b->frameTable = handler;
        part_b->unk_24 = value_at_24;
        actor->unk_9E = 0;

        if (kind == 1) {
            flags14 = actor->unk_14 | 0x6000;
            flags1c = actor->unk_1C | 0x6000;
            actor->unk_14 = flags14;
            actor->unk_1C = flags1c;
        } else if (kind >= 2) {
            flags14 = actor->unk_14 | 0x2000;
            flags1c = actor->unk_1C | 0x2000;
            actor->unk_14 = flags14;
            actor->unk_1C = flags1c;
        } else if (((mask & ~3) << 16) == 0 && !(actor->unk_14 & 0x200) && (generate_random_value() & 1)) {
            set_or_clear_actor_status_slot(actor, 1, (generate_random_value() & 0x3F) | 0x20);
            part_b->frameTable = D_80174158;
        }

        initialize_actor_sprite_and_animation(object, part_a, part_b, mask);
        actor2->unk_9A = 0xFF;
        actor2->unk_9C = -1;
        actor2->unk_8C = D_801714D4;
        actor->unk_1C |= 0x40000;
        actor2->unk_92 = -0x20;
        part_b->tpage_abr = 0x20;
        part_b->flags |= 0xC;
        try_move_actor_to_valid_position(actor2, part_a, part_b, actor);
    }
    return actor;
}
/* MECHANISM: 2.8.0-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds the a1/a2
   temps into them, so sched1 schedules the parameter copies and the entry order is retail's. */
