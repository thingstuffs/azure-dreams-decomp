#include "common.h"
#include "records/Rec_D_800E3D7C.h"

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
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
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

typedef struct S_80172FC0_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172FC0_8;   /* global in func_80172FC0 */



extern s32 func_8003DE58(s32, void *, u16 *, s32);
extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800BB044(void *);
extern void *func_80175858(void *, void *, void *);

extern void *D_80170850[];
extern void *D_80170870[];
extern u8 D_8006DE24[];
extern s32 D_800814A0[3];
extern void *D_800814A8[3];
extern s16 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern s32 D_8008346C;
extern u8 D_80171094[];
extern u8 D_80176460[];
extern u8 D_80176490[];
extern u8 D_80176498[];

/* Updates an actor effect through shrinking, fading, and restoring its sprite. */
void func_80172FC0(void *anim, void *transform_arg, void *sprite, void *actor)
{
    static void *const dispatch_labels[] = {
        &&start_effect, &&wait_effect, &&shrink_sprite, &&grow_sprite, &&wait_fade, &&fade_sprite, &&restore_sprite,
        &&select_first, &&select_second, &&select_third, &&no_effect, &&special_first, &&special_second, &&special_third
    };
    u16 offset[3];
    register void *transform ASM_REG("$20") = transform_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 is_special;
    u8 *effect_id;
    u8 state;
    u16 timer;
    void *main_actor;
    register void *child ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(transform);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    state = ((S_80172FC0_0 *)anim)->unk_9B;
    is_special = 0;
    if (state >= 7U) {
        return;
    }
    (void)dispatch_labels;
    goto *D_80170850[state];

start_effect:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x2000) {
        s32 effect_kind;
        u32 effect_index;

        effect_kind = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x3FFF;
        effect_index = effect_kind - 1;
        if (effect_index >= 7U) {
            goto no_effect;
        }
        goto *D_80170870[effect_index];
special_third:
        is_special = 1;
        goto select_third;
special_second:
        is_special = 1;
        goto select_second;
special_first:
        is_special = 1;
        goto select_first;
    }

    {
        s32 effect_kind;

        effect_kind = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x3FFF;
        if (effect_kind == 2) {
            goto select_second;
        }
        if (effect_kind < 3) {
            effect_id = 0;
            if (effect_kind == 1) {
                goto select_first;
            }
            goto apply_effect;
        }
        effect_id = 0;
        if (effect_kind != 3) {
            goto apply_effect;
        }
    }
select_third:
    effect_id = (u8 *)actor + 0xE;
    goto apply_effect;
select_second:
    effect_id = (u8 *)actor + 0xB;
    goto apply_effect;
select_first:
    effect_id = (u8 *)actor + 8;
    goto apply_effect;
no_effect:
    effect_id = 0;
