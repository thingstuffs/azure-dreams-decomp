#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_800814A8.h"



typedef struct S_801724BC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    M2C_UNK * unk_2C;
} S_801724BC_2;   /* arg2 in func_801724BC */


typedef struct S_801724BC_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801724BC_4;   /* temp_actor in func_801724BC */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *const D_80170808[];
void func_80047784();         /* extern */
s32 func_8009A180();                     /* extern */
s8 func_8009FB34();                           /* extern */
s32 func_8009FD7C();                  /* extern */
s32 func_800A0818();       /* extern */
s32 func_800A1C58();                          /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
M2C_UNK func_800AA258(); /* extern */
s32 func_800AA6B4(); /* extern */
M2C_UNK func_800AA79C(); /* extern */
M2C_UNK func_800AA888(); /* extern */
s32 func_800AA924(); /* extern */
M2C_UNK func_800AAB10(); /* extern */
M2C_UNK func_800AAF00(); /* extern */
void func_80172CC0(void *, M2C_UNK, void *, void *);                            /* extern */
M2C_UNK func_80172F58(); /* extern */
s32 func_80173734(); /* extern */
void func_80173B48(); /* extern */
s32 func_80173EAC(); /* extern */
void func_801759A0(); /* extern */
typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} D_800E2970_entry;
extern D_800E2970_entry D_800E2970[];
extern M2C_UNK D_801724BC;
extern M2C_UNK D_80175DF4;
extern M2C_UNK D_80175DFC;
extern M2C_UNK D_80175E04;
extern M2C_UNK D_80175E24;
extern M2C_UNK D_80175E2C;
extern M2C_UNK D_80175E34;
extern M2C_UNK D_80175E3C;
extern M2C_UNK D_80175E44;
extern M2C_UNK D_80175E4C;
extern M2C_UNK D_80175E54;
extern M2C_UNK D_80175E5C;
extern M2C_UNK D_80175E64;
extern M2C_UNK D_80175E84;
extern M2C_UNK D_80175E8C;
extern M2C_UNK D_80175E94;

/* Updates actor animation, facing, and actions from its dungeon state. */
void func_801724BC(void *actor, M2C_UNK context, void *sprite, void *state) {
    static void *const action_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    M2C_UNK path_info;
    u8 *next_row;
    M2C_UNK *current_row;
    s32 state_flags;
    s32 action_id;
    s32 heading;
    void *player;
    s8 room_id;
    u16 *flags_page;
    u16 action_flags;
    s32 transition_mode;
    s32 action_mode;
    s32 anim_mode;
    s32 idle_mode;
    s32 effect_mode;
    s32 rest_mode;

    if (!(dungeonStatus.flags & 0x1000)) {
        goto block_2;
    }
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
    func_80172CC0(actor, context, sprite, state);
    return;
block_2:
    if (((EntityRec *)state)->tileY != 0) {
        goto block_15;
    }
    func_800AA79C(actor, context, sprite, state);
    anim_mode = ((EntityRec *)state)->unk_48;
    if (anim_mode == 0xE) {
        goto block_11;
    }
    if ((s32) anim_mode >= 0xF) {
        goto block_7;
    }
    if (anim_mode == 0xD) {
        goto block_9;
    }
    return;
block_7:
    if (anim_mode == 0xF) {
        goto block_13;
    }
    return;
block_9:
    if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E54) {
        goto block_109;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80175E84;
    func_80047784(sprite, ((u8 *)&D_80175E84)[((s32) (gameWork.viewAngle + ((EntityRec *)state)->facing + 0x100) >> 9) & 7], 0);
    return;
block_11:
    if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E5C) {
        goto block_109;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80175E8C;
    func_80047784(sprite, ((u8 *)&D_80175E8C)[((s32) (gameWork.viewAngle + ((EntityRec *)state)->facing + 0x100) >> 9) & 7], 0);
    return;
block_13:
    if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E64) {
        goto block_109;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80175E94;
    func_80047784(sprite, ((u8 *)&D_80175E94)[((s32) (gameWork.viewAngle + ((EntityRec *)state)->facing + 0x100) >> 9) & 7], 0);
    return;
block_15:
    if (!(((EntityRec *)state)->flags1C & 0x200)) {
        goto block_32;
    }
    transition_mode = ((EntityRec *)state)->unk_48;
    if (transition_mode == 0xE) {
        goto block_25;
    }
    if ((s32) transition_mode >= 0xF) {
        goto block_20;
    }
    if (transition_mode == 0xD) {
        goto block_22;
    }
    flags_page = (u16 *)0x80080000;
    goto block_33;
block_20:
    if (transition_mode == 0xF) {
        goto block_27;
    }
    flags_page = (u16 *)0x80080000;
    goto block_33;
block_22:
    if (((S_801724BC_2 *)sprite)->unk_2C != &D_80175E54) {
        goto block_24;
    }
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = transition_mode;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
    ((EntityRec *)state)->flags1C = (s32) (((EntityRec *)state)->flags1C & 0xFFFBFFFF);
    return;
block_24:
    if (func_800AA924(actor, context, sprite, &D_80175E84) != 0) {
        goto block_109;
    }
    goto block_32;
block_25:
    if (((S_801724BC_2 *)sprite)->unk_2C == &D_80175E5C) {
        goto block_28;
    }
    if (func_800AA924(actor, context, sprite, &D_80175E8C) != 0) {
        goto block_109;
    }
    goto block_32;
block_27:
    if (((S_801724BC_2 *)sprite)->unk_2C != &D_80175E64) {
        goto block_30;
    }
block_28:
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xDU;
block_29:
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
    ((EntityRec *)state)->flags1C = (s32) (((EntityRec *)state)->flags1C & 0xFFFBFFFF);
    return;
block_30:
    if (func_800AA924(actor, context, sprite, &D_80175E94) != 0) {
        goto block_109;
    }
block_32:
    flags_page = (u16 *)0x80080000;
block_33:
    if (flags_page[0x1A31] & 0x2000) {
        goto block_64;
    }
    if (!(((EntityRec *)state)->flags1C & 0x100)) {
        goto block_36;
    }
    func_800AA258(actor, context, sprite, state);
    return;
block_36:
    if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 == 0xE) {
        goto block_49;
    }
    idle_mode = ((EntityRec *)state)->unk_48;
    switch (idle_mode) {
    case 0xD:
        if (((S_801724BC_2 *)sprite)->unk_2C != &D_80175E24) {
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80175E24;
            func_80047784(sprite, ((u8 *)&D_80175E24)[((s32) (gameWork.viewAngle + ((EntityRec *)state)->facing + 0x100) >> 9) & 7], 0);
        }
        break;
    case 0xE:
        if (((S_801724BC_2 *)sprite)->unk_2C != &D_80175E2C) {
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80175E2C;
            func_80047784(sprite, ((u8 *)&D_80175E2C)[((s32) (gameWork.viewAngle + ((EntityRec *)state)->facing + 0x100) >> 9) & 7], 0);
        }
        break;
    case 0xF:
        if (((S_801724BC_2 *)sprite)->unk_2C != &D_80175E34) {
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80175E34;
            func_80047784(sprite, ((u8 *)&D_80175E34)[((s32) (gameWork.viewAngle + ((EntityRec *)state)->facing + 0x100) >> 9) & 7], 0);
        }
        break;
    default:
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        goto block_49;
    }
