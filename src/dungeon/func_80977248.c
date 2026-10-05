#include "common.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void func_80170A44(void *, void *, void *, void *);

extern s32 D_801714D4[];
extern u8 D_801740E0[];
extern u8 D_80174110[];
extern u8 D_80174118[];

typedef struct S_80172A48_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_80172A48_0;   /* arg0 in func_80172A48 */

typedef struct S_80172A48_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A48_1_pre;   /* the 0x14 bytes before active in func_80172A48, addressed as active[-1] */

typedef struct S_80172A48_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A48_2;   /* linked in func_80172A48 */

typedef struct S_80172A48_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172A48_3;   /* arg2 in func_80172A48 */

/* Advance item use through effect activation, actor animation, and cleanup. */
void func_80172A48(void *action, EntityRec *motion, void *actor, void *item)
{
    register u8 *effect_slot;
    s16 is_special;
    s32 effect_special;
    s16 next_state;
    u8 state;
    void *target;
    void *linked;

    is_special = 0;
    state = ((S_80172A48_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)item + 0x1C)) & 0x2000) {
            u32 kind_index;

            kind_index = ((*(u16 *)((u8 *)item + 0x46)) & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                is_special = 1;
            case 2:
                goto kind_3;
            case 5:
                is_special = 1;
            case 1:
                goto kind_2;
            case 4:
                is_special = 1;
            case 0:
                goto kind_1;
            default:
                goto kind_default;
            }
        }

        {
            s32 item_kind;

            item_kind = (*(u16 *)((u8 *)item + 0x46)) & 0x3FFF;
            switch (item_kind) {
            case 1:
                effect_slot = (u8 *)item + 8;
                break;
            case 2:
                effect_slot = (u8 *)item + 0xB;
                break;
            case 3:
                effect_slot = (u8 *)item + 0xE;
                break;
            default:
                effect_slot = 0;
                break;
            }
            goto selection_ready;
        }

kind_3:
        effect_slot = (u8 *)item + 0xE;
        goto selection_ready;
kind_2:
        effect_slot = (u8 *)item + 0xB;
        goto selection_ready;
normal_kind_1:
kind_1:
        effect_slot = (u8 *)item + 8;
        goto selection_ready;
kind_default:
        effect_slot = 0;

