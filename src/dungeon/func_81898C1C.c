#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80024530(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80024370;
extern M2C_UNK D_80024E40;
extern M2C_UNK D_80045340;

typedef struct S_8002441C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} S_8002441C_0;   /* temp_v0 in func_8002441C */

typedef struct S_8002441C_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002441C_1;   /* temp_s0 in func_8002441C */

typedef struct S_8002441C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002441C_2;   /* temp_v1 in func_8002441C */

typedef struct S_8002441C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002441C_3;   /* arg1 in func_8002441C */

void *func_8002441C(s32 arg0, S_8002441C_3 *arg1) {
    S_8002441C_1 *temp_s0;
    S_8002441C_0 *temp_v0;
    S_8002441C_2 *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == 0) {
        register s32 tail_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */

        tail_v0 = 0;
        ASM_TAILSLOT_PIN(tail_v0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024530();
    }
    temp_v0->unk_10 = &D_80024370;
    temp_s0 = temp_v0->unk_0C;
    temp_v0->unk_20 = arg0;
    temp_v0->unk_24 = 0;
    temp_s0->unk_0E = 0x80;
    temp_s0->unk_0D = 0x80;
    temp_s0->unk_0C = 0x80;
    temp_s0->unk_0E = 0xC0;
    func_8003DB94(temp_s0, &D_80024E40, 0);
    temp_s0->unk_1C = 0x2000;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_12 = 0x7DCF;
    temp_s0->unk_14 = (u16)(temp_s0->unk_14 | 0xC);
    temp_s0->unk_10 = (u16)(temp_s0->unk_10 | 0x20);
    temp_s0->unk_14 = (u16)(temp_s0->unk_14 | 0x100);
    func_8004491C(temp_v0, &D_80045340);
    temp_v1 = temp_v0->unk_08;
    temp_v1->unk_00 = arg1->unk_00;
    temp_v1->unk_04 = arg1->unk_04;
    temp_v1->unk_08 = arg1->unk_08;
    temp_v1->unk_0C = arg1->unk_0C;
    temp_v1->unk_10 = arg1->unk_10;
    temp_v1->unk_14 = arg1->unk_14;
    return temp_v0;
}

/* MECHANISM: Unsigned byte fields preserve retail's positive 0x80/0xC0 immediates.
   A scoped $v0 zero plus ASM_TAILSLOT_PIN triggers LEAD 28b, sinking the
   live-for-compiler/dead-for-callee value into the noreturn tail-j delay slot. */
