#include "modules/dungeon_ovl_18b8824.h"

void func_80024370(void *entry, s32 unused, void *target)
{
    ovl_18b8824_81898B70_S_80024370_1 *object;
    u16 count;

    object = ((ovl_18b8824_81898B70_S_80024370_0 *)entry)->unk_00;
    object->unk_14++;

    count = ((ovl_18b8824_81898B70_S_80024370_0 *)entry)->unk_04 + 1;
    ((ovl_18b8824_81898B70_S_80024370_0 *)entry)->unk_04 = count;

    switch ((s16)count) {
    case 8:
        func_80024264((s32)((ovl_18b8824_81898B70_S_80024370_0 *)entry)->unk_00, (Rec_func_80024264_arg1 *)unused);
        break;
    case 0x10:
    {
        s32 *global_page;

        global_page = (s32 *)0x80080000;
        ((ovl_18b8824_81898B70_S_80024370_0_pre *)entry)[-1].unk_00 |= 0x8000;
        ((ovl_18b8824_81898B70_S_80024370_2 *)global_page)->unk_14A0 |= 0x8000;
        break;
    }
    }
    func_800478B8(target);
}
