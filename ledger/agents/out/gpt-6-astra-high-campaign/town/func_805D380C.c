#include "common.h"

typedef struct {
    u8 pad[0x14];
    s16 val;
    u8 pad2[2];
} Entry;

extern struct { void *ptr; s32 pad[2]; } D_80016000;
extern Entry D_800198A4[3];
extern s32 D_80019B8C[3];

/* Copy the selected entry value to the current object's destination field. */
void func_805D380C(void) {
    s32 *value_ptr = *(s32 **) ((u8 *) D_80016000.ptr + 0x1C);
    *value_ptr = D_800198A4[D_80019B8C[0]].val;
}
