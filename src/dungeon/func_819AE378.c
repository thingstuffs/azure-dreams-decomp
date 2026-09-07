#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct UnalignedWord {
    u32 value;
} __attribute__((packed)) UnalignedWord;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern M2C_UNK D_80025A34;
extern M2C_UNK D_80025AAC;

typedef struct S_80025B78_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80025B78_0;   /* temp_v0 in func_80025B78 */

typedef struct S_80025B78_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025B78_1;   /* temp_v1 in func_80025B78 */

typedef struct S_80025B78_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025B78_2;   /* arg1 in func_80025B78 */

typedef struct S_80025B78_3 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025B78_3;   /* temp_v1_2 in func_80025B78 */

typedef struct S_80025B78_4 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025B78_4;   /* arg2 in func_80025B78 */

void *func_80025B78(void *arg0, S_80025B78_2 *arg1, S_80025B78_4 *arg2)
{
    void *temp_v0;
    S_80025B78_1 *temp_v1;
    S_80025B78_3 *temp_v1_2;

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != NULL) {
        ((S_80025B78_0 *)temp_v0)->unk_10 = &D_80025A34;
        func_8004491C(temp_v0, &D_80025AAC);
        temp_v1 = ((S_80025B78_0 *)temp_v0)->unk_08;
        temp_v1->unk_02 = arg1->unk_02;
        temp_v1->unk_06 = arg1->unk_06;
        temp_v1->unk_0A = arg1->unk_0A;
        temp_v1_2 = ((S_80025B78_0 *)temp_v0)->unk_0C;
        temp_v1_2->unk_1C = arg2->unk_1C;
        temp_v1_2->unk_1E = arg2->unk_1E;
        temp_v1_2->unk_20 = arg2->unk_20;
        temp_v1_2->unk_16 = arg2->unk_16;
        temp_v1_2->unk_18 = arg2->unk_18;
        temp_v1_2->unk_1A = arg2->unk_1A;
        temp_v1_2->unk_0C = arg2->unk_0C;
        temp_v1_2->unk_14 = arg2->unk_14;
        temp_v1_2->unk_00 = arg2->unk_00;
        temp_v1_2->unk_08 = arg2->unk_08;
        temp_v1_2->unk_10 = arg2->unk_10;
        temp_v1_2->unk_04 = arg2->unk_04;
        {
            u32 copy0;
            u32 copy1;
            u32 copy2;
            register u32 copy3;

            copy0 = ((UnalignedWord *)arg0)[0].value;
            copy1 = ((UnalignedWord *)arg0)[1].value;
            copy2 = ((UnalignedWord *)arg0)[2].value;
            copy3 = ((UnalignedWord *)arg0)[3].value;
            ASM_KEEP(copy0);   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP(copy1);   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP(copy2);   /* MATCH pin: load-bearing for the whole function shape */
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[0].value = copy0;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[1].value = copy1;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[2].value = copy2;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[3].value = copy3;
            copy0 = ((UnalignedWord *)arg0)[4].value;
            copy1 = ((UnalignedWord *)arg0)[5].value;
            copy2 = ((UnalignedWord *)arg0)[6].value;
            copy3 = ((UnalignedWord *)arg0)[7].value;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[4].value = copy0;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[5].value = copy1;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[6].value = copy2;
            ((UnalignedWord *)((u8 *)temp_v0 + 0x20))[7].value = copy3;
        }
    }
    return temp_v0;
}
