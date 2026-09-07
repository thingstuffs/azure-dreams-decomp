#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

extern void *func_8003FD64();
extern void func_8004491C(void *, void *);
extern s32 D_80053858[4];
extern u8 D_80083498[];

typedef struct CopyBlock {
    s32 words[12];
} CopyBlock;

void func_800206F4(s32 arg0, void *arg1)
{
    void *obj;

    obj = func_8003FD64(1, &D_80083498);
    if (obj != NULL) {
        *(CopyBlock *)((s8 *)obj + 0x20) = *(CopyBlock *)arg1;
        FIELD(obj, s32, 0x10) = arg0;
        func_8004491C(obj, &D_80053858);
    }
}