block_48:
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
block_49:
    ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF3);
    if (((EntityRec *)state)->unk_64 == 0) {
        goto block_60;
    }
    effect_mode = ((EntityRec *)state)->unk_48;
    if (effect_mode == 0xE) {
        goto block_57;
    }
    if ((s32) effect_mode >= 0xF) {
        goto block_54;
    }
    if (effect_mode == 0xD) {
        goto block_56;
    }
    goto block_60;
block_54:
    if (effect_mode == 0xF) {
        goto block_58;
    }
    goto block_60;
block_56:
    if (func_800AA6B4(actor, context, sprite, &D_80175E3C) != 0) {
        goto block_109;
    }
    goto block_60;
block_57:
    if (func_800AA6B4(actor, context, sprite, &D_80175E44) != 0) {
        goto block_109;
    }
    goto block_60;
block_58:
    if (func_800AA6B4(actor, context, sprite, &D_80175E4C) != 0) {
        goto block_109;
    }
block_60:
    if (!(((EntityRec *)state)->flags1C & 0x80000)) {
        goto block_62;
    }
    func_800AA888(actor, context, sprite, state);
    func_801759A0(actor, context, sprite, state);
    return;
block_62:
    if ((func_800A1C58(state) << 0x10) == 0) {
        goto block_64;
    }
    func_800AAB10(actor, context, sprite, state);
