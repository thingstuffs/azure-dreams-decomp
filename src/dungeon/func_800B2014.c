#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Coord;

extern s32 D_80083460[3];
extern u8 *D_800E3D7C;
extern s32 D_800835E8[];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern s32 D_800814A0;
M2C_UNK func_8003E188();
M2C_UNK func_80042640();
M2C_UNK func_800424E0();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_80099734();
M2C_UNK func_800997FC();
s32 func_8009B88C();
s32 *(*func_800A0B94())(M2C_UNK, s16, s16, s16);
s32 func_800A1618();
M2C_UNK func_800A1D4C();
s32 func_800A384C();
s32 func_800A3D18();
M2C_UNK func_800A48F0();
M2C_UNK func_800A5720();
M2C_UNK func_800A90E8();
void func_8009A180(s32 *, u8 *);
M2C_UNK func_800B7A30();
M2C_UNK func_800B7B18();
extern M2C_UNK D_800E0A42;
extern M2C_UNK D_800E0A56;
extern M2C_UNK D_800E0A6A;


typedef struct S_800B7774_0_pre {
    u16 unk_00;
} S_800B7774_0_pre;   /* the 0x2 bytes before arg0 in func_800B7774, addressed as arg0[-1] */

typedef struct S_800B7774_0 {
    u8 unk_00;
    u8 pad_01[0x3];
    s32 * unk_04;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
    s16 unk_0E;
} S_800B7774_0;   /* arg0 in func_800B7774 */

typedef struct S_800B7774_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_800B7774_1;   /* controls_base in func_800B7774 */

typedef struct S_800B7774_2_pre {
    s32 unk_00;
    u8 pad_04[0x10];
} S_800B7774_2_pre;   /* the 0x14 bytes before temp_v0 in func_800B7774, addressed as temp_v0[-1] */

typedef struct S_800B7774_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x1];
    u8 unk_13;
    u8 pad_14[0x4];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x17];
    u8 unk_43;
    u8 pad_44[0x2];
    union { u16 u; s16 s; } unk_46;   /* accessed as both */
    u8 pad_48[0x18];
    s32 unk_60;
} S_800B7774_2;   /* temp_v0 in func_800B7774 */


typedef struct S_800B7774_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800B7774_4;   /* arg2 in func_800B7774 */

typedef struct S_800B7774_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800B7774_5;   /* state_base in func_800B7774 */

typedef struct S_800B7774_6_pre {
    u16 unk_00;
} S_800B7774_6_pre;   /* the 0x2 bytes before temp_v0_6 in func_800B7774, addressed as temp_v0_6[-1] */

void func_800B7774(void *arg0, Coord *arg1, void *arg2) {
    s16 sp18;
    s16 sp1A;
    s32 held_x;
    s32 held_y;
    u16 sp1C;
    s16 temp_v1;
    s32 *temp_v0;
    s32 *temp_v0_6;
    s32 temp_a1;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 var_v1;
    u16 temp_v0_5;
    S_8003E2D8 *state_base;
    Coord *coord_arg = arg1;

    state_base = &D_80083160;
    temp_v1 = ((S_800B7774_0 *)arg0)->unk_0A.s;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 != 0) {
            void *null_arg;
            null_arg = NULL;
            func_800B7B18();
            return;
        }
        goto state_0;
    }
    if (temp_v1 == 2) {
        goto state_2;
    }
    func_800B7B18(state_base);
    return;

