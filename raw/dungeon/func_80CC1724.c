#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80173B98;
extern u8 D_80176338[];
extern u8 D_80176340[];

void func_80174F24(void *arg0, void *in_arg1, void *in_arg2, void *arg3)
{
    register void *arg1 ASM_REG("$18") = in_arg1;
    register void *arg2 ASM_REG("$19") = in_arg2;
    s32 scratch;
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            u8 *table = D_80176338;

            FIELD(arg2, u8 *, 0x2C) = table;
            func_80047784(arg2,
                table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, u16, 0x98) |= 8;
            FIELD(arg3, u32, 0x1C) &= ~0x08000000;
            FIELD(arg0, s16, 0x9E) = 5;
            FIELD(arg0, s32, 0xA0) = 0;
            FIELD(arg0, u8, 0x9B)++;
        } else {
            goto shared;
        }
        /* fall through */

    case 1:
        {
            s16 timer;
            s32 delta;
            s32 position;
            s32 velocity;

            FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
            timer = FIELD(arg0, s16, 0x9E);
            if (timer != 0) {
                delta = FIELD(arg2, u8, 0x24) << 6;
                position = FIELD(arg1, s16, 2) - 0x20;
                delta -= position;
                velocity = (delta << 16) / timer;

                position = FIELD(arg1, s16, 6);
                FIELD(arg1, s32, 0x0C) = velocity;
                position -= 0x20;
                delta = FIELD(arg2, u8, 0x25) << 6;
                delta -= position;
                FIELD(arg1, s32, 0x10) =
                    (delta << 16) / FIELD(arg0, s16, 0x9E);

                FIELD(arg0, s32, 0xA0) =
                    (-func_800644B8(FIELD(arg0, s16, 0x9E) * 409)) << 9;
            }

            FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
            timer = FIELD(arg0, u16, 0x9E) - 1;
            FIELD(arg0, s16, 0x9E) = timer;
            if (timer >= 0) {
                goto state2;
            }
            FIELD(arg0, s32, 0x90) = 0;
            FIELD(arg0, u16, 0x98) &= 0xFFF7;
            FIELD(arg3, u32, 0x1C) |= 0x08000000;
            FIELD(arg0, u8, 0x9B)++;
        }
        /* fall through */

    case 2:
state2:
        if (FIELD(arg3, u32, 0x1C) & 0x08000000) {
            u8 *table;

            FIELD(arg0, u16, 0x98) &= 0xFFF7;
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
            func_800A2B04(arg1,
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
            table = D_80176340;
            FIELD(arg2, u8 *, 0x2C) = table;
            func_80047784(arg2,
                table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, u8, 0x9B)++;
        }
        break;

    default:
        break;
    }

shared:
    {
        s16 timer;
        s16 *counter;
        u32 flags;

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if (timer > 0) {
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1,
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        counter = (s16 *)&D_80083460;
        if (counter[4] != 0) {
            counter[4]--;
        }

        flags = FIELD(arg3, u32, 0x1C);
        if (flags & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
            }
            goto update_actor;
        }
        if (flags & 0x410) {
            goto update_actor;
        }
        if (flags & 0x20000) {
            FIELD(arg3, s16, 0x2A) = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                D_80082E80[0x24], D_80082E80[0x25], &scratch);
        }

update_actor:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, s32 *, 0x8C) = &D_80173B98;
            func_800A9A04(arg3);
        }
        ASM_KEEP(arg1);
        ASM_KEEP(arg2);
    }
}
