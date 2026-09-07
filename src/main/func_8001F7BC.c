#include "common.h"

extern void func_804045C8(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);
/* func_8040680C is a known zero-arg noreturn (config/noreturn_syms.txt); it is
 * NOT annotated here so gcc keeps the trailing var_s1++ live for the fall-through
 * merge. maspsx then rewrites the jal into a tail `j` and the (semantically dead)
 * increment fills the converted j's delay slot exactly as retail. */
extern void func_8040680C(void);

void func_8001F7BC(void *arg0) {
    void *var_s0;
    register s32 var_s1 ASM_REG("$17");   /* MATCH pin: keeps a statement from moving across a call/branch */

    var_s1 = 0;
    var_s0 = arg0;
loop_1:
    if (var_s1 == *(s32 *)((u8 *)arg0 + 0x2C)) {
        func_804045C8(*(void **)((u8 *)var_s0 + 0xC), 1);
        var_s1++;
        func_8040680C();
    }
    func_80404668(*(void **)((u8 *)var_s0 + 0xC));
    var_s1++;
    if (var_s1 < 5) {
        var_s0 = (u8 *)var_s0 + 4;
        goto loop_1;
    }
    func_80405A00(*(s32 *)((u8 *)arg0 + 4), *(s32 *)((u8 *)arg0 + 0x2C));
}
