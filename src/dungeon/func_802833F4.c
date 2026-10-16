#include "modules/dungeon_dungeon_setup.h"

void dungeonInitializeDungeonFloorState(void) {
    s32 floor_data;
    s32 floor_index;
    u32 saved_init_value;
    RuntimeDispatchState *dungeon_state;
    u8 *globals_base;

    dungeonInitializeDungeonRecordKinds();
    dungeonClearDungeonStateBytes();
    bzero(D_800E3E48, 0xAF0);
    D_80082E80.unk_038 = 0;
    dungeonStatus.unk_1E = 0;
    D_80080A88 = 0;
    if ((D_80013714 & 3) == 0) {
        D_8008146C = 1;
        D_8001022C++;
        initKohPropertiesAndEntryTables();
        func_8004A918();
    } else {
        saved_init_value = 0x80010000;

        saved_init_value = *(u16 *)(saved_init_value + 0x234);

        D_8008146C = (u16)saved_init_value;
    }
    globals_base = (u8 *)0x80010000;
    if (D_800DCF4E == 0) {
        D_80080A80 = func_80048D00();
        D_800DCF4E = 1;
    }
    if ((*(u16 *)(globals_base + 0x3714) & 3) == 0) {
        *(s32 *)(globals_base + 0x3628) = rand();
        *(s16 *)(globals_base + 0x3624) = rand() & 0xFF;
        *(s16 *)(globals_base + 0x209C) = rand() & 0xFF;
        markCategoryItemsFlag400(*(s32 *)(globals_base + 0x2090));
    }
    shuffleEnabledItemCategoryPointers();
    dungeon_state = &D_80082E60;
    if (dungeon_state->field_B >= 0x12) {
        floor_index = dungeon_state->field_B - 0x12;
        func_80040AA0(0x11);
        packTaggedResourceDescriptor(0xC, (void *)0x80010000, &floor_data,
                      (floor_index * 0xC) + 0x399D);
        Control_CD(6, &floor_data, 0);
        drainCdCommandQueue();
        D_800E3D1C = 0x384;
        *(u16 *)(globals_base + 0x3714) |= 5;
    } else {
        func_80040AA0(0x11);
        D_800E3D1C = 0;
    }
    dungeonSetMonsterDataPointer();
    func_800499BC();
    D_800E3CD0 = 0;
}
