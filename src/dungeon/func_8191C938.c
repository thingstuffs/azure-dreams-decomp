#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((u8 *)(expr) + (offset)))
#ifndef NULL
#define NULL 0
#endif

extern void func_8002426C() __attribute__((noreturn));
extern s32 func_8003DB94(void *, void *, s16);
extern void *func_8003FC64(u32);
extern s32 func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80024048[];
extern u8 D_80045340[];
extern u8 D_800DED70[];

typedef struct CopyBlock {
    s32 word[6];
} CopyBlock;

typedef struct S_8191C938_0 {
    u8 pad_00[0x8];
    CopyBlock * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8191C938_0;   /* temp_v0 in func_8191C938 */

typedef struct S_8191C938_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} S_8191C938_1;   /* temp_s0 in func_8191C938 */

typedef struct S_8191C938_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8191C938_2;   /* temp_s0_2 in func_8191C938 */

typedef struct S_8191C938_3 {
    u8 pad_00[0x16];
    u16 unk_16;
    u8 pad_18[0x8];
    CopyBlock * unk_20;
} S_8191C938_3;   /* arg0 in func_8191C938 */

typedef struct S_8191C938_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8191C938_4;   /* temp_a0 in func_8191C938 */

void *func_8191C938(S_8191C938_3 *arg0)
{
    s32 temp_v0_2;
    CopyBlock *temp_a0;
    S_8191C938_1 *temp_s0;
    S_8191C938_2 *temp_s0_2;
    void *temp_v0;
    CopyBlock *temp_v0_3;
    void *result;
    register u16 override;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0 + 0x20;
        ((S_8191C938_0 *)temp_v0)->unk_10 = D_80024048;
        ((S_8191C938_0 *)temp_v0)->unk_20 = arg0;
        temp_s0->unk_04 = 0;
        temp_s0->unk_06 = 6;
        temp_v0_2 = rand();
        temp_s0->unk_08 = temp_v0_2 % 0x1000;
        temp_s0->unk_0A = 0x10;
        temp_s0_2 = ((S_8191C938_0 *)temp_v0)->unk_0C;
        temp_s0_2->unk_0D = 0x80;
        temp_s0_2->unk_0C = 0x80;
        temp_s0_2->unk_0E = 0;
        temp_s0_2->unk_12 = 0x7DCF;
        temp_s0_2->unk_14 |= 0xC;
        temp_s0_2->unk_10 |= 0x20;
        temp_s0_2->unk_14 |= 0x100;
        func_8003DB94(temp_s0_2, D_800DED70, 0);
        temp_s0_2->unk_1E = 0x1000;
        temp_s0_2->unk_1C = 0x1000;
        func_8004491C(temp_v0, D_80045340);
        temp_a0 = ((S_8191C938_0 *)temp_v0)->unk_08;
        temp_v0_3 = arg0->unk_20;
        *temp_a0 = *temp_v0_3;
        override = arg0->unk_16;
        ASM_KEEP(override);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        result = temp_v0;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ((S_8191C938_4 *)temp_a0)->unk_0A = override;
        func_8002426C(temp_a0);
        return temp_v0;
    }
    result = NULL;
    return result;
}
