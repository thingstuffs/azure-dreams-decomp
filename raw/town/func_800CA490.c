#include "common.h"

typedef s32 M2C_UNK;
typedef struct {
    s32 value;
} Timer;

extern M2C_UNK func_800C2E84();
extern M2C_UNK D_800C78A8;
extern M2C_UNK D_800D5FE8;
extern Timer D_80113220;

void func_800C7BF0(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    Timer *timer;

    func_800C2E84(arg0, arg2, &D_800D5FE8);
    *(M2C_UNK **)((u8 *)arg0 + 0x50) = &D_800C78A8;
    timer = &D_80113220;
    do {
        timer->value = 0x10;
    } while (0);
}
