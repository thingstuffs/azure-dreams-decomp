#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8016C190_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016C190_0;   /* arg0 in func_8016C190 */

typedef struct S_8016C190_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_8016C190_1;   /* arg3 in func_8016C190 */

typedef struct S_8016C190_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016C190_2_pre;   /* the 0x14 bytes before v0 in func_8016C190, addressed as v0[-1] */

typedef struct S_8016C190_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016C190_3;   /* arg2 in func_8016C190 */


typedef struct S_8016C190_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8016C190_5;   /* control in func_8016C190 */



extern s32 func_8003F270();
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_8016A36C[];
extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_801739B8[];
extern void *D_80164960[];

/* Advances the selected actor action through targeting, animation, and cleanup. */
void func_8016C190(void *action, void *transform, void *sprite, void *actor)
{
    static void *const selection_labels[] = {
        &&select_1, &&select_2, &&select_3, &&select_none,
        &&mode_select_1, &&mode_select_2, &&mode_select_3
    };
    u8 action_state;
    u8 *action_slot;
    register u8 *target_sprite ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *direction_table;
    u8 *action_control;
    s32 target_mode;
    s32 flagged_action;
    s32 action_kind;
    register s32 action_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 target_y;
    void *current_table;

    action_state = ((S_8016C190_0 *)action)->unk_9B;
    target_mode = 0;
    (void)selection_labels;

    switch (action_state) {
    case 0:
        if (((S_8016C190_1 *)actor)->unk_1C & 0x2000) {
            flagged_action = ((S_8016C190_1 *)actor)->unk_46 & 0x3FFF;
            if ((u32)(flagged_action - 1) < 7) {
                goto *D_80164960[(u32)(flagged_action - 1)];
            }
            goto select_none;

mode_select_3:
            target_mode = 1;
            goto select_3;
mode_select_2:
            target_mode = 1;
            goto select_2;
mode_select_1:
            target_mode = 1;
            goto select_1;
        } else {
            action_kind = ((S_8016C190_1 *)actor)->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 1:
                goto select_1;
            case 2:
                goto select_2;
            case 3:
                goto select_3;
            default:
                goto select_none;
            }
        }

select_3:
        action_slot = (u8 *)actor + 0xE;
        goto selection_done;
select_2:
        action_slot = (u8 *)actor + 0xB;
        goto selection_done;
select_1:
        action_slot = (u8 *)actor + 8;
        goto selection_done;
select_none:
        action_slot = 0;
selection_done:
        if (*action_slot != 0) {
            action_value = ((S_8016C190_0 *)action)->unk_98 & 0xFF7F;
            ((S_8016C190_0 *)action)->unk_98 = action_value;
            action_value = target_mode;
            if (action_value != 0) {
                action_value = (s32)D_800814A8;
                ((S_8016C190_1 *)actor)->unk_60 = (void *)action_value;
                goto set_from_object;
            } else {
                u8 *action_defs = D_8006DE24;
                action_value = (s32)(action_defs + *action_slot * 20);
                if (((u8 *)action_value)[0x12] == 2) {
                    action_value = (s32)((S_8016C190_1 *)actor)->unk_60;
                    if (action_value != 0) {
set_from_object:
                        target_sprite = (u8 *)((S_8016C190_2_pre *)action_value)[-1].unk_00;
                        ((S_8016C190_1 *)actor)->unk_72.s = target_sprite[0x24];
                        ((S_8016C190_1 *)actor)->unk_73.s = target_sprite[0x25];
                    }
                } else {
                    ((S_8016C190_1 *)actor)->unk_60 = func_800A05A4(
                        actor,
                        ((S_8016C190_3 *)sprite)->unk_24,
                        ((S_8016C190_3 *)sprite)->unk_25,
                        ((S_8016C190_1 *)actor)->unk_2A,
                        0x10);
                    action_value = ((S_8016C190_1 *)actor)->unk_72.u;
                    target_y = ((S_8016C190_1 *)actor)->unk_73.u;
                    if (action_value < 0) {
                        action_value = -action_value;
                    }
                    if (target_y < 0) {
                        target_y = -target_y;
                    }
                    ((S_8016C190_1 *)actor)->unk_72.s = action_value;
                    ((S_8016C190_1 *)actor)->unk_73.s = target_y;
                }
            }

            if (func_800A94A0(actor, action_slot, target_mode,
                              (u16 *)((u8 *)action + 0x98)) != 0) {
                ((S_8016C190_0 *)action)->unk_96.s = 8;
                ((S_8016C190_0 *)action)->unk_9B++;
            }
            return;
        }

        ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
        func_800A2B04(transform, ((S_8016C190_3 *)sprite)->unk_24, ((S_8016C190_3 *)sprite)->unk_25);
        D_8008346C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(actor);
        ((S_8016C190_1 *)actor)->unk_6D--;
        ((S_8016C190_0 *)action)->unk_8C = D_8016A36C;
        ((S_8016C190_1 *)actor)->unk_73.s = 0;
        ((S_8016C190_1 *)actor)->unk_72.s = 0;
        ((S_8016C190_1 *)actor)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((S_8016C190_3 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_8016C190_3 *)sprite)->unk_14 &= 0xF7FF;
        ((S_8016C190_0 *)action)->unk_9B++;
        func_800A56E0(0x703);
        /* fall through */

    case 2:
        ((S_8016C190_0 *)action)->unk_96.u--;
        if ((s16)((S_8016C190_0 *)action)->unk_96.u > 0 &&
            !(((S_8016C190_3 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        ((S_8016C190_0 *)action)->unk_98 |= 0x80;
        ((S_8016C190_0 *)action)->unk_9B++;
        return;

    case 3:
        if (D_8008346C == 0) {
            ((S_8016C190_0 *)action)->unk_96.s = 0;
        }
        if (!(((S_8016C190_3 *)sprite)->unk_14 & 0xE000)) {
            return;
        }

        ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
        func_800A2B04(transform, ((S_8016C190_3 *)sprite)->unk_24, ((S_8016C190_3 *)sprite)->unk_25);

        switch (((S_8016C190_0 *)action)->unk_AC) {
        case 0:
            current_table = ((S_8016C190_3 *)sprite)->unk_2C;
            direction_table = D_801739A0;
            break;
        case 1:
            current_table = ((S_8016C190_3 *)sprite)->unk_2C;
            direction_table = D_801739A8;
            break;
        case 2:
            current_table = ((S_8016C190_3 *)sprite)->unk_2C;
            direction_table = D_801739B0;
            break;
        case 3:
            current_table = ((S_8016C190_3 *)sprite)->unk_2C;
            direction_table = D_801739B8;
            break;
        default:
            goto finish;
        }

        if ((u8 *)current_table != direction_table) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = direction_table;
            func_80047784(
                sprite,
                *(u8 *)((unsigned long)(((D_80083228 +
                    ((S_8016C190_1 *)actor)->unk_2A + 0x100) >> 9) & 7) +
                    (unsigned long)direction_table),
                0);
        }

finish:
        action_control = (u8 *)&D_80083460;
        if (((S_8016C190_5 *)action_control)->unk_0C != 0) {
            return;
        }
        ((S_8016C190_5 *)action_control)->unk_0A--;
        ((S_8016C190_0 *)action)->unk_8C = D_8016A36C;
        func_800A4ACC(actor);
        ((S_8016C190_1 *)actor)->unk_6D--;
        ((S_8016C190_1 *)actor)->unk_73.s = 0;
        ((S_8016C190_1 *)actor)->unk_72.s = 0;
        ((S_8016C190_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        return;

    default:
        return;
    }
}
