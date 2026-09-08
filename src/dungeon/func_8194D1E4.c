#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_80024918;

typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct {
    UnalignedS32 word;
} Packed4;

typedef struct {
    s32 words[4];
} FourWords;

typedef struct {
    Packed4 part[2];
} Packed8;


typedef struct S_800249E4_0 {
    u8 pad_00[0x74];
    s16 unk_74;
    s16 unk_76;
} S_800249E4_0;   /* temp_a0 in func_800249E4 */

void func_800249E4(s32 arg0, void *arg1, void *arg2, s16 arg3, FourWords arg4, FourWords arg8, Packed8 arg12) {
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 copy0;
    s32 copy1;
    s32 copy2;
    s32 copy3;
    s32 tail0;
    s32 tail1;
    void *temp_a0;
    register void *temp_v0 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *stackbase ASM_REG("$29");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_a0 = temp_v0 + 0x20;
        (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = &D_80024918;
        (*(s32 *)((u8 *)temp_v0 + 0x20)) = arg0;
        ((S_800249E4_0 *)temp_a0)->unk_74 = 0;
        ((S_800249E4_0 *)temp_a0)->unk_76 = arg3;
        temp_v0_2 = (*(s32 *)((u8 *)arg1 + 0));
        (*(s32 *)((u8 *)temp_a0 + 0x1C)) = temp_v0_2;
        (*(s32 *)((u8 *)temp_a0 + 0x34)) = temp_v0_2;
        temp_v0_3 = (*(s32 *)((u8 *)arg1 + 4));
        (*(s32 *)((u8 *)temp_a0 + 0x20)) = temp_v0_3;
        (*(s32 *)((u8 *)temp_a0 + 0x38)) = temp_v0_3;
        temp_v0_4 = (*(s32 *)((u8 *)arg1 + 8));
        (*(s32 *)((u8 *)temp_a0 + 0x24)) = temp_v0_4;
        (*(s32 *)((u8 *)temp_a0 + 0x3C)) = temp_v0_4;
        (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) (*(s32 *)((u8 *)arg2 + 0));
        (*(s32 *)((u8 *)temp_a0 + 8)) = (s32) (*(s32 *)((u8 *)arg2 + 4));
        (*(s32 *)((u8 *)temp_a0 + 0xC)) = (s32) (*(s32 *)((u8 *)arg2 + 8));
        (*(s32 *)((u8 *)temp_a0 + 0x40)) = (s32) ((s32) ((*(s32 *)((u8 *)arg2 + 0)) - (*(s32 *)((u8 *)arg1 + 0))) >> 3);
        (*(s32 *)((u8 *)temp_a0 + 0x44)) = (s32) ((s32) ((*(s32 *)((u8 *)arg2 + 4)) - (*(s32 *)((u8 *)arg1 + 4))) >> 3);
        (*(s32 *)((u8 *)temp_a0 + 0x48)) = (s32) ((s32) ((*(s32 *)((u8 *)arg2 + 8)) - (*(s32 *)((u8 *)arg1 + 8))) >> 3);
        copy0 = arg4.words[0];
        copy1 = arg4.words[1];
        copy2 = arg4.words[2];
        copy3 = arg4.words[3];
        (*(s32 *)((u8 *)temp_v0 + 0x6C)) = copy0;
        (*(s32 *)((u8 *)temp_v0 + 0x70)) = copy1;
        (*(s32 *)((u8 *)temp_v0 + 0x74)) = copy2;
        (*(s32 *)((u8 *)temp_v0 + 0x78)) = copy3;
        copy0 = arg8.words[0];
        copy1 = arg8.words[1];
        copy2 = arg8.words[2];
        copy3 = arg8.words[3];
        (*(s32 *)((u8 *)temp_v0 + 0x7C)) = copy0;
        (*(s32 *)((u8 *)temp_v0 + 0x80)) = copy1;
        (*(s32 *)((u8 *)temp_v0 + 0x84)) = copy2;
        (*(s32 *)((u8 *)temp_v0 + 0x88)) = copy3;
        stackbase = (u8 *)&arg12 - 0x58;
        tail0 = (*(Packed4 *)((u8 *)stackbase + 0x58)).word;
        tail1 = (*(Packed4 *)((u8 *)stackbase + 0x5C)).word;
        (*(Packed4 *)((u8 *)temp_v0 + 0x8C)).word = tail0;
        (*(Packed4 *)((u8 *)temp_v0 + 0x90)).word = tail1;
    }
}

/* MECHANISM: Two 16-byte plus one packed 8-byte by-value args preserve the 0x28/s0-s3 hold set.
   Scalarized copy bursts color through v0,v1,a0,a1 while the allocation result is held in a2.
   A derived sp base with ASM_KEEP prevents packed tail loads folding from lwl/lwr pairs into lw;
   the paired tail source reads then also eliminate both downstream branch-displacement drifts. */
