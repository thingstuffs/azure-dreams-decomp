#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801728B4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
} S_801728B4_0;   /* arg0 in func_801728B4 */


typedef struct S_801728B4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801728B4_2_pre;   /* the 0x14 bytes before var_v0 in func_801728B4, addressed as var_v0[-1] */

typedef struct S_801728B4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801728B4_3;   /* temp_v1_3 in func_801728B4 */


typedef struct S_801728B4_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801728B4_5;   /* arg1 in func_801728B4 */

typedef struct S_801728B4_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x6F];
    s8 unk_BB;
} S_801728B4_6;   /* temp_v0_2 in func_801728B4 */

typedef struct S_801728B4_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_801728B4_7;   /* temp_a0 in func_801728B4 */


typedef struct S_801728B4_9 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xAB];
    u8 unk_BB;
} S_801728B4_9;   /* var_s0 in func_801728B4 */

typedef struct S_801728B4_10 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801728B4_10;   /* temp_v1_4 in func_801728B4 */

typedef struct S_801728B4_11 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801728B4_11;   /* ((S_801728B4_6 *)temp_v0_2)->unk_08 in func_801728B4 */

extern void *D_80170838[];
s32 func_8003F270(void);
void *func_8003FD64();
s32 func_8004491C();
void func_80047784();
void *func_800A05A4();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A94A0(void *, u8 *, s32, void *);
extern M2C_UNK D_80045340;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[];
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D7960;
extern M2C_UNK D_80170E54;
extern u8 D_80173C6C[];

/* Updates an actor action, its visual effect, and completion cleanup. */
void func_801728B4(void *actor, void *motion, void *sprite, void *action) {
    static void *const action_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s32 action_id;
    s32 action_value;
    s32 effect_anim;
    s32 use_player;
    s32 target_x;
    s32 target_y;
    u16 saved_pos[4];
    u16 sprite_flags;
    u16 ticks_left;
    u16 sprite_angle;
    u8 *slot_or_effect;
    s32 state;
    u8 *action_status;
    void *effect_sprite;
    void *new_effect;
    void *target;

    state = ((S_801728B4_0 *)actor)->unk_9B;
    use_player = 0;
    if (state == 1) {
        goto block_37;
    }
    if ((s32) state >= 2) {
        goto block_4;
    }
    if (state == 0) {
        goto block_6;
    }
    return;
block_4:
    if (state == 2) {
        goto block_40;
    }
    return;
block_6:
    if (!(((Rec_D_800E3D7C *)action)->unk_1C.as_s32 & 0x2000)) {
        goto block_12;
    }
    action_id = ((Rec_D_800E3D7C *)action)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (action_id - 1) >= 7U) {
        goto block_20;
    }
    (void)action_labels; goto *D_80170838[(u32)((action_id) - 1)];
jt_c7:
    use_player = 1;
    goto block_17;
jt_c6:
    use_player = 1;
    goto block_18;
jt_c5:
    use_player = 1;
    goto block_19;
block_12:
    action_value = ((Rec_D_800E3D7C *)action)->unk_44.at02_u16.v & 0x3FFF;
    if (action_value == 2) {
        goto block_18;
    }
    if (action_value >= 3) {
        goto block_16;
    }
    slot_or_effect = NULL;
    if (action_value == 1) {
        goto block_19;
    }
    goto block_21;
block_16:
    slot_or_effect = NULL;
    if (action_value != 3) {
        goto block_21;
    }
jt_c3:
block_17:
    slot_or_effect = action + 0xE;
    goto block_21;
jt_c2:
block_18:
    slot_or_effect = action + 0xB;
    goto block_21;
jt_c1:
block_19:
    slot_or_effect = action + 8;
    goto block_21;
jt_c4:
block_20:
    slot_or_effect = NULL;
