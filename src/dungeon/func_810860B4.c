#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


typedef s32 M2C_UNK;

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800BB044(void *);
extern void func_80174BC8(void *, void *, void *);

extern M2C_UNK D_80170E94;
extern u8 D_80175F10[8];


typedef struct S_801738B4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801738B4_0;   /* arg0 in func_801738B4 */

typedef struct S_801738B4_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801738B4_1_pre;   /* the 0x14 bytes before copy_object in func_801738B4, addressed as copy_object[-1] */

typedef struct S_801738B4_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801738B4_2;   /* entity in func_801738B4 */


typedef struct S_801738B4_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801738B4_4;   /* global in func_801738B4 */

/* Advances an actor's item-use sequence and resets its state when the action ends. */
void func_801738B4(void *action_ctx, void *scene_object, void *entity, void *actor_arg)
{
    register void *actor ASM_REG("$17") = actor_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *item;
    s32 special_mode;
    s32 action_state;
    s32 item_selector;
    u16 remaining_ticks;
    s32 target_x;
    s32 target_y;
    void *active_object;
    void *copy_object;
    u8 *action_status;
    s32 use_shared_object;

    special_mode = 0;
    action_state = ((S_801738B4_0 *)action_ctx)->unk_9B;
    switch (action_state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
            item_selector = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
            switch (item_selector) {
            case 0:
                goto item_1;
            case 1:
                goto item_2;
            case 2:
                goto item_3;
            case 6:
                special_mode = 1;
                goto item_3;
            case 5:
                special_mode = 1;
                goto item_2;
            case 4:
                special_mode = 1;
                goto item_1;
            default:
                goto no_item;
            }
        } else {
            item_selector = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            if (item_selector == 2) {
                goto item_2;
            }
            if (item_selector < 3) {
                if (item_selector == 1) {
                    goto item_1;
                }
                goto no_item;
            }
            if (item_selector == 3) {
                goto item_3;
            }
            goto no_item;
        }

    item_3:
        item = (u8 *)actor + 0x0E;
        goto have_item;
    item_2:
        item = (u8 *)actor + 0x0B;
        goto have_item;
    item_1:
        item = (u8 *)actor;
        item += 8;
        goto have_item;
    no_item:
        item = 0;

    have_item:
        if (*item != 0) {

            ((S_801738B4_0 *)action_ctx)->unk_98 &= 0xFF7F;
            use_shared_object = (special_mode == 1);
            if (use_shared_object) {
                copy_object = D_800814A8;
                (*(void * *)((u8 *)actor + 0x60)) = copy_object;
                action_status = ((S_801738B4_1_pre *)copy_object)[-1].unk_00;
                (*(u8 *)((u8 *)actor + 0x72)) = action_status[0x24];
                (*(u8 *)((u8 *)actor + 0x73)) = action_status[0x25];
            } else if (D_8006DE24[*item].kind == 2) {
                copy_object = (*(void * *)((u8 *)actor + 0x60));
                if (copy_object != 0) {
                    action_status = ((S_801738B4_1_pre *)copy_object)[-1].unk_00;
                    (*(u8 *)((u8 *)actor + 0x72)) = action_status[0x24];
                    (*(u8 *)((u8 *)actor + 0x73)) = action_status[0x25];
                }
            } else {
                target_x = (s32)func_800A05A4(actor,
                    ((S_801738B4_2 *)entity)->unk_24,
                    ((S_801738B4_2 *)entity)->unk_25,
                    (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                (*(void * volatile *)((u8 *)actor + 0x60)) = (void *)target_x;
                target_x = (*(s8 *)((u8 *)actor + 0x72));
                target_y = (*(s8 *)((u8 *)actor + 0x73));
                if (target_x < 0) {
                    target_x = -target_x;
                }
                if (target_y < 0) {
                    target_y = -target_y;
                }
                (*(s8 *)((u8 *)actor + 0x72)) = target_x;
                (*(s8 *)((u8 *)actor + 0x73)) = target_y;
            }
            if (func_800A94A0(actor, item, special_mode, &((S_801738B4_0 *)action_ctx)->unk_98)) {
                func_800BB044(actor);
                ((S_801738B4_0 *)action_ctx)->unk_9B++;
            }
            break;
        } else {
            ((EntityRec *)scene_object)->flags14 = 0;
            ((EntityRec *)scene_object)->unk_10 = 0;
            ((EntityRec *)scene_object)->unk_0C = 0;
            func_800A2B04(scene_object, ((S_801738B4_2 *)entity)->unk_24, ((S_801738B4_2 *)entity)->unk_25);
            active_object = D_800814A8;
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)active_object + 0xA6))--;
            func_800A4ACC(actor);
            (*(u8 *)((u8 *)actor + 0x6D))--;
            ((S_801738B4_0 *)action_ctx)->unk_8C = &D_80170E94;
            (*(u8 *)((u8 *)actor + 0x73)) = 0;
            (*(u8 *)((u8 *)actor + 0x72)) = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            break;
        }

    case 1:
        if (func_8003F270()) {
            ((S_801738B4_2 *)entity)->unk_14 |= 0x0800;
            break;
        }
        ((S_801738B4_2 *)entity)->unk_14 &= 0xF7FF;
        ((S_801738B4_0 *)action_ctx)->unk_9B++;

    case 2:
        if ((((S_801738B4_2 *)entity)->unk_04 == 3 &&
             (((S_801738B4_2 *)entity)->unk_14 & 0x1000)) ||
            (((S_801738B4_2 *)entity)->unk_14 & 0xE000)) {
            func_80174BC8(action_ctx, scene_object, entity);
            ((S_801738B4_0 *)action_ctx)->unk_9B++;
        }

    case 3:
        if ((((S_801738B4_2 *)entity)->unk_04 == 4 &&
             (((S_801738B4_2 *)entity)->unk_14 & 0x1000)) ||
            (((S_801738B4_2 *)entity)->unk_14 & 0xE000)) {
            ((S_801738B4_2 *)entity)->unk_14 |= 0x0800;
            ((S_801738B4_0 *)action_ctx)->unk_96 = 1;
            ((S_801738B4_0 *)action_ctx)->unk_98 |= 0x0080;
        }

        remaining_ticks = ((S_801738B4_0 *)action_ctx)->unk_96 - 1;
        ((S_801738B4_0 *)action_ctx)->unk_96 = remaining_ticks;
        if ((s16)remaining_ticks <= 0) {
            ((S_801738B4_0 *)action_ctx)->unk_96 = 0;
            ((S_801738B4_2 *)entity)->unk_14 &= 0xF7FF;
        }
        if (!(((S_801738B4_2 *)entity)->unk_14 & 0xE000)) {
            break;
        }

        ((EntityRec *)scene_object)->flags14 = 0;
        ((EntityRec *)scene_object)->unk_10 = 0;
        ((EntityRec *)scene_object)->unk_0C = 0;
        func_800A2B04(scene_object, ((S_801738B4_2 *)entity)->unk_24, ((S_801738B4_2 *)entity)->unk_25);
        if (((S_801738B4_2 *)entity)->unk_2C != D_80175F10) {
            (*(u8 * *)((u8 *)entity + 0x2C)) = D_80175F10;
            func_80047784(entity,
                D_80175F10[((gameWork.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }

        action_status = (u8 *)&dungeonStatus.unk_00;
        if (((S_801738B4_4 *)action_status)->unk_0C != 0) {
            break;
        }
        ((S_801738B4_4 *)action_status)->unk_0A--;
        ((S_801738B4_0 *)action_ctx)->unk_8C = &D_80170E94;
        func_800A4ACC(actor);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);

    }

    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return;
}
