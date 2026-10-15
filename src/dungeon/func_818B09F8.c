#include "modules/dungeon_ovl_18d0850.h"

ovl_18d0850_818B09F8_MainObj *func_800241F8(s32 object_value, ovl_18d0850_818B09F8_VecObj *source_vec) {
    ovl_18d0850_818B09F8_MainObj *obj = (ovl_18d0850_818B09F8_MainObj *)func_8003FC64(530);
    ovl_18d0850_818B09F8_SubObj *sub;
    ovl_18d0850_818B09F8_VecObj *vec;
    ovl_18d0850_818B09F8_MainObj *result;

    if (obj != 0) {
        obj->callback = (void *)func_8002417C;
        sub = obj->sub;
        obj->source_state = object_value;
        sub->b = 128;
        sub->g = 128;
        sub->r = 128;
        func_8003DB94(sub, D_800DEC70, 0);

        sub->unk1E = 4096;
        sub->unk1C = 4096;
        sub->unk12 = 0x7E09;
        sub->unk14 |= 0x100;
        func_8004491C(obj, func_80045340);

        vec = obj->vec;
        vec->unk2 = source_vec->unk2;
        vec->unk6 = source_vec->unk6;
        vec->unkA = source_vec->unkA;

        result = obj;
        return result;
    } else {
        result = 0;
        return result;
    }
}
