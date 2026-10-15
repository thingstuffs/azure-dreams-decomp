#include "slus/gp_shared_8152c.h"

void *func_80047D44(int resource_id)
{
    func_800479D4(&D_80016000, &D_80023000, (unsigned short)resource_id);
    func_8003F320();
    D_8008152C = func_80047AB0(&D_80016000, 0xB, 0x7900, 0xD, &D_80023000);
    return &D_8008152C;
}
