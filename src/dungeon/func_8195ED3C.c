#include "modules/dungeon_ovl_197e800.h"
#include "common.h"

   /* obj in func_8002453C */

   /* part in func_8002453C */

   /* arg0 in func_8002453C */


#define NULL 0

extern s32 D_80027380;
extern s32 D_800273B0;
extern s32 D_800DF334;

/* Creates an object, initializes its parts, and loads its graphics. */
void *func_8002453C(S_8195ED3C_2 *source, s32 offset)
{
    s32 rect[2];
    s32 rect_size;
    void *obj;
    S_8195ED3C_1 *part;
    void *handle;

    obj = func_8003FC64(2);
    if (obj != NULL) {
        rect[0] = 0x01000340;
        rect_size = 0x200020;
        rect[1] = rect_size;
        draw_textured_ellipse(&D_800DF334, rect, 1, 0);
        rect[0] = 0x01000360;
        rect[1] = rect_size;
        draw_textured_ellipse(&D_80027380, rect, 1, 0);
        part = ((S_8195ED3C_0 *)obj)->unk_08;
        ((S_8195ED3C_0 *)obj)->unk_10 = update_brightening_fading_effect;
        part->unk_02 = source->unk_02;
        part->unk_06 = source->unk_06;
        part->unk_08.at02.v = source->unk_0A;
        part = ((S_8195ED3C_0 *)obj)->unk_0C;
        part->unk_08.at00.v = &D_800273B0;
        part->unk_1E = 0xC00;
        part->unk_1C = 0xC00;
        ((S_8195ED3C_0 *)obj)->unk_2C = offset - 0x20;
    }
    handle = NULL;
    if (obj != NULL) {
        handle = (u8 *)obj + 0x20;
    }
    return handle;
}
