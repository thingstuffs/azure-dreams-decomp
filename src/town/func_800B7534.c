#include "common.h"

extern u8 D_800D1760[];
extern void build_reverse_indexed_chain(void *a0, void *a1, s32 a2);

/* Processes the target with D_800D1760 and parameter 41. */
void process_target_with_code_41(void *target) {
    build_reverse_indexed_chain(target, D_800D1760, 41);
}
