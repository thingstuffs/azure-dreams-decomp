#include "common.h"

typedef struct S_8009BFD8_0 {
    u8 pad_00[0x7C];
    void * unk_7C;
} S_8009BFD8_0;   /* arg0 in func_8009BFD8 */

typedef struct S_8009BFD8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8009BFD8_1;   /* arg2 in func_8009BFD8 */

typedef struct S_8009BFD8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009BFD8_2;   /* arg3 in func_8009BFD8 */

typedef struct S_8009BFD8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009BFD8_3;   /* ((S_8009BFD8_0 *)arg0)->unk_7C in func_8009BFD8 */



extern s32 func_8008C180();
extern void func_8009BFC0();
extern s32 func_800C1D44();
extern s16 D_800D45AA[];

void func_8009BFD8(S_8009BFD8_0 *arg0, void *arg1, S_8009BFD8_1 *arg2, S_8009BFD8_2 *arg3)
{
    s32 index;
    s16 delta;

    func_8009BFC0();
    if (arg0->unk_7C == 0) {
        return;
    }

    index = func_800C1D44(
        func_8008C180(arg2->unk_02, arg2->unk_06) & 0xFFFF);
    if (index != 0) {
        delta = arg2->unk_0A - D_800D45AA[index];
        if (delta >= 0x19) {
            if (delta < 0x29) {
                arg3->unk_08 =
                    ((S_8009BFD8_3 *)(arg0->unk_7C))->unk_04;
                return;
            }
            arg3->unk_08 =
                ((S_8009BFD8_3 *)(arg0->unk_7C))->unk_08;
            return;
        }
    }

    arg3->unk_08 = ((S_8009BFD8_3 *)(arg0->unk_7C))->unk_00;
}

/* MECHANISM: The unused second parameter preserves the retail $a2/$a3-to-$s0/$s2
   argument roles and 0x20 frame. A signed halfword delta and s16 table restore
   the two-byte index; the +4/+8 selections store before noreturn tail exits. */
