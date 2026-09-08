#include "common.h"

extern void func_800491F4(s32, void *, s32);
extern u8 D_800D15CC[];

/* Links nodes in the order specified by D_800D15CC. */
void func_800B091C(s32 node_table) {
    func_800491F4(node_table, D_800D15CC, 31);
}
