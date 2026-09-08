#include "common.h"

typedef s32 M2C_UNK;
typedef struct {
    s32 value;
} Timer;

extern M2C_UNK func_800C2E84();
extern M2C_UNK D_800C78A8;
extern M2C_UNK D_800D5FE8;
extern Timer D_80113220;

/* Initialize the object callback and set the shared timer to 16. */
void func_800C7BF0(void *object, M2C_UNK unused, M2C_UNK init_data) {
    Timer *timer;

    func_800C2E84(object, init_data, &D_800D5FE8);
    *(M2C_UNK **)((u8 *)object + 0x50) = &D_800C78A8;
    timer = &D_80113220;
    do {
        timer->value = 0x10;
    } while (0);
}
