#include "common.h"


typedef struct {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec;

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern s32 D_80083780[3];
extern s32 D_801717A8;
extern PackedVec D_80173B40;
extern void *D_80175D60;


typedef struct S_80171C7C_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80171C7C_0;   /* temp_a3 in func_80171C7C */

typedef struct S_80171C7C_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80171C7C_1;   /* temp_a0 in func_80171C7C */

typedef struct S_80171C7C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80171C7C_2;   /* temp_v1 in func_80171C7C */

void func_80171C7C(void) {
    s32 *temp_v1;
    S_80171C7C_1 *temp_a0;
    S_80171C7C_0 *temp_a3;
    void *temp_v0;
    u16 temp_flags;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != 0) {
        (*(s16 *)((u8 *)temp_v0 + 0x38)) = 0;
        (*(s32 * *)((u8 *)temp_v0 + 0x10)) = &D_801717A8;
        func_8004491C(temp_v0, &D_80045340);
        temp_a3 = (*(void * *)((u8 *)temp_v0 + 0xC));
        temp_a3->unk_06 = 0;
        temp_a0 = (*(void * *)((u8 *)temp_v0 + 8));
        temp_v1 = D_80083780;
        temp_a0->unk_00 = ((S_80171C7C_2 *)temp_v1)->unk_00;
        temp_a0->unk_04 = ((S_80171C7C_2 *)temp_v1)->unk_04;
        temp_a0->unk_08 = ((S_80171C7C_2 *)temp_v1)->unk_08;
        temp_a3 = (*(void * *)((u8 *)temp_v0 + 0xC));
        temp_a3->unk_1E = 0x1000;
        temp_a3->unk_1C = 0x1000;
        temp_a3->unk_0E = 0x80;
        temp_a3->unk_0D = 0x80;
        temp_a3->unk_0C = 0x80;
        temp_flags = temp_a3->unk_14;
        D_80175D60 = temp_v0;
        temp_a3->unk_14 = temp_flags | 0x80;
        (*(PackedVec *)((u8 *)temp_v0 + 0x48)) = D_80173B40;
        temp_a3->unk_08 = (u8 *)temp_v0 + 0x48;
    }
}
