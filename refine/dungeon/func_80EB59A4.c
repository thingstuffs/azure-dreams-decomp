#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"



typedef struct S_801711A4_2 {
    u8 pad_00[0x5];
    s8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    M2C_UNK * unk_2C;
} S_801711A4_2;   /* arg2 in func_801711A4 */

typedef struct S_801711A4_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    s8 unk_9B;
} S_801711A4_3;   /* saved0 in func_801711A4 */

typedef struct S_801711A4_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_801711A4_4;   /* saved2 in func_801711A4 */


typedef struct S_801711A4_6 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801711A4_6;   /* temp_env in func_801711A4 */


typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

typedef struct DungeonEnv {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} DungeonEnv;

typedef struct EmptyArg {
} EmptyArg;

#define M2C_BREAK() 0
#define M2C_SYNC() 0

extern void *D_80170808[];
void func_80047784();
s32 func_8009A180();
s8 func_8009FB34();
s32 func_8009FD7C();
s16 func_800A0818();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAB10();
M2C_UNK func_800AAF00();
M2C_UNK func_801716CC();
M2C_UNK func_80171884();
s32 func_80171FCC();
M2C_UNK func_80172190();
s32 func_801722B8();
M2C_UNK func_80173D10();
extern void *D_800814A8;
extern DungeonEnv D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern M2C_UNK D_801711A4;
extern M2C_UNK D_8017418C;
extern M2C_UNK D_80174194;
extern M2C_UNK D_801741AC;
extern M2C_UNK D_801741C4;
extern M2C_UNK D_801741CC;

/* Updates the actor animation and dispatches dungeon actions based on status and position. */
void func_801711A4(void *actor, M2C_UNK context, void *sprite, void *status) {
    static void *const action_labels[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    M2C_UNK direction_aux;
    M2C_UNK *next_handler;
    s32 status_flags;
    s32 action_id;
    s8 room_id;
    s16 angle;
    u16 action_flags;
    void *active_actor;
    DungeonEnv *dungeon_env;
    M2C_UNK *direction_aux_ptr;
    EmptyArg empty_arg;

    if (!(D_80083462 & 0x1000)) {
        goto block_3;
    }
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
    func_801716CC(actor, context, sprite, status);
    goto block_55;
block_3:
    if (((Rec_D_800E3D7C *)status)->unk_24.at01_u8.v != 0) {
        goto block_7;
    }
    func_800AA79C(actor, context, sprite, status);
    if (((S_801711A4_2 *)sprite)->unk_2C == &D_801741CC) {
        goto block_55;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_801741C4;
    func_80047784(sprite, *(((u8 *)&D_801741C4) + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)status)->unk_2A.as_s16 + 0x100) >> 9) & 7)), 0);
    goto block_55;
block_7:
    if (!(((Rec_D_800E3D7C *)status)->unk_1C.as_s32 & 0x200)) {
        goto block_12;
    }
    {
        void *action_actor = actor;
        if (((S_801711A4_2 *)sprite)->unk_2C != &D_801741CC) {
            goto block_11;
        }
        {
            void *reset_actor = actor;
            register void *reset_status ASM_REG("$18") = status;   /* MATCH pin: load-bearing for the whole function shape */
            s32 clear_mask = (s32)0xFFFB0000;
            s32 flags;
            ((S_801711A4_3 *)reset_actor)->unk_9A = 0xDU;
            ((S_801711A4_3 *)reset_actor)->unk_9B = 1;
            ((S_801711A4_3 *)reset_actor)->unk_8C = 0;
            flags = ((S_801711A4_4 *)reset_status)->unk_1C;
            clear_mask |= 0xFFFF;
            flags &= clear_mask;
            ((S_801711A4_4 *)reset_status)->unk_1C = flags;
            goto block_55;
        }
block_11:
        if (func_800AA924(action_actor, context, sprite, &D_801741C4) != 0) {
            goto block_55;
        }
    }
block_12:
    if (D_80083462 & 0x2000) {
        goto block_27;
    }
    if (!(((Rec_D_800E3D7C *)status)->unk_1C.as_s32 & 0x100)) {
        goto block_16;
    }
    func_800AA258(actor, context, sprite, status);
    goto block_55;
block_16:
    if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 == 0xE) {
        goto block_18;
    }
    ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
