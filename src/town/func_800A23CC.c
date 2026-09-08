#include "common.h"
#include "m2c_compat.h"

void *func_8003C06C();        /* extern */
M2C_UNK func_800422DC();            /* extern */
M2C_UNK func_800423C0();      /* extern */
M2C_UNK func_80042640();               /* extern */
M2C_UNK memset(); /* extern */
s32 func_8009F970();              /* extern */
void *func_800B2344();                              /* extern */
extern M2C_UNK D_800102F0;
extern M2C_UNK D_80010324;
extern M2C_UNK D_80100A10;
typedef struct {
    s32 words[0x15];
} Record84;
extern Record84 D_80100AF8;

typedef struct Copy16 {
    s32 words[4];
} Copy16;

typedef struct Copy10 {
    s8 bytes[10];
} __attribute__((packed)) Copy10;

typedef struct S_8009FB2C_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8009FB2C_0;   /* temp_v0 in func_8009FB2C */

typedef struct S_8009FB2C_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8009FB2C_1;   /* arg1 in func_8009FB2C */

typedef struct S_8009FB2C_2 {
    u8 pad_00[0x29C];
    void * unk_29C;
    s32 unk_2A0;
} S_8009FB2C_2;   /* temp_v1 in func_8009FB2C */

void func_8009FB2C(s32 arg0, S_8009FB2C_1 *arg1) {
    u8 *var_a2;
    u8 *var_s1;
    s32 temp_a1;
    s32 temp_v0_2;
    u8 *temp_a3;
    void *temp_s0;
    S_8009FB2C_0 *temp_v0;
    void *temp_v0_3;
    S_8009FB2C_2 *temp_v1;
    void *temp_a0;
    register void *result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    temp_v0 = func_800B2344();
    temp_v0->unk_00 = (u8) arg1->unk_00;
    temp_v0->unk_01 = (u8) arg1->unk_01;
    temp_v0->unk_02 = (u8) arg1->unk_02;
    temp_v0->unk_03 = (u8) arg1->unk_03;
    if (temp_v0->unk_01 == 0x13) {
        memset(&D_80100A10, 0, 0x54);
        func_80042640(&D_80100A10, temp_v0->unk_00);
        func_800423C0(&D_80100A10, temp_v0->unk_00, 0);
        {
            register u8 *addr ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            addr = (u8 *)&D_80100AF8;
            var_s1 = addr;
            func_800422DC(addr, &D_80100A10);
        }
        temp_v0_2 = func_8009F970((void *)0x800102F0, 0x14);
        var_a2 = (temp_v0_2 * 0x54) + (u8 *)0x800102F0;
        temp_a3 = var_s1 + 0x50;
        do {
            *(Copy16 *)var_a2 = *(Copy16 *)var_s1;
            var_s1 += 0x10;
            var_a2 += 0x10;
        } while (var_s1 != temp_a3);
        *(s32 *)var_a2 = *(s32 *)var_s1;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        temp_s0 = (temp_v0_2 * 0x54) + (u8 *)0x80010324;
        temp_v0_3 = func_8003C06C(temp_v0->unk_00);
        *(Copy10 *)temp_s0 = *(Copy10 *)temp_v0_3;
        temp_v0->unk_03 = (u8) ((temp_v0->unk_03 & 0xC0) | temp_v0_2);
        ASM_KEEP(temp_v0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        result = temp_v0;
    } else {
        result = temp_v0;
    }
    temp_a0 = (void *)0x80010000;
    temp_v1 = (arg0 * 4) + temp_a0;
    temp_v1->unk_29C = result;
    temp_v1->unk_2A0 = 0;
}
