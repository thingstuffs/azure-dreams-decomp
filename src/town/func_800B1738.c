#include "common.h"

extern s32 D_800D15B0;
extern void func_80049D80(void *arg0, void *arg1);

/* Pass the data pointer and D_800D15B0 to func_80049D80. */
void func_800AEE98(void *data) {
    func_80049D80(data, &D_800D15B0);
}