block_21:
    if (*slot_or_effect == 0) {
        goto block_36;
    }
    ((S_801728B4_0 *)actor)->unk_98 = (u16) (((S_801728B4_0 *)actor)->unk_98 & 0xFF7F);
    {
        s32 player_target = use_player;

        ASM_KEEP(player_target);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (player_target == 0) {
            goto block_24;
        }
    }
    target = D_800814A8;
    ((Rec_D_800E3D7C *)action)->unk_60.as_pv = target;
    goto block_26;
block_24:
    if (D_8006DE24[(*slot_or_effect * 0x14) + 0x12] != 2) {
        goto block_27;
    }
    target = ((Rec_D_800E3D7C *)action)->unk_60.as_pv;
    if (target == NULL) {
        goto block_33;
    }
block_26:
    action_value = ((S_801728B4_2_pre *)target)[-1].unk_00;
    ((Rec_D_800E3D7C *)action)->unk_72.as_s8 = (s8) ((S_801728B4_3 *)action_value)->unk_24;
    ((Rec_D_800E3D7C *)action)->unk_73.as_s8 = (s8) ((S_801728B4_3 *)action_value)->unk_25;
    goto block_32;
block_27:
    ((Rec_D_800E3D7C *)action)->unk_60.as_pv = func_800A05A4(action, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25, ((Rec_D_800E3D7C *)action)->unk_2A.as_s16, 0x10);
    ASM_KEEP(action);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    target_x = ((Rec_D_800E3D7C *)action)->unk_72.as_s8;
    target_y = ((Rec_D_800E3D7C *)action)->unk_73.as_s8;
    if (target_x >= 0) {
        goto block_29;
    }
    target_x = 0 - target_x;
block_29:
    if (target_y >= 0) {
        goto block_31;
    }
    target_y = 0 - target_y;
block_31:
    ((Rec_D_800E3D7C *)action)->unk_72.as_s8 = target_x;
    ((Rec_D_800E3D7C *)action)->unk_73.as_s8 = target_y;
block_32:
block_33:
    saved_pos[0] = ((S_801728B4_5 *)motion)->unk_00.at02.v;
    saved_pos[1] = ((S_801728B4_5 *)motion)->unk_04.at02.v;
    saved_pos[2] = ((S_801728B4_5 *)motion)->unk_08.at02.v;
    if (func_800A94A0(action, slot_or_effect, use_player, actor + 0x98) == 0) {
        goto block_56;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
    func_800A56E0(0x703);
    ((S_801728B4_0 *)actor)->unk_9B = (u8) (((S_801728B4_0 *)actor)->unk_9B + 1);
    new_effect = func_8003FD64(0x112, &D_80083498);
    ((S_801728B4_0 *)actor)->unk_A0 = new_effect;
    if (new_effect == NULL) {
        goto block_56;
    }
    func_8004491C(new_effect, &D_80045340);
    ((S_801728B4_6 *)new_effect)->unk_10 = &D_800D7960;
    ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_00 = (s32) ((S_801728B4_5 *)motion)->unk_00.at00.v;
    ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_04 = (s32) ((S_801728B4_5 *)motion)->unk_04.at00.v;
    ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_08 = (s32) (((S_801728B4_5 *)motion)->unk_08.at00.v + 0xFF800000);
    ((S_801728B4_6 *)new_effect)->unk_BB = 0;
    effect_sprite = ((S_801728B4_6 *)new_effect)->unk_0C;
    ((S_801728B4_6 *)new_effect)->unk_4A = (u16) ((Rec_D_800E3D7C *)action)->unk_2A.as_s16;
    action_value = ((Rec_D_80082E80 *)sprite)->unk_28.at00_s32.v;
    ((S_801728B4_7 *)effect_sprite)->unk_1E = 0x1000;
    ((S_801728B4_7 *)effect_sprite)->unk_1C = 0x1000;
    ((S_801728B4_7 *)effect_sprite)->unk_28 = action_value;
    sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
    effect_anim = 0x2D;
    ((S_801728B4_7 *)effect_sprite)->unk_14 = sprite_flags;
    sprite_angle = ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v;
    ((S_801728B4_7 *)effect_sprite)->unk_10 = 0;
    ((S_801728B4_7 *)effect_sprite)->unk_14 = (u16) (sprite_flags | 0xC);
    ((S_801728B4_7 *)effect_sprite)->unk_12 = (s16) (sprite_angle - 0x80);
    ((S_801728B4_7 *)effect_sprite)->unk_0C = (s32) ((Rec_D_80082E80 *)sprite)->unk_0C.at00_s32.v;
    func_80047784(effect_sprite, effect_anim, 0);
    return;
block_36:
    ((S_801728B4_5 *)motion)->unk_14 = 0;
    ((S_801728B4_5 *)motion)->unk_10 = 0;
    ((S_801728B4_5 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    ((Rec_D_800814A8 *)D_800814A8)->unk_A6 = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
    func_800A4ACC(action);
    ((Rec_D_800E3D7C *)action)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)action)->unk_6D.as_u8 - 1);
    ((S_801728B4_0 *)actor)->unk_8C = &D_80170E54;
    ((Rec_D_800E3D7C *)action)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)action)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)action)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)action)->unk_44.at02_u16.v & 0x7FFF);
    return;
