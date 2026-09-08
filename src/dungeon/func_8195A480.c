#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8002589C();        /* extern */
void func_8002600C(void) __attribute__((noreturn)); /* extern */
void func_80026270(void) __attribute__((noreturn)); /* extern */
void func_8002633C() __attribute__((noreturn));        /* extern */
M2C_UNK func_80026548();                 /* extern */
M2C_UNK func_8002660C();    /* extern */
M2C_UNK func_800266D0();                  /* extern */
s32 func_8003DE58(); /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_8009B4B0();                /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s32 func_800A44E0();              /* extern */
extern u16 D_800281F8;
extern s16 D_8002966C[6];
extern u8 D_8002966E;
extern s32 D_80029670;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0;
extern M2C_UNK D_80082E80;
extern u16 D_80082E94;
extern u16 D_80083780[];
extern M2C_UNK D_800C9034;
extern void *D_800E3D7C;


typedef struct S_80025C80_0_pre {
    u16 unk_00;
} S_80025C80_0_pre;   /* the 0x2 bytes before arg0 in func_80025C80, addressed as arg0[-1] */

typedef struct S_80025C80_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    union { s16 n; volatile u16 v; } unk_30;   /* accessed as both */
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    s16 unk_38;
    u16 unk_3A;
    s16 unk_3C;
    union { s16 n; volatile s16 v; } unk_3E;   /* accessed as both */
    union { u16 u; s16 s; } unk_40;   /* accessed as both */
    u16 unk_42;
} S_80025C80_0;   /* arg0 in func_80025C80 */

typedef struct S_80025C80_1 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025C80_1;   /* arg2 in func_80025C80 */

typedef struct S_80025C80_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_80025C80_2;   /* arg1 in func_80025C80 */

typedef struct S_80025C80_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x1E];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80025C80_3;   /* temp_v1_6 in func_80025C80 */

typedef struct S_80025C80_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80025C80_4;   /* case0_base in func_80025C80 */

typedef struct S_80025C80_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025C80_5;   /* var_a0 in func_80025C80 */

typedef struct S_80025C80_6 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x12];
    u16 unk_1E;
} S_80025C80_6;   /* temp_a0 in func_80025C80 */

typedef struct S_80025C80_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    s32 unk_0C;
    u8 pad_10[0x6];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025C80_7;   /* temp_s0 in func_80025C80 */

typedef struct S_80025C80_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80025C80_8;   /* ((S_80025C80_0 *)arg0)->unk_20 in func_80025C80 */

void func_80025C80(void *arg0_in, void *arg1_in, void *arg2_in) {
    void *arg0;
    void *arg1;
    void *arg2;
    register s32 x_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 y_step ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 eight ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *case0_base;
    void *temp_v1_6;
    register s16 *update_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 *update_ptr;
    register s16 *update_y_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 *update_y_base;
    s16 *update_y_ptr;
    s32 update_y_offset;
    register s32 motion_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 motion_dx ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 motion_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 motion_dy;
    register s32 motion_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 motion_dz ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 motion_damp_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 motion_damp_y;
    u16 linked_flags;
    s32 *linked_global;
    u8 *resident_hi;
    s16 temp_v0;
    s16 temp_v0_4;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v1;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 delta_x;
    s32 delta_y;
    s32 target_x;
    s32 target_y;
    s32 temp_v0_10;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_9;
    u16 *var_v0;
    u16 temp_v0_6;
    register u16 update_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u16 update_y;
    u8 temp_v0_5;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 case0_byte;
    S_80025C80_6 *temp_a0;
    S_80025C80_7 *temp_s0;
    S_80025C80_5 *var_a0;

    arg0 = arg0_in;
    arg1 = arg1_in;
    arg2 = arg2_in;
    temp_a0 = ((S_80025C80_0 *)arg0)->unk_20;
    D_800281F8 = D_800281F8 + 1;
    if (temp_a0 != NULL) {
        goto linked_monster;
    }
    func_8002660C(arg2, arg0 + 0x32, ((S_80025C80_0 *)arg0)->unk_38, ((S_80025C80_0 *)arg0)->unk_36);
    func_80026548(arg0, ((S_80025C80_1 *)arg2)->unk_00);
    temp_v1 = ((S_80025C80_0 *)arg0)->unk_2C;
    if (temp_v1 == 1) {
        goto case_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto case_0;
        }
        func_8002633C();
        return;
    }
    if (temp_v1 == 2) {
        goto case_2;
    }
    if (temp_v1 == 0x10) {
        goto case_16;
    }
    func_8002633C();
    return;

