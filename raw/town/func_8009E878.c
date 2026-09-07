#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8008C180();
extern void func_8009BFC0();
extern void func_8009C0A4(void) __attribute__((noreturn));
extern s32 func_800C1D44();
extern s16 D_800D45AA[];

void func_8009BFD8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 index;
    s16 delta;

    func_8009BFC0();
    if (FIELD(arg0, void *, 0x7C) == 0) {
        return;
    }

    index = func_800C1D44(
        func_8008C180(FIELD(arg2, s16, 2), FIELD(arg2, s16, 6)) & 0xFFFF);
    if (index != 0) {
        delta = FIELD(arg2, u16, 0xA) - D_800D45AA[index];
        if (delta >= 0x19) {
            if (delta < 0x29) {
                FIELD(arg3, s32, 8) =
                    FIELD(FIELD(arg0, void *, 0x7C), s32, 4);
                func_8009C0A4();
            }
            FIELD(arg3, s32, 8) =
                FIELD(FIELD(arg0, void *, 0x7C), s32, 8);
            func_8009C0A4();
        }
    }

    FIELD(arg3, s32, 8) = FIELD(FIELD(arg0, void *, 0x7C), s32, 0);
}

/* MECHANISM: The unused second parameter preserves the retail $a2/$a3-to-$s0/$s2
   argument roles and 0x20 frame. A signed halfword delta and s16 table restore
   the two-byte index; the +4/+8 selections store before noreturn tail exits. */
