#include "common.h"

#include "common.h"

typedef struct {
    u32 value[8];
} FuncState;

extern u8 D_80016000[0x10];
extern FuncState D_8006B200;
extern s32 D_80080A6C;
extern u8 D_80082E6A[];

extern FuncState D_8002D594;

/* Initializes runtime state and selects its mode from the configuration byte. */
void func_8003C920(void) {
    volatile FuncState default_state;

    __builtin_memcpy(&default_state, &D_8002D594, 0x20);
    if (D_80082E6A[0] != 2) {
        D_8006B200 = D_8002D594;
        D_80080A6C = 4;
    } else {
        D_8006B200.value[0] = 0;
        D_8006B200.value[1] = (u32)D_80016000;
        D_80080A6C = 1;
    }
}
