#include "common.h"

typedef struct Object13B18 Object13B18;
extern void func_80026B18(Object13B18 *, s32 *, s32 *);

/* Pass the data at offset 0x20 to func_80026B18. */
void func_80026FF8(s32 base_addr, s32 *enable_flags, s32 *active_flags) {
    func_80026B18((Object13B18 *)(base_addr + 0x20), enable_flags, active_flags);
}
