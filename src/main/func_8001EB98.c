#include "common.h"

extern void func_804045C8(void *, s32);
extern void func_80404618(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);
extern void func_80405C0C(void);

void func_8001EB98(void *arg0) {
    register s32 var_s1 ASM_REG("$17");
    void *var_s0;

    var_s1 = 0;
    var_s0 = arg0;
    while (1) {
        if (var_s1 == *((s32 *)arg0 + 0xB)) {
            func_80404618(((void **)var_s0)[1], 1);
            var_s1++;
            func_80405C0C();
        }
        if (var_s1 == *((s32 *)arg0 + 0xA)) {
            func_804045C8(((void **)var_s0)[1], 1);
            var_s1++;
            func_80405C0C();
        }
        func_80404668(((void **)var_s0)[1]);
        var_s1++;
        var_s0 = (u8 *)var_s0 + 4;
        if (var_s1 >= 5) {
            func_80405A00(*((s32 *)arg0 + 7), *((s32 *)arg0 + 0xA));
            ASM_KEEP(var_s1);
            return;
        }
    }
}