block_37:
    if (func_8003F270() == 0) {
        goto block_39;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x800);
    return;
block_39:
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
    ((S_801728B4_0 *)actor)->unk_9B = (u8) (((S_801728B4_0 *)actor)->unk_9B + 1);
block_40:
    target_x = ((S_801728B4_0 *)actor)->unk_A0;
    if (target_x == NULL) {
        goto block_43;
    }
    slot_or_effect = target_x;
    effect_sprite = ((S_801728B4_9 *)slot_or_effect)->unk_0C;
    if (!(((S_801728B4_7 *)effect_sprite)->unk_14 & 0xE000)) {
        goto block_43;
    }
    ((S_801728B4_9 *)slot_or_effect)->unk_BB = 0xFF;
    ((S_801728B4_0 *)actor)->unk_A0 = NULL;
block_43:
    if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 != 4) {
        goto block_45;
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000) {
        goto block_46;
    }
block_45:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto block_47;
    }
block_46:
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x800);
    ((S_801728B4_0 *)actor)->unk_96 = 3U;
    ((S_801728B4_0 *)actor)->unk_98 = (u16) (((S_801728B4_0 *)actor)->unk_98 | 0x80);
block_47:
    ticks_left = ((S_801728B4_0 *)actor)->unk_96 - 1;
    ((S_801728B4_0 *)actor)->unk_96 = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        goto block_49;
    }
    ((S_801728B4_0 *)actor)->unk_96 = 0U;
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
block_49:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto block_56;
    }
    ((S_801728B4_5 *)motion)->unk_14 = 0;
    ((S_801728B4_5 *)motion)->unk_10 = 0;
    ((S_801728B4_5 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pm == &D_80173C6C) {
        goto block_52;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80173C6C;
    func_80047784(sprite, D_80173C6C[((s32) (D_80083228 + ((Rec_D_800E3D7C *)action)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
block_52:
    action_status = D_80083460;
    if (((S_801728B4_10 *)action_status)->unk_0C != 0) {
        goto block_56;
    }
    ((S_801728B4_10 *)action_status)->unk_0A = (u16) (((S_801728B4_10 *)action_status)->unk_0A - 1);
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
    ((S_801728B4_0 *)actor)->unk_8C = &D_80170E54;
    func_800A4ACC(action);
    if ((s8) ((Rec_D_800E3D7C *)action)->unk_6D.as_u8 <= 0) {
        goto block_55;
    }
    ((Rec_D_800E3D7C *)action)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)action)->unk_6D.as_u8 - 1);
block_55:
    ((Rec_D_800E3D7C *)action)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)action)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)action)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)action)->unk_44.at02_u16.v & 0x7FFF);
    func_800A56E0(0xB4);
block_56:
    return;
}
