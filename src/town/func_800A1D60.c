#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_8009F4C0_3 {
    u8 pad_00[0xAC3];
    u8 unk_AC3;
} S_8009F4C0_3;   /* (temp_s0 + (u8 *)baseD) in func_8009F4C0 */

typedef struct S_8009F4C0_4 {
    u8 pad_00[0x983];
    u8 unk_983;
} S_8009F4C0_4;   /* ((arg0->unk_95 * 4) + (u8 *)baseD) in func_8009F4C0 */

typedef struct S_8009F4C0_5 {
    u8 pad_00[0xA94];
    s32 unk_A94;
} S_8009F4C0_5;   /* ((temp_s3 * 0x54) + (u8 *)baseD) in func_8009F4C0 */




struct PackedTownEntry {
    s32 word0;
    s32 word4;
    s8 byte8;
    s8 byte9;
} __attribute__((packed));

struct TownCopy84 {
    s32 words[21];
};

M2C_UNK func_80033CD8();                   /* extern */
void *func_8003C06C();               /* extern */
M2C_UNK func_8003E188();        /* extern */
M2C_UNK func_800422DC();            /* extern */
M2C_UNK func_800423C0();      /* extern */
M2C_UNK func_80042640();               /* extern */
M2C_UNK memset(); /* extern */
M2C_UNK func_8009DC8C();    /* extern */
extern M2C_UNK D_80010A80;
extern M2C_UNK D_80010AB4;
extern M2C_UNK D_80045340;
extern M2C_UNK D_8009F374;
extern M2C_UNK D_80100A10;
extern struct TownCopy84 D_80100AF8;
extern u8 D_80010000[];


typedef struct S_8009F4C0_1 {
    u8 pad_00[0x981];
    s8 unk_981;
} S_8009F4C0_1;   /* temp_v2 in func_8009F4C0 */

typedef struct S_8009F4C0_2 {
    u8 pad_00[0x981];
    u8 unk_981;
    u8 pad_982[0x1];
    u8 unk_983;
} S_8009F4C0_2;   /* temp_v1 in func_8009F4C0 */

void func_8009F4C0(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    void *var_s1;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s5;
    register s32 temp_s3;
    void *temp_v0;
    S_8009F4C0_2 *temp_v1;
    S_8009F4C0_1 *temp_v2;
    register void *baseD ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */

    temp_s5 = arg0->unk_95;
    func_80033CD8(arg0, &D_80045340);
    temp_v2 = (temp_s5 * 4) + 0x80010000;
    temp_v2->unk_981 = 0x13;
    memset(&D_80100A10, 0, 0x54);
    func_80042640(&D_80100A10, arg0->unk_4C);
    temp_s3 = temp_s5;
    func_800423C0(&D_80100A10, arg0->unk_4C, 0);
    func_800422DC(&D_80100AF8, &D_80100A10);
    *(struct TownCopy84 *)((u8 *)0x80010A80 + (temp_s3 * 0x54)) = D_80100AF8;
    var_s1 = (void *) 0x80010AB4;
    temp_s0 = temp_s3 * 0x54;
    var_s1 = (u8 *)var_s1 + temp_s0;
    temp_v0 = func_8003C06C(arg0->unk_4C);
    *(struct PackedTownEntry *)var_s1 = *(struct PackedTownEntry *)temp_v0;
    baseD = (void *) 0x80010000;
    temp_v1 = (temp_s5 * 4) + (u8 *)baseD;
    temp_v1->unk_983 = (u8) ((temp_v1->unk_983 & 0xC0) | temp_s3);
    ((S_8009F4C0_3 *)((temp_s0 + (u8 *)baseD)))->unk_AC3 = temp_s5;
    arg0->unk_4D = (u8) temp_v1->unk_981;
    arg0->unk_4F = (u8) temp_v1->unk_983;
    temp_s3 = (u8) (((S_8009F4C0_4 *)(((arg0->unk_95 * 4) + (u8 *)baseD)))->unk_983 & 0x3F);
    temp_s0_2 = ((S_8009F4C0_5 *)(((temp_s3 * 0x54) + (u8 *)baseD)))->unk_A94;
    func_8003E188(arg0->unk_4C, 1, baseD);
    func_8009DC8C(arg0, arg3, arg0->unk_4C, temp_s0_2);
    arg0->unk_50.as_pm = &D_8009F374;
    arg0->unk_6C.as_s16 = 0xA;
}
