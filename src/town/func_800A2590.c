#include "common.h"

extern s32 func_8009F6E4(void);
extern s32 func_8009FB2C();
extern s32 func_8009FD48();

void func_8009FCF0(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    s8 args[4];
    s32 slot;
    s8 *argp;

    slot = func_8009F6E4();
    argp = args;
    if (slot == -1) {
        s32 result;

        ASM_KEEP(slot);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        result = 0;
        ASM_TAILSLOT_PIN_TIED(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_8009FD48(slot, argp);
        return;
    }

    args[0] = arg0;
    args[1] = arg1;
    args[2] = arg2;
    args[3] = arg3;
    func_8009FB2C(slot, argp);
}

/* MECHANISM: The four-byte args array and separate slot produce the retail 0x30 frame and s0-s3 saves.
   Fixed a0/a1 locals preserve the runtime slot and one shared stack-address setup across the failure edge.
   A tied v0 tail-slot pin lets LEAD 28 sink zero into the converted func_8009FD48 jump delay. */
