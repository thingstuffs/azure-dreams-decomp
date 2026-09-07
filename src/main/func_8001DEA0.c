#include "common.h"
#include "m2c_compat.h"

typedef struct S_80404EA0_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80404EA0_3;   /* temp_s2 in func_80404EA0 */

typedef struct S_80404EA0_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    u32 unk_1C;
    u8 pad_20[0x4];
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} S_80404EA0_4;   /* D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7) in func_80404EA0 */

typedef struct S_80404EA0_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80404EA0_5;   /* ((S_80404EA0_3 *)temp_s2)->unk_04 in func_80404EA0 */


typedef struct S_80404EA0_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    u8 pad_80[0xA98];
    void * unk_B18;
    void * unk_B1C;
    void * unk_B20;
    void * unk_B24;
    void * unk_B28;
    void * unk_B2C;
    void * unk_B30;
} S_80404EA0_0;   /* arg0 in func_80404EA0 */

typedef struct S_80404EA0_1 {
    union { void * s; s32 u; } unk_00;   /* accessed as both */
} S_80404EA0_1;   /* temp_s2 in func_80404EA0 */

typedef struct S_80404EA0_2 {
    u8 pad_00[0xB34];
    void * unk_B34;
} S_80404EA0_2;   /* var_a1 in func_80404EA0 */

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Copy4;

M2C_UNK func_8003830C();                  /* extern */
M2C_UNK func_80051520();      /* extern */
M2C_UNK func_80051804();         /* extern */
M2C_UNK func_8005184C();         /* extern */
M2C_UNK func_80051898();                  /* extern */
M2C_UNK func_80051900();                       /* extern */
M2C_UNK func_80051B50(); /* extern */
M2C_UNK func_8007BF50();                /* extern */
M2C_UNK func_8007BF80();                  /* extern */
extern M2C_UNK D_8009DDE4[];
extern s16 D_80400660[];
extern s32 D_80400668[];
extern s16 D_804006AC[];
extern s16 D_804006BC[];
extern s16 D_804006C0[];
extern s32 D_80408CF4[];
extern s32 D_80408CFC[];
extern u8 D_8009DDD8[];
__asm__(".set D_8009DDD8, 0x8009DDD8");

/* The retail live range keeps the descriptor cursor in one saved register. */

void func_80404EA0(void *arg0) {
    s16 sp10[32];
    s16 sp50[8];
    s16 sp60[4];
    s16 var_a3_2;
    s32 *var_a2_2;
    s32 *var_a2_end;
    s32 var_a0;
    s32 descriptor_value;
    s32 bit_one;
    s16 height_b0;
    u32 hours;
    u32 mins;
    u32 mins_q;
    u32 secs;
    u32 secs_q;
    void *temp_s0;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s1;
    S_80404EA0_1 *temp_s2;
    void *var_a1;
    void *final_sp;
    s32 *descriptor_base;

    temp_s2 = ((S_80404EA0_0 *)arg0)->unk_B18;
    func_8003830C(((S_80404EA0_0 *)arg0)->unk_7C + 1, sp10);
    func_8007BF50(sp10, D_80400660);
    func_8007BF50(sp10, (s16 *)((((S_80404EA0_0 *)arg0)->unk_7C << 7) + (s32)&D_8009DDE4));
    temp_s0 = arg0 + 0x80;
    func_80051B50(temp_s0, sp10, 1);
    temp_s2->unk_00.s = temp_s0;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_08 = 0xA9;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_0A = 0x110;
    temp_s2 = ((S_80404EA0_0 *)arg0)->unk_B1C;
    memcpy(sp10, D_80400668, 0x2A);
    func_80051B50(arg0 + 0x188, sp10, 1);
    temp_s2->unk_00.s = arg0 + 0x188;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_08 = 0xBC;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_0A = 0x110;
    if (((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_08 != 0) {
        temp_s2 = ((S_80404EA0_0 *)arg0)->unk_B20;
        func_8007BF80(sp10, D_80408CF4[0]);
        func_8003830C(((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_34, sp50);
        func_8007BF50(sp10, sp50);
        func_8007BF50(sp10, D_804006AC);
        temp_s0_3 = arg0 + 0x290;
        func_80051B50(temp_s0_3, sp10, 1);
        temp_s2->unk_00.s = temp_s0_3;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_08 = 0xBC;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_0A = 0x140;
    }
    temp_s2 = ((S_80404EA0_0 *)arg0)->unk_B24;
    func_80051804(((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_24, 0xA, sp10);
    func_80051900(sp10);
    temp_s0_4 = arg0 + 0x398;
    func_80051520(temp_s0_4, sp10, 1);
    temp_s2->unk_00.s = temp_s0_4;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_08 = 0x140;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_0A = 0x110;
    temp_s2 = ((S_80404EA0_0 *)arg0)->unk_B28;
    func_80051898(((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_1C, sp10);
    hours = ((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_1C / 216000;
    func_80051804(hours, 3, sp10);
    func_8007BF50(sp10, D_804006BC);
    mins = ((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_1C / 3600;
    mins_q = mins / 3600;
    func_8005184C(mins - mins_q * 3600, 2, sp60);
    func_8007BF50(sp10, sp60);
    func_8007BF50(sp10, D_804006BC);
    secs = ((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_1C / 60;
    secs_q = secs / 60;
    func_8005184C(secs - secs_q * 60, 2, sp60);
    func_8007BF50(sp10, sp60);
    func_80051900(sp10);
    temp_s0_5 = arg0 + 0x4A0;
    func_80051520(temp_s0_5, sp10, 1);
    temp_s2->unk_00.s = temp_s0_5;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_08 = 0x147;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_0A = 0x120;
    temp_s2 = ((S_80404EA0_0 *)arg0)->unk_B2C;
    func_80051804(((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_2C, 4, sp10);
    func_80051900(sp10);
    temp_s0_6 = arg0 + 0x5A8;
    func_80051520(temp_s0_6, sp10, 1);
    temp_s2->unk_00.s = temp_s0_6;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_08 = 0xF2;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_0A = 0x120;
    temp_s2 = ((S_80404EA0_0 *)arg0)->unk_B30;
    memcpy(sp10, D_804006C0, 3);
    final_sp = sp10;
    func_80051900(final_sp);
    temp_s1 = arg0 + 0x6B0;
    func_80051520(temp_s1, final_sp, 1);
    var_a0 = 0;
    bit_one = 1;
    descriptor_base = D_80408CFC;
    var_a2_end = descriptor_base + 10;
    height_b0 = 0xB0;
    var_a3_2 = 0x38;
    var_a2_2 = descriptor_base;
    var_a1 = arg0;
    temp_s2->unk_00.s = temp_s1;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_08 = 0x180;
    ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_0A = 0x130;
    do {
        temp_s2 = ((S_80404EA0_2 *)var_a1)->unk_B34;
        if ((bit_one << var_a0) & ((S_80404EA0_4 *)(D_8009DDD8 + (((S_80404EA0_0 *)arg0)->unk_7C << 7)))->unk_30) {
            descriptor_value = *var_a2_2;
        } else {
            descriptor_value = *var_a2_end;
        }
        var_a2_2 += 1;
        var_a1 += 4;
        temp_s2->unk_00.u = descriptor_value;
        var_a0 += 1;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_08 = var_a3_2;
        ((S_80404EA0_5 *)(((S_80404EA0_3 *)temp_s2)->unk_04))->unk_0A = height_b0;
        var_a3_2 += 0x10;
    } while (var_a0 < 0xA);
}
