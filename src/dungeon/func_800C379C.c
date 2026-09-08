#include "common.h"

extern s32 func_80041E70(void *);
extern s32 func_800990FC(void);
extern s32 func_80099194(char *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern s32 func_800A56E0(s32);
extern s32 func_800A5720(s32);
extern s32 func_800A6D30(void);
extern s32 func_800C8078();

extern char D_800E1A88[];
extern char D_800E1A9D[];
extern char D_800E1AC2[];
extern char D_800E1AD0[];

s32 func_800C8EFC(void *arg0, s32 arg1)
{
    s32 mod;
    s32 handle;
    s32 text;
    u8 count;

    if (func_800C8078() != 0) {
        return 0;
    }

    {
        s32 random;
        register s32 masked ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s32 denominator;
        u8 divisor;

        random = func_800A6D30();
        divisor = *(u8 *)((u8 *)arg0 + 3);
        if (divisor != 0) {
            masked = random & 0xFFFF;
            denominator = divisor;
            ASM_KEEP(denominator);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            mod = masked % denominator;
        } else {
            mod = 0;
        }
    }

    {
        register s32 signed_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        register s32 work ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        work = arg1 << 16;
        signed_arg = work >> 16;
        work = mod < signed_arg;
        if (!work) {
            work = 0xFF;
            if (signed_arg != work) {
                return 0;
            }
        }
    }

    count = *(u8 *)((u8 *)arg0 + 0x26);
    if (count < 2) {
        return 0;
    }

    {
        void *object;
        register s32 decremented ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        object = arg0;
        ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        decremented = count - 1;
        *(u8 *)((u8 *)arg0 + 0x26) = decremented;
        func_80041E70(object);
    }
    handle = func_800990FC();
    text = func_80099194(D_800E1A88, handle);

    {
        register void *message_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

        message_object = arg0;
        if (*(s32 *)((u8 *)arg0 + 0x14) & 0x4000) {
            text = func_80099734(message_object, text);
            text = func_80099194(D_800E1A9D, text);
        } else {
            text = func_80099194(D_800E1AC2, text);
            text = func_80099734(arg0, text);
            text = func_80099194(D_800E1AD0, text);
        }
    }

    func_80099290(text);
    func_800A5720(handle);
    func_800A56E0(0x615);
    return 1;
}

/* MECHANISM: The true-space CFG naturally holds arg0/arg1 in s0/s1 with a 0x20 frame.
   Split early/late live ranges plus guarded a0/v0 roles reproduce remainder and byte RMW code.
   Keeping the message object live on both flag edges fills the beq delay slot and removes the nop. */
