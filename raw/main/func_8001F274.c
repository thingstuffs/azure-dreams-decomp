#include "common.h"

extern u8 D_8009DDD8[];
extern void func_8040339C(void *arg0, void *arg1);
extern void func_804062D4(void) __attribute__((noreturn));
extern void func_804032FC(void *arg0);
extern void func_804061C4(void);
extern void func_80406368(void);
extern void func_80405A64(void);

void func_8001F274(u8 *arg0) {
    u8 *temp_a0 = arg0 - 0x20;

    if (*(s32 *)(D_8009DDD8 + (*(u32 *)(arg0 + 0x28) << 7)) != 0) {
        void *a1 = arg0 + 0x38;
        void *fn = (void *)func_804061C4;
        /* Keep fn live so la schedules before a1 and store fills the jal delay slot. */
        __asm__ __volatile__("" : "=r"(fn) : "0"(fn));
        *(void **)(arg0 + 0x34) = fn;
        func_8040339C(temp_a0, a1);
        func_804062D4();
        return;
    }
    *(void **)(arg0 + 0x34) = (void *)func_80406368;
    func_804032FC(temp_a0);
    *(void **)(arg0 - 0x10) = (void *)func_80405A64;
}
