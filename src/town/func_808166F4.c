#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800206F4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800206F4_0;   /* obj in func_800206F4 */



extern void *func_8003FD64();
extern void func_8004491C(void *, void *);
extern s32 D_80053858[4];
extern u8 D_80083498[];

typedef struct CopyBlock {
    s32 words[12];
} CopyBlock;

/* Creates an object with the supplied value and 48-byte initialization block. */
void func_800206F4(s32 init_value, void *init_data)
{
    void *obj;

    obj = func_8003FD64(1, &D_80083498);
    if (obj != NULL) {
        *(CopyBlock *)((s8 *)obj + 0x20) = *(CopyBlock *)init_data;
        ((S_800206F4_0 *)obj)->unk_10 = init_value;
        func_8004491C(obj, &D_80053858);
    }
}
