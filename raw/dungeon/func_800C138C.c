#include "common.h"

typedef struct Func800C138CData {
    u8 pad0[8];
    void *arg1;
    void *arg2;
} Func800C138CData;

#ifdef NON_MATCHING
#define KEEP_REG(value) ((void)0)
#else
#define KEEP_REG(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
#endif

extern void func_800C6B40(void *arg0, void *arg1, void *arg2, s32 arg3);
extern s32 func_800C6B00(void *arg0, void *arg1, void *arg2);

s32 func_800C6AEC(void *arg0, void *arg1, void *arg2) {
    register void *next ASM_REG("$16") = arg0;
    register void *data ASM_REG("$6");

    KEEP_REG(next);
    func_800C6B40(next, arg1, arg2, 0);
    data = *((void **)next - 2);
    if (data == 0) {
        KEEP_REG(data);
        return 0;
    }
    next = (u8 *)data + 0x20;
    KEEP_REG(next);
    return func_800C6B00(next, ((Func800C138CData *)data)->arg1,
                         ((Func800C138CData *)data)->arg2);
}
