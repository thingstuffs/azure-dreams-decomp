#include "modules/dungeon_resource06_slot0.h"

void dungeonAdvanceRecordCountdown(void *record_data) {
    u16 remaining_count;

    remaining_count = ((R06_801748F0_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((R06_801748F0_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((R06_801748F0_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((R06_801748F0_S_801748F0_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags = (s32) (objectFlagBlock.flags | 0x8000);
    }
}
