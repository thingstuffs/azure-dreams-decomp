#include "common.h"
#include "records/Rec_D_80174CD8.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;


typedef struct S_80172160_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_80172160_1;   /* temp_v1 in func_80172160 */

typedef struct S_80172160_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80172160_2;   /* temp_v0 in func_80172160 */

typedef struct S_80172160_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80172160_3;   /* temp_a0 in func_80172160 */

typedef struct S_80172160_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80172160_4;   /* temp_s0 in func_80172160 */

typedef struct S_80172160_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172160_5;   /* temp_s2 in func_80172160 */

typedef struct S_80172160_6 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80172160_6;   /* temp_a0_2 in func_80172160 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_801720D0;
extern Rec_D_80174CD8 *D_80174CD8;

void func_80172160(void)
{
    S_80172160_3 *temp_a0;
    S_80172160_6 *temp_a0_2;
    S_80172160_4 *temp_s0;
    S_80172160_5 *temp_s2;
    void *temp_v0;
    S_80172160_1 *temp_v1;
    s32 random;
    s32 coord;

    temp_s2 = D_80174CD8->unk_08;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_16 = 0x1E;
        temp_v1->unk_18 = 0x1E;
        ((S_80172160_2 *)temp_v0)->unk_10 = &D_801720D0;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = ((S_80172160_2 *)temp_v0)->unk_0C;
        temp_a0->unk_06 = 0;
        temp_s0 = ((S_80172160_2 *)temp_v0)->unk_08;
        temp_s0->unk_00.at00.v = temp_s2->unk_00;
        temp_s0->unk_04.at00.v = temp_s2->unk_04;
        temp_s0->unk_08 = temp_s2->unk_08;
        random = rand(temp_a0);
        coord = temp_s0->unk_00.at02.v;
        random &= 0x3F;
        coord -= 0x20;
        coord += random;
        temp_s0->unk_00.at02.v = coord;
        random = rand();
        coord = temp_s0->unk_04.at02.v;
        random &= 0x3F;
        coord -= 0x20;
        coord += random;
        temp_s0->unk_04.at02.v = coord;
        temp_a0_2 = ((S_80172160_2 *)temp_v0)->unk_0C;
        temp_a0_2->unk_1E = 0x1000;
        temp_a0_2->unk_1C = 0x1000;
        temp_a0_2->unk_0E = 0x80;
        temp_a0_2->unk_0D = 0x80;
        temp_a0_2->unk_0C = 0x80;
        temp_a0_2->unk_14 |= 0x80;
        func_8003DB94(temp_a0_2, &D_800DE870, 0);
    }
}

/* MECHANISM: The 32-byte frame holds the source, allocated object, and copied object
   across calls in s2, s1, and s0. Split random-coordinate RMWs keep -0x20 as
   per-use addiu operations instead of a shared saved-register constant. */
