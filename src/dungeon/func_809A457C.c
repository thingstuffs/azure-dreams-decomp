#include "common.h"



typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Pair {
    s32 first;
    s32 second;
} Pair;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800B835C();
extern u8 D_80045340[12];
extern u8 D_80175B1C[12];
extern u8 D_80175FA8[12];
extern u8 D_80175FB4[12];

typedef struct S_80175D7C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80175D7C_0;   /* temp_v0 in func_80175D7C */

typedef struct S_80175D7C_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_80175D7C_1;   /* temp_v1 in func_80175D7C */

typedef struct S_80175D7C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s16 unk_0C;
} S_80175D7C_2;   /* temp_v1_2 in func_80175D7C */

typedef struct S_80175D7C_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175D7C_3;   /* arg0 in func_80175D7C */

void func_80175D7C(void *arg0) {
    Pair pair;
    s32 pair_first;
    s32 pair_second;
    Pair *pair_arg;
    void *temp_v0;
    S_80175D7C_1 *temp_v1;
    S_80175D7C_2 *temp_v1_2;

    temp_v0 = func_8003FD64(514, (u8 *)arg0 - 0x20);
    if (temp_v0 != 0) {
        ((S_80175D7C_0 *)temp_v0)->unk_10 = D_80175B1C;
        func_8004491C(temp_v0, D_80045340);
        pair_first = 0x01000340;
        pair_second = 0x200020;
        pair_arg = &pair;
        temp_v1 = ((S_80175D7C_0 *)temp_v0)->unk_0C;
        temp_v1->unk_08 = D_80175FA8;
        temp_v1->unk_1C = 0x1000;
        temp_v1->unk_1E = 0x800;
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        ((S_80175D7C_0 *)temp_v0)->unk_20 = arg0;
        temp_v1_2->unk_0A = ((S_80175D7C_3 *)arg0)->unk_2A;
        temp_v1_2->unk_0C = 0x30;
        pair.second = pair_second;
        pair.first = pair_first;
        func_800B835C(D_80175FB4, pair_arg, 1, 0);
    }
}

/* MECHANISM: The Pair stack object plus long-lived arg0/result locals produces the
   retail 0x28 frame and s1/s0 save contract. Removing inherited ASM_REG/ASM_KEEP
   pins releases both tail argument schedules and closes the reorder-only residue. */
