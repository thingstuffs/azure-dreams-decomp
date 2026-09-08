#include "common.h"

typedef struct {
    u8 pad[0x1E];
    u16 flag;
} S800083498;

extern S800083498 D_80083498;
extern void func_8004EE50(void *arg0);

/* Set up mcard_func_set after clearing flag bit 0x2000. */
void func_800C1AEC(void) {
    D_80083498.flag &= 0xDFFF;
    func_8004EE50(&D_80083498);
}
