#include "common.h"
#include "m2c_compat.h"
M2C_UNK func_80058588();
s32 func_80071424();
extern s32 D_80084D5C;
void func_80526B18(void *ptr)
{
    s16 selector;
    u16 value;
    u16 next_value;
    void *field_ptr;
    field_ptr = *((void **) (((s8 *) ptr) + 0xC));
    func_80058588(*(*((s16 **) (((s8 *) ptr) + 8))), func_80071424(*((s32 *) (((s8 *) ptr) + 4))),
        *((s32 *) (((s8 *) ptr) + 4)));
    selector = *((s16 *) (((s8 *) ptr) + 0));
    switch (selector) {
    case 0:
        do {
            value = (*((u16 *) (((s8 *) ptr) + 2))) - 1;
            *((u16 *) (((s8 *) ptr) + 2)) = value;
            if ((value << 0x10) > 0) {
                return;
            }
            next_value = (*((u16 *) (((s8 *) ptr) + 0))) + 1;
            value = (*((u16 *) (((s8 *) ptr) + 0x1C))) & 0xFFFD;
        } while (0);
        *((u16 *) (((s8 *) ptr) + 0x1C)) = value;
        *((u16 *) (((s8 *) ptr) + 0)) = next_value;
        return;
    case 1:
        if ((*((u16 *) (((s8 *) field_ptr) + 0x2A))) & 1) {
            *((u16 *) (((s8 *) ptr) + (-2))) = (u16) ((*((u16 *) (((s8 *) ptr) + (-2)))) | 0x8000);
            *((s32 *) 0x80084D5C) = D_80084D5C | 0x8000;
        }
    }
}
