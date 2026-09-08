#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"
typedef s32 M2C_UNK;

typedef struct S_8016A36C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8016A36C_0;   /* state in func_8016A36C */



typedef struct S_8016A36C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    union { M2C_UNK * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_8016A36C_3;   /* arg2 in func_8016A36C */

typedef struct S_8016A36C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_8016A36C_4;   /* late_state in func_8016A36C */


typedef struct S_8016A36C_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016A36C_6;   /* home in func_8016A36C */

typedef struct S_8016A36C_7 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8016A36C_7;   /* owner in func_8016A36C */


typedef struct DungeonEntry {
    u8 pad00[0xC];
    u16 flags;
    u8 pad0E[6];
} DungeonEntry;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80164918[];
void func_80047784();
void func_800478B8();
s32 func_80069EF8();
s32 func_8009A180();
s8 func_8009FB34();
s32 func_8009FD7C();
s32 func_800A0818();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAF00();
M2C_UNK func_8016AFC4(void *, void *, void *, void *);
M2C_UNK func_8016B230();
s32 func_8016B954();
M2C_UNK func_8016BAE0();
s32 func_8016BBC0();
void func_8016D4B8();
M2C_UNK func_8016D6F8();
void func_8016DAC0();
s32 func_801732A4();
extern u16 D_80013714;
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern DungeonEntry D_800E2970[];
extern u8 D_801739A0;
extern u8 D_801739A8;
extern u8 D_801739B0;
extern u8 D_801739B8;
extern M2C_UNK D_801739E0;
extern M2C_UNK D_801739E8;
extern M2C_UNK D_801739F0;
extern M2C_UNK D_801739F8;
extern M2C_UNK D_80173A00;
extern M2C_UNK D_80173A08;
extern M2C_UNK D_80173A10;
extern M2C_UNK D_80173A18;
extern u8 D_80173A50;
extern u8 D_80173A58;
extern M2C_UNK D_80173AC0;
extern M2C_UNK D_80173AC8;

/* Updates dungeon actor actions, facing, and idle animations. */
void func_8016A36C(void *actor, void *context, void *sprite_arg, void *entity) {
    static void *const action_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    register void *sprite = sprite_arg;
    M2C_UNK distance;
    u8 *idle_table;
    M2C_UNK *dungeon_state;
    M2C_UNK *turn_state;
    u8 *pose2_table;
    u8 *pose3_table;
    register u8 *anim_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    unsigned long table_index;
    u8 *next_table;
    u8 *current_table;
    s32 entity_flags;
    s32 action_id;
    s8 room_id;
    u16 action_flags;
    u16 pose2_idle_ticks;
    u16 pose2_anim_ticks;
    u16 pose3_idle_ticks;
    u16 pose3_anim_ticks;
    s32 inactive_pose;
    s32 flagged_pose;
    s32 anim_state;
    s32 active_pose;
    s32 action_pose;
    s32 idle_pose;
    u32 clear_mask;
    s32 state_changed;

    dungeon_state = &D_80083460;
    if (!(((S_8016A36C_0 *)dungeon_state)->unk_02 & 0x1000)) {
        goto block_3;
    }
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
    func_8016AFC4(actor, context, sprite, entity);
    if (((Rec_func_800A9E70_arg0 *)actor)->unk_B0 != 1) {
        goto block_150;
    }
    ((Rec_func_800A9E70_arg0 *)actor)->unk_AD = (u8) (((Rec_func_800A9E70_arg0 *)actor)->unk_AD + 1);
    ((S_8016A36C_0 *)dungeon_state)->unk_0A = (u16) (((S_8016A36C_0 *)dungeon_state)->unk_0A + 1);
    return;
block_3:
    if (((Rec_func_800A9E70_arg0 *)actor)->unk_B0 != 1) {
        goto block_6;
    }
    if (((Rec_func_800A9E70_arg0 *)actor)->unk_AD == 0) {
        goto block_6;
    }
    ((S_8016A36C_0 *)dungeon_state)->unk_0A = (u16) (((S_8016A36C_0 *)dungeon_state)->unk_0A - ((Rec_func_800A9E70_arg0 *)actor)->unk_AD);
    ((Rec_func_800A9E70_arg0 *)actor)->unk_AD = 0U;
block_6:
    if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v != 0) {
        goto block_19;
    }
    func_800AA79C(actor, context, sprite, entity);
    ASM_KEEP_NV(actor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    inactive_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
    if (inactive_pose == 0xE) {
        goto block_15;
    }
    if ((s32) inactive_pose >= 0xF) {
        goto block_11;
    }
    if (inactive_pose == 0xD) {
        goto block_13;
    }
    return;
block_11:
    if (inactive_pose == 0xF) {
        goto block_17;
    }
    return;
block_13:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p == (M2C_UNK *)((u8 *)&D_80173AC0 + 8)) {
        goto block_150;
    }
    anim_table = (M2C_UNK *)((u8 *)&D_80173A58 + 0x68);
    goto block_130;
block_15:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p == (M2C_UNK *)((u8 *)&D_80173A58 + 0x70)) {
        goto block_150;
    }
    anim_table = &D_80173AC0;
    goto block_130;
