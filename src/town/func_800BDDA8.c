#include "common.h"

extern s32 func_8009CFE0(void *, void *);
extern void func_8008F134(void *arg0);
extern void func_80033D08(void *arg0);
extern s32 D_800814A0;

typedef struct S_func_800BB508_0 {
    u8 pad_00[0x98];
    void *unk_98;
} S_func_800BB508_0;

/* On a successful object check, clear its linked byte and set object and global flags. */
void func_800BB508(S_func_800BB508_0 *object, void *context) {
    if (func_8009CFE0(object, context) != 0) {
        func_8008F134(object);
        if (object->unk_98 != 0) {
            *(s8 *)object->unk_98 = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
