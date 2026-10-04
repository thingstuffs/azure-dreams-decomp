#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008D024_arg0.h"
#include "records/Rec_D_80082EB0.h"


typedef struct S_80090C10_1 {
    union { s32 s; void * (*u)(s32, s32); } unk_00;   /* accessed as both */
    s32 unk_04;
    s32 unk_08;
} S_80090C10_1;   /* &D_800E4938 in func_80090C10 */


typedef struct S_80090C10_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80090C10_4;   /* temp_v0_2 in func_80090C10 */

typedef struct S_80090C10_5 {
    s32 unk_00;
} S_80090C10_5;   /* &D_800E296C in func_80090C10 */

typedef struct S_80090C10_6 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
} S_80090C10_6;   /* (*(void **)&D_80082EB0) in func_80090C10 */


typedef struct S_80090C10_8 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x40];
    s32 unk_60;
} S_80090C10_8;   /* (void *)temp_a0 in func_80090C10 */

typedef struct S_80090C10_9 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80090C10_9;   /* (((s32) (*(void **)&D_80082EB0) * 4) + arg0) in func_80090C10 */

typedef struct S_80090C10_10 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x32];
    u16 unk_46;
} S_80090C10_10;   /* temp_v1_3 in func_80090C10 */

typedef struct S_80090C10_11 {
    void * unk_00;
    u8 pad_04[0x4];
    u16 unk_08;
} S_80090C10_11;   /* case_base in func_80090C10 */

typedef struct S_80090C10_12 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80090C10_12;   /* ((Rec_func_8008D024_arg0 *)arg0)->unk_C8 in func_80090C10 */

typedef struct S_80090C10_13 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
} S_80090C10_13;   /* ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv in func_80090C10 */

typedef struct S_80090C10_14 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80090C10_14;   /* (((s32) ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv * 4) + arg0) in func_80090C10 */


typedef struct DdcbcEntry {
    u8 pad[7];
    u8 flags;
} DdcbcEntry;

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8002534C(); /* extern */
void func_8003DB94();        /* extern */
s32 func_80042900();                 /* extern */
void func_80048A44(); /* extern */
void func_8004B568();                            /* extern */
s32 func_8008D024(); /* extern */
void func_8008D330(); /* extern */
s32 func_8008D388(); /* extern */
void func_8008D9F0(); /* extern */
void func_80091920(); /* extern */
s32 func_80094270(); /* extern */
void func_800956B8(); /* extern */
s32 func_80095854(); /* extern */
void func_80096088();              /* extern */
void *func_80097F84(); /* extern */
void func_800982A8();              /* extern */
void func_80098614();              /* extern */
s32 func_80098920(); /* extern */
s16 func_80098C80();                          /* extern */
void *func_80098CF8(); /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
void *func_80099290();                         /* extern */
s32 func_80099734();                        /* extern */
void func_800997FC();                   /* extern */
s32 func_8009B88C(); /* extern */
void func_8009F644();   /* extern */
s32 func_800A5720();                         /* extern */
s32 func_800BA33C();                             /* extern */
void func_800BA810();            /* extern */
extern M2C_UNK D_8001EF2C;
extern M2C_UNK D_8004F5F4;
extern M2C_UNK D_80082EB0;
extern s32 D_80082EB8;
extern s8 D_800DCF4D;
extern u8 D_800DCFB0[];
extern u8 D_800DD0B8[];
extern u8 D_800DD274[];
extern DdcbcEntry D_800DDCBC[];
extern M2C_UNK D_800E0462;
extern M2C_UNK D_800E0472;
extern M2C_UNK D_800E0542;
extern M2C_UNK D_800E0571;
extern M2C_UNK D_800E069D;
extern M2C_UNK D_800E06BD;
extern M2C_UNK D_800E06C0;
extern M2C_UNK D_800E06E0;
extern s32 D_800E3DF0[];
extern M2C_UNK D_800E4938;

