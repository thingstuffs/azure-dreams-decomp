#include "common.h"

extern void func_804086CC(void);
extern void func_804086BC(s32, s32, s32);

void func_802F1684(s32 arg0) {
    s32 value = arg0;

    func_804086CC();
    func_804086BC(value, 63, 0);
}
