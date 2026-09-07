#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"



typedef struct S_8016B778_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    union { u8 * p; void * p2; } unk_2C;   /* accessed as both */
} S_8016B778_2;   /* arg2 in func_8016B778 */

typedef struct S_8016B778_3 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_8016B778_3;   /* *D_800814A8 in func_8016B778 */

typedef struct S_8016B778_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8016B778_4;   /* global_814A8 in func_8016B778 */

typedef struct S_8016B778_5 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_8016B778_5;   /* entry in func_8016B778 */


extern u16 D_80083462[5];
extern u8 D_801746A4[];
extern u8 D_80174684[];
extern s16 D_80083228[5];
extern volatile s16 D_80013714[8];
extern u8 D_801746C4[];
extern s32 D_80083460[3];
extern u8 D_8017467C[];
extern s32 D_8008346C[];
extern u16 D_80082EA4[8];
extern int D_800814A8[4];
extern u8 D_80082E80[];
extern u8 D_8016B778[];
extern s8 D_800E2970[];
extern void *D_8016A828[];
s8 func_8009FB34();
s32 func_8009FD7C();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
extern void func_800AA258(void *, void *, void *, void *);
s32 func_800AA6B4();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAF00();
extern void func_8016B8AC() __attribute__((noreturn));
M2C_UNK func_8016BD14();
M2C_UNK func_8016BF74();
s32 func_8016C720();
M2C_UNK func_8016C8AC();
s32 func_8016C98C();
M2C_UNK func_8016DAA4();
M2C_UNK func_8016EF10();
extern M2C_UNK D_8017469C;
extern M2C_UNK D_801746BC;

void func_8016B778(Rec_func_800A9E70_arg0 *arg0, M2C_UNK arg1, S_8016B778_2 *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&state_store };
    M2C_UNK sp18;
    s32 temp_a1_value;
    s32 bits_100;
    s32 mask_100;
    s16 a0818_result;
    s32 temp_v0_3;
    s8 temp_v0;
    u16 temp_v0_2;
    u8 *var_v0;
    register void *temp_v1_dispatch ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register u32 temp_v0_page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *temp_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    void *call_obj;
    s32 clear_mask_hi;
    u8 *dungeon_obj;
    u8 *entry_base;
    u8 *entry;
    u8 *global_814A8;
    s32 *global_83460;
    if (!(*D_80083462 & 0x1000)) {
        goto block_3;
    }
    arg0->unk_9A.as_u8 = 0xEU;
    func_8016BD14();
    return;
block_3:
    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x200)) {
        goto block_8;
    }
    if (arg2->unk_2C.p != D_801746A4) {
        goto block_7;
    }
    clear_mask_hi = (s32)0xFFFB0000;
    arg0->unk_9A.as_u8 = 0xDU;
    arg0->unk_9B.as_s8 = 1;
    arg0->unk_8C = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= clear_mask_hi | 0xFFFF;
    return;
block_7:
    if (func_800AA924(arg0, arg1, arg2, &D_8017469C) != 0) {
        goto block_65;
    }
block_8:
    if (*D_80083462 & 0x2000) {
        goto block_33;
    }
    bits_100 = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
    mask_100 = bits_100 & 0x100;
    call_obj = arg0;
    if (!mask_100) {
        goto block_12;
    }
    func_800AA258(call_obj, arg1, arg2, arg3);
    return;
