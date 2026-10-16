#include "common.h"

typedef struct Object13B18 Object13B18;
extern void cardBootSetPairedChoiceAnimations(Object13B18 *, s32 *, s32 *);

/* Pass the data at offset 0x20 to cardBootSetPairedChoiceAnimations. */
void cardBootUpdatePairedChoiceAnimations(s32 base_addr, s32 *enable_flags, s32 *active_flags) {
    cardBootSetPairedChoiceAnimations((Object13B18 *)(base_addr + 0x20), enable_flags, active_flags);
}
