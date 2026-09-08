#include "common.h"
typedef long long s64;



typedef s32 M2C_UNK;

typedef struct {
    s32 words[6];
} Copy24;

typedef struct {
    s32 words[4];
} Copy16;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define MULT_HI(a, b) (0)

extern s32 D_80045C34[3];
void func_80025078() __attribute__((noreturn));
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_80024C48;
extern M2C_UNK D_80025AF0;

typedef struct S_818C370C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818C370C_0;   /* temp_v0 in func_818C370C */

typedef struct S_818C370C_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
} S_818C370C_1;   /* temp_s2 in func_818C370C */

typedef struct S_818C370C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818C370C_2;   /* arg0 in func_818C370C */

typedef struct S_818C370C_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C370C_3;   /* temp_s0 in func_818C370C */

s32 func_818C370C(S_818C370C_2 *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_ret;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_v0;
    s32 word4;
    s32 word5;
    char byte_value;
    S_818C370C_3 *temp_s0;
    S_818C370C_1 *temp_s2;
    void *temp_v0;
    void *temp_v1;
    register s32 tail_ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s2 = temp_v0 + 0x20;
        ((S_818C370C_0 *)temp_v0)->unk_10 = &D_80024C48;
        ((S_818C370C_0 *)temp_v0)->unk_20 = arg0;
        temp_s2->unk_0E = 0;
        temp_s2->unk_10 = 0;
        temp_ret = func_80069EF8();
        temp_s2->unk_12 = (s16)(temp_ret % 7);
        byte_value = 0x80;
        temp_s2->unk_14 = arg0->unk_14;
        temp_s0 = ((S_818C370C_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = byte_value;
        temp_s0->unk_0D = byte_value;
        temp_s0->unk_0C = byte_value;
        temp_s0->unk_12 = 0x7DCF;
        temp_s0->unk_14 = temp_s0->unk_14 | 0xC;
        temp_s0->unk_10 = temp_s0->unk_10 | 0x20;
        temp_s0->unk_14 = temp_s0->unk_14 | 0x100;
        func_8003DB94(temp_s0, &D_80025AF0, 0);
        temp_v0_2 = func_80069EF8();
        temp_v1_2 = temp_v0_2;
        ASM_KEEP(temp_v0_2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        var_v0 = temp_v0_2 >> 0xC;
        if (temp_v1_2 < 0) {
            var_v0 = (temp_v1_2 + 0xFFF) >> 0xC;
        }
        temp_s0->unk_1A = temp_v1_2 - (var_v0 << 0xC);
        temp_lo = 0x1400 / (s16)temp_s2->unk_14;
        temp_s0->unk_1E = temp_lo;
        temp_s0->unk_1C = temp_lo;
        func_8004491C(temp_v0, D_80045C34);
        temp_v1 = ((S_818C370C_0 *)temp_v0)->unk_08;
        tail_ret = (s32)temp_v0;
        *(Copy16 *)temp_v1 = *(Copy16 *)arg1;
        ASM_KEEP(tail_ret);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        word4 = ((Copy24 *)arg1)->words[4];
        word5 = ((Copy24 *)arg1)->words[5];
        ((Copy24 *)temp_v1)->words[4] = word4;
        ((Copy24 *)temp_v1)->words[5] = word5;
        func_80025078(word4, word5);
        return (s32)temp_v0;
    }
    return 0;
}
