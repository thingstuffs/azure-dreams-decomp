#include "modules/dungeon_ovl_18c4828.h"

void func_80024340(Row_818A4B40_S_818A4B40_0 *motion, Row_818A4B40_S_818A4B40_2 *position, Rec_D_80082E80 *object) {
    s16 angle;
    s32 random_value;
    s32 biased_random;
    u16 height_offset;
    Row_818A4B40_S_818A4B40_1 *counter;

    counter = motion->unk_00;
    counter->unk_14 = (u16) (counter->unk_14 + 1);
    height_offset = motion->unk_04 + motion->unk_06;
    motion->unk_04 = height_offset;
    if ((s16) height_offset < -0x80) {
        random_value = rand();
        biased_random = random_value;
        angle = (random_value % 4096);
        position->unk_02 = (s16) (motion->unk_08 + ((s32) (func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16) (motion->unk_0A + ((s32) (func_80064584(angle) * 2) >> 8));
        motion->unk_04 = (u16) (motion->unk_04 + 0x80);
        motion->unk_06 = (u16) (-6 - (rand() % 5));
    }
    position->unk_0A = (s16) (motion->unk_0C + motion->unk_04);
    func_800478B8(object);
    if (object->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(object, &D_800DECF8, 0);
    }
}
