#include "common.h"

extern u8 D_8009DDD8[];
extern void func_8040339C(void *task, void *arg1);
extern void func_804032FC(void *task);
extern void func_804061C4(void);
extern void func_80406368(void);
extern void func_80405A64(void);

/* Arm the task's next callback: ready slot -> attach the sub-object, otherwise detach it. */
void func_8001F274(u8 *task) {
    u8 *owner = task - 0x20;

    if (*(s32 *)(D_8009DDD8 + (*(u32 *)(task + 0x28) << 7)) != 0) {
        *(void **)(task + 0x34) = (void *)func_804061C4;
        func_8040339C(owner, task + 0x38);
        *(void **)(task - 0x10) = (void *)func_80405A64;
        return;
    }
    *(void **)(task + 0x34) = (void *)func_80406368;
    func_804032FC(owner);

    *(void **)(task - 0x10) = (void *)func_80405A64;
}
