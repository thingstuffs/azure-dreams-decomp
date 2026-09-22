#include "common.h"
#ifndef NULL
#define NULL 0
#endif
/* Point the object's two handler slots at one of two sub-blocks, chosen by a flag word. */
void func_8001D6C8(void *obj) {
    s32 *flag_ptr = *(s32 **)((u8 *)obj + 4);
    if (flag_ptr != NULL) {
        s32 flag = *flag_ptr;
        if (flag != 0) {
            void *alt_block = (u8 *)obj + 0xF8;
            *(void **)((u8 *)obj + 0x274) = NULL;
            *(void **)((u8 *)obj + 0x284) = alt_block;
            return;
        }
        *(void **)((u8 *)obj + 0x274) = (void *)((u8 *)obj + 0x80);
        *(void **)((u8 *)obj + 0x284) = NULL;
    }
}
