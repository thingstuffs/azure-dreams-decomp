#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/position_views.h"

   /* object in create_overlay_effect_object */

typedef struct S_80171718_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80171718_1;   /* result in create_overlay_effect_object */

   /* part0 in create_overlay_effect_object */

typedef struct S_80171718_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80171718_3;   /* part1 in create_overlay_effect_object */

typedef struct S_80171718_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80171718_4;   /* result_copy in create_overlay_effect_object */


extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern u8 D_801718E0[];
extern s32 D_80171CE8;
extern u8 D_80174EB8[];
extern u8 D_80174F00[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *create_overlay_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    void *result;
    void *object;
    SignedHeightView *part0;
    S_80171718_3 *part1;
    S_80171718_4 *result_copy;

    result = 0;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != 0) {
        result = (u8 *)object;
        result += 0x20;
        ((ProjectileObject *)object)->unk_10 = D_801718E0;
        ((S_80171718_1 *)result)->unk_13 = 34;
        register_node(object, project_sprite_chain);

        {
            void *handler;

            part0 = ((ProjectileObject *)object)->unk_08;
            handler = D_80174EB8;
            part0->unk_0A = attr_c;
            part1 = ((ProjectileObject *)object)->unk_0C;
            kind = spawn_flags & 3;
            part1->unk_25 = attr_b;
            result_copy = result;
            part1->unk_2C = handler;
        }
        part1->unk_24 = attr_a;

        if (kind == 1) {
            flags0 = ((S_80171718_1 *)result)->unk_14;
            flags1 = ((S_80171718_1 *)result)->unk_1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            ((S_80171718_1 *)result)->unk_14 = flags0;
            ((S_80171718_1 *)result)->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((S_80171718_1 *)result)->unk_14;
            flags1 = ((S_80171718_1 *)result)->unk_1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            ((S_80171718_1 *)result)->unk_14 = flags0;
            ((S_80171718_1 *)result)->unk_1C = flags1;
        } else if (((spawn_flags & -4) << 16) == 0 &&
                   (((S_80171718_1 *)result)->unk_14 & 0x200) == 0 &&
                   (generate_random_value() & 1) != 0) {
            set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
            part1->unk_2C = D_80174F00;
        }

        initialize_actor_sprite_and_animation(object, part0, part1, spawn_flags);
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = &D_80171CE8;
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }

    return result;
}

/* MECHANISM: 2.7.2-cdk-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds the a1/a2
   temps into them, so sched1 schedules the parameter copies and the entry order is retail's. */
