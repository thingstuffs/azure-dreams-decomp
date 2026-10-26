#include "common.h"
#include "dungeon/effect/mesh.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"

#ifndef NULL
#define NULL 0
#endif

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in spawn_angled_random_velocity_effect */

typedef struct EffectBase {
    u8 pad0[8];
    s32 field8;
    u8 padC[8];
    u16 field14;
    u8 pad16[0x1C];
    s16 field32;
    s16 field34;
} EffectBase;

typedef struct Effect {
    u8 pad0[0x20];
    EffectBase base;
} Effect;

extern void *allocate_list_node();
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

extern s32 D_800D707C[];
extern s16 actor_direction_step_pairs[];

typedef struct S_80D659DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80D659DC_0;

typedef struct S_80D659DC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80D659DC_1;

typedef struct S_80D659DC_2 {
    s16 unk_00;
    s16 unk_02;
} S_80D659DC_2;

typedef struct S_80D659DC_3 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80D659DC_3;

typedef struct S_80D659DC_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80D659DC_4;

typedef struct S_80D659DC_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80D659DC_5;

/* Spawns an effect offset from the source with randomized velocity biased along the given angle. */
void spawn_angled_random_velocity_effect(EntityRec *source, u32 angle, s32 effect_param) {
    ObjectPosition *position_x;
    ObjectPosition *position_y;
    ObjectPosition *velocity_x;
    ObjectPosition *velocity_y;
    S_80D659DC_2 *direction;
    EffectBase *base;
    Effect *effect;

    effect = allocate_list_node(0x211, source);
    if (effect != NULL) {
        base = &effect->base;
        ((ObjectNodeHeader *)effect)->update_callback = &D_800D707C;
        ((ObjectNodeHeader *)effect)->position->x.w.i = (u16)
        ((MovingPosition *)((*(void * *)&source->z)))->x;
        ((ObjectNodeHeader *)effect)->position->y.w.i = (u16)
        ((MovingPosition *)((*(void * *)&source->z)))->y;
        ((ObjectNodeHeader *)effect)->position->z.w.i = (s16)
        (((MovingPosition *)((*(void * *)&source->z)))->z - 0x58);
        direction = (void *)actor_direction_step_pairs + ((angle >> 7) & 0x1C);
        position_x = ((ObjectNodeHeader *)effect)->position;
        position_x->x.w.i = (u16)
        ((u16)position_x->x.w.i +
            (direction->unk_00 * 0x12));
        position_y = ((ObjectNodeHeader *)effect)->position;
        position_y->y.w.i = (u16)
        ((u16)position_y->y.w.i +
            (direction->unk_02 * 0x12));
        ((ObjectNodeHeader *)effect)->position->velocity_x = (s32)
        (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((ObjectNodeHeader *)effect)->position->velocity_y = (s32)
        (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((ObjectNodeHeader *)effect)->position->velocity_z = (s32)
        (((rand() & 0x7FFF) - 0x4000) * 0x10);
        velocity_x = ((ObjectNodeHeader *)effect)->position;
        velocity_x->velocity_x = (s32)
        (velocity_x->velocity_x +
            (direction->unk_00 * 0x1C0000));
        {
            s32 direction_y = direction->unk_02;

            velocity_y = ((ObjectNodeHeader *)effect)->position;
            velocity_y->velocity_y = (s32)
            (velocity_y->velocity_y +
                (direction_y * 0x1C0000));
            base->field14 = angle;
            base->field32 = 0xC;
            base->field34 = 0xC;
            register_node(effect, queue_projected_mesh_points_and_texture_packets);
            ((S_80D659DC_0 *)effect)->unk_20 = effect_param;
            base->field8 = effect_param;
        }
    }
}
