#include "modules/dungeon_resource03_slot0.h"

void func_801721C0(R03_801721C0_S_801721C0_0 *object, void *unused, void *check_data, void *target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(check_data, target) << 0x10) > 0) {
            object->unk_8C = ((void *)func_80170E54);
            if (dungeonStatus.flags & 0x80) {
                object->unk_90.at02.v = 0;
                object->unk_90.at00.v = 0;
            }
        }
    } else {
        if (dungeonStatus.flags & 0x80) {
            object->unk_90.at02.v = 0;
            object->unk_90.at00.v = 0;
        }
    }
}
