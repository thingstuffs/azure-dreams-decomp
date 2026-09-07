#include "common.h"

#define UNALIGNED32(expr) (expr)

typedef struct {
    u8 bytes[12];
} Block12;

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern s32 D_800D4954;
extern Block12 D_800E233C;


typedef struct S_800D4AB0_0 {
    u8 pad_00[0x5A];
    s16 unk_5A;
    s16 unk_5C;
    u8 pad_5E[0x2A];
    void * unk_88;
} S_800D4AB0_0;   /* temp_v1 in func_800D4AB0 */

typedef struct S_800D4AB0_1 {
    u8 pad_00[0x88];
    void * unk_88;
} S_800D4AB0_1;   /* arg0 in func_800D4AB0 */

typedef struct S_800D4AB0_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800D4AB0_2;   /* temp_a3 in func_800D4AB0 */

typedef struct S_800D4AB0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D4AB0_3;   /* temp_a0 in func_800D4AB0 */

typedef struct S_800D4AB0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D4AB0_4;   /* temp_v1_2 in func_800D4AB0 */

typedef struct S_800D4AB0_5_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800D4AB0_5_pre;   /* the 0x18 bytes before ((S_800D4AB0_1 *)arg0)->unk_88 in func_800D4AB0, addressed as ((S_800D4AB0_1 *)arg0)->unk_88[-1] */

void func_800D4AB0(S_800D4AB0_1 *arg0) {
    S_800D4AB0_3 *temp_a0;
    S_800D4AB0_2 *temp_a3;
    void *temp_v0;
    S_800D4AB0_0 *temp_v1;
    S_800D4AB0_4 *temp_v1_2;

    temp_v0 = func_8003FC64(0x12);
    temp_v1 = temp_v0 + 0x20;
    if (temp_v0 != 0) {
        temp_v1->unk_5A = 0x78;
        temp_v1->unk_5C = 0x78;
        temp_v1->unk_88 = arg0->unk_88;
        (*(s32 * *)((u8 *)temp_v0 + 0x10)) = &D_800D4954;
        func_8004491C(temp_v0, &D_80045340);
        temp_a3 = (*(void * *)((u8 *)temp_v0 + 0xC));
        temp_a3->unk_10 = 0x60;
        temp_a3->unk_06 = 0;
        temp_a3->unk_14 = temp_a3->unk_14 | 0xC;
        temp_v1_2 = ((S_800D4AB0_5_pre *)(arg0->unk_88))[-1].unk_00;
        temp_a0 = (*(void * *)((u8 *)temp_v0 + 0x8));
        temp_a0->unk_02 = temp_v1_2->unk_02;
        temp_a0->unk_06 = temp_v1_2->unk_06;
        temp_a0->unk_0A = temp_v1_2->unk_0A - 0x32;
        temp_a3 = (*(void * *)((u8 *)temp_v0 + 0xC));
        temp_a3->unk_0E = 0x80;
        temp_a3->unk_0D = 0x80;
        temp_a3->unk_0C = 0x80;
        temp_a3->unk_1E = 0;
        temp_a3->unk_1C = 0;
        (*(Block12 *)((u8 *)temp_v0 + 0x96)) = D_800E233C;
        temp_a3->unk_08 = temp_v0 + 0x96;
    }
}
