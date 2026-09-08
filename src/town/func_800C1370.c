#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BEAD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800BEAD0_0;   /* temp_v0 in func_800BEAD0 */

typedef struct S_800BEAD0_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BEAD0_1;   /* temp_v1 in func_800BEAD0 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK func_80053DA8();
extern M2C_UNK D_80045340;
extern M2C_UNK D_8007789C;
extern s32 D_80083780;
extern M2C_UNK D_800BEBA4;

s32 func_800BEAD0(void)
{
    s32 *temp_v0_2;
    s32 color;
    volatile s32 *temp_s0;
    s32 temp_z;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        func_80053DA8(0x512);
        temp_s0 = ((S_800BEAD0_0 *)temp_v0)->unk_08;
        ((S_800BEAD0_0 *)temp_v0)->unk_10 = &D_800BEBA4;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = temp_v0 + 0x20;
        ASM_KEEP(temp_v1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        (*(s16 *)((u8 *)temp_v1 + 2)) = 0x10;
        color = 0x00800000;
        temp_s0[0] = D_80083780;
        temp_v0_2 = &D_80083780;
        temp_s0[1] = temp_v0_2[1];
        color |= 0x8080;
        temp_z = temp_v0_2[2];
        temp_s0[3] = 0x100000;
        temp_s0[5] = 0xFFF00000;
        temp_s0[2] = temp_z + 0xFFA00000;
        temp_v1 = ((S_800BEAD0_0 *)temp_v0)->unk_0C;
        ((S_800BEAD0_1 *)temp_v1)->unk_1E = 0x1000;
        ((S_800BEAD0_1 *)temp_v1)->unk_1C = 0x1000;
        ((S_800BEAD0_1 *)temp_v1)->unk_08 = &D_8007789C;
        ((S_800BEAD0_1 *)temp_v1)->unk_0C = color;
    }
    return 0;
}

/* MECHANISM: The 0x20 frame and s0/s1 holds already matched retail.
   Depinning the page base and color restored the page-lui/color-lui sched2 order.
   Retaining only ASM_KEEP(temp_v1) preserves the standalone s1+0x20 address word. */
