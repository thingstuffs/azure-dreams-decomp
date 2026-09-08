#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80090C10_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x8];
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x8];
    void * unk_BC;
    u8 pad_C0[0x8];
    void * unk_C8;
} S_80090C10_0;   /* arg0 in func_80090C10 */

typedef struct S_80090C10_1 {
    union { s32 s; void * (*u)(s32, s32); } unk_00;   /* accessed as both */
    s32 unk_04;
    s32 unk_08;
} S_80090C10_1;   /* &D_800E4938 in func_80090C10 */


typedef struct S_80090C10_3 {
    void * unk_00;
    void * unk_04;
} S_80090C10_3;   /* &D_80082EB0 in func_80090C10 */

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
} S_80090C10_12;   /* ((S_80090C10_0 *)arg0)->unk_C8 in func_80090C10 */

typedef struct S_80090C10_13 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
} S_80090C10_13;   /* ((S_80090C10_3 *)(&D_80082EB0))->unk_00 in func_80090C10 */

typedef struct S_80090C10_14 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80090C10_14;   /* (((s32) ((S_80090C10_3 *)(&D_80082EB0))->unk_00 * 4) + arg0) in func_80090C10 */


typedef struct DdcbcEntry {
    u8 pad[7];
    u8 flags;
} DdcbcEntry;

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_800888B0[];
M2C_UNK func_8002534C(); /* extern */
void func_8003DB94();        /* extern */
s32 func_80042900();                 /* extern */
void func_80048A44(); /* extern */
void func_8004B568();                            /* extern */
s32 func_8008D024(); /* extern */
M2C_UNK func_8008D330(); /* extern */
s32 func_8008D388(); /* extern */
void func_8008D9F0(); /* extern */
M2C_UNK func_80091920(); /* extern */
s32 func_80094270(); /* extern */
M2C_UNK func_800956B8(); /* extern */
s32 func_80095854(); /* extern */
M2C_UNK func_80096088();              /* extern */
M2C_UNK func_80097F84(); /* extern */
M2C_UNK func_800982A8();              /* extern */
void func_80098614();              /* extern */
s32 func_80098920(); /* extern */
s16 func_80098C80();                          /* extern */
M2C_UNK func_80098CF8(); /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099734();                        /* extern */
M2C_UNK func_800997FC();                   /* extern */
s32 func_8009B88C(); /* extern */
M2C_UNK func_8009F644();   /* extern */
M2C_UNK func_800A5720();                         /* extern */
s32 func_800BA33C();                             /* extern */
M2C_UNK func_800BA810();            /* extern */
extern M2C_UNK D_8001EF2C;
extern M2C_UNK D_8004F5F4;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern M2C_UNK D_80082EB0;
extern s32 D_80082EB8;
extern s16 D_80083228;
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
extern M2C_UNK D_800E296C;
extern s32 D_800E3DF0[];
extern M2C_UNK D_800E4938;

/* Wait for the menu to close, then dispatch the selected item or companion action. */
void func_80090C10(void *state, M2C_UNK context, void *sprite, void *actor) {
    static void *const action_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20, &&jt_c21 };
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

    phase = ((S_80090C10_0 *)state)->unk_9B;
    if (phase == 1) {
        goto block_14;
    }
    if ((s32) phase >= 2) {
        goto block_4;
    }
    if (phase == 0) {
        goto block_6;
    }
    return;
block_4:
    if (phase == 2) {
        goto block_16;
    }
    return;
block_6:
    D_800DCF4D = -1;
    func_8004B568();
    if (((S_80090C10_1 *)(&D_800E4938))->unk_00.s == &D_8004F5F4) {
        goto block_13;
    }
    if ((func_80042900(actor, 0xA) << 0x10) == 0) {
        goto block_9;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_800DD274;
    func_8003DB94(sprite, *(s32 *)(D_800DD274 + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 7) & 0x1C)), 0);
    goto block_13;
