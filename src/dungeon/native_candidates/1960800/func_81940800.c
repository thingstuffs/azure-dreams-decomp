#include "modules/dungeon_ovl_1960800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/entity.h"

   /* the 0x2 bytes before arg0 in func_8002405C, addressed as arg0[-1] */


   /* arg2 in func_8002405C */

   /* ((((Rec_D_800E3D7C *)arg0)->unk_32 * 2) + ((Rec_D_800E3D7C *)arg0)->unk_60.as_s32) in func_8002405C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
void func_8002405C(void *effect, void *unused, void *primitive)
;
/* Advance the effect fade and mark it finished when its countdown expires. */
void func_8002405C(void *effect, void *unused, void *primitive) {
    s32 shade;
    u16 frames_left;

    frames_left = ((u16)((EntityRec *)effect)->facing) - 1;
    shade = (s32)((s32)(frames_left << 0x10) >> 9) / (s16)((EntityRec *)effect)->unk_2C;
    D_8002571C = 1;
    ((EntityRec *)effect)->facing = frames_left;
    ((S_81940800_1 *)primitive)->unk_0E = (s8)shade;
    ((S_81940800_1 *)primitive)->unk_0D = (s8)shade;
    ((S_81940800_1 *)primitive)->unk_0C = (s8)(shade + 0x10);
    if (((S_81940800_1 *)primitive)->unk_06 >= -6) {
        ((S_81940800_1 *)primitive)->unk_06 = (s16)((u16)((S_81940800_1 *)primitive)->unk_06 - 2);
    }
    if ((s16)((u16)((EntityRec *)effect)->facing) <= 0) {
        ((S_81940800_2 *)(((((EntityRec *)effect)->unk_32 * 2) + ((s32)((EntityRec *)effect)->target))))->unk_46 = 0;
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_81940800_0_pre *)effect)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
