#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80091C64_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x76];
    u16 unk_11A;
} S_80091C64_0;   /* arg0 in func_80091C64 */

typedef struct S_80091C64_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_80091C64_1;   /* arg3 in func_80091C64 */

typedef struct S_80091C64_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_80091C64_2;   /* arg1 in func_80091C64 */


typedef struct S_80091C64_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80091C64_4;   /* var_v1 in func_80091C64 */


extern void *D_800889A8[];
void func_80048A44();
s32 func_800644B8();
s32 func_80064584();
M2C_UNK func_800A2B04();
M2C_UNK func_800A56E0();
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_8008EAC8;
extern u8 D_800DD038[];
extern u8 D_800DD058[];

void func_80091C64(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    M2C_UNK *var_v0;
    M2C_UNK *var_v1;
    s16 temp_a0;
    u8 temp_v1;
    u8 temp_state;
    register u16 temp_duration ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_byte;
    s32 temp_coord;
    s32 temp_y_work;
    register s32 temp_y_num ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;

    temp_v1 = ((S_80091C64_0 *)arg0)->unk_9B;
    if (temp_v1 >= 5U) {
        goto block_19;
    }
    (void)jt_keep; goto *D_800889A8[(u32)(temp_v1)];
jt_c0:
    temp_v0 = ((S_80091C64_0 *)arg0)->unk_96.s - 1;
    ((S_80091C64_0 *)arg0)->unk_96.s = temp_v0;
    if ((s16) temp_v0 >= 9) {
        goto block_19;
    }
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD038;
    func_80048A44(arg2, D_800DD038[((s32) (D_80083228 + ((S_80091C64_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    ((S_80091C64_0 *)arg0)->unk_98 = (u16) (((S_80091C64_0 *)arg0)->unk_98 | 0xC);
    ((S_80091C64_0 *)arg0)->unk_9B = (u8) (((S_80091C64_0 *)arg0)->unk_9B + 1);
    func_800A56E0(0x701);
    return;
jt_c1:
    if (((S_80091C64_0 *)arg0)->unk_96.u == 0) {
        goto block_6;
    }
    ((S_80091C64_2 *)arg1)->unk_00.at00.v = (s32) (((S_80091C64_2 *)arg1)->unk_00.at00.v + (func_80064584(((S_80091C64_1 *)arg3)->unk_2A + 0x400) << 6));
    ((S_80091C64_2 *)arg1)->unk_04.at00.v = (s32) (((S_80091C64_2 *)arg1)->unk_04.at00.v + (func_800644B8(((S_80091C64_1 *)arg3)->unk_2A + 0x400) << 6));
    ((S_80091C64_0 *)arg0)->unk_92 = (s16) ((s32) (0 - func_800644B8((s16) ((S_80091C64_0 *)arg0)->unk_96.s << 8)) >> 8);
block_6:
    temp_v0_2 = ((S_80091C64_0 *)arg0)->unk_96.s - 1;
    ((S_80091C64_0 *)arg0)->unk_96.s = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto block_19;
    }
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD058;
    func_80048A44(arg2, D_800DD058[((s32) (D_80083228 + ((S_80091C64_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    temp_state = ((S_80091C64_0 *)arg0)->unk_9B;
    ((S_80091C64_0 *)arg0)->unk_92 = 0;
    goto block_10;
jt_c2:
    if (D_8008346C != 0) {
        goto block_19;
    }
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD038;
    func_80048A44(arg2, D_800DD038[((s32) (D_80083228 + ((S_80091C64_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    temp_state = ((S_80091C64_0 *)arg0)->unk_9B;
    temp_duration = 8U;
    ((S_80091C64_0 *)arg0)->unk_96.s = temp_duration;
block_10:
    ((S_80091C64_0 *)arg0)->unk_9B = (u8) (temp_state + 1);
    return;
jt_c3:
    temp_a0 = (s16) ((S_80091C64_0 *)arg0)->unk_96.s;
    if (temp_a0 == 0) {
        goto block_13;
    }
    temp_byte = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
    temp_coord = ((S_80091C64_2 *)arg1)->unk_00.at02.v - 0x20;
    ((S_80091C64_2 *)arg1)->unk_00.at00.v = (s32) (((S_80091C64_2 *)arg1)->unk_00.at00.v + ((temp_byte - temp_coord) << 0x10) / temp_a0);
    temp_y_num = ((Rec_D_80082E80 *)arg2)->unk_25;
    temp_y_work = ((S_80091C64_2 *)arg1)->unk_04.at02.v;
    temp_y_num <<= 6;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    temp_y_work -= 0x20;
    temp_y_num = (temp_y_num - temp_y_work) << 0x10;
    temp_y_work = ((S_80091C64_0 *)arg0)->unk_96.u;
    temp_y_num /= temp_y_work;
    temp_y_work = ((S_80091C64_2 *)arg1)->unk_04.at00.v + temp_y_num;
    ((S_80091C64_2 *)arg1)->unk_04.at00.v = temp_y_work;
    ((S_80091C64_0 *)arg0)->unk_92 = (s16) ((s32) (0 - func_800644B8((s16) ((S_80091C64_0 *)arg0)->unk_96.s << 8)) >> 8);
block_13:
    temp_v0_3 = ((S_80091C64_0 *)arg0)->unk_96.s - 1;
    ((S_80091C64_0 *)arg0)->unk_96.s = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_19;
    }
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    ((S_80091C64_0 *)arg0)->unk_92 = 0;
    ((S_80091C64_0 *)arg0)->unk_9B = (u8) (((S_80091C64_0 *)arg0)->unk_9B + 1);
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD058;
    func_80048A44(arg2, D_800DD058[((s32) (D_80083228 + ((S_80091C64_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    return;
jt_c4:
    var_v1 = &D_80083460;
    ((S_80091C64_4 *)var_v1)->unk_0A = (u16) (((S_80091C64_4 *)var_v1)->unk_0A - 1);
    ((S_80091C64_1 *)arg3)->unk_2A = (s16) ((S_80091C64_0 *)arg0)->unk_11A;
    if (!(((S_80091C64_1 *)arg3)->unk_1C & 0x100000)) {
        goto block_17;
    }
    var_v0 = &D_8008EAC8;
    goto block_18;
block_17:
    var_v0 = &D_8008ACDC;
block_18:
    ((S_80091C64_0 *)arg0)->unk_8C = var_v0;
    ((S_80091C64_1 *)arg3)->unk_14 = (s32) (((S_80091C64_1 *)arg3)->unk_14 & 0xFFFDFFFF);
    ((S_80091C64_0 *)arg0)->unk_98 = (u16) (((S_80091C64_0 *)arg0)->unk_98 & 0xFFF3);
    ((S_80091C64_0 *)arg0)->unk_A2 = (u16) (((S_80091C64_0 *)arg0)->unk_A2 | 0x10);
block_19:
    return;
}
