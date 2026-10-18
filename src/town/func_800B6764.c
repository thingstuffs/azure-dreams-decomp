#include "common.h"

extern unsigned char D_800D16BC[16];
extern void build_reverse_indexed_chain(void *a0, void *a1, int a2);

/* Pass the target and D_800D16BC to build_reverse_indexed_chain with code 33. */
void process_target_with_code_33(void *target)
{
    build_reverse_indexed_chain(target, D_800D16BC, 33);
}
