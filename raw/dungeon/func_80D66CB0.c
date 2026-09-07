#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80172E0C();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800E2348[8];

void func_801724B0(void *arg0, s32 arg1, void *arg2, void *arg3) {
    s32 mode;
    s16 result;
    register s32 state ASM_REG("$16");
    s32 x;
    s32 y;

    if ((FIELD(arg3, s8, 0x71) > 0) &&
        (FIELD(arg3, u8, 0x71) > FIELD(arg3, s16, 0x8A))) {
        if (FIELD(arg2, u8 *, 0x2C) != D_800E2348) {
            FIELD(arg2, u8 *, 0x2C) = D_800E2348;
            func_80047784(
                arg2,
                D_800E2348[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, s16, 0x9E) = 0;
        }

        x = FIELD(arg2, u8, 0x24);
        y = FIELD(arg2, u8, 0x25);
        mode = (FIELD(arg3, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000;
        func_8009A3D0(x, y, mode);

        result = func_800A0818(
            x,
            y,
            FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x74),
            FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x7C),
            (u8 *)arg0 + 0x98);
        state = (s16)func_8009A66C(result, arg2, arg3, 0x20);

        FIELD(arg2, u8, 0x24) =
            FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x74);
        mode = 0x3000;
        FIELD(arg2, u8, 0x25) =
            FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x7C);
        FIELD(arg3, u16, 0x8A)++;

        {
            s32 next_x = FIELD(arg2, u8, 0x24);
            s32 next_y = FIELD(arg2, u8, 0x25);

            if (FIELD(arg3, s32, 0x1C) & 0x2000) {
                mode = 0x300;
            }
            func_8009A21C(next_x, next_y, mode);
        }

        ASM_KEEP(state);
        FIELD(arg3, s16, 0x2A) = result;
        if (state == 3) {
            if (!(D_80083462 & 0x80) && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
                func_80172E0C(arg0, arg1, arg2, arg3);
                FIELD(arg0, s32, 0x8C) = 0;
                goto post_state;
            }
        }

        FIELD(arg0, s8, 0x9A) = 0xF;
        FIELD(arg0, s32, 0x8C) = 0;

post_state:
        FIELD(arg3, s32, 0x1C) |= 0x40000000;
        if (D_80083462 & 0x80) {
            FIELD(arg0, s16, 0x96) = 0;
            goto end;
        }

        FIELD(arg0, s16, 0x96) = 8;
        x = FIELD(arg3, u8, 0x71);
        if (x > 0) {
            FIELD(arg0, s16, 0x96) = 8 / x;
        }
    }

end:
    return;
}

/* MECHANISM: The four live arguments and two call results naturally produce the retail 0x38 frame and saved-register order.
   A guarded s0 pin holds the signed func_8009A66C result; placing ASM_KEEP before the result store lets that sh fill the bne delay slot.
   Explicit mode initialization plus scoped next-coordinate locals reproduce the post-call load/store and branch emission order. */