block_17:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p == &D_80173AC8) {
        goto block_150;
    }
    anim_table = (M2C_UNK *)((u8 *)&D_80173A00 + 0xC0);
    goto block_130;
block_19:
    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x200)) {
        goto block_36;
    }
    flagged_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
    if (flagged_pose == 0xE) {
        goto block_28;
    }
    if ((s32) flagged_pose >= 0xF) {
        goto block_24;
    }
    if (flagged_pose == 0xD) {
        goto block_26;
    }
    goto block_37;
block_24:
    if (flagged_pose == 0xF) {
        goto block_30;
    }
    goto block_37;
block_26:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173AC8) {
        goto block_33;
    }
    clear_mask = 0xFFFB0000U;
    state_changed = 1;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = flagged_pose;
    goto block_32;
block_28:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p == &D_80173AC8) {
        goto block_31;
    }
    goto block_35;
block_30:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173AC8) {
        goto block_34;
    }
block_31:
    clear_mask = 0xFFFB0000U;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xDU;
    state_changed = 1;
block_32:
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = (s8)state_changed;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & (clear_mask | 0xFFFFU));
    return;
block_33:
block_34:
block_35:
    if (func_800AA924(actor, context, sprite, &D_80173AC0) != 0) {
        goto block_150;
    }
block_36:
block_37:
    if (D_80083462 & 0x2000) {
        goto block_77;
    }
    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x100)) {
        goto block_40;
    }
    func_800AA258(actor, context, sprite, entity);
    return;
block_40:
    {
        register s32 idle_state ASM_REG("$2") = 0xE;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        anim_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8;
        if (anim_state == idle_state) {
            goto block_56;
        }
    }
    anim_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
    if (anim_state == 1) {
        goto block_49;
    }
    if ((s32) anim_state >= 2) {
        goto block_45;
    }
    if (anim_state == 0) {
        goto block_48;
    }
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
    goto block_55;
block_45:
    if (anim_state == 2) {
        goto block_50;
    }
    if (anim_state == 3) {
        goto block_51;
    }
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
    goto block_55;
block_48:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739A0) {
        (*(u8 **)((u8 *)sprite + 0x2C)) = &D_801739A0;
        func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_801739A0), 0);
    }
    goto block_54;
block_49:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739A8) {
        (*(u8 **)((u8 *)sprite + 0x2C)) = &D_801739A8;
        func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_801739A8), 0);
    }
    goto block_54;
block_50:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739B0) {
        (*(u8 **)((u8 *)sprite + 0x2C)) = &D_801739B0;
        func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_801739B0), 0);
    }
    goto block_54;
block_51:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739B8) {
        (*(u8 **)((u8 *)sprite + 0x2C)) = &D_801739B8;
        func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_801739B8), 0);
    }
block_54:
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
block_55:
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x1F) + 0xF);
block_56:
    ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF3);
    if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 == 0) {
        goto block_69;
    }
    active_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
    if (active_pose == 1) {
        goto block_65;
    }
    if ((s32) active_pose >= 2) {
        goto block_61;
    }
    if (active_pose == 0) {
        goto block_64;
    }
    goto block_69;
block_61:
    if (active_pose == 2) {
        goto block_66;
    }
    if (active_pose == 3) {
        goto block_67;
    }
    goto block_69;
block_64:
    if (func_800AA6B4(actor, context, sprite, &D_80173A00) != 0) {
        goto block_150;
    }
    goto block_69;
