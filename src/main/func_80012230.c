#include "common.h"

extern s32 func_80021FF0(s32, s32, s32);
extern void func_80023004(void *);
extern void func_8002519C(s32);
extern void func_80020984(void);

extern s32 D_8002593C;
extern s32 D_800251A4;
extern s32 D_80024F7C;

#ifndef NON_MATCHING
register s32 *dead_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#else
s32 *dead_v0;
#endif

void func_80025230(s8 *arg0) {
    s32 result;
    s8 *call_arg;

    result = func_80021FF0(*(s32 *)(arg0 + 0x28), 0x80010000, 1);
    call_arg = arg0 - 0x20;
    if (result == 0) {
#ifndef NON_MATCHING
        dead_v0 = &D_8002593C;
        *(s32 **)(arg0 + 0x34) = dead_v0;
#else
        *(s32 **)(arg0 + 0x34) = &D_8002593C;
#endif
        func_80023004(call_arg);
#ifndef NON_MATCHING
        dead_v0 = (s32 *)0x80020000;
        __asm__ __volatile__("" : "=r"(dead_v0) : "0"(dead_v0));
        dead_v0 = (s32 *)((u8 *)dead_v0 + 0x4F7C);
#else
        dead_v0 = &D_80024F7C;
#endif
    } else {
        func_8002519C(0x80010000);
        dead_v0 = &D_800251A4;
    }
    *(s32 **)(arg0 - 0x10) = dead_v0;
    func_80020984();
    *(s32 *)(arg0 + 0x40) = 0;
}
