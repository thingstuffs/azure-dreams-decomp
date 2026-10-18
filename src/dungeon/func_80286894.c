#include "modules/dungeon_floor_generate.h"

s32 load_generation_resource_slot(s16 resource_index) {
    s16 slot_index;
    s32 resource_id;
    u8 *loaded_id;
    floor_generate_isolated_80286894_S_80019894_0 *resource;
    void *cd_data;

    resource = (resource_index * 0xC) + (s8 *)&D_8006E61C;
    slot_index = resource->unk_00 - 1;
    loaded_id = slot_index + (u8 *)&D_80080AF0;
    resource_id = resource_index + 1;
    if (*loaded_id == resource_id) {
        return 0;
    }
    SD_Call(0x72, resource_id);
    func_800542BC();
    *loaded_id = resource_index + 1;
    func_80067014(0);
    func_8005FE18(0);
    cd_data = resource->unk_08;
    (*(s32 *)D_80081480) = ((Rec_D_80082E80 *)(&(*(s32 *)D_8008148C)))->unk_00;
    Control_CD(6, cd_data, 0);
    Control_CD(6, resource->unk_04, 0);
    drain_cd_command_queue();
    func_8003F5E0((*(s32 *)D_8008148C));
    SD_Call(((2 << slot_index) | 0x10) & 0xFFFF);
    func_800542BC();
    do {
    } while (test_sound_channel_availability((s16) resource->unk_00) != 1);
    return 1;
}
