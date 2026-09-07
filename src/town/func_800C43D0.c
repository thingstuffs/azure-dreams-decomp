#include "common.h"

typedef struct {
    u8 pad[0x1E];
    u16 flag;
} S800083498;

extern S800083498 D_80083498;
extern void func_800511B4(void *arg0);

void func_800C1B30(void) {
    D_80083498.flag &= 0xDFFF;
    func_800511B4(&D_80083498);
}
