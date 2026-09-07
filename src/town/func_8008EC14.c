#include "common.h"

typedef struct S_8008EC14_node {
    u8 pad0[0x10];
    void *field_0x10;
    u8 pad14[0x20 - 0x14];
    s32 field_0x20;
} S_8008EC14_node;

extern void *func_8003FC64(s32 a0);
extern s32 D_8008C304[];
extern void *D_800CFCA8[];

void func_8008C374(void)
{
    S_8008EC14_node *v1 = func_8003FC64(0);

    if (v1 != 0) {
        v1->field_0x10 = D_8008C304;
        v1->field_0x20 = 0;
        v1 = (S_8008EC14_node *)((u8 *)v1 + 0x20);
        D_800CFCA8[0] = v1;
    }
}
