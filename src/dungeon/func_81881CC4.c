#include "common.h"

typedef struct S_800254C4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800254C4_0;   /* node in func_800254C4 */

typedef struct S_800254C4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800254C4_1;   /* payload in func_800254C4 */

typedef struct S_800254C4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800254C4_2;   /* source in func_800254C4 */

typedef struct S_800254C4_3 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x8];
    s16 unk_26;
} S_800254C4_3;   /* fields in func_800254C4 */

typedef struct S_800254C4_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
} S_800254C4_4;   /* ((S_800254C4_0 *)node)->unk_0C in func_800254C4 */



extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_800250E8[3];
extern s32 D_800252E0[3];

s32 func_800254C4(void *arg0, s16 arg1, s16 arg2, s16 arg3) {
    register void *source = arg0;
    register s16 value1 ASM_REG("$20") = arg1;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s16 value2 ASM_REG("$21") = arg2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s16 mode = arg3;
    register void *node;

    node = func_8003FC64(0x202);
    if (node != 0) {
        register s16 savedMode ASM_REG("$19") = mode;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        s32 modeTest;

        ASM_KEEP(savedMode);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_800254C4_0 *)node)->unk_10 = D_800250E8;
        func_8004491C(node, D_800252E0);
        modeTest = mode << 0x10;
        {
            S_800254C4_1 *payload = ((S_800254C4_0 *)node)->unk_08;

            s32 tailValue;

            if (modeTest == 0) {
                payload->unk_02 =
                    (u16)((((S_800254C4_2 *)source)->unk_02 + (rand() & 0x1F)) - 0x10);
                payload->unk_06 =
                    (u16)((((S_800254C4_2 *)source)->unk_06 + (rand() & 0x1F)) - 0x10);
                tailValue = ((S_800254C4_2 *)source)->unk_0A - 0x50;
            } else {
                payload->unk_02 = ((S_800254C4_2 *)source)->unk_02;
                payload->unk_06 = ((S_800254C4_2 *)source)->unk_06;
                tailValue = ((S_800254C4_2 *)source)->unk_0A;
            }
            payload->unk_0A = tailValue;
        }
        ((S_800254C4_4 *)(((S_800254C4_0 *)node)->unk_0C))->unk_0C = 0xF0;
        {
            S_800254C4_3 *fields = node + 0x20;

            fields->unk_1A = value1;
            fields->unk_1C = value2;
            fields->unk_26 = savedMode;
        }
    }
}

/* MECHANISM: Retail's six saved roles come from the pinned argument/payload lifetimes;
   keeping savedMode at the branch places move s3,s0 in its delay slot.
   A noreturn dispatcher plus a pinned $v0 tail value forms lhu;j;addiu, and the
   final color byte is unsigned so 0xF0 materializes as 240 rather than -16. */
