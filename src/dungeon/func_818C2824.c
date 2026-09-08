#include "common.h"

typedef struct {
    u8 pad00[0x28];
    u8 flags;
    u8 pad29[0x3B];
    u16 value64;
} Obj;

extern s32 func_8009D218(Obj *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD568(Obj *, s32);
extern void func_800B4C7C(s32, Obj *, s16, s32);
extern void func_800AD4D0(Obj *);

void func_818C2824(Obj *arg0, s32 arg1)
{
    register s32 amount ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 adjusted;

    if (func_8009D218(arg0, 4) == 0) {
        amount = func_800A6870(arg1 & 0xFF) + 0x10;
        adjusted = amount;
        if (arg0->flags & 1) {
            adjusted = amount + ((s16)amount >> 1);
        }
        arg0->value64 += adjusted;
        func_800AD568(arg0, adjusted);
        func_800B4C7C(0x8004, arg0, (s16)arg0->value64, 1);
        func_800AD4D0(arg0);
    }
}
