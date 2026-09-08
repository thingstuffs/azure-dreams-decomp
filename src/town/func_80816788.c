#include "common.h"

typedef struct S_80020788_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80020788_0;   /* object in func_80020788 */



typedef struct {
    s32 words[10];
} Record;

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 D_80053A88;
extern u8 D_80083498[];

/* Allocate an object, copy its record, set its value, and pass it for initialization. */
void func_80020788(s32 object_value, void *record) {
    void *object;

    object = func_8003FD64(1, D_80083498);
    if (object != 0) {
        *(Record *)(object + 0x20) = *(Record *)record;
        ((S_80020788_0 *)object)->unk_10 = object_value;
        func_8004491C(object, &D_80053A88);
    }
}