case_0:
    ((S_80025C80_2 *)arg1)->unk_08.at00.v = (s32) (((S_80025C80_2 *)arg1)->unk_08.at00.v + 0xFFFF0000);
    temp_v1_2 = ((S_80025C80_1 *)arg2)->unk_0C.at00.v;
    temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / (s16) ((S_80025C80_0 *)arg0)->unk_30.n);
    ((S_80025C80_1 *)arg2)->unk_0C.at00.v = temp_v1_3;
    ((S_80025C80_1 *)arg2)->unk_0C.at02.v = temp_v1_3;
    ((S_80025C80_1 *)arg2)->unk_0C.at01.v = temp_v1_3;
    temp_v0 = ((u16) ((S_80025C80_0 *)arg0)->unk_30.n ^ 1) & 1;
    temp_v1_4 = ((S_80025C80_0 *)arg0)->unk_30.v - 1;
    ASM_KEEP(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80025C80_0 *)arg0)->unk_30.n = temp_v1_4;
    ((S_80025C80_0 *)arg0)->unk_32 = temp_v0;
    if (((temp_v1_4 << 0x10) <= 0) && (((S_80025C80_1 *)arg2)->unk_14 & 0x4000)) {
        eight = 8;
        ASM_KEEP(eight);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v1_6 = D_800E3D7C;
        ((S_80025C80_0 *)arg0)->unk_38 = eight;
        ((S_80025C80_0 *)arg0)->unk_36 = 0xF;
        ((S_80025C80_0 *)arg0)->unk_32 = 1;
        ((S_80025C80_0 *)arg0)->unk_3A = (u16) ((S_80025C80_3 *)temp_v1_6)->unk_88;
        ((S_80025C80_0 *)arg0)->unk_40.u = (u16) (((u16) ((S_80025C80_3 *)temp_v1_6)->unk_2A >> 9) & 7);
        case0_base = &D_80082E80;
        ((S_80025C80_0 *)arg0)->unk_3C = ((S_80025C80_4 *)case0_base)->unk_24;
        case0_byte = ((S_80025C80_4 *)case0_base)->unk_25;
        ((S_80025C80_0 *)arg0)->unk_42 = eight;
        ((S_80025C80_0 *)arg0)->unk_30.n = 3;
        ((S_80025C80_0 *)arg0)->unk_2C = (s16) ((u16) ((S_80025C80_0 *)arg0)->unk_2C + 1);
        ((S_80025C80_0 *)arg0)->unk_3E.n = case0_byte;
        func_8002633C();
        return;
    }
    goto block_54;

case_1:
    resident_hi = (u8 *) 0x80080000;
    ASM_KEEP_NV(resident_hi);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    arg2 = resident_hi + 0x2E80;
    temp_v0_10 = func_8003DE58(((S_80025C80_1 *)arg2)->unk_08, arg2, arg0 + 0x24, 0);
    temp_v1_5 = (u16) ((S_80025C80_0 *)arg0)->unk_30.n - 1;
    ((S_80025C80_0 *)arg0)->unk_30.n = temp_v1_5;
    if ((temp_v1_5 << 0x10) <= 0) {
        goto case1_check_flag;
    }
    if (temp_v0_10 == 0) {
        goto case1_check_flag;
    }
    if ((((S_80025C80_1 *)arg2)->unk_14 & 0x8000) == 0) {
        goto case1_add_base;
    }
