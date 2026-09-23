#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_800A9358(s32 arg1, s32 arg2);

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
} Struct800ABDC8;

/* Process the initial value and each linked record value until the chain ends. */
s32 func_800A9528(void *object, s32 x, s32 initial_value) {
    s32 current_value;
   

    current_value = initial_value;
    object = (Struct800ABDC8 *)object;
    for (;;) {
           
        func_800A9358(current_value, x);
        current_value = *(s32 *)((u8 *)object - 8);
        object = (Struct800ABDC8 *)((u8 *)current_value + 0x20);
        if (current_value == 0) {
            break;
        }
           
        x = ((Struct800ABDC8 *)current_value)->unk08;
   
        current_value = ((Struct800ABDC8 *)current_value)->unk0C;
    }
    return 0;
}
