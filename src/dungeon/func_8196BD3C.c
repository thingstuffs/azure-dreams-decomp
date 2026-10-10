#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/slus_callbacks.h"

   /* work in func_8196BD3C */

   /* obj in func_8196BD3C */

   /* the 0x18 bytes before arg0 in func_8196BD3C, addressed as arg0[-1] */








/* Creates a display object at the source position with zero scale and color. */
void func_8002553C(void *source, s32 unused_position, s32 unused_render) {
    void *object;
    u8 *object_state;
    Display *display;
    void *source_pos;
    void *object_pos;

    object = func_8003FC64(0x212);
    if (object != 0) {
        object_state = (u8 *)object + 0x20;
        ((S_8196BD3C_0 *)object_state)->unk_2C = 0xB;
        ((S_8196BD3C_0 *)object_state)->unk_7C = source;
        ((S_8196BD3C_1 *)object)->unk_10 = func_8002525C;
        func_8004491C(object, (s32)func_80045340);

        display = ((S_8196BD3C_1 *)object)->unk_0C;
        display->field10 = 0x20;
        display->field6 = 0;
        display->flags |= 0xC;

        source_pos = ((S_8196BD3C_2_pre *)source)[-1].unk_00;
        object_pos = ((S_8196BD3C_1 *)object)->unk_08;
        ((s32 *)object_pos)[0] = ((s32 *)source_pos)[0];
        ((s32 *)object_pos)[1] = ((s32 *)source_pos)[1];
        ((s32 *)object_pos)[2] = ((s32 *)source_pos)[2];

        display = ((S_8196BD3C_1 *)object)->unk_0C;
        display->scaleX = 0;
        display->scaleY = 0;
        display->blue = 0;
        display->green = 0;
        display->red = 0;

        *(PackedVec3 *)((u8 *)object + 0x58) = D_80026978;
        display->vector = (u8 *)object + 0x58;
    }
}