block_65:
    if (func_800AA6B4(actor, context, sprite, &D_80173A08) != 0) {
        goto block_150;
    }
    goto block_69;
block_66:
    if (func_800AA6B4(actor, context, sprite, &D_80173A10) != 0) {
        goto block_150;
    }
    goto block_69;
block_67:
    if (func_800AA6B4(actor, context, sprite, &D_80173A18) != 0) {
        goto block_150;
    }
block_69:
    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x80000)) {
        goto block_71;
    }
    func_800AA888(actor, context, sprite, entity);
    func_8016D4B8(actor, context, sprite, entity);
    return;
block_71:
    if ((func_800A1C58(entity) << 0x10) == 0) {
        goto block_77;
    }
    turn_state = &D_80083460;
    if (((S_8016A36C_4 *)turn_state)->unk_0C != entity) {
        goto block_150;
    }
    if (((S_8016A36C_4 *)turn_state)->unk_10 != 0) {
        goto block_150;
    }
    if ((s16) ((S_8016A36C_4 *)turn_state)->unk_0A >= 2) {
        goto block_150;
    }
    if (((S_8016A36C_4 *)turn_state)->unk_02 & 8) {
        goto block_150;
    }
    ((Rec_D_800E3D7C *)entity)->unk_18 = 0;
    ((S_8016A36C_4 *)turn_state)->unk_0C = 0;
block_77:
    room_id = func_8009FB34(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v);
    ((S_8016A36C_3 *)sprite)->unk_26 = room_id;
    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 <= 0) {
        goto block_108;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x20) {
        goto block_94;
    }
    if (((S_8016A36C_3 *)sprite)->unk_24.at00u.v == D_80082EA4) {
        goto block_107;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000) {
        goto block_87;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_83;
    }
    if ((func_8009A180(entity, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) != 0) {
        goto block_150;
    }
block_83:
    if (!(D_80013714 & 8)) {
        goto block_85;
    }
    func_801732A4(actor, context, sprite);
    ((Rec_D_800E3D7C *)entity)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)entity)->unk_71.as_u8 & 0x7F);
    func_800A9A0C(entity);
    ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x7FFF);
    return;
block_85:
    if ((func_8016BBC0(actor, context, sprite, 0) << 0x10) == 0) {
        goto block_150;
    }
    action_flags = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v | 0x4000;
    ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v = action_flags;
    if (!(action_flags & 0x8000)) {
        goto block_107;
    }
block_87:
    action_id = ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (action_id - 1) >= 0xCU) {
        goto block_106;
    }
    (void)action_labels; goto *D_80164918[(u32)((action_id) - 1)];
jt_c8:
    if ((func_8016B954(actor, context, sprite, entity) << 0x10) != 0) {
        goto block_150;
    }
    func_8016BAE0(actor, context, sprite, entity);
    return;
jt_c9:
    func_8016D6F8(actor, context, sprite, entity);
    return;
jt_c10:
    func_8016DAC0(actor, context, sprite, entity);
    return;
jt_c5:
jt_c6:
jt_c7:
    {
        u8 *home = (u8 *)&D_80082E80;
        s32 angle = func_800A0818(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v, ((S_8016A36C_6 *)home)->unk_24, ((S_8016A36C_6 *)home)->unk_25, &distance);
        void *owner = D_800814A8;
        ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = (s16)angle;
        if (((S_8016A36C_7 *)owner)->unk_9A == 0x11) {
            goto block_95;
        }
    }
jt_c12:
block_94:
    func_800A9A0C(entity);
    return;
jt_c1:
jt_c2:
jt_c3:
block_95:
    action_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
    if (action_pose == 1) {
        goto block_103;
    }
    if ((s32) action_pose >= 2) {
        goto block_99;
    }
    if (action_pose == 0) {
        goto block_102;
    }
    return;
block_99:
    if (action_pose == 2) {
        goto block_104;
    }
    if (action_pose == 3) {
        goto block_105;
    }
    return;
block_102:
    func_800AAF00(actor, context, sprite, &D_801739E0, &func_8016A36C);
    return;
block_103:
    func_800AAF00(actor, context, sprite, &D_801739E8, &func_8016A36C);
    return;
block_104:
    func_800AAF00(actor, context, sprite, &D_801739F0, &func_8016A36C);
    return;
