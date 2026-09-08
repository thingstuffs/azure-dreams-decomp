#include "common.h"

typedef struct S_800B19F8_1 {
    u8 pad_00[0x48];
    void * unk_48;
    void * unk_4C;
    void * unk_50;
    void * unk_54;
} S_800B19F8_1;   /* arg0 in func_800B19F8 */

typedef struct S_800B19F8_2 {
    s32 unk_00;
    void * unk_04;
} S_800B19F8_2;   /* ((S_800B19F8_1 *)arg0)->unk_48 in func_800B19F8 */

typedef struct S_800B19F8_3 {
    s32 unk_00;
    void * unk_04;
} S_800B19F8_3;   /* ((S_800B19F8_1 *)arg0)->unk_4C in func_800B19F8 */

typedef struct S_800B19F8_4 {
    s32 unk_00;
    void * unk_04;
} S_800B19F8_4;   /* ((S_800B19F8_1 *)arg0)->unk_54 in func_800B19F8 */

typedef struct S_800B19F8_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B19F8_5;   /* ((S_800B19F8_1 *)arg0)->unk_50 in func_800B19F8 */

typedef struct S_800B19F8_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B19F8_6;   /* ((S_800B19F8_2 *)(((S_800B19F8_1 *)arg0)->unk_48))->unk_04 in func_800B19F8 */

typedef struct S_800B19F8_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B19F8_7;   /* ((S_800B19F8_3 *)(((S_800B19F8_1 *)arg0)->unk_4C))->unk_04 in func_800B19F8 */

typedef struct S_800B19F8_8 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B19F8_8;   /* ((S_800B19F8_4 *)(((S_800B19F8_1 *)arg0)->unk_54))->unk_04 in func_800B19F8 */

typedef struct S_800B19F8_9 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B19F8_9;   /* ((S_800B19F8_5 *)(((S_800B19F8_1 *)arg0)->unk_50))->unk_04 in func_800B19F8 */




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern void *func_8004DA74(void *a0, u8 *a1, s32 a2);
extern void func_800B180C(void *a0, s32 a1);
extern void func_800B18F8(s32 a0);
extern s32 D_80078D6C[4];
extern u8 D_800D1560[16];

typedef struct S_800B19F8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_800B19F8_0;   /* arg0 in func_800B19F8 */

void func_800B19F8(S_800B19F8_0 *arg0)
{
    register s32 v88 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    ((S_800B19F8_2 *)(((S_800B19F8_1 *)arg0)->unk_48))->unk_00 = (s32) D_80078D6C;
    ((S_800B19F8_6 *)(((S_800B19F8_2 *)(((S_800B19F8_1 *)arg0)->unk_48))->unk_04))->unk_08 = 0;
    ((S_800B19F8_6 *)(((S_800B19F8_2 *)(((S_800B19F8_1 *)arg0)->unk_48))->unk_04))->unk_0A = 0;

    ((S_800B19F8_3 *)(((S_800B19F8_1 *)arg0)->unk_4C))->unk_00 = arg0->unk_08;
    ((S_800B19F8_7 *)(((S_800B19F8_3 *)(((S_800B19F8_1 *)arg0)->unk_4C))->unk_04))->unk_08 = 0;
    ((S_800B19F8_7 *)(((S_800B19F8_3 *)(((S_800B19F8_1 *)arg0)->unk_4C))->unk_04))->unk_0A = 0xF;

    ((S_800B19F8_4 *)(((S_800B19F8_1 *)arg0)->unk_54))->unk_00 =
        (s32) func_8004DA74(arg0->unk_0C, D_800D1560, 0);
    ((S_800B19F8_8 *)(((S_800B19F8_4 *)(((S_800B19F8_1 *)arg0)->unk_54))->unk_04))->unk_08 = 0x43;
    v88 = 0x88;
    ((S_800B19F8_8 *)(((S_800B19F8_4 *)(((S_800B19F8_1 *)arg0)->unk_54))->unk_04))->unk_0A = v88;

    ((S_800B19F8_9 *)(((S_800B19F8_5 *)(((S_800B19F8_1 *)arg0)->unk_50))->unk_04))->unk_08 = 0x67;
    ((S_800B19F8_9 *)(((S_800B19F8_5 *)(((S_800B19F8_1 *)arg0)->unk_50))->unk_04))->unk_0A = v88;

    func_800B180C(arg0, v88);
    func_800B18F8(arg0->unk_08);
}
