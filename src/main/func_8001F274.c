#include "common.h"

extern u8 D_8009DDD8[];
extern void func_8040339C(void *arg0, void *arg1);
extern void func_804032FC(void *arg0);
extern void func_804061C4(void);
extern void func_80406368(void);
extern void func_80405A64(void);

void func_8001F274(u8 *arg0) {
    u8 *temp_a0 = arg0 - 0x20;

    if (*(s32 *)(D_8009DDD8 + (*(u32 *)(arg0 + 0x28) << 7)) != 0) {
        *(void **)(arg0 + 0x34) = (void *)func_804061C4;
        func_8040339C(temp_a0, arg0 + 0x38);
        *(void **)(arg0 - 0x10) = (void *)func_80405A64;
        return;
    }
    *(void **)(arg0 + 0x34) = (void *)func_80406368;
    func_804032FC(temp_a0);

    *(void **)(arg0 - 0x10) = (void *)func_80405A64;
}
