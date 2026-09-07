#include "common.h"

#include "common.h"

typedef struct {
    s8 type;
    s8 value;
} Slot;

typedef struct {
    u8 pad[0x2C];
    Slot slots[4];
} SlotOwner;

extern void func_80042BDC();

void func_80042B68(SlotOwner *arg0, s8 arg1)
{
    s32 var_s1;
    s8 temp_a1;

    for (var_s1 = 3; var_s1 >= 0; var_s1--) {
        temp_a1 = arg0->slots[var_s1].type;
        if (temp_a1 == arg1) {
            arg0->slots[var_s1].type = 0;
            arg0->slots[var_s1].value = 0;
            func_80042BDC(arg0, arg1);
        }
    }
}
