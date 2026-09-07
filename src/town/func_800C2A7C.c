#include "common.h"
#include "m2c_compat.h"

extern void *func_8003FE78();
extern M2C_UNK func_8008EF58();
extern M2C_UNK func_8008F01C();
extern M2C_UNK func_8008FCE0();
extern M2C_UNK func_8008FD48();
extern M2C_UNK func_8009550C();
extern s16 func_800C2AE8();

extern M2C_UNK D_8006ADBC;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800C02C4;
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800D0420;
extern s32 D_800D0438;
extern M2C_UNK D_800FE490;

typedef struct S_800C01DC_0 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    M2C_UNK * unk_0C;
    M2C_UNK * unk_10;
} S_800C01DC_0;   /* temp_v0 in func_800C01DC */

typedef struct S_800C01DC_1 {
    u8 pad_00[0x10];
    u16 * unk_10;
    u16 unk_14;
    u16 unk_16;
} S_800C01DC_1;   /* base in func_800C01DC */

typedef struct S_800C01DC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C01DC_2;   /* &D_80083780 in func_800C01DC */

void func_800C01DC(void) {
    S_800C01DC_0 *temp_v0;

    D_800D0438 = 0;
    temp_v0 = func_8003FE78(0, &D_80083498, 0x22);
    temp_v0->unk_10 = &D_800C02C4;
    temp_v0->unk_0C = &D_80082E80;
    temp_v0->unk_08 = &D_80083780;
    func_8008EF58();
    func_8008F01C(&D_800CFCB4, &D_80083780, &D_800D0420);
    func_8008FCE0();
    func_8008FD48(&D_800FE490, &D_80083780, &D_800D0420);
    {
        register s8 *base ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        u16 *ptr10;

        base = (s8 *) &D_8006ADBC;
        ptr10 = ((S_800C01DC_1 *)base)->unk_10;
        ((S_800C01DC_2 *)(&D_80083780))->unk_02 = (s16) (((S_800C01DC_1 *)base)->unk_14 + ptr10[0]);
        ((S_800C01DC_2 *)(&D_80083780))->unk_06 = (s16) (((S_800C01DC_1 *)base)->unk_16 + ptr10[1]);
        ((S_800C01DC_2 *)(&D_80083780))->unk_0A = func_800C2AE8(&D_80083780, ptr10);
    }
    func_8009550C(&D_80083780);
}
