#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80158854_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void * unk_10;
} S_80158854_0;   /* temp_v0 in func_80158854 */

typedef struct S_80158854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80158854_1;   /* var_s1 in func_80158854 */

typedef struct S_80158854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80158854_2;   /* temp_s6 in func_80158854 */

typedef struct S_80158854_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80158854_3;   /* temp_s2 in func_80158854 */

typedef struct S_80158854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_80158854_4;   /* temp_s3 in func_80158854 */


extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_80158A8C[];
extern u8 D_8015BD30[];
extern u8 D_8015BD78[];
extern u8 D_80158F74[];

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern s32 func_800A6D30();
extern M2C_UNK func_800A48F0();
extern M2C_UNK func_800A9C18();
extern M2C_UNK func_800AA36C();
extern M2C_UNK func_80044A50();
extern M2C_UNK func_800BC318();

#ifdef __mips__
#define BODY_STORAGE
#define BODY_ATTR __attribute__((used, section(".text.func_80158854")))
#else
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void *func_80158854(s16 arg0, s16 arg1, s16 arg2, s16 arg3) BODY_ATTR;

BODY_STORAGE void *func_80158854(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    s32 temp_v0_2;
    s32 var_s5;
    void *temp_s0;
    S_80158854_3 *temp_s2;
    S_80158854_2 *temp_s6;
    void *temp_s3;
    void *temp_v0;
    S_80158854_1 *var_s1;

    var_s1 = 0;
    var_s5 = 1;
    temp_v0 = func_8003FD64(274, D_80083498);
    if (temp_v0 == 0) {
        goto done;
    }

    var_s1 = (u8 *)temp_v0 + 0x20;
    ((S_80158854_0 *)temp_v0)->unk_10 = D_80158A8C;
    var_s1->unk_13 = 0x23;
    func_8004491C(temp_v0, D_80045340);
    temp_s6 = ((S_80158854_0 *)temp_v0)->unk_08;
    temp_s6->unk_0A = arg3;
    temp_s2 = ((S_80158854_0 *)temp_v0)->unk_0C;
    temp_s2->unk_25 = arg2;
    temp_s3 = var_s1;
    temp_s2->unk_2C = D_8015BD30;
    temp_v0_2 = arg0 & 3;
    temp_s2->unk_24 = arg1;
    if (temp_v0_2 == 1) {
        var_s1->unk_14 |= 0x6000;
        var_s1->unk_1C |= 0x6000;
    } else if (temp_v0_2 >= 2) {
        var_s1->unk_14 |= 0x2000;
        var_s1->unk_1C |= 0x2000;
    } else if (((arg0 & ~3) << 16) == 0) {
        if (var_s1->unk_14 & 0x200) {
            goto status_done;
        }
        if (!(func_800A6D30() & 1)) {
            goto status_done;
        }
        var_s1->unk_1C |= 0x200;
        func_800A48F0(var_s1, 1, (func_800A6D30() & 0x3F) | 0x20);
        temp_s2->unk_2C = D_8015BD78;
    status_done:
        var_s5 = func_800A6D30() & 3;
    }
    func_800A9C18(temp_v0, temp_s6, temp_s2, arg0);
    ((S_80158854_4 *)temp_s3)->unk_9A = 0xFF;
    ((S_80158854_4 *)temp_s3)->unk_9C = -1;
    ((S_80158854_4 *)temp_s3)->unk_8C = D_80158F74;
    ((S_80158854_4 *)temp_s3)->unk_A4 = -1;
    if (var_s5 != 0) {
        ((S_80158854_4 *)temp_s3)->unk_A6 = 0;
    } else {
        temp_s0 = (u8 *)temp_s3 - 0x20;
        ((S_80158854_4 *)temp_s3)->unk_A6 = 1;
        temp_s2->unk_10 = 0x60;
        temp_s2->unk_14 |= 0xC;
        temp_s2->unk_12 -= 0x80;
        func_80044A50(temp_s0);
        func_800BC318(temp_s0);
    }
    func_800AA36C(temp_s3, temp_s6, temp_s2, var_s1);
done:
    return var_s1;
}