block_12:
    if (arg0->unk_9A.as_u8 != 0xE) {
        if (arg0->unk_B3 == 0) {
            temp_v1_dispatch = arg2->unk_2C.p2;
            ASM_KEEP(temp_v1_dispatch);   /* MATCH pin: retail basic-block layout depends on it */
            temp_v0_page = 0x80170000;
            ASM_KEEP(temp_v0_page);   /* MATCH pin: keeps a constant in a register as retail does */
            temp_a1 = (u8 *)temp_v0_page + 0x467C;
            ASM_TAILSLOT_PIN(temp_a1);   /* MATCH pin: retail delay-slot contents depend on it */
            func_8016B8AC();
            return;
        }
        if (arg2->unk_2C.p != D_80174684) {
            arg2->unk_2C.p = D_80174684;
            func_80047784(arg2, D_80174684[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
        }
state_store:
        arg0->unk_9A.as_u8 = 0xEU;
    }
    arg0->unk_98 = (u16) (arg0->unk_98 & 0xFFF3);
    if (arg0->unk_B4 != 0) {
        goto block_25;
    }
    if ((u16) *D_80013714 & 8) {
        goto block_25;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 == 0) {
        goto block_28;
    }
    if (func_800AA6B4(arg0, arg1, arg2, D_801746C4) == 0) {
        goto block_28;
    }
    return;
block_25:
    if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 == 0) {
        goto block_28;
    }
    global_83460 = D_80083460;
    if (global_83460[4] != (arg3 - 0x20)) {
        goto block_28;
    }
    global_83460[4] &= 0x7FFFFFFF;
block_28:
    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x80000)) {
        goto block_31;
    }
    func_800AA888(arg0, arg1, arg2, arg3);
    func_8016DAA4(arg0, arg1, arg2, arg3);
    arg2->unk_2C.p = D_8017467C;
    func_80047784(arg2, D_8017467C[((s32) (*D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    arg0->unk_90.at00_s32.v = 0;
    return;
block_31:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_33;
    }
    ((Rec_D_800E3D7C *)arg3)->unk_18 = 0;
    *D_8008346C = 0;
block_33:
    temp_v0 = func_8009FB34(arg2->unk_24.at00.v, arg2->unk_24.at01.v);
    arg2->unk_26 = temp_v0;
    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 <= 0) {
        goto block_58;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x20) {
        goto block_50;
    }
    if (arg2->unk_24.at00u.v == *D_80082EA4) {
        goto block_56;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) {
        goto block_44;
    }
    if (!(*D_80083462 & 0x2000)) {
        goto block_39;
    }
    if ((func_8009A180(arg3, ((S_8016B778_3 *)(*D_800814A8))->unk_58 + 0x20) << 0x10) != 0) {
        goto block_65;
    }
block_39:
    if (!((u16) *D_80013714 & 8)) {
        goto block_42;
    }
    func_8016EF10(arg0, arg1, arg2);
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F);
    func_800A9A0C(arg3);
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
    return;
block_42:
    if ((func_8016C98C(arg0, arg1, arg2, 0) << 0x10) == 0) {
        goto block_65;
    }
    temp_v0_2 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v | 0x4000;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = temp_v0_2;
    if (!(temp_v0_2 & 0x8000)) {
        goto block_56;
    }
block_44:
    temp_v0_3 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
    if ((u32) (temp_v0_3 - 1) >= 0xCU) {
        goto block_55;
    }
    (void)jt_keep; goto *D_8016A828[(u32)((temp_v0_3) - 1)];
jt_c8:
jt_c9:
    if ((func_8016C720(arg0, arg1, arg2, arg3) << 0x10) != 0) {
        goto block_65;
    }
    func_8016C8AC(arg0, arg1, arg2, arg3);
    return;
jt_c5:
jt_c6:
jt_c7:
    a0818_result = func_800A0818(arg2->unk_24.at00.v, arg2->unk_24.at01.v, D_80082E80[0x24], D_80082E80[0x25], &sp18);
    global_814A8 = (u8 *)*D_800814A8;
    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = a0818_result;
    if (((S_8016B778_4 *)global_814A8)->unk_9A == 0x11) {
        var_v0 = (u8 *)0x80170000;
        goto block_53_low;
    }
jt_c12:
block_50:
    func_800A9A0C(arg3);
    return;
jt_c1:
jt_c2:
jt_c3:
    var_v0 = (u8 *)0x80170000;
block_53_low:
    var_v0 -= 0x4888;
block_53:
    func_800AAF00(arg0, arg1, arg2, &D_801746BC, var_v0);
    return;
jt_c4:
jt_c10:
jt_c11:
block_55:
block_56:
    func_8016BF74(arg0, arg1, arg2, arg3);
    return;
block_58:
    temp_a1_value = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
    if (temp_a1_value & 0x2000) {
        goto block_65;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    if ((u16) *D_80013714 & 8) {
        goto block_65;
    }
    if (temp_v0 < 0) {
        goto block_62;
    }
    entry_base = D_800E2970;
    entry = (temp_v0 * 0x14) + entry_base;
    if (((S_8016B778_5 *)entry)->unk_0C & 2) {
        goto block_65;
    }
block_62:
    if (temp_a1_value & 0x430) {
        goto block_65;
    }
    dungeon_obj = D_80082E80;
    if ((func_8009FD7C(arg2->unk_24.at00.v, arg2->unk_24.at01.v, dungeon_obj[0x24], dungeon_obj[0x25]) << 0x10) == 0) {
        goto block_65;
    }
    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(arg2->unk_24.at00.v, arg2->unk_24.at01.v, dungeon_obj[0x24], dungeon_obj[0x25], &sp18);
block_65:
    return;
}