block_18:
    if (((S_801711A4_2 *)sprite)->unk_2C == &D_8017418C) {
        goto block_20;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_8017418C;
    func_80047784(sprite, *(((u8 *)&D_8017418C) + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)status)->unk_2A.as_s16 + 0x100) >> 9) & 7)), 0);
    ((S_801711A4_2 *)sprite)->unk_05 = 1;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_AE = 0;
    ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
block_20:
    ((Rec_D_800E3D7C *)status)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)status)->unk_1C.as_s32 | 0x40000);
    ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF7);
    if (((Rec_D_800E3D7C *)status)->unk_64.as_s16 == 0) {
        goto block_22;
    }
    if (func_800AA6B4(actor, context, sprite, &D_80174194) != 0) {
        goto block_55;
    }
block_22:
    if (!(((Rec_D_800E3D7C *)status)->unk_1C.as_s32 & 0x80000)) {
        goto block_25;
    }
    func_800AA888(actor, context, sprite, status);
    ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
    func_80173D10(actor, context, sprite, status);
    goto block_55;
block_25:
    if ((func_800A1C58(status) << 0x10) == 0) {
        goto block_27;
    }
    func_800AAB10(actor, context, sprite, status);
block_27:
    room_id = func_8009FB34(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v);
    ((S_801711A4_2 *)sprite)->unk_26 = room_id;
    if (((Rec_D_800E3D7C *)status)->unk_6D.as_s8 <= 0) {
        goto block_49;
    }
    if (((Rec_D_800E3D7C *)status)->unk_1C.as_s32 & 0x20) {
        goto block_41;
    }
    if (((S_801711A4_2 *)sprite)->unk_24.at00u.v == D_80082EA4) {
        goto block_47;
    }
    if (((Rec_D_800E3D7C *)status)->unk_44.at02_u16.v & 0x8000) {
        goto block_35;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_33;
    }
    if ((func_8009A180(status, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) != 0) {
        goto block_55;
    }
block_33:
    if ((func_801722B8(actor, context, sprite, 0) << 0x10) == 0) {
        goto block_55;
    }
    action_flags = ((Rec_D_800E3D7C *)status)->unk_44.at02_u16.v | 0x4000;
    ((Rec_D_800E3D7C *)status)->unk_44.at02_u16.v = action_flags;
    if (!(action_flags & 0x8000)) {
        goto block_47;
    }
block_35:
    action_id = ((Rec_D_800E3D7C *)status)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (action_id - 1) >= 0xCU) {
        goto block_46;
    }
    (void)action_labels; goto *D_80170808[(u32)((action_id) - 1)];
jt_c8:
jt_c9:
    if ((func_80171FCC(actor, context, sprite, status) << 0x10) != 0) {
        goto block_55;
    }
    func_80172190(actor, context, sprite, status);
    goto block_55;
jt_c5:
jt_c6:
jt_c7:
    angle = func_800A0818(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v, D_80082E80.x, D_80082E80.y, &direction_aux);
    active_actor = D_800814A8;
    ((Rec_D_800E3D7C *)status)->unk_2A.as_s16 = angle;
    if (((S_801711A4_6 *)active_actor)->unk_9A == 0x11) {
        next_handler = &D_801711A4;
        goto block_44;
    }
jt_c12:
block_41:
    func_800A9A0C(status);
    goto block_55;
jt_c1:
jt_c2:
jt_c3:
    next_handler = &D_801711A4;
block_44:
    func_800AAF00(actor, context, sprite, &D_801741AC, next_handler);
    goto block_55;
jt_c4:
jt_c10:
jt_c11:
block_46:
block_47:
    func_80171884(actor, context, sprite, status);
    goto block_55;
block_49:
    status_flags = ((Rec_D_800E3D7C *)status)->unk_1C.as_s32;
    if (status_flags & 0x2000) {
        goto block_55;
    }
    if (room_id < 0) {
        goto block_52;
    }
    if (D_800E2970[room_id].flags & 2) {
        goto block_55;
    }
block_52:
    if (status_flags & 0x430) {
        goto block_55;
    }
    dungeon_env = &D_80082E80;
    if ((func_8009FD7C(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v, dungeon_env->x, dungeon_env->y) << 0x10) == 0) {
        goto block_55;
    }
    direction_aux_ptr = &direction_aux;
    angle = func_800A0818(((S_801711A4_2 *)sprite)->unk_24.at00.v, ((S_801711A4_2 *)sprite)->unk_24.at01.v, dungeon_env->x, dungeon_env->y, direction_aux_ptr, ({  empty_arg; }));
    ((Rec_D_800E3D7C *)status)->unk_2A.as_s16 = angle;
block_55:
    return;
}
