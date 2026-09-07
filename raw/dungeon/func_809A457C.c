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

void func_80175D7C(void *arg0) {
    Pair pair;
    s32 pair_first;
    s32 pair_second;
    Pair *pair_arg;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FD64(514, (u8 *)arg0 - 0x20);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, u8 **, 0x10) = D_80175B1C;
        func_8004491C(temp_v0, D_80045340);
        pair_first = 0x01000340;
        pair_second = 0x200020;
        pair_arg = &pair;
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1, u8 **, 8) = D_80175FA8;
        M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x1E) = 0x800;
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_v1_2, u16 *, 0xA) = M2C_FIELD(arg0, u16 *, 0x2A);
        M2C_FIELD(temp_v1_2, s16 *, 0xC) = 0x30;
        pair.second = pair_second;
        pair.first = pair_first;
        func_800B835C(D_80175FB4, pair_arg, 1, 0);
    }
}

/* MECHANISM: The Pair stack object plus long-lived arg0/result locals produces the
   retail 0x28 frame and s1/s0 save contract. Removing inherited ASM_REG/ASM_KEEP
   pins releases both tail argument schedules and closes the reorder-only residue. */
