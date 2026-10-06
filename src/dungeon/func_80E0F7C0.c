#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
extern int abs(int);
#include "shared/entity.h"

typedef struct S_80172FC0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
    s32 unk_A4;
    u8 pad_A8[0x4];
    s16 unk_AC;
    union { u16 u; s16 s; } unk_AE;   /* accessed as both */
    u8 pad_B0[0x2];
    u16 unk_B2;
    s32 unk_B4;
    u16 unk_B8;
    u16 unk_BA;
} S_80172FC0_0;   /* arg0 in func_80172FC0 */

typedef struct S_80172FC0_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172FC0_2_pre;   /* the 0x14 bytes before effect in func_80172FC0, addressed as effect[-1] */

typedef struct S_80172FC0_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172FC0_3;   /* owner in func_80172FC0 */

typedef struct S_80172FC0_4 {
    void * unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    void * unk_28;
    void * unk_2C;
} S_80172FC0_4;   /* arg2 in func_80172FC0 */

typedef struct S_80172FC0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FC0_5;   /* arg1_s4 in func_80172FC0 */

typedef struct S_80172FC0_6 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172FC0_6;   /* selected_model in func_80172FC0 */

typedef struct S_80172FC0_7 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80172FC0_7;   /* active_child in func_80172FC0 */

extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void func_800BB044(void *);
extern void *func_80175858(void *, void *, void *);

extern s32 D_800814A0;
extern u8 D_80171094[];
extern u8 D_80176460[];
extern u8 D_80176490[];
extern u8 D_80176498[];

