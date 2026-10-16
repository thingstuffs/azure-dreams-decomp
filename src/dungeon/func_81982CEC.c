#include "modules/dungeon_ovl_19a332c.h"

void *dungeonAllocateTwoPartObject(ovl_19a332c_81982CEC_S_800244EC_2 *source_part, s32 offset)
{
    s32 rect[2];
    s32 rect_size;
    void *obj;
    ovl_19a332c_81982CEC_S_800244EC_1 *part;
    void *result;

    obj = func_8003FC64(2);
    if (obj != NULL) {
        rect[0] = 0x01000340;
        rect_size = 0x200020;
        rect[1] = rect_size;
        dungeonDrawTexturedEllipse(&D_800DF31C, rect, 1, 0);
        rect[0] = 0x01200340;
        rect[1] = rect_size;
        dungeonDrawTexturedEllipse(&D_800269D4, rect, 1, 0);
        part = ((ovl_19a332c_81982CEC_S_800244EC_0 *)obj)->unk_08;
        ((ovl_19a332c_81982CEC_S_800244EC_0 *)obj)->unk_10 = (void *)dungeonInitializeEntityPositionAndMotion;
        part->unk_02 = source_part->unk_02;
        part->unk_06 = source_part->unk_06;
        part->unk_08.at02.v = source_part->unk_0A;
        part = ((ovl_19a332c_81982CEC_S_800244EC_0 *)obj)->unk_0C;
        part->unk_08.at00.v = &D_800269FC;
        part->unk_1E = 0xC00;
        part->unk_1C = 0xC00;
        ((ovl_19a332c_81982CEC_S_800244EC_0 *)obj)->unk_28 = offset - 0x20;
    }
    result = NULL;
    if (obj != NULL) {
        result = (u8 *)obj + 0x20;
    }
    return result;
}
