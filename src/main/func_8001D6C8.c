#include "common.h"
#ifndef NULL
#define NULL 0
#endif
extern void func_80404700(void) __attribute__((noreturn));

void func_8001D6C8(void *arg0) {
    s32 *t = *(s32 **)((u8 *)arg0 + 4);
    if (t != NULL) {
        s32 v = *t;
        if (v != 0) {
            void *p = (u8 *)arg0 + 0xF8;
            *(void **)((u8 *)arg0 + 0x274) = NULL;
            *(void **)((u8 *)arg0 + 0x284) = p;
            func_80404700();
        }
        __asm__("");
        *(void **)((u8 *)arg0 + 0x274) = (void *)((u8 *)arg0 + 0x80);
        *(void **)((u8 *)arg0 + 0x284) = NULL;
    }
}
