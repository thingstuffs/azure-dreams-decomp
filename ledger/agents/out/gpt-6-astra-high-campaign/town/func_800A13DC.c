#include "common.h"

/* Sibling of w_800510DC.c / code9.c / code10.c: sets the "used"/flag bit
 * (0x8000) on a 16-bit flags field 2 bytes before a0, and on the global
 * 32-bit flags word D_800814A0. Here the target reuses a SINGLE lui-computed
 * base register across both the load and the store of D_800814A0 (no second
 * lui before the store), the "array/struct >8B" codegen shape noted in
 * w_800510DC.c rather than the two-independent-lui -G0 shape. */
extern int D_800814A0[];

extern void func_8009FA14(void *a0, void *a1);
extern void func_8008F134(void *a0);
extern void func_80033D08(void *a0);

/* Update the object from supplied data and set its local and global flags. */
void func_8009EB3C(void *object, void *update_data)
{
    func_8009FA14(update_data, (u8 *)object + 0x4C);
    func_8008F134(object);
    func_80033D08(object);
    *(u16 *)((u8 *)object - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
