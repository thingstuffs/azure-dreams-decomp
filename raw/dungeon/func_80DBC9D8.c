#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174890(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171E20[];
extern u8 D_80175404[];
extern u8 D_8017540C[];

void func_801741D8(void *in0, void *in1, void *in2, void *in3)
{
    register void *arg0 ASM_REG("$18") = in0;
    register void *arg1 ASM_REG("$19") = in1;
    register void *arg2 ASM_REG("$17") = in2;
    void *arg3;
    u8 state;
    u8 *global_state;
    void *path_arg;
    register void *final_arg ASM_REG("$4");
    s8 tile;

    state = FIELD(arg0, u8, 0x9B);
    arg3 = in3;
    switch (state) {
    case 0:
        if (FIELD(arg2, u16, 0x14) & 0xE000) {
            u8 *counter;

            FIELD(arg2, void *, 0x2C) = D_80175404;
            func_80047784(arg2,
                D_80175404[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            counter = (u8 *)&D_80083460;
            FIELD(counter, u16, 0xA)--;
            goto increment_state;
        }
        break;

    case 1:
        if ((s16)func_80042900(arg3, 1) == 0) {
            goto set_effect;
        }

        global_state = (u8 *)&D_80083460;
        if (FIELD(global_state, u16, 2) & 0x1000) {
            break;
        }

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                break;
            }
        }

        if (FIELD(arg3, u8, 0x25) == 0) {
            if (FIELD(global_state, u16, 2) & 0x2008) {
                break;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            break;
        }

        if ((s16)func_800A2C34(arg3) != 0) {
            break;
        }

        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            break;
        }

        if ((s16)func_800A2C34(arg3) != 0) {
            break;
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80174890(arg0, arg1, arg2, arg3);
            break;
        }

        if (FIELD(arg3, s8, 0x6D) == 0) {
            break;
        }

        if ((s16)func_800A2C34(arg3) != 0) {
            if ((s16)func_8009A180(
                    arg3, (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
                break;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((s16)func_80042900(arg3, 1) != 0) {
            path_arg = D_80082E80;
            tile = FIELD(arg2, s8, 0x26);
            if (tile != FIELD(D_80082E80, s8, 0x26) || tile < 0) {
                s16 distance;

                distance = func_8009FD40(D_80082E80, arg2);
                final_arg = arg3;
                if (distance >= 2) {
                    goto final_call;
                }
                path_arg = final_arg;
            }
            if ((func_800A6D30(path_arg) & 7) == 0) {
                func_80042B68(arg3, 1);
            }
        }

        final_arg = arg3;
final_call:
        if ((s16)func_80042900(final_arg, 1) != 0) {
            break;
        }

set_effect:
        FIELD(arg2, void *, 0x2C) = D_8017540C;
        func_80047784(arg2,
            D_8017540C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            goto set_owner;
        } else {
            register u8 *counter ASM_REG("$2") = (u8 *)&D_80083460;
            ASM_KEEP(counter);
            FIELD(counter, u16, 0xA)++;
        }

increment_state:
        FIELD(arg0, u8, 0x9B)++;
        break;

    case 2:
        if (FIELD(arg2, u16, 0x14) & 0xE000) {
            register u8 *counter ASM_REG("$2") = (u8 *)&D_80083460;
            ASM_KEEP(counter);
            FIELD(counter, u16, 0xA)--;
set_owner:
            FIELD(arg0, void *, 0x8C) = D_80171E20;
        }
        break;

    default:
        break;
    }
    return;
}

/* MECHANISM: Keep the s2/s3/s1 argument homes but remove their entry ASM_KEEP fences;
   sched2 then emits the 0x28-frame tail saves as s0,ra,s4 and delays a3->s0.
   A named s16 distance plus two-edge $a0 final_arg makes word 167 target the final call. */
