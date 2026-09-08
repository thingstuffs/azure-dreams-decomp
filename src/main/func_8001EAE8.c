#include "common.h"

extern void func_80403D7C(s32, s32);
extern void func_804045C8(s32, s32);
extern void func_80404668(s32);
extern void func_80405A00(s32, s32);
/* noreturn only via config/noreturn_syms.txt so maspsx jal->j keeps delay fill */
extern void func_80405B5C(void);

void func_8001EAE8(void *arg0) {
    s32 sentinel;
    void *p;
    register s32 i ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    if (*(s32 *)((u8 *)arg0 + 0x48) == 1) {
        sentinel = 1;
    } else {
        func_80403D7C(*(s32 *)((u8 *)arg0 + 0x18), *(s32 *)((u8 *)arg0 + 0x44));
        sentinel = 0;
    }
    i = 0;
    p = arg0;
loop_3:
    if (i == *(s32 *)((u8 *)arg0 + 0x28)) {
        func_804045C8(*(s32 *)((u8 *)p + 4), sentinel);
        i += 1;
        func_80405B5C();
        /* no return: fall through is dead; avoids j-epilogue after tail j */
    }
    func_80404668(*(s32 *)((u8 *)p + 4));
    i += 1;
    if (i >= 5) {
        func_80405A00(*(s32 *)((u8 *)arg0 + 0x1C), *(s32 *)((u8 *)arg0 + 0x28));
        return;
    }
    p = (u8 *)p + 4;
    goto loop_3;
}
