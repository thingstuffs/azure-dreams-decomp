#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_80172D74_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
    u16 unk_A8;
} S_80172D74_1;   /* arg0 in func_80172D74 */

typedef struct S_80172D74_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172D74_2_pre;   /* the 0x14 bytes before entity in func_80172D74, addressed as entity[-1] */

typedef struct S_80172D74_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172D74_3;   /* position in func_80172D74 */

typedef struct S_80172D74_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172D74_4;   /* arg2 in func_80172D74 */

typedef struct S_80172D74_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80172D74_5;   /* part20 in func_80172D74 */


typedef struct S_80172D74_7 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80172D74_7;   /* part28 in func_80172D74 */


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_800DAE44(void *, s32);

extern u8 D_80171400[];
extern u8 D_80175140[];
extern u8 D_80175148[];
extern u8 D_80175168[];
extern u8 D_80175170[];

/* Advances an item action through setup, animation, movement, and cleanup. */
void func_80172D74(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    void *owner;
    void *owner_flags;
    void *owner_sprite;
    u8 *item_slot;
    void *entity;
    void *position;
    s32 special_item;
    s32 step_x;
    s32 step_z;
    s32 next_state;
    u8 state_value;

    special_item = 0;
    {
        u32 direction_index = ((u16)actor->facing >> 8) & 0xE;

        owner = ((S_80172D74_1 *)action)->unk_A4;
        owner_flags = (u8 *)owner + 0x20;
        step_x = *(s16 *)(((s8 *)dirStepX) + direction_index);
        step_z = *(s16 *)(((s8 *)dirStepY) + direction_index);
        owner_sprite = (u8 *)owner + 0x28;
    }
    ((S_80172D74_1 *)action)->unk_96.s--;
    switch (((S_80172D74_1 *)action)->unk_9B) {
    case 0:
        if (actor->flags1C & 0x2000) {
            s32 kind_index = (actor->unk_46 & 0x3FFF) - 1;

            switch (kind_index) {
            case 0:
                goto kind1;
            case 1:
                goto kind2;
            case 2:
                goto kind3;
            case 6:
                special_item = 1;
                goto kind3;
            case 5:
                special_item = 1;
                goto kind2;
            case 4:
                special_item = 1;
                goto kind1;
            default:
                goto kind4;
            }
        }

        {
            s32 item_kind = actor->unk_46 & 0x3FFF;

            if (item_kind == 2) {
                goto kind2;
            }
            if (item_kind < 3) {
                if (item_kind == 1) {
                    goto kind1;
                }
                item_slot = 0;
                goto selected;
            }
            if (item_kind == 3) {
                goto kind3;
            }
            item_slot = 0;
            goto selected;
        }

kind3:
        item_slot = (u8 *)actor + 0xE;
        goto selected;
kind2:
        item_slot = (u8 *)actor + 0xB;
        goto selected;
kind1:
        item_slot = (u8 *)actor + 8;
        goto selected;
kind4:
        item_slot = 0;

selected:
        if (*item_slot != 0) {
            ((S_80172D74_1 *)action)->unk_98 &= 0xFF7F;
            {
                s16 special_test;

                special_test = special_item;
                if (special_test != 0) {
                    entity = D_800814A8;
                    actor->target = entity;
                    goto have_entity;
                }
            }
            {
                u8 *item_defs = D_8006DE24;
                u8 item_id = *item_slot;

                if (item_defs[item_id * 20 + 0x12] == 2) {
                    entity = actor->target;

                    if (entity != 0) {


have_entity:
                        position = ((S_80172D74_2_pre *)entity)[-1].unk_00;
                        actor->unk_72 = ((S_80172D74_3 *)position)->unk_24;
                        actor->unk_73 = ((S_80172D74_3 *)position)->unk_25;
                    }
                } else {


                    position = func_800A05A4(actor,
                        ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25,
                        actor->facing, 0x10);
                    actor->target = position;
                    actor->unk_72 = abs(actor->unk_72);
                    actor->unk_73 = abs(actor->unk_73);
                }
            }

            ((S_80172D74_5 *)owner_flags)->unk_04 &= 0x7FFF;
            (*(u8 * *)((u8 *)owner_sprite + 0x2C)) = D_80175168;
            func_80047784(owner_sprite,
                D_80175168[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            if (!func_800A94A0(actor, item_slot, special_item, (u8 *)action + 0x98)) {
                return;
            }
            ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
            func_800DAE44(motion, 3);
            func_800A56E0(0x703);
            state_value = ((S_80172D74_1 *)action)->unk_9B;
            ((S_80172D74_1 *)action)->unk_96.s = 6;
            ((S_80172D74_1 *)action)->unk_9B = state_value + 1;
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25);
        {
            void *entity = D_800814A8;

            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)entity + 0xA6))--;
        }
        func_800A4ACC(actor);
        (*(u8 *)&actor->unk_6D)--;
        ((S_80172D74_1 *)action)->unk_8C = D_80171400;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270()) {
            ((S_80172D74_4 *)sprite)->unk_14 |= 0x0800;
            return;
        }
        ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172D74_1 *)action)->unk_9B++;

    case 2:
        if (((S_80172D74_1 *)action)->unk_96.u > 0 &&
            !(((S_80172D74_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        ((S_80172D74_1 *)action)->unk_96.s = 7;
        ((S_80172D74_1 *)action)->unk_98 |= 0x80;
        if (((S_80172D74_4 *)sprite)->unk_14 & 0x8000) {
            next_state = 0x10;
            ((S_80172D74_1 *)action)->unk_9B = next_state;
            return;
        }
        ((S_80172D74_1 *)action)->unk_9B = ((S_80172D74_1 *)action)->unk_9B + 1;
        return;

    case 3:
        if (((S_80172D74_1 *)action)->unk_96.u < 4) {
            motion->unk_0C = -step_x << 18;
            motion->unk_10 = -step_z << 18;
        }
        if (((S_80172D74_1 *)action)->unk_96.u > 0) {
            return;
        }
        next_state = 4;
        ((S_80172D74_1 *)action)->unk_96.s = next_state;
        next_state = 0x10;
        ((S_80172D74_1 *)action)->unk_9B = next_state;
        return;

    case 16:
    {
        s32 target_x = ((S_80172D74_4 *)sprite)->unk_24 << 6;
        s32 current_x = motion->x.w.i - 0x20;

        motion->unk_0C = (target_x - current_x) << 14;
    }
        {
            s32 target_z = ((S_80172D74_4 *)sprite)->unk_25 << 6;
            s32 current_z = motion->y.w.i - 0x20;

            motion->unk_10 = (target_z - current_z) << 14;
        }
        if (!(((S_80172D74_7 *)owner_sprite)->unk_14 & 0x8000) &&
            ((S_80172D74_1 *)action)->unk_96.u > 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25);
        {
            u8 *animation = ((S_80172D74_4 *)sprite)->unk_2C;
            u8 *next_animation = D_80175140;

            if (animation != D_80175140) {
                u8 *alternate_animation = D_80175148;

                if (animation != alternate_animation && (((S_80172D74_4 *)sprite)->unk_14 & 0x6000)) {
                    ((S_80172D74_5 *)owner_flags)->unk_04 |= 0x8000;
                    ((S_80172D74_1 *)action)->unk_A8 = 0;
                    if (((S_80172D74_4 *)sprite)->unk_2C == D_80175170) {
                        next_animation = alternate_animation;
                    }
                    (*(u8 * *)((u8 *)sprite + 0x2C)) = next_animation;
                    func_80047784(sprite,
                        next_animation[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                        0);
                }
            }
        }
        {

            if (((s32)dungeonStatus.unk_0C) != 0) {
                return;
            }
            dungeonStatus.unk_0A--;
        }
        ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172D74_1 *)action)->unk_8C = D_80171400;
        func_800A4ACC(actor);
        if (actor->unk_6D > 0) {
            (*(u8 *)&actor->unk_6D)--;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
    }
}
