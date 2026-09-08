#include "common.h"

extern void func_80096A5C(void *, u8, s8, s32);

/* Passes an indexed byte and the object's signed field to func_80096A5C. */
void func_80096A30(void *object, u8 *values, s32 index) {
    func_80096A5C(object, values[index], ((s8 *)object)[4], 0);
}
