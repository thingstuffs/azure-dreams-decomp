#include "modules/dungeon_ovl_e0365c.h"

void func_801728B4(void *obj, EntityRec *record, void *entity, void *actor) {
    s32 state;

    state = ((E_801728B4_S_801728B4_0 *)obj)->unk_9B;
    switch (state) {
    case 0:
        if (((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0x8000) {
            ((E_801728B4_S_801728B4_0 *)obj)->unk_9B = 2U;
            ((E_801728B4_S_801728B4_1 *)entity)->unk_14 =
                (u16)(((E_801728B4_S_801728B4_1 *)entity)->unk_14 | 0x6000);
            func_8009C12C(actor, entity, ((E_801728B4_S_801728B4_2 *)actor)->unk_2A, 1);
            return;
        }
        record->flags14 = 0;
        record->unk_10 = 0;
        record->unk_0C = 0;
        ((E_801728B4_S_801728B4_0 *)obj)->unk_9B =
            (u8)(((E_801728B4_S_801728B4_0 *)obj)->unk_9B + 1);
        return;

    case 1:
        if ((((E_801728B4_S_801728B4_1 *)entity)->unk_04 == 7) &&
            (((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (((((E_801728B4_S_801728B4_1 *)entity)->unk_04 == 9) &&
             (((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0x1000)) ||
            (((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0xE000)) {
            func_8009C12C(actor, entity, ((E_801728B4_S_801728B4_2 *)actor)->unk_2A, 1);
            ((E_801728B4_S_801728B4_0 *)obj)->unk_9B =
                (u8)(((E_801728B4_S_801728B4_0 *)obj)->unk_9B + 1);
        } else {
            return;
        }
                        /* fall through */

    case 2:
        if (!(((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0xE000)) {
            return;
        }
        func_800AD594(actor, 0x100);
        ((E_801728B4_S_801728B4_0 *)obj)->unk_8C = func_80170E5C;
        dungeonStatus.unk_0C = 0;
        ((E_801728B4_S_801728B4_2 *)actor)->unk_46 =
            (u16)((*(u16 *)((u8 *)actor + 0x46)) & 0x7FFF);
        func_800A4ACC(actor);
        break;

    default:
        break;
    }
}
