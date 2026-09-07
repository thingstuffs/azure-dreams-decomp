#include "common.h"



typedef s32 M2C_UNK;
typedef struct {
    s32 words[4];
} __attribute__((packed)) Copy16;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

extern void func_80064BC0(void *, s32 *);

typedef struct S_80025FB0_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    s8 unk_12;
    s8 unk_13;
    s8 unk_14;
    s8 unk_15;
} S_80025FB0_0;   /* arg1 in func_80025FB0 */

typedef struct S_80025FB0_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_80025FB0_1;   /* arg0 in func_80025FB0 */

/* Copy a compact record, widen its signed fields, and apply zero values when its flag is clear. */
void func_80025FB0(S_80025FB0_1 *dst, S_80025FB0_0 *src) {
    s32 zero_args[4];
    s32 signed_field;

    *(Copy16 *)dst = *(Copy16 *)src;
    signed_field = src->unk_10;
    
    dst->unk_10 = signed_field;
    dst->unk_14 = (s32) src->unk_12;
    dst->unk_18 = (s32) src->unk_13;
    dst->unk_1C = (s32) src->unk_14;
    if (src->unk_15 == 0) {
        zero_args[2] = 0;
        zero_args[1] = 0;
        zero_args[0] = 0;
        func_80064BC0(dst, zero_args);
    }
}
