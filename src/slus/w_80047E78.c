#include "slus/address_slot.h"

void *func_80047E78(int resource_id)
{
    func_800479D4(&D_80119000, &D_80126000, (unsigned short)resource_id);
    func_8003F320();
    D_80081528 = func_80047AB0(&D_80119000, 5, 0x7F80, 0xF, &D_80126000);
    return &D_80081528;
}
