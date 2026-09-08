#include "common.h"

typedef struct S_8001D188_3 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001D188_3;   /* page in func_8001D188 */

typedef struct S_8001D188_4 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_8001D188_4;   /* ((S_8001D188_3 *)page)->unk_6000 in func_8001D188 */


typedef struct S_8001D188_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001D188_0;   /* page in func_8001D188 */

typedef struct S_8001D188_1 {
    u8 pad_00[0x24];
    void * unk_24;
    u8 pad_28[0x44];
    void * unk_6C;
    u8 pad_70[0x17C];
    s16 * unk_1EC;
} S_8001D188_1;   /* cursor in func_8001D188 */

typedef struct S_8001D188_2 {
    u8 pad_00[0x3700];
    union { u8 s; volatile u8 u; } unk_3700;   /* accessed as both */
} S_8001D188_2;   /* temp_a2 in func_8001D188 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001D414();
extern s8 D_80016000[];
extern s8 D_8001902C[];

void func_8001D188(s32 arg0) {
    s32 temp_a3;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_a0;
    u8 *temp_v0_2;
    u8 *temp_a1;
    s32 temp_v1;
    s32 var_s1;
    register S_8001D188_2 *temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s8 *temp_a0;
    u8 *page;
    S_8001D188_1 *cursor;
    s16 *entries;
    s32 next_count;
    u8 count;

    do { page = (u8 *)0x80010000; } while (0);
    temp_s2 = ((S_8001D188_4 *)(((S_8001D188_3 *)page)->unk_6000))->unk_38;
    var_s1 = arg0;
    temp_v0 = func_8001D414();
    cursor = ((S_8001D188_0 *)page)->unk_6000;
    cursor = cursor->unk_24;
    cursor = cursor->unk_6C;
    entries = cursor->unk_1EC;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    temp_a3 = *(s16 *)((u8 *)entries + (var_s1 * 0x14));
    temp_a2 = temp_s2 + temp_a3;
    next_count = temp_a2->unk_3700.s;
    next_count += 1;
    temp_a2->unk_3700.s = next_count;
    count = temp_a2->unk_3700.u;
    ASM_USE(count);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    var_a0 = 0;
    temp_a0 = D_8001902C;
    if (count >= *(s16 *)((u8 *)temp_a0 + (((temp_a3 * 3) + temp_v0) * 8))) {
        temp_a2->unk_3700.s = 0U;
    }
    ASM_KEEP_NV(temp_a3);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    temp_a1 = (u8 *)(temp_a3 * 0xC) + temp_s2 + 0x3640;
    do {
        temp_v0_2 = temp_a1 + var_a0;
        temp_v1 = *temp_v0_2;
        *temp_v0_2 = var_s1;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        var_a0 += 1;
        var_s1 = temp_v1;
    } while (var_a0 < 0xC);
}