selection_ready:
        if (*effect_slot != 0) {
            ((S_80172A48_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 special_target;

                special_target = is_special;
                if (special_target != 0) {
                    target = D_800814A8;
                    (*(void * *)((u8 *)item + 0x60)) = target;
                    linked = ((S_80172A48_1_pre *)target)[-1].unk_00;
                    (*(u8 *)((u8 *)item + 0x72)) = ((S_80172A48_2 *)linked)->unk_24;
                    (*(u8 *)((u8 *)item + 0x73)) = ((S_80172A48_2 *)linked)->unk_25;
                } else {
                    u8 effect_id;

                    effect_id = *effect_slot;
                    if (D_8006DE24[effect_id].kind == 2) {
                        target = (*(void * *)((u8 *)item + 0x60));
                        if (target != 0) {
                            linked = ((S_80172A48_1_pre *)target)[-1].unk_00;
                            (*(u8 *)((u8 *)item + 0x72)) = ((S_80172A48_2 *)linked)->unk_24;
                            (*(u8 *)((u8 *)item + 0x73)) = ((S_80172A48_2 *)linked)->unk_25;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        target = func_800A05A4(
                            item, ((S_80172A48_3 *)actor)->unk_24, ((S_80172A48_3 *)actor)->unk_25,
                            (*(s16 *)((u8 *)item + 0x2A)), 0x10);
                        (*(void * *)((u8 *)item + 0x60)) = target;
                        do {
                            dx = (*(s8 *)((u8 *)item + 0x72));
                        } while (0);
                        dy = (*(s8 *)((u8 *)item + 0x73));
                        dx = abs(dx);
                        dy = abs(dy);
                        (*(u8 *)((u8 *)item + 0x72)) = dx;
                        (*(u8 *)((u8 *)item + 0x73)) = dy;
                    }
                }
            }

            effect_special = is_special;
            if (func_800A94A0(item, effect_slot, effect_special, (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_80172A48_0 *)action)->unk_96.u = 0;
            ((S_80172A48_0 *)action)->unk_9B++;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            if ((u32)(*effect_slot - 0x2E) >= 3) {
                return;
            }
            if (effect_special == 1) {
                return;
            }
            ((S_80172A48_0 *)action)->unk_9B = 0x10;
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((S_80172A48_3 *)actor)->unk_24, ((S_80172A48_3 *)actor)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(item);
        (*(u8 *)((u8 *)item + 0x6D))--;
        ((S_80172A48_0 *)action)->unk_8C = D_801714D4;
        (*(u8 *)((u8 *)item + 0x73)) = 0;
        (*(u8 *)((u8 *)item + 0x72)) = 0;
        (*(u16 *)((u8 *)item + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270()) {
            ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
            return;
        }
        ((S_80172A48_3 *)actor)->unk_14 &= 0xF7FF;
        ((S_80172A48_0 *)action)->unk_9B++;

    case 2:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 8) {
            if (!(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
                return;
            }
        }
    }
        next_state = ((S_80172A48_0 *)action)->unk_9B;
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        next_state++;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;

    case 3:
        if (((S_80172A48_0 *)action)->unk_A2 != 0) {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 15) {
                if (!(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
                    return;
                }
            }
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        func_800A56E0(0x703);
        (*(void * *)((u8 *)actor + 0x2C)) = D_80174110;
        func_80047784(actor,
            *((u8 *)((((gameWork.view.viewAngle + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7) + (u32)D_80174110)),
            0);
        return;

    case 4:
        func_80170A44(action, motion, actor, item);
        {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 3) {
                if (!(((S_80172A48_3 *)actor)->unk_14 & 0xE000)) {
                    return;
                }
            }
        }
        ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
        ((S_80172A48_0 *)action)->unk_9B++;
        return;

    case 5:
        ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
        {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 10) {
                if (!(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
                    return;
                }
            }
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        ((S_80172A48_3 *)actor)->unk_14 &= 0xF7FF;
        return;

    case 6:
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_98 |= 0x80;
        ((S_80172A48_0 *)action)->unk_9B++;
        return;

    case 7:
        if (!(((S_80172A48_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((S_80172A48_3 *)actor)->unk_24, ((S_80172A48_3 *)actor)->unk_25);
        ((S_80172A48_0 *)action)->unk_9B++;
        if (((S_80172A48_3 *)actor)->unk_2C == D_801740E0) {
            return;
        }
        {
            u8 *model = D_801740E0;

            (*(void * *)((u8 *)actor + 0x2C)) = model;
            func_80047784(actor,
                model[((gameWork.view.viewAngle + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }
        ((S_80172A48_0 *)action)->unk_9E = 0;
        ((S_80172A48_0 *)action)->unk_92 = -0x20;
        return;

    case 8:
    {

        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A--;
        ((S_80172A48_0 *)action)->unk_8C = D_801714D4;
        func_800A4ACC(item);
        (*(u8 *)((u8 *)item + 0x73)) = 0;
        (*(u8 *)((u8 *)item + 0x72)) = 0;
        (*(u8 *)((u8 *)item + 0x6D))--;
        (*(u16 *)((u8 *)item + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }
        return;

    case 16:
        if (func_8003F270()) {
            ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
            return;
        }
        ((S_80172A48_3 *)actor)->unk_14 &= 0xF7FF;
        ((S_80172A48_0 *)action)->unk_9B++;

    case 17:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 8 &&
            !(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
            return;
        }
    }
        next_state = ((S_80172A48_0 *)action)->unk_9B;
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        next_state++;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;

    case 18:
        if (((S_80172A48_0 *)action)->unk_A2 != 0) {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 15 &&
                !(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
                return;
            }
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        func_800A56E0(0x703);
                    /* MATCH: the preceding eight-byte model table uses a distinct address expression in this arm. */
        (*(void * *)((u8 *)actor + 0x2C)) = (u8 *)((u32)D_80174118 - 8);
        func_80047784(actor,
            *((u8 *)((((gameWork.view.viewAngle + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7)
                + (u32)(u8 *)((u32)D_80174118 - 8))),
            0);
        return;

    case 19:
        func_80170A44(action, motion, actor, item);
        {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 2 &&
                !(((S_80172A48_3 *)actor)->unk_14 & 0xE000)) {
                return;
            }
        }
        ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
        next_state = ((S_80172A48_0 *)action)->unk_9B;
        next_state++;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;

    case 20:
        ((S_80172A48_3 *)actor)->unk_14 |= 0x800;
        if (((S_80172A48_0 *)action)->unk_96.s < 5) {
            func_80170A44(action, motion, actor, item);
        }
        {
            s16 timer;

            timer = ((S_80172A48_0 *)action)->unk_96.u;
            ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
            if ((s16)timer < 10 &&
                !(((S_80172A48_3 *)actor)->unk_14 & 0x8000)) {
                return;
            }
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        ((S_80172A48_3 *)actor)->unk_14 &= 0xF7FF;
        ((S_80172A48_0 *)action)->unk_98 |= 0x80;
        return;

    case 21:
        if (!(((S_80172A48_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B++;
        {

            (*(void * *)((u8 *)actor + 0x2C)) = D_80174118;
            func_80047784(actor,
                *((u8 *)((((gameWork.view.viewAngle + (*(s16 *)((u8 *)item + 0x2A)) + 0x100) >> 9) & 7)
                    + (u32)D_80174118)),
                0);
        }
        return;

    case 22:
    {
        s16 timer;

        timer = ((S_80172A48_0 *)action)->unk_96.u;
        ((S_80172A48_0 *)action)->unk_96.u = timer + 1;
        if ((s16)timer < 5) {
            return;
        }
    }
        next_state = ((S_80172A48_0 *)action)->unk_9B;
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        next_state++;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;

    case 23:
        next_state = 6;
        ((S_80172A48_0 *)action)->unk_96.u = 0;
        ((S_80172A48_0 *)action)->unk_9B = next_state;
        return;
    default:
        return;
    }

}
