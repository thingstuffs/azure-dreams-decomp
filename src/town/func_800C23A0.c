#include "common.h"

typedef struct S_800BFB00_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void);
    u8 pad_14[0xC];
    u16 unk_20;
} S_800BFB00_0;   /* temp_v0 in func_800BFB00 */

typedef struct S_800BFB00_1 {
    u8 pad_00[0x2];
    volatile u16 unk_02;
    volatile u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
} S_800BFB00_1;   /* temp_a0 in func_800BFB00 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern u8 D_80083498[12];
extern u16 D_80083780[6];
extern void func_800BFB8C(void);

void func_800BFB00(s16 arg0, s16 arg1) {
    u16 temp_v1;
    S_800BFB00_1 *temp_a0;
    void *temp_v0;

    temp_v0 = func_8003FD64(2, D_80083498);
    if (temp_v0 != 0) {
        ((S_800BFB00_0 *)temp_v0)->unk_10 = func_800BFB8C;
        ((S_800BFB00_0 *)temp_v0)->unk_20 = D_80083780[1];
        temp_a0 = (s8 *)temp_v0 + 0x20;
        temp_a0->unk_02 = D_80083780[3];
        temp_v1 = D_80083780[5];
        temp_a0->unk_08 = arg0;
        temp_a0->unk_0A = arg1;
        temp_a0->unk_0E = 6;
        temp_a0->unk_04 = temp_v1;
    }
}