case1_check_flag:
    if (D_80082E94 & 0x8000) {
        ((S_80025C80_2 *)arg1)->unk_00.at02.v = D_80083780[1];
        ((S_80025C80_2 *)arg1)->unk_04.at02.v = D_80083780[3];
        ((S_80025C80_2 *)arg1)->unk_08.at02.v = D_80083780[5] - 0x10;
    }
    ((S_80025C80_0 *)arg0)->unk_30.n = 0;
    ((S_80025C80_0 *)arg0)->unk_2C = (u16) ((S_80025C80_0 *)arg0)->unk_2C + 1;
    func_8002633C();
    return;

case1_add_base:
    var_a0 = &D_80083780;
    ((S_80025C80_2 *)arg1)->unk_00.at02.v = (s16) (var_a0->unk_02 + ((S_80025C80_0 *)arg0)->unk_24);
    ((S_80025C80_2 *)arg1)->unk_04.at02.v = (s16) (var_a0->unk_06 + ((S_80025C80_0 *)arg0)->unk_26);
    ((S_80025C80_2 *)arg1)->unk_08.at02.v = (s16) (var_a0->unk_0A + ((S_80025C80_0 *)arg0)->unk_28);
    func_8002633C();
    return;

case_2:
    if (((S_80025C80_0 *)arg0)->unk_30.n != 0) {
        goto block_31;
    }
    if ((func_800A44E0(((((S_80025C80_0 *)arg0)->unk_3C << 6) + 0x20) & 0xFFE0, ((((S_80025C80_0 *)arg0)->unk_3E.n << 6) + 0x20) & 0xFFE0, (s16) (((S_80025C80_0 *)arg0)->unk_3A - 0x20), (s16) (((S_80025C80_0 *)arg0)->unk_40.u << 9)) << 0x10) != 0) {
        goto case2_complete;
    }
    temp_v0_6 = ((S_80025C80_0 *)arg0)->unk_42 - 1;
    ((S_80025C80_0 *)arg0)->unk_42 = temp_v0_6;
    if ((temp_v0_6 << 0x10) > 0) {
        goto case2_update;
    }
case2_complete:
    ((S_80025C80_0 *)arg0)->unk_2C = 0x10;
    ((S_80025C80_2 *)arg1)->unk_0C.at02.v = D_8006CCD8[((S_80025C80_0 *)arg0)->unk_40.s] * 8;
    ((S_80025C80_2 *)arg1)->unk_10.at02.v = D_8006CCE8[((S_80025C80_0 *)arg0)->unk_40.s] * 8;
    x_step = 8;
    ((S_80025C80_2 *)arg1)->unk_14.at02.v = x_step;
    ((S_80025C80_0 *)arg0)->unk_30.n = x_step;
    func_8002600C();
    return;

case2_update:
    update_base = D_8006CCD8;
    update_ptr = &update_base[((S_80025C80_0 *)arg0)->unk_40.s];
    update_x = (u16) ((S_80025C80_0 *)arg0)->unk_3C;
    x_step = (u16) *update_ptr;
    update_x += x_step;
    update_y_page = (s16 *) 0x80070000;
    ASM_KEEP_NV(update_y_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_80025C80_0 *)arg0)->unk_3C = update_x;
    update_y_base = (s16 *) ((u8 *) update_y_page - 0x3318);
    update_y_offset = ((S_80025C80_0 *)arg0)->unk_40.s << 1;
    update_y_ptr = (s16 *) ((unsigned long) update_y_offset + (unsigned long) update_y_base);
    update_y = (u16) ((S_80025C80_0 *)arg0)->unk_3E.v;
    y_step = (u16) *(volatile u16 *) update_y_ptr;
    ((S_80025C80_0 *)arg0)->unk_30.n = 3;
    update_y += y_step;
    ((S_80025C80_0 *)arg0)->unk_3E.n = update_y;
