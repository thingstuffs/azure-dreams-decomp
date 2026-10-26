#include "common.h"
#include "engine/texture.h"
#include "town/shop.h"

extern unsigned char D_800D16BC[16];

/* Links the indexed parts with limit 33 and returns the chain head. */
void *process_target_with_code_33(void *target)
{
    return build_reverse_indexed_chain(target, D_800D16BC, 33);
}
