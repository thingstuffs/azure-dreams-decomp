#include "slus/gp_shared_8152c.h"

void runtimeNoOpCallback(void)
{
    D_8008152C = uploadImageTiles(&D_80016000, 0xB, 0x7900, 0xD, &D_80023000);
}
