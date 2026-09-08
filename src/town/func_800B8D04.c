#include "common.h"

extern void func_800491F4(s32 arg0, void *arg1, s32 arg2);
extern u8 D_800D17AC[];

/* Chains nodes using D_800D17AC indices until an index reaches 24. */
void func_800B6464(s32 nodes) {
    func_800491F4(nodes, D_800D17AC, 24);
}