apply_effect:
    if (*effect_id != 0) {
        void *effect;

        (*(volatile u16 *)((u8 *)anim + 0x98)) &= 0xFF7F;
        {
            s32 special_flag;

            do {
                special_flag = is_special;
            } while (0);
            ASM_KEEP(special_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            if (special_flag != 0) {
                effect = D_800814A8[0];
                ((Rec_D_800E3D7C *)actor)->unk_60.as_pv = effect;
                goto copy_effect;
            }
        }
        if (D_8006DE24[*effect_id * 0x14 + 0x12] == 2) {
            effect = ((Rec_D_800E3D7C *)actor)->unk_60.as_pv;
            if (effect != 0) {
                register void *owner ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
copy_effect:
                owner = ((S_80172FC0_2_pre *)effect)[-1].unk_00;
                ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = ((S_80172FC0_3 *)owner)->unk_24;
                ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = ((S_80172FC0_3 *)owner)->unk_25;
            }
        } else {
            s32 x;
            s32 y;

            (*(void *volatile *)((u8 *)actor + 0x60)) = func_800A05A4(
                actor,
                ((S_80172FC0_4 *)sprite)->unk_24,
                ((S_80172FC0_4 *)sprite)->unk_25,
                ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16,
                0x10);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            x = ((Rec_D_800E3D7C *)actor)->unk_72.as_s8;
            y = ((Rec_D_800E3D7C *)actor)->unk_73.as_s8;
            if (x < 0) {
                x = -x;
            }
            if (y < 0) {
                y = -y;
            }
            ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = x;
            ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = y;
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

    ((S_80172FC0_5 *)transform)->unk_14 = 0;
    ((S_80172FC0_5 *)transform)->unk_10 = 0;
    ((S_80172FC0_5 *)transform)->unk_0C = 0;
    func_800A2B04(transform, ((S_80172FC0_4 *)sprite)->unk_24, ((S_80172FC0_4 *)sprite)->unk_25);
    main_actor = D_800814A8[0];
    D_8008346C = 0;
    (*(u16 *)((u8 *)main_actor + 0xA6))--;
    func_800A4ACC(actor);
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
    ((S_80172FC0_0 *)anim)->unk_8C = D_80171094;
    ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
    return;

wait_effect:
    if (func_8003F270() != 0) {
        ((S_80172FC0_4 *)sprite)->unk_14 |= 0x800;
        return;
    }
    ((S_80172FC0_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172FC0_0 *)anim)->unk_AE.u = 8;
    ((S_80172FC0_0 *)anim)->unk_9B++;

shrink_sprite:
    timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
    ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
    if ((s16)timer > 0) {
        u16 scale;

        scale = ((S_80172FC0_4 *)sprite)->unk_1E - 0x100;
        ((S_80172FC0_4 *)sprite)->unk_1E = scale;
        ((S_80172FC0_4 *)sprite)->unk_1C = scale;
        return;
    }

    ((S_80172FC0_0 *)anim)->unk_A0 = func_80175858(anim, transform, sprite);
    do {
    } while (0);
    {
        s16 *camera_data;
#ifndef NON_MATCHING
        u8 *camera_page;
#endif
        s32 direction;
        u8 frame;
        void *model_root;
        void *model;
        void *model_table;
        void *selected_model;

#ifdef NON_MATCHING
        camera_data = D_80083160;
#else
        camera_page = (u8 *)0x80080000;
        ASM_KEEP(camera_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        camera_data = (s16 *)(camera_page + 0x3160);
#endif
        {
            s32 model_direction;
            s32 view_angle;
            s32 actor_angle;

            view_angle = camera_data[0x64];
            actor_angle = ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16;
            model_root = ((S_80172FC0_4 *)sprite)->unk_28;
            do {
                model_direction =
                    ((view_angle + actor_angle + 0x100) >> 9) & 7;
            } while (0);
            ASM_KEEP_NV(model_direction);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            model = *(void **)model_root;
            model_table = *(void **)model;
            selected_model =
                ((void **)model_table)[D_80176498[model_direction]];
        }
        {
            void *sprite_arg;
            s32 model_data;

            do {
                sprite_arg = sprite;
            } while (0);
            ASM_KEEP(sprite_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_80172FC0_4 *)sprite)->unk_00 = selected_model;
            model_data = ((S_80172FC0_6 *)selected_model)->unk_04;
            {
                u16 *offset_arg;

                do {
                    offset_arg = offset;
                } while (0);
                ASM_KEEP(offset_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ((S_80172FC0_4 *)sprite)->unk_08 = model_data;
                offset[2] = 0;
                offset[1] = 0;
                offset[0] = 0;
                if (func_8003DE58(
                        ((S_80172FC0_4 *)sprite)->unk_08, sprite_arg, offset_arg, 0) != 0) {
                    u16 height_offset;

                    ((S_80172FC0_5 *)transform)->unk_02 += offset[0];
                    ((S_80172FC0_5 *)transform)->unk_06 += offset[1];
                    height_offset = offset[2];
                    ((S_80172FC0_0 *)anim)->unk_B2 = height_offset;
                    ((S_80172FC0_0 *)anim)->unk_90.at02.v =
                        ((S_80172FC0_5 *)transform)->unk_0A - ((Rec_D_800E3D7C *)actor)->unk_88.as_u16 +
                        (s16)height_offset / 2;
                }
            }
        }
        ((S_80172FC0_0 *)anim)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= 0xBFFFFFFF;
        ((S_80172FC0_4 *)sprite)->unk_2C = D_80176490;
        direction = ((camera_data[0x64] + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
        frame = D_80176490[direction];
        func_80047784(sprite, frame, 0);
        ((S_80172FC0_4 *)sprite)->unk_1E = 0x800;
        ((S_80172FC0_4 *)sprite)->unk_1C = 0x800;
    }
    goto advance_state;

grow_sprite:
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

wait_fade:
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

fade_sprite:
    timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
    ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
    if ((s16)timer <= 0) {
        return;
    }
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 |= 0x10000000;
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

advance_state:
        next_state = ((S_80172FC0_0 *)anim)->unk_9B;
        timer = 8;
        ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
        next_state++;
        ((S_80172FC0_0 *)anim)->unk_9B = next_state;
        return;
    }

restore_sprite:
    timer = ((S_80172FC0_0 *)anim)->unk_AE.u - 1;
    ((S_80172FC0_0 *)anim)->unk_AE.u = timer;
    if ((s16)timer > 0 && !(((S_80172FC0_4 *)sprite)->unk_14 & 0x8000)) {
        return;
    }
    child = ((S_80172FC0_0 *)anim)->unk_A0;
    if (child != 0) {
        void *active_child;
        s32 pool_flags;
        register u16 child_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u8 *pool_page;

        pool_page = (u8 *)0x80080000;
        ASM_KEEP(pool_page);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        active_child = child;
        ASM_KEEP(active_child);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        pool_flags = *(volatile s32 *)(pool_page + 0x14A0);
        ASM_KEEP(pool_flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_80172FC0_0 *)anim)->unk_AC = 0;
        ((S_80172FC0_0 *)anim)->unk_A4 = 0;
        ((S_80172FC0_0 *)anim)->unk_90.at00.v = 0;
        child_flags = ((S_80172FC0_7 *)active_child)->unk_1E;
        ASM_KEEP(child_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        pool_flags |= 0x8000;
        child_flags |= 0x8000;
        *(volatile s32 *)(pool_page + 0x14A0) = pool_flags;
        ((S_80172FC0_7 *)active_child)->unk_1E = child_flags;
        ((S_80172FC0_0 *)anim)->unk_A0 = 0;
    }
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= 0xEFFFFFFF;
    ((S_80172FC0_4 *)sprite)->unk_12 = ((S_80172FC0_0 *)anim)->unk_B8;
    ((S_80172FC0_4 *)sprite)->unk_0C.at00.v = ((S_80172FC0_0 *)anim)->unk_B4;
    ((S_80172FC0_4 *)sprite)->unk_10 = ((S_80172FC0_0 *)anim)->unk_BA;
    ((S_80172FC0_5 *)transform)->unk_14 = 0;
    ((S_80172FC0_5 *)transform)->unk_10 = 0;
    ((S_80172FC0_5 *)transform)->unk_0C = 0;
    func_800A2B04(transform, ((S_80172FC0_4 *)sprite)->unk_24, ((S_80172FC0_4 *)sprite)->unk_25);
    ((S_80172FC0_0 *)anim)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 |= 0x40000000;
    if (((S_80172FC0_4 *)sprite)->unk_2C != D_80176460) {
        s32 direction;

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80176460;
        direction = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
        func_80047784(sprite, D_80176460[direction], 0);
    }
    {
        u8 *dungeon_state;

        dungeon_state = D_80083460;
        if (((S_80172FC0_8 *)dungeon_state)->unk_0C != 0) {
            return;
        }
        ((S_80172FC0_8 *)dungeon_state)->unk_0A--;
    }
    ((S_80172FC0_0 *)anim)->unk_8C = D_80171094;
    ((S_80172FC0_4 *)sprite)->unk_1E = 0x1000;
    ((S_80172FC0_4 *)sprite)->unk_1C = 0x1000;
    func_800A4ACC(actor);
    ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
    func_800A56E0(0xB4);
}
