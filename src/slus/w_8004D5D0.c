#include "common.h"
#include "shared/entity_objects.h"

extern void func_8004D4AC(void);

/* Copies rotation angles from D_80083780 into D_80083178 and builds matrices. */
void func_8004D5D0(void)
{
    D_80083178.state_94.v[2].x = D_80083780.x.w.i;
    D_80083178.state_94.v[2].y = D_80083780.y.w.i;
    D_80083178.state_94.v[2].z = D_80083780.z.w.i;
    func_8004D4AC();
}