block_9:
    if (!(((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x100000)) {
        goto block_11;
    }
    anim_table = D_800DD0B8;
    goto block_12;
block_11:
    anim_table = D_800DCFB0;
block_12:
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = anim_table;
    func_80048A44(sprite, *(anim_table + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)), 0, 1);
block_13:
    ((S_80090C10_0 *)state)->unk_9B = (u8) (((S_80090C10_0 *)state)->unk_9B + 1);
block_14:
    menu = ((S_80090C10_1 *)(&D_800E4938))->unk_00.u(((S_80090C10_1 *)(&D_800E4938))->unk_04, ((S_80090C10_1 *)(&D_800E4938))->unk_08);
    ((S_80090C10_0 *)state)->unk_C8 = menu;
    if (menu == NULL) {
        goto block_68;
    }
    ((S_80090C10_0 *)state)->unk_96 = 0;
    ((S_80090C10_3 *)(&D_80082EB0))->unk_00 = NULL;
    selection = &D_80082EB0;
    ((S_80090C10_4 *)selection)->unk_04 = 0;
    ((S_80090C10_4 *)selection)->unk_08 = 0;
    ((S_80090C10_0 *)state)->unk_9B = (u8) (((S_80090C10_0 *)state)->unk_9B + 1);
block_16:
    if (!(((S_80090C10_12 *)(((S_80090C10_0 *)state)->unk_C8))->unk_1E & 0x8000)) {
        goto block_18;
    }
    func_800BA810(0, 0);
    ui_flags = ((S_80090C10_5 *)(&D_800E296C))->unk_00;
    ((S_80090C10_0 *)state)->unk_C8 = NULL;
    (*(s32 *)&D_800E296C) = ui_flags & ~0x2000;
block_18:
    if (((S_80090C10_0 *)state)->unk_C8 != NULL) {
        goto block_68;
    }
    if ((u32) (D_80082EB8 - 1) >= 0x15U) {
        goto block_64;
    }
    (void)action_labels; goto *D_800888B0[(u32)((D_80082EB8) - 1)];
jt_c1:
    func_8009F644(actor, 0x48, func_80098C80(((S_80090C10_3 *)(&D_80082EB0))->unk_00), 0);
    if (((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_01 != 0x11) {
        goto block_23;
    }
    func_80098614(actor, (*(void **)&D_80082EB0));
    goto block_64;
block_23:
    func_800982A8(actor, (*(void **)&D_80082EB0));
    goto block_64;
jt_c2:
    if (((S_80090C10_13 *)(((S_80090C10_3 *)(&D_80082EB0))->unk_00))->unk_01 != 0x11) {
        goto block_26;
    }
    func_8009F644(actor, 0x48, func_80098C80(((Rec_D_800E3D7C *)actor)->unk_50.at00_pv.v), 0);
    func_80098614(actor, NULL);
    goto block_64;
block_26:
    func_8009F644(actor, 0x48, func_80098C80(((Rec_D_800E3D7C *)actor)->unk_4C.as_pv), 0);
    func_800982A8(actor, NULL);
    goto block_64;
jt_c21:
    if (!(((S_80090C10_13 *)(((S_80090C10_3 *)(&D_80082EB0))->unk_00))->unk_03 & 0x20)) {
        goto block_29;
    }
    func_800997FC(&D_800E0542);
    goto block_64;
block_29:
    if (func_800BA33C(((S_80090C10_0 *)state)->unk_AC) != 0) {
        goto block_31;
    }
    if (func_800BA33C(((S_80090C10_0 *)state)->unk_B0) == 0) {
        goto block_32;
    }
block_31:
    func_80091920(state, context, sprite, actor);
    return;
block_32:
    func_800997FC(&D_800E0571);
    goto block_64;
jt_c3:
jt_c4:
jt_c20:
    item_result = func_80098920(actor, ((S_80090C10_3 *)(&D_80082EB0))->unk_00, 3, 0);
    if (item_result < 0) {
        goto block_36;
    }
    item_text_id = (s16) func_80098C80((*(void **)&D_80082EB0));
    func_8009F644(actor, 0x48, item_text_id, func_80098C80(((S_80090C10_3 *)(&D_80082EB0))->unk_04));
    if (item_result > 0) {
        goto block_64;
    }
    if (item_result >= 0) {
        goto block_68;
    }
block_36:
    if (((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_01 != 0x15) {
        goto block_68;
    }
    ((S_80090C10_0 *)state)->unk_9B = 3U;
    return;
jt_c5:
    func_8009F644(actor, 0x58, 0, func_80098C80(((S_80090C10_3 *)(&D_80082EB0))->unk_00));
    func_80098CF8(state, context, sprite, (*(void **)&D_80082EB0));
    goto block_64;
jt_c8:
jt_c9:
    func_8009F644(actor, 0x98, 0, func_80098C80(((S_80090C10_3 *)(&D_80082EB0))->unk_00));
    if (!(((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_03 & 0x20)) {
        goto block_41;
    }
    func_800956B8(state, context, sprite, (*(void **)&D_80082EB0));
    goto block_64;
block_41:
    direction = ((u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 9) & 7;
    if ((func_8009B88C(0, (s16) (((Rec_D_80082E80 *)sprite)->unk_24 + D_8006CCD8[direction]), (s16) (((Rec_D_80082E80 *)sprite)->unk_25 + D_8006CCE8[direction]), &tile_x, &tile_y) << 0x10) != 0) {
        goto block_43;
    }
    text_buffer = func_800990FC();
    text_end = func_80099734(D_800E3DF0[((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_03 & 0x1F], func_80099194(&D_800E069D, text_buffer));
    func_80099290(func_80099194(&D_800E06BD, text_end));
    func_800A5720(text_buffer);
    goto block_64;
block_43:
    if (func_80095854(state, context, sprite, (*(void **)&D_80082EB0)) != 0) {
        goto block_68;
    }
    text_buffer = func_800990FC();
    text_end = func_80099734(D_800E3DF0[((S_80090C10_6 *)((*(void **)&D_80082EB0)))->unk_03 & 0x1F], func_80099194(&D_800E06C0, text_buffer));
    func_80099290(func_80099194(&D_800E06E0, text_end));
    func_800A5720(text_buffer);
    goto block_64;
jt_c10:
    func_8002534C(state, context, sprite, actor);
    ((S_80090C10_0 *)state)->unk_C8 = NULL;
    return;
jt_c14:
    func_8008D330(state, context, sprite, actor);
    ((S_80090C10_0 *)state)->unk_C8 = NULL;
    goto block_64;
jt_c12:
    companion_value = (s32) ((S_80090C10_14 *)((((s32) ((S_80090C10_3 *)(&D_80082EB0))->unk_00 * 4) + state)))->unk_AC;
    if (((S_80090C10_8 *)((void *)companion_value))->unk_1C & 0x80000) {
        goto block_50;
    }
    ((S_80090C10_8 *)((void *)companion_value))->unk_60 = 0;
block_50:
    if (((S_80090C10_1 *)(&D_800E4938))->unk_00.s == &D_8001EF2C) {
        goto block_64;
    }
    companion = ((S_80090C10_9 *)((((s32) (*(void **)&D_80082EB0) * 4) + state)))->unk_AC;
    companion_value = ((S_80090C10_10 *)companion)->unk_46 & 0x3FFF;
    if ((u32) (companion_value - 5) < 3U) {
        goto block_64;
    }
    if ((u32) (companion_value - 9) >= 2U) {
        goto block_56;
    }
    companion_flags = D_800DDCBC[((S_80090C10_10 *)companion)->unk_13].flags;
    if (companion_value != 9) {
        state_allowed = companion_flags & 2;
    } else {
        state_allowed = companion_flags & 1;
    }
block_55:
    if (state_allowed != 0) {
        goto block_64;
    }
block_56:
    if (func_8008D024(state, context, sprite, (s16) ((S_80090C10_3 *)(&D_80082EB0))->unk_00, 1) != 0) {
        goto block_68;
    }
    D_80082EB8 = 0;
    goto block_66;
jt_c16:
    ((S_80090C10_0 *)state)->unk_BC = (void *) ((S_80090C10_3 *)(&D_80082EB0))->unk_00;
    if (func_8008D388(state, context, sprite, actor) != 0) {
        goto block_68;
    }
    D_80082EB8 = 0;
    goto block_66;
jt_c6:
jt_c7:
    {
        u8 *action_data = (u8 *)&D_80082EB0;
        action_index = ((S_80090C10_11 *)action_data)->unk_08 - 6;
        ((Rec_D_800E3D7C *)actor)->unk_8A.as_s16 = action_index;
        if (func_80094270(state, context, sprite, ((S_80090C10_11 *)action_data)->unk_00, (s32) action_index) == 0) {
            goto block_68;
        }
        D_80082EB8 = 0;
        goto block_66;
    }
jt_c17:
jt_c18:
    func_80097F84(((S_80090C10_3 *)(&D_80082EB0))->unk_00, &D_800E0462, &D_800E0472, 1);
    goto block_64;
jt_c19:
    func_8008D9F0(state, context, sprite, actor);
    return;
jt_c11:
jt_c13:
jt_c15:
block_64:
    D_80082EB8 = 0;
block_66:
    if (((S_80090C10_0 *)state)->unk_C8 != NULL) {
        goto block_68;
    }
    ((S_80090C10_0 *)state)->unk_A2 = (u16) (((S_80090C10_0 *)state)->unk_A2 | 0x40);
    func_80096088(state, actor);
block_68:
    return;
}