/* Updates an actor effect through shrinking, fading, and restoring its sprite. */
void func_80172FC0(void *anim, void *transform_arg, void *sprite, EntityRec *actor)
{
    u16 offset[3];
    s32 is_special;
    u8 *effect_id;
    u8 state;
    u16 timer;
    void *main_actor;
    void *child;

    state = ((S_80172FC0_0 *)anim)->unk_9B;
    is_special = 0;
    switch (state) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            s32 effect_kind;

            effect_kind = actor->unk_46 & 0x3FFF;
            switch (effect_kind) {
            case 7:
                is_special = 1;
            case 3:
                effect_id = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
            case 2:
                effect_id = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
            case 1:
                effect_id = (u8 *)actor + 8;
                break;
            default:
                effect_id = 0;
                break;
            }
        } else {
            s32 effect_kind;

            effect_kind = actor->unk_46 & 0x3FFF;
            switch (effect_kind) {
            case 3:
                effect_id = (u8 *)actor + 0xE;
                break;
            case 2:
                effect_id = (u8 *)actor + 0xB;
                break;
            case 1:
                effect_id = (u8 *)actor + 8;
                break;
            default:
                effect_id = 0;
                break;
            }
        }
        if (*effect_id != 0) {
            void *effect;

            ((S_80172FC0_0 *)anim)->unk_98 &= 0xFF7F;
            if ((s16)is_special != 0) {
                effect = D_800814A8;
                actor->target = effect;
                main_actor = ((S_80172FC0_2_pre *)effect)[-1].unk_00;
                actor->unk_72 = ((S_80172FC0_3 *)main_actor)->unk_24;
                actor->unk_73 = ((S_80172FC0_3 *)main_actor)->unk_25;
            } else if (D_8006DE24[*effect_id].kind == 2) {
                effect = actor->target;
                if (effect != 0) {
                    main_actor = ((S_80172FC0_2_pre *)effect)[-1].unk_00;
                    actor->unk_72 = ((S_80172FC0_3 *)main_actor)->unk_24;
                    actor->unk_73 = ((S_80172FC0_3 *)main_actor)->unk_25;
                }
            } else {
                actor->target = func_800A05A4(
                    actor,
                    ((S_80172FC0_4 *)sprite)->unk_24,
                    ((S_80172FC0_4 *)sprite)->unk_25,
                    actor->facing,
                    0x10);
                actor->unk_72 =
                    abs(actor->unk_72);
                actor->unk_73 =
                    abs(actor->unk_73);
            }
            if (func_800A94A0(actor, effect_id, is_special, (u8 *)anim + 0x98) == 0) {
                return;
            }
            func_800BB044(actor);
            {
                u8 next_state;

                next_state = ((S_80172FC0_0 *)anim)->unk_9B;
                next_state++;
                ((S_80172FC0_0 *)anim)->unk_9B = next_state;
                return;
            }
        }

        ((S_80172FC0_5 *)transform_arg)->unk_14 = 0;
        ((S_80172FC0_5 *)transform_arg)->unk_10 = 0;
        ((S_80172FC0_5 *)transform_arg)->unk_0C = 0;
        func_800A2B04(transform_arg, ((S_80172FC0_4 *)sprite)->unk_24, ((S_80172FC0_4 *)sprite)->unk_25);
        main_actor = D_800814A8;
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)main_actor + 0xA6))--;
        func_800A4ACC(actor);
        actor->unk_6D--;
        ((S_80172FC0_0 *)anim)->unk_8C = D_80171094;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_80172FC0_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_80172FC0_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172FC0_0 *)anim)->unk_AE.u = 8;
        ((S_80172FC0_0 *)anim)->unk_9B++;

    case 2:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer > 0) {
            u16 scale;

            scale = ((S_80172FC0_4 *)sprite)->unk_1E - 0x100;
            ((S_80172FC0_4 *)sprite)->unk_1E = scale;
            ((S_80172FC0_4 *)sprite)->unk_1C = scale;
            return;
        }

        ((S_80172FC0_0 *)anim)->unk_A0 = func_80175858(anim, transform_arg, sprite);
        {
            s32 direction;
            u8 frame;
            void *model_root;
            void *model;
            void *model_table;
            void *selected_model;

            {
                s32 model_direction;
                s32 view_angle;
                s32 actor_angle;

                view_angle = gameWork.view.viewAngle;
                actor_angle = actor->facing;
                model_root = ((S_80172FC0_4 *)sprite)->unk_28;
                model_direction =
                    ((view_angle + actor_angle + 0x100) >> 9) & 7;
                model = *(void **)model_root;
                model_table = *(void **)model;
                selected_model =
                    ((void **)model_table)[D_80176498[model_direction]];
            }
            {
                s32 model_data;

                ((S_80172FC0_4 *)sprite)->unk_00 = selected_model;
                model_data = ((S_80172FC0_6 *)selected_model)->unk_04;
                {

                    ((S_80172FC0_4 *)sprite)->unk_08 = model_data;
                    offset[2] = 0;
                    offset[1] = 0;
                    offset[0] = 0;
                    if (func_8003DE58(
                            ((S_80172FC0_4 *)sprite)->unk_08, sprite, offset, 0) != 0) {
                        u16 height_offset;

                        ((S_80172FC0_5 *)transform_arg)->unk_02 += offset[0];
                        ((S_80172FC0_5 *)transform_arg)->unk_06 += offset[1];
                        height_offset = offset[2];
                        ((S_80172FC0_0 *)anim)->unk_B2 = height_offset;
                        ((S_80172FC0_0 *)anim)->unk_90.at02.v =
                            ((S_80172FC0_5 *)transform_arg)->unk_0A - ((u16)actor->unk_88) +
                            (s16)height_offset / 2;
                    }
                }
            }
            ((S_80172FC0_0 *)anim)->unk_98 |= 8;
            actor->flags1C &= 0xBFFFFFFF;
            ((S_80172FC0_4 *)sprite)->unk_2C = D_80176490;
            direction = ((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7;
            frame = D_80176490[direction];
            func_80047784(sprite, frame, 0);
            ((S_80172FC0_4 *)sprite)->unk_1E = 0x800;
            ((S_80172FC0_4 *)sprite)->unk_1C = 0x800;
        }
        {
            u8 next_state;

            next_state = ((S_80172FC0_0 *)anim)->unk_9B;
            timer = 8;
            ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
            next_state++;
            ((S_80172FC0_0 *)anim)->unk_9B = next_state;
            return;
        }

    case 3:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer >= 0) {
            u16 scale;

            scale = ((S_80172FC0_4 *)sprite)->unk_1E + 0x100;
            ((S_80172FC0_4 *)sprite)->unk_1E = scale;
            ((S_80172FC0_4 *)sprite)->unk_1C = scale;
            ((S_80172FC0_0 *)anim)->unk_90.at02.v += (s16)((S_80172FC0_0 *)anim)->unk_B2 >> 4;
            return;
        }
        ((S_80172FC0_0 *)anim)->unk_AE.u = 4;
        ((S_80172FC0_0 *)anim)->unk_98 |= 0x80;
        ((S_80172FC0_0 *)anim)->unk_9B++;
        return;

    case 4:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer >= 0) {
            return;
        }
        timer = 9;
        ((S_80172FC0_0 *)anim)->unk_B4 = ((S_80172FC0_4 *)sprite)->unk_0C.at00.v;
        ((S_80172FC0_0 *)anim)->unk_BA = ((S_80172FC0_4 *)sprite)->unk_10;
        ((S_80172FC0_0 *)anim)->unk_B8 = ((S_80172FC0_4 *)sprite)->unk_12;
        ((S_80172FC0_4 *)sprite)->unk_12 -= 0x80;
        {
            u8 next_state;

            next_state = ((S_80172FC0_0 *)anim)->unk_9B;
            ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
            next_state++;
            ((S_80172FC0_0 *)anim)->unk_9B = next_state;
            return;
        }

    case 5:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer <= 0) {
            return;
        }
        actor->flags1C |= 0x10000000;
        ((S_80172FC0_4 *)sprite)->unk_14 |= 0xC;
        ((S_80172FC0_4 *)sprite)->unk_10 |= 0x20;
        ((S_80172FC0_4 *)sprite)->unk_0C.at00u.v -= ((S_80172FC0_4 *)sprite)->unk_0C.at00u.v / (s16)((S_80172FC0_0 *)anim)->unk_AE.u;
        ((S_80172FC0_4 *)sprite)->unk_0C.at01.v -= ((S_80172FC0_4 *)sprite)->unk_0C.at01.v / (s16)((S_80172FC0_0 *)anim)->unk_AE.u;
        ((S_80172FC0_4 *)sprite)->unk_0C.at02.v -= ((S_80172FC0_4 *)sprite)->unk_0C.at02.v / (s16)((S_80172FC0_0 *)anim)->unk_AE.u;
        if (((S_80172FC0_0 *)anim)->unk_AE.s != 1) {
            return;
        }
        {
            u8 next_state;

            next_state = ((S_80172FC0_0 *)anim)->unk_9B;
            timer = 8;
            ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
            next_state++;
            ((S_80172FC0_0 *)anim)->unk_9B = next_state;
            return;
        }

    case 6:
        timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        if ((s16)timer > 0 && !(((S_80172FC0_4 *)sprite)->unk_14 & 0x8000)) {
            return;
        }
        child = ((S_80172FC0_0 *)anim)->unk_A0;
        if (child != 0) {
            void *active_child;
            s32 pool_flags;
            s32 new_pool_flags;
            u32 child_flags;

            pool_flags = D_800814A0;
            ((S_80172FC0_0 *)anim)->unk_AC = 0;
            ((S_80172FC0_0 *)anim)->unk_A4 = 0;
            ((S_80172FC0_0 *)anim)->unk_90.at00.v = 0;
            active_child = ((S_80172FC0_0 *)anim)->unk_A0;
            child_flags = ~((S_80172FC0_7 *)active_child)->unk_1E;
            child_flags &= 0x7FFF;
            child_flags = ~child_flags;
            new_pool_flags = pool_flags | 0x8000;
            D_800814A0 = new_pool_flags;
            ((S_80172FC0_7 *)active_child)->unk_1E = child_flags;
            ((S_80172FC0_0 *)anim)->unk_A0 = 0;
        }
        actor->flags1C &= 0xEFFFFFFF;
        ((S_80172FC0_4 *)sprite)->unk_12 = ((S_80172FC0_0 *)anim)->unk_B8;
        ((S_80172FC0_4 *)sprite)->unk_0C.at00.v = ((S_80172FC0_0 *)anim)->unk_B4;
        ((S_80172FC0_4 *)sprite)->unk_10 = ((S_80172FC0_0 *)anim)->unk_BA;
        ((S_80172FC0_5 *)transform_arg)->unk_14 = 0;
        ((S_80172FC0_5 *)transform_arg)->unk_10 = 0;
        ((S_80172FC0_5 *)transform_arg)->unk_0C = 0;
        func_800A2B04(transform_arg, ((S_80172FC0_4 *)sprite)->unk_24, ((S_80172FC0_4 *)sprite)->unk_25);
        ((S_80172FC0_0 *)anim)->unk_98 &= 0xFFF7;
        actor->flags1C |= 0x40000000;
        if (((S_80172FC0_4 *)sprite)->unk_2C != D_80176460) {
            s32 direction;

            (*(void * *)((u8 *)sprite + 0x2C)) = D_80176460;
            direction = ((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7;
            func_80047784(sprite, D_80176460[direction], 0);
        }
        {

            if (((s32)dungeonStatus.unk_0C) != 0) {
                return;
            }
            dungeonStatus.unk_0A--;
        }
        ((S_80172FC0_0 *)anim)->unk_8C = D_80171094;
        ((S_80172FC0_4 *)sprite)->unk_1E = 0x1000;
        ((S_80172FC0_4 *)sprite)->unk_1C = 0x1000;
        func_800A4ACC(actor);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_6D--;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
    default:
        return;
    }
}
