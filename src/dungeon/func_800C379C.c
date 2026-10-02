#include "common.h"

extern s32 func_80041E70(void *);
extern s32 func_800990FC(void);
extern s32 func_80099194(char *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern s32 func_800A56E0(s32);
extern s32 func_800A5720(s32);
extern s32 func_800A6D30(void);
extern s32 func_800C8078(void *);

extern char D_800E1A88[];
extern char D_800E1A9D[];
extern char D_800E1AC2[];
extern char D_800E1AD0[];

/* Roll the actor's stack-split chance; on a hit decrement the stack and post the split message. */
s32 func_800C8EFC(void *actor, s32 chance)
{
    s32 mod;
    s32 handle;
    s32 text;
    u8 count;
    s32 signed_arg;

    if (func_800C8078(actor) != 0) {
        return 0;
    }

    {
        signed_arg = func_800A6D30() & 0xFFFF;
        if (*(u8 *)((u8 *)actor + 3) != 0) {
            mod = signed_arg % *(u8 *)((u8 *)actor + 3);
        } else {
            mod = 0;
        }
    }

    {
        s32 work;

        text = chance << 16;
        signed_arg = text >> 16;
        work = mod < signed_arg;
        if (!work) {
            work = 0xFF;
            if (signed_arg != work) {
                return 0;
            }
        }
    }

    count = *(u8 *)((u8 *)actor + 0x26);
    if (count < 2) {
        return 0;
    }

    {
        void *object;
        s32 decremented;

        object = actor;
        decremented = count - 1;
        *(u8 *)((u8 *)actor + 0x26) = decremented;
        func_80041E70(object);
    }
    handle = func_800990FC();
    text = func_80099194(D_800E1A88, handle);

    {
        s32 named = *(s32 *)((u8 *)actor + 0x14) & 0x4000;
        void *msg = actor;
        if (named) {
            text = func_80099734(msg, text);
            text = func_80099194(D_800E1A9D, text);
        } else {
            text = func_80099194(D_800E1AC2, text);
            text = func_80099734(actor, text);
            msg = D_800E1AD0;
            text = func_80099194(msg, text);
        }
    }

    func_80099290(text);
    func_800A5720(handle);
    func_800A56E0(0x615);
    return 1;
}
