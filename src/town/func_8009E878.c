#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


extern s32 func_8008C180();
extern void func_8009BFC0();
extern void func_8009C0A4(void) __attribute__((noreturn));
extern s32 func_800C1D44();
extern s16 D_800D45AA[];





typedef struct S_8009BFD8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009BFD8_3;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_7C.as_pv in func_8009BFD8 */

void func_8009BFD8(Rec_func_80094268_arg0 *arg0, void *arg1, Rec_D_800E3D7C *arg2, Rec_D_80082E80 *arg3)
{
    s32 index;
    s16 delta;

    func_8009BFC0();
    if (arg0->unk_7C.as_pv == 0) {
        return;
    }

    index = func_800C1D44(
        func_8008C180(arg2->unk_00.at02_s16.v, arg2->unk_04.at02_s16.v) & 0xFFFF);
    if (index != 0) {
        delta = arg2->unk_08.at02_u16.v - D_800D45AA[index];
        if (delta >= 0x19) {
            if (delta < 0x29) {
                arg3->unk_08 =
                    ((S_8009BFD8_3 *)(arg0->unk_7C.as_pv))->unk_04;
                func_8009C0A4();
            }
            arg3->unk_08 =
                ((S_8009BFD8_3 *)(arg0->unk_7C.as_pv))->unk_08;
            func_8009C0A4();
        }
    }

    arg3->unk_08 = ((S_8009BFD8_3 *)(arg0->unk_7C.as_pv))->unk_00;
}

/* MECHANISM: The unused second parameter preserves the retail $a2/$a3-to-$s0/$s2
   argument roles and 0x20 frame. A signed halfword delta and s16 table restore
   the two-byte index; the +4/+8 selections store before noreturn tail exits. */
