#include "slus/gp_shared_8152c.h"

void advanceEffectState(void)
{
    func_80046F88(&D_80016000);
    func_80047054(&D_80016000, 0xB, 0x7900, 0xD);
    D_8008152C = &D_80016000;
}
