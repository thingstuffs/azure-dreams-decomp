#include "common.h"
#include "shared/game_work.h"

/* D_80083160: shared state table (own view here); this function only touches
 * a u32 field at offset 8 and a s16 field at offset 0xC8 (declared >8 bytes
 * to force %hi/%lo addressing). */


extern s32 func_80094BC8(s32 unused, s16 angle_offset);
extern void func_80094F58(s16 angle, s32 max_length, s32 vector);

/* Passes the valid shared angle, fixed value 0x120000, and context to func_80094F58. */
void func_8009503C(s32 context)
{
    s16 angle = func_80094BC8(gameWork.buttons, gameWork.view.viewAngle);

    if (angle != -1) {
        func_80094F58(angle, 0x120000, context);
    }
}
