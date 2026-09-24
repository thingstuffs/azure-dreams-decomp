#include "slus/runtime_directory.h"

/* Initializes runtime state and selects its mode from the configuration byte. */
void func_8003C920(void)
{
    volatile GpTablePrefix default_state;

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
