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

/* Creates and initializes a child object linked to its parent state. */
void func_80175D7C(void *parent_state) {
    Pair pair;
    s32 pair_first;
    s32 pair_second;
    Pair *pair_ptr;
    void *child;
    S_80175D7C_1 *visual;
    S_80175D7C_2 *child_state;

    child = func_8003FD64(514, (u8 *)parent_state - 0x20);
    if (child != 0) {
        ((S_80175D7C_0 *)child)->unk_10 = D_80175B1C;
        func_8004491C(child, D_80045340);
        pair_first = 0x01000340;
        pair_second = 0x200020;
        pair_ptr = &pair;
        visual = ((S_80175D7C_0 *)child)->unk_0C;
        visual->unk_08 = D_80175FA8;
        visual->unk_1C = 0x1000;
        visual->unk_1E = 0x800;
        child_state = (u8 *)child + 0x20;
        ((S_80175D7C_0 *)child)->unk_20 = parent_state;
        child_state->unk_0A = ((S_80175D7C_3 *)parent_state)->unk_2A;
        child_state->unk_0C = 0x30;
        pair.second = pair_second;
        pair.first = pair_first;
        func_800B835C(D_80175FB4, pair_ptr, 1, 0);
    }
}

/* MECHANISM: The Pair stack object plus long-lived arg0/result locals produces the
   retail 0x28 frame and s1/s0 save contract. Removing inherited ASM_REG/ASM_KEEP
   pins releases both tail argument schedules and closes the reorder-only residue. */
