#include "modules/dungeon_ovl_1830850.h"

ovl_1830850_81811168_DungeonObj81811168 *func_80026168(s32 parent_obj, s32 initial_value, s32 text_addr)
{
    ovl_1830850_81811168_DungeonObj81811168 *obj;
    ovl_1830850_81811168_DungeonSub81811168 *state;

    obj = (ovl_1830850_81811168_DungeonObj81811168 *)func_8003FC64(0);
    state = &obj->sub20;
    if (obj != 0) {
        if (func_800260CC(state, 13) != 0) {
            obj->field0C = (u8 *)obj + 0x64;
            state->value50 = (s32)func_80025D74(state->value54);
            func_80026084(state, parent_obj, initial_value, text_addr);
            func_8004491C(obj, (void *)func_8004CAA0);
            func_80026314(obj);
        } else {
            func_8004B248((u8 *)obj + 0x78);
            obj->flags1E |= 0x8000;
            obj = 0;
            objectFlagBlock.flags |= 0x8000;
        }
    }
    return obj;
}
