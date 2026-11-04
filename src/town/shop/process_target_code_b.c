#include "common.h"
#include "engine/texture.h"
#include "town/shop.h"

extern u8 D_800D1760[];

/* Links the indexed parts with limit 41 and returns the chain head. */
void *process_target_with_code_41(void *target) {
    return build_reverse_indexed_chain(target, D_800D1760, 41);
}