/* Wait for the menu to close, then dispatch the selected item or companion action. */
void func_80090C10(void *state, M2C_UNK context, void *sprite, EntityRec *actor) {
    s16 tile_x;
    s16 tile_y;
    u8 *anim_table;
    s32 item_text_id;
    s16 action_index;
    s32 ui_flags;
    s32 item_result;
    s32 direction;
    s32 text_buffer;
    s32 text_end;
    s32 state_allowed;
    s32 phase;
    u8 companion_flags;
    s32 companion_value;
    void *menu;
    void *selection;
    void *companion;

    phase = ((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8;
    switch (phase) {
    case 0:
        D_800DCF4D = -1;
        func_8004B568();
        if (((S_80090C10_1 *)(&D_800E4938))->unk_00.s != &D_8004F5F4) {
            if ((func_80042900(actor, 0xA) << 0x10) != 0) {
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_800DD274;
                func_8003DB94(sprite, *(s32 *)(D_800DD274 + (((s32) (gameWork.view.viewAngle + actor->facing + 0x100)
                    >> 7) & 0x1C)), 0);
            } else {
                if (actor->flags1C & 0x100000) {
                    anim_table = D_800DD0B8;
                } else {
                    anim_table = D_800DCFB0;
                }
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = anim_table;
                func_80048A44(sprite, *(anim_table + (((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                    0, 1);
            }
        }
        ((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 = (u8) (((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 + 1);
    case 1:
        menu = ((S_80090C10_1 *)(&D_800E4938))->unk_00.u(((S_80090C10_1 *)(&D_800E4938))->unk_04,
            ((S_80090C10_1 *)(&D_800E4938))->unk_08);
        ((Rec_func_8008D024_arg0 *)state)->unk_C8 = menu;
        if (menu == NULL) {
            return;
        }
        ((Rec_func_8008D024_arg0 *)state)->unk_96 = 0;
        ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv = NULL;
        selection = &D_80082EB0;
        ((S_80090C10_4 *)selection)->unk_04 = 0;
        ((S_80090C10_4 *)selection)->unk_08 = 0;
        ((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 = (u8) (((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 + 1);
    case 2:
        break;
    default:
        return;
    }
    if (((S_80090C10_12 *)(((Rec_func_8008D024_arg0 *)state)->unk_C8))->unk_1E & 0x8000) {
        func_800BA810(0, 0);
        ui_flags = ((S_80090C10_5 *)(&D_800E296C))->unk_00;
        ((Rec_func_8008D024_arg0 *)state)->unk_C8 = NULL;
        (*(s32 *)&D_800E296C) = ui_flags & ~0x2000;
    }
    if (((Rec_func_8008D024_arg0 *)state)->unk_C8 != NULL) {
        return;
    }
    switch (D_80082EB8) {
    case 1:
        func_8009F644(actor, 0x48, func_80098C80(((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv), 0);
        if (((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_01 == 0x11) {
            func_80098614(actor, (*(void **)&D_80082EB0));
            D_80082EB8 = 0;
            break;
        }
        func_800982A8(actor, (*(void **)&D_80082EB0));
        D_80082EB8 = 0;
        break;
    case 2:
        if (((S_80090C10_13 *)(((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv))->unk_01 == 0x11) {
            func_8009F644(actor, 0x48, func_80098C80((*(void * *)&actor->unk_50)), 0);
            func_80098614(actor, NULL);
            D_80082EB8 = 0;
            break;
        }
        func_8009F644(actor, 0x48, func_80098C80(actor->unk_4C), 0);
        func_800982A8(actor, NULL);
        D_80082EB8 = 0;
        break;
    case 21:
        if (((S_80090C10_13 *)(((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv))->unk_03 & 0x20) {
            func_800997FC(&D_800E0542);
            D_80082EB8 = 0;
            break;
        }
        if (func_800BA33C(((Rec_func_8008D024_arg0 *)state)->unk_AC) != 0 || func_800BA33C(((Rec_func_8008D024_arg0 *)state)->unk_B0) != 0) {
            func_80091920(state, context, sprite, actor);
            return;
        }
        func_800997FC(&D_800E0571);
        D_80082EB8 = 0;
        break;
    case 3:
    case 4:
    case 20:
        item_result = func_80098920(actor, ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv, 3, 0);
        if (item_result >= 0) {
            item_text_id = (s16) func_80098C80((*(void **)&D_80082EB0));
            func_8009F644(actor, 0x48, item_text_id, func_80098C80(((Rec_D_80082EB0 *)(&D_80082EB0))->unk_04));
            if (item_result > 0) {
                goto block_64;
            }
            if (item_result >= 0) {
                return;
            }
        }
        if (((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_01 != 0x15) {
            return;
        }
        ((Rec_func_8008D024_arg0 *)state)->unk_9B.as_u8 = 3U;
        return;
    case 5:
        func_8009F644(actor, 0x58, 0, func_80098C80(((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv));
        func_80098CF8(state, context, sprite, (*(void **)&D_80082EB0));
        D_80082EB8 = 0;
        break;
    case 8:
    case 9:
        func_8009F644(actor, 0x98, 0, func_80098C80(((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv));
        if (((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_03 & 0x20) {
            func_800956B8(state, context, sprite, (*(void **)&D_80082EB0));
            D_80082EB8 = 0;
            break;
        }
        direction = ((u16) actor->facing >> 9) & 7;
        if ((func_8009B88C(0, (s16) (((Rec_D_80082E80 *)sprite)->unk_24 + dirStepX[direction]),
            (s16) (((Rec_D_80082E80 *)sprite)->unk_25 + dirStepY[direction]), &tile_x, &tile_y) << 0x10) == 0) {
            text_buffer = func_800990FC();
            text_end = func_80099734(D_800E3DF0[((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_03 & 0x1F],
                func_80099194(&D_800E069D, text_buffer));
            func_80099290(func_80099194(&D_800E06BD, text_end));
            func_800A5720(text_buffer);
            D_80082EB8 = 0;
            break;
        }
        if (func_80095854(state, context, sprite, (*(void **)&D_80082EB0)) != 0) {
            return;
        }
        text_buffer = func_800990FC();
        text_end = func_80099734(D_800E3DF0[((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_03 & 0x1F],
            func_80099194(&D_800E06C0, text_buffer));
        func_80099290(func_80099194(&D_800E06E0, text_end));
        func_800A5720(text_buffer);
        goto block_64;
    case 10:
        func_8002534C(state, context, sprite, actor);
        ((Rec_func_8008D024_arg0 *)state)->unk_C8 = NULL;
        return;
    case 14:
        func_8008D330(state, context, sprite, actor);
        ((Rec_func_8008D024_arg0 *)state)->unk_C8 = NULL;
        goto block_64;
    case 12:
        companion_value = (s32) ((S_80090C10_14 *)((((s32) ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv * 4)
            + state)))->unk_AC;
        if (!(((S_80090C10_8 *)((void *)companion_value))->unk_1C & 0x80000)) {
            ((S_80090C10_8 *)((void *)companion_value))->unk_60 = 0;
        }
        if (((S_80090C10_1 *)(&D_800E4938))->unk_00.s == &D_8001EF2C) {
            D_80082EB8 = 0;
            break;
        }
        companion = ((S_80090C10_9 *)((((s32) (*(void **)&D_80082EB0) * 4) + state)))->unk_AC;
        companion_value = ((S_80090C10_10 *)companion)->unk_46 & 0x3FFF;
        if ((u32) (companion_value - 5) < 3U) {
            D_80082EB8 = 0;
            break;
        }
        if ((u32) (companion_value - 9) < 2U) {
            companion_flags = D_800DDCBC[((S_80090C10_10 *)companion)->unk_13].flags;
            if (companion_value != 9) {
                state_allowed = companion_flags & 2;
            } else {
                state_allowed = companion_flags & 1;
            }
            if (state_allowed != 0) {
                D_80082EB8 = 0;
                break;
            }
        }
        if (func_8008D024(state, context, sprite, (s16) ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv, 1) != 0) {
            return;
        }
        D_80082EB8 = 0;
        break;
    case 16:
        ((Rec_func_8008D024_arg0 *)state)->unk_BC = (void *) ((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv;
        if (func_8008D388(state, context, sprite, actor) != 0) {
            return;
        }
        D_80082EB8 = 0;
        break;
    case 6:
    case 7:
    {
        u8 *action_data = (u8 *)&D_80082EB0;
        action_index = ((S_80090C10_11 *)action_data)->unk_08 - 6;
        actor->unk_8A = action_index;
        if (func_80094270(state, context, sprite, ((S_80090C10_11 *)action_data)->unk_00, (s32) action_index) == 0) {
            return;
        }
        D_80082EB8 = 0;
        break;
    }
    case 17:
    case 18:
        func_80097F84(((Rec_D_80082EB0 *)(&D_80082EB0))->unk_00.as_pv, &D_800E0462, &D_800E0472, 1);
        goto block_64;
    case 19:
        func_8008D9F0(state, context, sprite, actor);
        return;
    case 15:
    default:
block_64:
        D_80082EB8 = 0;
    }
    if (((Rec_func_8008D024_arg0 *)state)->unk_C8 != NULL) {
        return;
    }
    ((Rec_func_8008D024_arg0 *)state)->unk_A2 = (u16) (((Rec_func_8008D024_arg0 *)state)->unk_A2 | 0x40);
    func_80096088(state, actor);
    return;
}
