#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800B1188_1 {
    u8 pad_00[0xCC];
    void * unk_CC;
} S_800B1188_1;   /* arg0 in func_800B1188 */

typedef struct S_800B1188_2 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x10];
    void * unk_24;
    u8 pad_28[0x10];
    void * unk_38;
    u8 pad_3C[0x10];
    void * unk_4C;
    u8 pad_50[0x10];
    void * unk_60;
} S_800B1188_2;   /* (temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC) in func_800B1188 */

typedef struct S_800B1188_3 {
    M2C_UNK ** unk_00;
    void ** unk_04;
    s32 unk_08;
    M2C_UNK ** unk_0C;
} S_800B1188_3;   /* ((S_800B1188_1 *)arg0)->unk_CC in func_800B1188 */

typedef struct S_800B1188_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_4;   /* ((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_10 in func_800B1188 */

typedef struct S_800B1188_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_5;   /* ((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_24 in func_800B1188 */

typedef struct S_800B1188_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_6;   /* ((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_38 in func_800B1188 */

typedef struct S_800B1188_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_7;   /* ((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_4C in func_800B1188 */

typedef struct S_800B1188_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_8;   /* ((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_60 in func_800B1188 */

typedef struct S_800B1188_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_9;   /* ((S_800B1188_3 *)(((S_800B1188_1 *)arg0)->unk_CC))->unk_04 in func_800B1188 */

typedef struct S_800B1188_10 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_10;   /* ((S_800B1188_4 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_10))->unk_04 in func_800B1188 */

typedef struct S_800B1188_11 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_11;   /* ((S_800B1188_5 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_24))->unk_04 in func_800B1188 */

typedef struct S_800B1188_12 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_12;   /* ((S_800B1188_6 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_38))->unk_04 in func_800B1188 */

typedef struct S_800B1188_13 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_13;   /* ((S_800B1188_7 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_4C))->unk_04 in func_800B1188 */

typedef struct S_800B1188_14 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_14;   /* ((S_800B1188_8 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_60))->unk_04 in func_800B1188 */

typedef struct S_800B1188_15 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B1188_15;   /* ((S_800B1188_9 *)(((S_800B1188_3 *)(((S_800B1188_1 *)arg0)->unk_CC))->unk_04))->unk_04 in func_800B1188 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004CBFC();
extern M2C_UNK func_800B08D4();
extern M2C_UNK func_800B0C68();
extern M2C_UNK func_800B0D0C();
extern M2C_UNK func_800B0FD4();
extern M2C_UNK D_800788E0;
extern M2C_UNK D_800792DC;
extern M2C_UNK D_800D15F4;

typedef struct S_800B1188_0 {
    u8 pad_00[0xCC];
    s32 unk_CC;
} S_800B1188_0;   /* arg0 in func_800B1188 */

void func_800B1188(void *arg0) {
    s32 var_a1;
    s32 var_a3;
    s32 var_t0;
    s32 temp_a0_2;
    s32 var_a2;
    void *temp_a0;

    *((S_800B1188_3 *)(((S_800B1188_1 *)arg0)->unk_CC))->unk_00 = &D_800788E0;
    temp_a0 = arg0 + 0x34;
    *((S_800B1188_3 *)(((S_800B1188_1 *)arg0)->unk_CC))->unk_04 = temp_a0;
    ((S_800B1188_15 *)(((S_800B1188_9 *)(((S_800B1188_3 *)(((S_800B1188_1 *)arg0)->unk_CC))->unk_04))->unk_04))->unk_0A = 0x2F;
    func_800B08D4(temp_a0);
    func_800B0C68(arg0);
    func_8004CBFC(arg0 + 0x28, &D_800792DC, ((S_800B1188_3 *)(((S_800B1188_1 *)arg0)->unk_CC))->unk_08);
    var_a2 = 4;
    var_a1 = 0xC8;
    var_t0 = 0x55;
    var_a3 = 0x58;
    *((S_800B1188_3 *)(((S_800B1188_1 *)arg0)->unk_CC))->unk_0C = &D_800D15F4;
    do {
        temp_a0_2 = var_a2 * 4;
        ((S_800B1188_10 *)(((S_800B1188_4 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_10))->unk_04))->unk_08 = -0x50;
        ((S_800B1188_10 *)(((S_800B1188_4 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_10))->unk_04))->unk_0A = var_a3;
        ((S_800B1188_11 *)(((S_800B1188_5 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_24))->unk_04))->unk_08 = 0x56;
        ((S_800B1188_11 *)(((S_800B1188_5 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_24))->unk_04))->unk_0A = var_t0;
        ((S_800B1188_12 *)(((S_800B1188_6 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_38))->unk_04))->unk_08 = 0x3C;
        ((S_800B1188_12 *)(((S_800B1188_6 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_38))->unk_04))->unk_0A = var_a1;
        ((S_800B1188_13 *)(((S_800B1188_7 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_4C))->unk_04))->unk_08 = 0x8C;
        ((S_800B1188_13 *)(((S_800B1188_7 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_4C))->unk_04))->unk_0A = var_a1;
        ((S_800B1188_14 *)(((S_800B1188_8 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_60))->unk_04))->unk_08 = 0x34;
        var_a2 -= 1;
        var_a3 -= 0x10;
        var_t0 -= 0x10;
        ((S_800B1188_14 *)(((S_800B1188_8 *)(((S_800B1188_2 *)((temp_a0_2 + ((S_800B1188_0 *)arg0)->unk_CC)))->unk_60))->unk_04))->unk_0A = var_a1;
        var_a1 -= 0x10;
    } while (var_a2 >= 0);
    func_800B0D0C(arg0, var_a1, var_a2, var_a3);
    func_800B0FD4(arg0);
}
