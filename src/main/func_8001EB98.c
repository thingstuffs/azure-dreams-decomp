#include "common.h"

extern void func_804045C8(void *, s32);
extern void func_80404618(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);

void func_80405B98(void *arg0) {
    s32 var_s1;

    for (var_s1 = 0; var_s1 < 5; var_s1++) {
        if (var_s1 == *((s32 *)arg0 + 0xB)) {
            func_80404618(((void **)arg0)[var_s1 + 1], 1);
        } else if (var_s1 == *((s32 *)arg0 + 0xA)) {
            func_804045C8(((void **)arg0)[var_s1 + 1], 1);
        } else {
            func_80404668(((void **)arg0)[var_s1 + 1]);
        }
    }
    func_80405A00(*((s32 *)arg0 + 7), *((s32 *)arg0 + 0xA));
}
