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

void func_801711A4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    M2C_UNK sp18;
    M2C_UNK *var_v0;
    s32 temp_a1;
    s32 temp_v0_3;
    s8 temp_v0;
    s16 temp_calc;
    u16 temp_v0_2;
    void *temp_env;
    DungeonEnv *dungeon_env;
    M2C_UNK *sp18p;
    EmptyArg empty_arg;

    if (!(D_80083462 & 0x1000)) {
        goto block_3;
    }
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xEU;
    func_801716CC();
    goto block_55;
block_3:
    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v != 0) {
        goto block_7;
    }
    func_800AA79C(arg0, arg1, arg2, arg3);
    if (((S_801711A4_2 *)arg2)->unk_2C == &D_801741CC) {
        goto block_55;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_801741C4;
    func_80047784(arg2, *(((u8 *)&D_801741C4) + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7)), 0);
    goto block_55;
block_7:
    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x200)) {
        goto block_12;
    }
    {
        void *common_a0 = arg0;
        if (((S_801711A4_2 *)arg2)->unk_2C != &D_801741CC) {
            goto block_11;
        }
        {
            void *saved0 = arg0;
            register void *saved2 ASM_REG("$18") = arg3;   /* MATCH pin: load-bearing for the whole function shape */
            s32 mask = (s32)0xFFFB0000;
            s32 flags;
            ((S_801711A4_3 *)saved0)->unk_9A = 0xDU;
            ((S_801711A4_3 *)saved0)->unk_9B = 1;
            ((S_801711A4_3 *)saved0)->unk_8C = 0;
            flags = ((S_801711A4_4 *)saved2)->unk_1C;
            mask |= 0xFFFF;
            flags &= mask;
            ((S_801711A4_4 *)saved2)->unk_1C = flags;
            goto block_55;
        }
block_11:
        if (func_800AA924(common_a0, arg1, arg2, &D_801741C4) != 0) {
            goto block_55;
        }
    }
block_12:
    if (D_80083462 & 0x2000) {
        goto block_27;
    }
    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x100)) {
        goto block_16;
    }
    func_800AA258(arg0, arg1, arg2, arg3);
    goto block_55;
block_16:
    if (((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 == 0xE) {
        goto block_18;
    }
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xEU;
block_18:
    if (((S_801711A4_2 *)arg2)->unk_2C == &D_8017418C) {
        goto block_20;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_8017418C;
    func_80047784(arg2, *(((u8 *)&D_8017418C) + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7)), 0);
    ((S_801711A4_2 *)arg2)->unk_05 = 1;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_AE = 0;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_A8 = 0;
block_20:
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 | 0x40000);
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0xFFF7);
    if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 == 0) {
        goto block_22;
    }
    if (func_800AA6B4(arg0, arg1, arg2, &D_80174194) != 0) {
        goto block_55;
    }
block_22:
    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x80000)) {
        goto block_25;
    }
    func_800AA888(arg0, arg1, arg2, arg3);
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_A8 = 0;
    func_80173D10(arg0, arg1, arg2, arg3);
    goto block_55;
block_25:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_27;
    }
    func_800AAB10(arg0, arg1, arg2, arg3);
block_27:
    temp_v0 = func_8009FB34(((S_801711A4_2 *)arg2)->unk_24.at00.v, ((S_801711A4_2 *)arg2)->unk_24.at01.v);
    ((S_801711A4_2 *)arg2)->unk_26 = temp_v0;
    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 <= 0) {
        goto block_49;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x20) {
        goto block_41;
    }
    if (((S_801711A4_2 *)arg2)->unk_24.at00u.v == D_80082EA4) {
        goto block_47;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) {
        goto block_35;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_33;
    }
    if ((func_8009A180(arg3, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) != 0) {
        goto block_55;
    }
block_33:
    if ((func_801722B8(arg0, arg1, arg2, 0) << 0x10) == 0) {
        goto block_55;
    }
    temp_v0_2 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v | 0x4000;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = temp_v0_2;
    if (!(temp_v0_2 & 0x8000)) {
        goto block_47;
    }
block_35:
    temp_v0_3 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (temp_v0_3 - 1) >= 0xCU) {
        goto block_46;
    }
    (void)jt_keep; goto *D_80170808[(u32)((temp_v0_3) - 1)];
jt_c8:
jt_c9:
    if ((func_80171FCC(arg0, arg1, arg2, arg3) << 0x10) != 0) {
        goto block_55;
    }
    func_80172190(arg0, arg1, arg2, arg3);
    goto block_55;
jt_c5:
jt_c6:
jt_c7:
    temp_calc = func_800A0818(((S_801711A4_2 *)arg2)->unk_24.at00.v, ((S_801711A4_2 *)arg2)->unk_24.at01.v, D_80082E80.x, D_80082E80.y, &sp18);
    temp_env = D_800814A8;
    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = temp_calc;
    if (((S_801711A4_6 *)temp_env)->unk_9A == 0x11) {
        var_v0 = &D_801711A4;
        goto block_44;
    }
jt_c12:
block_41:
    func_800A9A0C(arg3);
    goto block_55;
jt_c1:
jt_c2:
jt_c3:
    var_v0 = &D_801711A4;
block_44:
    func_800AAF00(arg0, arg1, arg2, &D_801741AC, var_v0);
    goto block_55;
jt_c4:
jt_c10:
jt_c11:
block_46:
block_47:
    func_80171884(arg0, arg1, arg2, arg3);
    goto block_55;
block_49:
    temp_a1 = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
    if (temp_a1 & 0x2000) {
        goto block_55;
    }
    if (temp_v0 < 0) {
        goto block_52;
    }
    if (D_800E2970[temp_v0].flags & 2) {
        goto block_55;
    }
block_52:
    if (temp_a1 & 0x430) {
        goto block_55;
    }
    dungeon_env = &D_80082E80;
    if ((func_8009FD7C(((S_801711A4_2 *)arg2)->unk_24.at00.v, ((S_801711A4_2 *)arg2)->unk_24.at01.v, dungeon_env->x, dungeon_env->y) << 0x10) == 0) {
        goto block_55;
    }
    sp18p = &sp18;
    temp_calc = func_800A0818(((S_801711A4_2 *)arg2)->unk_24.at00.v, ((S_801711A4_2 *)arg2)->unk_24.at01.v, dungeon_env->x, dungeon_env->y, sp18p, ({  empty_arg; }));
    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = temp_calc;
block_55:
    return;
}