state_0:
    if ((func_8009B88C(0, (u16) coord_arg->x >> 6, (u16) coord_arg->y >> 6, &sp18, &sp1A) << 0x10) == 0) {
        {
        u8 *controls_base = (u8 *)&D_80083460;
        ((S_800B7774_1 *)controls_base)->unk_0A = (u16) (((S_800B7774_1 *)controls_base)->unk_0A - 1);
        }
        func_800997FC(&D_800E0A42);
        (*(u16 *)((u8 *)arg0 + (-2))) = (u16) (((S_800B7774_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
        return;
    }
    held_x = sp18;
    held_y = sp1A;
    temp_v0 = func_800A0B94(((S_800B7774_0 *)arg0)->unk_00, func_800A1618(((S_800B7774_0 *)arg0)->unk_00, 2), 1)(2, held_x, held_y, (s16) (coord_arg->z - 0x20));
    ((S_800B7774_0 *)arg0)->unk_04 = temp_v0;
    if (temp_v0 != NULL) {
        func_8003E188(((S_800B7774_2 *)temp_v0)->unk_13, 0);
        func_800A90E8(arg0);
        func_80042640(temp_v0, ((S_800B7774_2 *)temp_v0)->unk_13);
        func_800424E0(temp_v0, ((S_800B7774_2 *)temp_v0)->unk_13, 0);
        ((S_800B7774_2 *)temp_v0)->unk_43 = 0xFE;
        func_800A48F0(temp_v0, 0x1B, 0);
        {
        register s32 clamp_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 first_call_arg ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
        s32 first_call_mode;
        s32 raw_first_result;
        clamp_value = ((Rec_D_800E3D7C *)D_800E3D7C)->unk_10.at01_u8.v + 0x32;
        var_v1 = clamp_value;
        ASM_KEEP(clamp_value);   /* MATCH pin: retail register colouring depends on it */
        if (clamp_value >= 0x64) {
            var_v1 = 0x63;
        }
        {
        s32 *scan_arg = D_800835E8;
        temp_v1_2 = D_800835E8[var_v1];
        ((S_800B7774_2 *)temp_v0)->unk_18 = temp_v1_2;
        if ((u32) temp_v1_2 >= (u32) D_800835E8[((S_800B7774_2 *)temp_v0)->unk_11]) {
            s32 *loop_base = D_800835E8;
            do {
                func_800A1D4C(temp_v0, 0);
            } while ((u32) loop_base[((S_800B7774_2 *)temp_v0)->unk_11] <= (u32) ((S_800B7774_2 *)temp_v0)->unk_18);
            scan_arg = temp_v0;
        }
        raw_first_result = func_800990FC(scan_arg);
        }
        first_call_mode = 8;
        ASM_KEEP(first_call_mode);   /* MATCH pin: retail schedule: same instructions, different order without it */
        first_call_arg = raw_first_result;
        ASM_KEEP(first_call_arg);   /* MATCH pin: retail register colouring depends on it */
        temp_v0_3 = first_call_arg;
        func_80099290(func_80099194(&D_800E0A6A, func_8009929C(0xA, func_80099734(temp_v0, func_80099194(&D_800E0A56, func_8009929C(first_call_mode, first_call_arg))))));
        }
        func_800A5720(temp_v0_3);
        {
        s32 *call_obj;
        u8 *call_state;
        call_obj = temp_v0;
        call_state = D_800E3D7C;
        ((S_800B7774_0 *)arg0)->unk_0C = 0x10U;
        func_8009A180(call_obj, call_state);
        }
        func_800B7A30();
        return;
    }
    goto block_30;

state_1:
    temp_v0_5 = ((S_800B7774_0 *)arg0)->unk_0C - 1;
    ((S_800B7774_0 *)arg0)->unk_0C = temp_v0_5;
    if (((temp_v0_5 << 0x10) > 0) && !(((S_800B7774_4 *)arg2)->unk_14 & 0x8000) && (((S_800B7774_5 *)state_base)->unk_10 == 0)) {
        goto block_30;
    }
    ((S_800B7774_0 *)arg0)->unk_0A.u = (u16) (((S_800B7774_0 *)arg0)->unk_0A.u + 1);
    func_800B7B18(state_base);
    return;

state_2:
    temp_v0 = ((S_800B7774_0 *)arg0)->unk_04;
    if (((S_800B7774_0 *)arg0)->unk_0E == 0) {
        ((S_800B7774_2 *)temp_v0)->unk_60 = func_800A3D18(((S_800B7774_2_pre *)temp_v0)[-1].unk_00, temp_v0, 2);
        {
        u8 *controls_base = (u8 *)&D_80083460;
        ((S_800B7774_1 *)controls_base)->unk_02 = (u16) (((S_800B7774_1 *)controls_base)->unk_02 | 2);
        }
        temp_a1 = ((S_800B7774_2 *)temp_v0)->unk_60;
        ((S_800B7774_2 *)temp_v0)->unk_46.u = 0x800C;
        if (temp_a1 != 0) {
            temp_v0_4 = func_800A384C(temp_v0, temp_a1, &sp1C, 1);
            ((S_800B7774_2 *)temp_v0)->unk_2A = sp1C;
            if ((s16) temp_v0_4 >= 0) {
                ((S_800B7774_2 *)temp_v0)->unk_46.s = (s16) (temp_v0_4 | 0x8000);
            }
        }
    }
    ((Rec_D_800E3D7C *)D_800E3D7C)->unk_110 = 0;
    (*(s32 *)((u8 *)temp_v0 + (0x1C))) = (s32) (((S_800B7774_2 *)temp_v0)->unk_1C | 0x400000);
    {
    u8 *controls_base = (u8 *)&D_80083460;
    ((S_800B7774_1 *)controls_base)->unk_0A = (u16) (((S_800B7774_1 *)controls_base)->unk_0A - 1);
    }
    (*(u16 *)((u8 *)arg0 + (-2))) = (u16) (((S_800B7774_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0 = D_800814A0 | 0x8000;
block_30:
    temp_v0_6 = ((S_800B7774_0 *)arg0)->unk_04;
    if ((temp_v0_6 != NULL) && (((S_800B7774_6_pre *)temp_v0_6)[-1].unk_00 & 0x8000)) {
        ((S_800B7774_0 *)arg0)->unk_0E = 1;
    }
}