block_31:
    target_x = ((S_80025C80_0 *)arg0)->unk_3C << 6;
    delta_x = ((S_80025C80_2 *)arg1)->unk_00.at02.v - 0x20;
    x_step = (target_x - delta_x) / ((S_80025C80_0 *)arg0)->unk_30.n;
    ((S_80025C80_2 *)arg1)->unk_00.at02.v = (u16) ((S_80025C80_2 *)arg1)->unk_00.at02.v + x_step;
    target_y = ((S_80025C80_0 *)arg0)->unk_3E.n << 6;
    delta_y = ((S_80025C80_2 *)arg1)->unk_04.at02.v - 0x20;
    y_step = (target_y - delta_y) / ((S_80025C80_0 *)arg0)->unk_30.n;
    temp_v0_7 = (u16) ((S_80025C80_2 *)arg1)->unk_08.at02.v + 5;
    ((S_80025C80_2 *)arg1)->unk_08.at02.v = temp_v0_7;
    ((S_80025C80_2 *)arg1)->unk_04.at02.v = (u16) ((S_80025C80_2 *)arg1)->unk_04.at02.v + y_step;
    if (((s16) ((S_80025C80_0 *)arg0)->unk_3A - 0x10) < temp_v0_7) {
        ((S_80025C80_2 *)arg1)->unk_08.at02.v = (s16) (((S_80025C80_0 *)arg0)->unk_3A - 0x10);
    }
    temp_v0_8 = (u16) ((S_80025C80_0 *)arg0)->unk_30.n - 1;
    ((S_80025C80_0 *)arg0)->unk_30.n = temp_v0_8;
    if (temp_v0_8 == 2) {
        temp_v0_9 = func_8009B4B0(D_800E3D7C, (u16) ((S_80025C80_0 *)arg0)->unk_3C, (u16) ((S_80025C80_0 *)arg0)->unk_3E.n);
        if (temp_v0_9 != 0) {
            func_8009CE1C(temp_v0_9, 0xC, D_8002966E, 9, (s32) (s16) (((S_80025C80_0 *)arg0)->unk_40.u << 9), D_80029670, 5);
        }
        goto block_47;
    }
    goto block_47;

case_16:
    motion_x = ((S_80025C80_2 *)arg1)->unk_00.at00.v;
    motion_dx = ((S_80025C80_2 *)arg1)->unk_0C.at00.v;
    motion_y = ((S_80025C80_2 *)arg1)->unk_04.at00.v;
    motion_dy = ((S_80025C80_2 *)arg1)->unk_10.at00.v;
    motion_x += motion_dx;
    motion_y += motion_dy;
    ((S_80025C80_2 *)arg1)->unk_04.at00.v = motion_y;
    motion_z = ((S_80025C80_2 *)arg1)->unk_08.at00.v;
    motion_dz = ((S_80025C80_2 *)arg1)->unk_14.at00.v;
    ((S_80025C80_2 *)arg1)->unk_00.at00.v = motion_x;
    motion_damp_x = ((S_80025C80_2 *)arg1)->unk_0C.at00.v;
    motion_z += motion_dz;
    ((S_80025C80_2 *)arg1)->unk_08.at00.v = motion_z;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    motion_damp_x -= motion_damp_x >> 2;
    motion_damp_y = motion_dy;
    ((S_80025C80_2 *)arg1)->unk_0C.at00.v = motion_damp_x;
    ASM_KEEP(motion_damp_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    motion_damp_y -= motion_damp_x >> 2;
    ((S_80025C80_2 *)arg1)->unk_10.at00.v = motion_damp_y;
    if (((s16) ((S_80025C80_0 *)arg0)->unk_3A - 0x10) < ((S_80025C80_2 *)arg1)->unk_08.at02.v) {
        ((S_80025C80_2 *)arg1)->unk_08.at02.v = (s16) (((S_80025C80_0 *)arg0)->unk_3A - 0x10);
    }
    ((S_80025C80_1 *)arg2)->unk_0C.at00.v = ((S_80025C80_1 *)arg2)->unk_0C.at00.v - ((s32) ((S_80025C80_1 *)arg2)->unk_0C.at00.v / ((S_80025C80_0 *)arg0)->unk_30.n);
    ((S_80025C80_1 *)arg2)->unk_0C.at01.v = ((S_80025C80_1 *)arg2)->unk_0C.at01.v - ((s32) ((S_80025C80_1 *)arg2)->unk_0C.at01.v / ((S_80025C80_0 *)arg0)->unk_30.n);
    ((S_80025C80_1 *)arg2)->unk_0C.at02.v = ((S_80025C80_1 *)arg2)->unk_0C.at02.v - ((s32) ((S_80025C80_1 *)arg2)->unk_0C.at02.v / ((S_80025C80_0 *)arg0)->unk_30.n);
    temp_v0_4 = (u16) ((S_80025C80_0 *)arg0)->unk_30.n - 1;
    ((S_80025C80_0 *)arg0)->unk_30.n = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        D_8002966C[0] = 0;
        func_80026270();
        return;
    }
    temp_v0_5 = ((S_80025C80_1 *)arg2)->unk_04;
    if ((s8) temp_v0_5 == ((S_80025C80_0 *)arg0)->unk_36) {
        ((S_80025C80_0 *)arg0)->unk_32 = -1;
        goto block_47;
        return;
    }
    if ((s8) temp_v0_5 == ((S_80025C80_0 *)arg0)->unk_38) {
        ((S_80025C80_0 *)arg0)->unk_32 = 1;
        goto block_47;
    }
