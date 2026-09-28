#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"

/* gameWork.view declared on its own: retail forms this TU's base at 0x80083178 itself (not gameWork + 0x18). */
extern GameView D_80083178;

extern void func_8004D4AC(void);

/* Copies rotation angles from D_80083780 into D_80083178 (gameWork.view's position vector) and builds matrices. */
void func_8004D5D0(void)
{
    D_80083178.unk_0A4 = D_80083780.x.w.i;
    D_80083178.unk_0A6 = D_80083780.y.w.i;
    D_80083178.unk_0A8 = D_80083780.z.w.i;
    func_8004D4AC();
}