block_105:
    func_800AAF00(actor, context, sprite, &D_801739F8, &func_8016A36C);
    return;
jt_c4:
jt_c11:
block_106:
block_107:
    func_8016B230(actor, context, sprite, entity);
    return;
block_108:
    entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32;
    if (entity_flags & 0x2000) {
        goto block_116;
    }
    if (D_80013714 & 8) {
        goto block_116;
    }
    if (room_id < 0) {
        goto block_112;
    }
    if (D_800E2970[room_id].flags & 2) {
        goto block_116;
    }
block_112:
    if (entity_flags & 0x430) {
        goto block_116;
    }
    {
        u8 *home = (u8 *)&D_80082E80;
        if ((func_8009FD7C(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v, ((S_8016A36C_6 *)home)->unk_24, ((S_8016A36C_6 *)home)->unk_25) << 0x10) == 0) {
            goto block_115;
        }
        ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v, ((S_8016A36C_6 *)home)->unk_24, ((S_8016A36C_6 *)home)->unk_25, &distance);
    }
block_115:
block_116:
    if (D_80083462 & 0x2000) {
        goto block_150;
    }
    if (((S_8016A36C_3 *)sprite)->unk_14 & 0x40) {
        goto block_150;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x20) {
        goto block_150;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (D_80013714 & 8) {
        goto block_150;
    }
    idle_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
    if (idle_pose == 1) {
        goto block_128;
    }
    if ((s32) idle_pose >= 2) {
        goto block_124;
    }
    if (idle_pose == 0) {
        goto block_127;
    }
    return;
block_124:
    if (idle_pose == 2) {
        goto block_131;
    }
    if (idle_pose == 3) {
        goto block_140;
    }
    return;
block_127:
    next_table = &D_801739A0;
    current_table = ((S_8016A36C_3 *)sprite)->unk_2C.p2;
    goto block_129;
block_128:
    current_table = ((S_8016A36C_3 *)sprite)->unk_2C.p2;
    next_table = &D_801739A8;
block_129:
    anim_table = next_table;
    if (current_table == anim_table) {
        goto block_150;
    }
block_130:
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = anim_table;
    table_index = ((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7;
    table_index += (unsigned long)anim_table;
    func_80047784(sprite, *(u8 *)table_index, 0);
    return;
block_131:
    pose2_table = ((S_8016A36C_3 *)sprite)->unk_2C.p;
    if (pose2_table == &D_801739B0) {
        goto block_135;
    }
    if (pose2_table == &D_80173A50) {
        goto block_134;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_801739B0;
    func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_801739B0), 0);
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
block_134:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_801739B0) {
        goto block_137;
    }
block_135:
    pose2_idle_ticks = ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = (u16) (pose2_idle_ticks + 1);
    if ((s16) pose2_idle_ticks < ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v) {
        goto block_137;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80173A50;
    func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_80173A50), 0);
    func_800478B8(sprite);
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
block_137:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173A50) {
        goto block_150;
    }
    pose2_anim_ticks = ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = (u16) (pose2_anim_ticks + 1);
    if ((s16) pose2_anim_ticks < 0x12) {
        goto block_150;
    }
    anim_table = &D_801739B0;
    goto block_149;
block_140:
    pose3_table = ((S_8016A36C_3 *)sprite)->unk_2C.p;
    idle_table = &D_801739B8;
    if (pose3_table == idle_table) {
        goto block_144;
    }
    if (pose3_table == &D_80173A58) {
        goto block_143;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = idle_table;
    func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + idle_table), 0);
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
block_143:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p != idle_table) {
        goto block_146;
    }
block_144:
    pose3_idle_ticks = ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = (u16) (pose3_idle_ticks + 1);
    if ((s16) pose3_idle_ticks < ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v) {
        goto block_146;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80173A58;
    func_80047784(sprite, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_80173A58), 0);
    func_800478B8(sprite);
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
block_146:
    if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173A58) {
        goto block_150;
    }
    pose3_anim_ticks = ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = (u16) (pose3_anim_ticks + 1);
    if ((s16) pose3_anim_ticks < 0x12) {
        goto block_150;
    }
    anim_table = &D_801739B8;
block_149:
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = anim_table;
    table_index = ((s32) (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7;
    table_index += (unsigned long)anim_table;
    func_80047784(sprite, *(u8 *)table_index, 0);
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
block_150:
    return;
}