block_64:
    room_id = func_8009FB34(((S_801724BC_2 *)sprite)->unk_24.at00.v, ((S_801724BC_2 *)sprite)->unk_24.at01.v);
    ((S_801724BC_2 *)sprite)->unk_26 = room_id;
    if (((EntityRec *)state)->unk_6D <= 0) {
        goto block_89;
    }
    if (((EntityRec *)state)->flags1C & 0x20) {
        goto block_77;
    }
    if (((S_801724BC_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
        goto block_88;
    }
    if (((EntityRec *)state)->unk_46 & 0x8000) {
        goto block_72;
    }
    if (!(dungeonStatus.flags & 0x2000)) {
        goto block_70;
    }
    if ((func_8009A180(state, ((s32)((EntityRec *)D_800814A8)->unk_58) + 0x20) << 0x10) != 0) {
        goto block_109;
    }
block_70:
    if ((func_80173EAC(actor, context, sprite, 0) << 0x10) == 0) {
        goto block_109;
    }
    action_flags = ((EntityRec *)state)->unk_46 | 0x4000;
    ((EntityRec *)state)->unk_46 = action_flags;
    if (!(action_flags & 0x8000)) {
        goto block_88;
    }
block_72:
    action_id = ((EntityRec *)state)->unk_46 & 0x3FFF;
    if ((u32) (action_id - 1) >= 0xCU) {
        goto block_87;
    }
    (void)action_labels;
    goto *D_80170808[(u32)((action_id) - 1)];
jt_c8:
jt_c9:
    if ((func_80173734(actor, context, sprite, state) << 0x10) != 0) {
        goto block_109;
    }
    func_80173B48(actor, context, sprite, state);
    return;
jt_c5:
jt_c6:
jt_c7:
    {
        heading = func_800A0818(((S_801724BC_2 *)sprite)->unk_24.at00.v, ((S_801724BC_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &path_info);
    }
    player = D_800814A8;
    ((EntityRec *)state)->facing = heading;
    if (((S_801724BC_4 *)player)->unk_9A == 0x11) {
        goto block_78;
    }
jt_c12:
block_77:
    func_800A9A0C(state);
    return;
jt_c1:
jt_c2:
jt_c3:
block_78:
    action_mode = ((EntityRec *)state)->unk_48;
    if (action_mode == 0xE) {
        goto block_85;
    }
    if ((s32) action_mode >= 0xF) {
        goto block_82;
    }
    if (action_mode == 0xD) {
        goto block_84;
    }
    return;
block_82:
    if (action_mode == 0xF) {
        goto block_86;
    }
    return;
block_84:
    func_800AAF00(actor, context, sprite, &D_80175DF4, &D_801724BC);
    return;
block_85:
    func_800AAF00(actor, context, sprite, &D_80175DFC, &D_801724BC);
    return;
block_86:
    func_800AAF00(actor, context, sprite, &D_80175E04, &D_801724BC);
    return;
jt_c4:
jt_c10:
jt_c11:
block_87:
block_88:
    func_80172F58(actor, context, sprite, state);
    return;
block_89:
    state_flags = ((EntityRec *)state)->flags1C;
    if (state_flags & 0x2000) {
        if (dungeonStatus.flags & 0x2000) {
            goto block_109;
        }
        goto block_97;
    }
    if (room_id < 0) {
        goto block_92;
    }
    if (D_800E2970[room_id].flags & 2) {
        if (dungeonStatus.flags & 0x2000) {
            goto block_109;
        }
        goto block_97;
    }
block_92:
    if (state_flags & 0x430) {
        if (dungeonStatus.flags & 0x2000) {
            goto block_109;
        }
        goto block_97;
    }
    {
        if ((func_8009FD7C(((S_801724BC_2 *)sprite)->unk_24.at00.v, ((S_801724BC_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY) << 0x10) == 0) {
            goto block_95;
        }
        ((EntityRec *)state)->facing = func_800A0818(((S_801724BC_2 *)sprite)->unk_24.at00.v, ((S_801724BC_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &path_info);
    }
block_95:
    if (dungeonStatus.flags & 0x2000) {
        goto block_109;
    }
block_97:
    if (((S_801724BC_2 *)sprite)->unk_14 & 0x40) {
        goto block_109;
    }
    rest_mode = ((EntityRec *)state)->unk_48;
    if (rest_mode == 0xE) {
        goto block_105;
    }
    if ((s32) rest_mode >= 0xF) {
        goto block_102;
    }
    if (rest_mode == 0xD) {
        goto block_104;
    }
    return;
block_102:
    if (rest_mode == 0xF) {
        goto block_106;
    }
    return;
block_104:
    current_row = ((S_801724BC_2 *)sprite)->unk_2C;
    next_row = (u8 *)&D_80175E24;
    goto block_107;
block_105:
    current_row = ((S_801724BC_2 *)sprite)->unk_2C;
    next_row = (u8 *)&D_80175E2C;
    goto block_107;
block_106:
    current_row = ((S_801724BC_2 *)sprite)->unk_2C;
    next_row = (u8 *)&D_80175E34;
block_107:
    if (current_row == next_row) {
        goto block_109;
    }
block_108:
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = next_row;
    func_80047784(sprite, *(u8 *)((unsigned long)(((s32) (gameWork.viewAngle + ((EntityRec *)state)->facing + 0x100) >> 9) & 7) + (unsigned long)next_row), 0);
block_109:
    return;
}
