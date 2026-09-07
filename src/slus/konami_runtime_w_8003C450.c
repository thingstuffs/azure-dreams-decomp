#include "common.h"

#include "common.h"

typedef struct {
    unsigned char pad[0x1e];
    u16 value;
} Func8003C450State;

extern void func_8003C488(void);

void func_8003C450(void **arg0, s32 arg1, Func8003C450State *arg2) {
    u32 value;

    value = arg2->value;
    value += 0x400;
    arg2->value = value;
    if ((value & 0xffff) < 0x1000) {
        return;
    }
    arg2->value = 0x1000;
    *arg0 = (void *)func_8003C488;
}
