#include "common.h"

s32 func_800A9878(s32 arg0) {
    register u8 *base ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 carrier;
    s32 result;
    s32 index;

    base = (u8 *)0x800D0000;
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    carrier = *(s16 *)(base + 0x1054);
    result = -1;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    index = 0;
    if (carrier != result) {
        s32 sentinel = result;
        carrier = (s32)(base + 0x1054);
loop:
        if (*(s16 *)carrier == arg0) {
            result = index;
        } else {
            carrier += 2;
            index++;
            if (*(s16 *)carrier == sentinel) {
                result = -1;
            } else {
                goto loop;
            }
        }
    }
    return result;
}

/* MECHANISM: Frameless leaf with no saved registers or stack objects.
   Guarded $a2 holds page 0x800D0000; one guarded $v1 carrier is reused from
   the initial signed halfword to the loop cursor, matching retail lifetimes. */