block_47:
    func_8002589C(arg0 - 0x20, (s16) ((S_80025C80_0 *)arg0)->unk_40.u, 0xF0);
    func_8002633C();
    return;

linked_monster:
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (temp_a0->unk_1E & 0x8000) {
        linked_flags = ((S_80025C80_0_pre *)arg0)[-1].unk_00;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        linked_global = &D_800814A0;
        linked_flags |= 0x8000;
        ((S_80025C80_0_pre *)arg0)[-1].unk_00 = linked_flags;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        *linked_global |= 0x8000;
        return;
    }
    temp_v1_6 = temp_a0->unk_08;
    ((S_80025C80_2 *)arg1)->unk_00.at02.v = (s16) ((S_80025C80_3 *)temp_v1_6)->unk_02;
    ((S_80025C80_2 *)arg1)->unk_04.at02.v = (s16) ((S_80025C80_3 *)temp_v1_6)->unk_06;
    ((S_80025C80_2 *)arg1)->unk_08.at02.v = (s16) ((S_80025C80_3 *)temp_v1_6)->unk_0A;
    temp_s0 = ((S_80025C80_8 *)(((S_80025C80_0 *)arg0)->unk_20))->unk_0C;
    func_800266D0(arg2, temp_s0->unk_04);
    func_80026548(arg0, ((S_80025C80_1 *)arg2)->unk_00);
    ((S_80025C80_1 *)arg2)->unk_1C = (u16) temp_s0->unk_1C;
    ((S_80025C80_1 *)arg2)->unk_1E = (u16) temp_s0->unk_1E;
    ((S_80025C80_1 *)arg2)->unk_20 = (u16) temp_s0->unk_20;
    ((S_80025C80_1 *)arg2)->unk_0C.at00u.v = temp_s0->unk_0C;
    ((S_80025C80_1 *)arg2)->unk_16 = (u16) temp_s0->unk_16;
    ((S_80025C80_1 *)arg2)->unk_18 = (u16) temp_s0->unk_18;
    ((S_80025C80_1 *)arg2)->unk_1A = (u16) temp_s0->unk_1A;
block_54:
    if (((S_80025C80_0 *)arg0)->unk_2E == 0) {
        func_8004491C(arg0 - 0x20, &D_800C9034);
        ((S_80025C80_0 *)arg0)->unk_2E = (s16) ((u16) ((S_80025C80_0 *)arg0)->unk_2E + 1);
    }
}
