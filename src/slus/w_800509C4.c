#include "common.h"

typedef struct {
    void (*field_0)();
    unsigned char pad4[0x1C - 4];
    void *field_1C;
    unsigned char pad20[0x2C - 0x20];
    char *field_2C;
} S_800509C4;

extern void func_8005097C(char *a0);
extern void func_80050640(void);

/* Sets a0->field_1C = a1, re-inits the sub-object via func_8005097C(a0->field_2C),
   then installs func_80050640 as a0's vtable/dispatch function pointer at field_0. */
void func_800509C4(S_800509C4 *a0, void *a1)
{
    a0->field_1C = a1;
    func_8005097C(a0->field_2C);
    a0->field_0 = func_80050640;
}
