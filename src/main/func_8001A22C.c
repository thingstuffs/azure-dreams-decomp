#include "common.h"

extern s32 D_804094E8[4];
extern s32 D_804094E8_2[4];
extern s32 D_804094E8_3[4];
extern s32 D_804094E8_4[4];
extern s32 D_804094EC[4];
extern s32 D_80409500[4];
__asm__(".set D_804094E8, 0x804094E8");
__asm__(".set D_804094E8_2, 0x804094E8");
__asm__(".set D_804094E8_3, 0x804094E8");
__asm__(".set D_804094E8_4, 0x804094E8");
__asm__(".set D_804094EC, 0x804094EC");
__asm__(".set D_80409500, 0x80409500");

extern void func_804014E4(void);
extern s32 func_80408674(s32 arg0);
extern s32 func_80401298(void) __attribute__((noreturn));

s32 func_8001A22C(void) {
    s32 var_s0;

    var_s0 = 0;

    if (D_804094E8[0] == 2) {
        func_804014E4();
        if (func_80408674(D_804094EC[0]) == 0) {
            D_804094E8_2[0] = 0;
            var_s0 = 5;
            ASM_TAILSLOT_PIN_TIED(var_s0);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            return func_80401298();
        }
        D_80409500[0] = 0;
        D_804094E8_3[0] = D_804094E8_4[0] + 1;
    }
    return var_s0;
}
