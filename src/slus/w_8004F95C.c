#include "common.h"

/* Increments a->counter (post-increment), and once counter reaches/exceeds
 * a->limit, installs func_8004F67C as a->func (a no-op callback). Always
 * forwards `a0` to func_8004F884 first. */
typedef struct S_8004F95C {
    void (*func)(void);
    u8 pad4[0x28 - 0x4];
    s32 limit;
    s32 counter;
} S_8004F95C;

extern void func_8004F884(S_8004F95C *a0);
extern void func_8004F67C(void);

void func_8004F95C(S_8004F95C *a0) {
    func_8004F884(a0);
    if (a0->counter++ >= a0->limit) {
        a0->func = func_8004F67C;
    }
}
