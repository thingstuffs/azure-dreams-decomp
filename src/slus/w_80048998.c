#include "common.h"

typedef struct S_80083110 {
    u8 pad0[8];
    s32 field_8;
    u8 pad1[0x28 - 0xC];
    s32 field_28;
} S_80083110;

extern S_80083110 *D_80083110[4];
extern void func_800488F0(s32, s32, s32);

/* If index != 0, store the struct pointer into D_80083110[index-1] and dispatch with mode 2; otherwise dispatch with mode 3. Both paths pass the struct's field_8/field_28 as args. */
void func_80048998(S_80083110 *a0, s32 a1) {
    if (a1 != 0) {
        a1 = a1 - 1;
        D_80083110[a1] = a0;
        func_800488F0(a0->field_8, a0->field_28, 2);
    } else {
        func_800488F0(a0->field_8, a0->field_28, 3);
    }
}
