#include "modules/dungeon_dungeon_setup.h"

void func_800161D8(void) {
    u32 color_command = 0x2C808080;
    dungeon_setup_802831D8_GlobalState *state = ((dungeon_setup_802831D8_GlobalState *)&gameWork);
    dungeon_setup_802831D8_InitBlock *init_block = &state->unk1DC;
    u16 block_extent = 0x3F;
    u32 block_offset;
    u8 *flag_page;


    init_block->unk14 = 6;
    init_block->unk18 = block_extent;
    block_offset = 6;
    init_block->unk16 = block_offset;
    init_block->unk1C = 0x180;
    init_block->unk1E = 0x180;
    init_block->unk1A = block_extent;
    state->unkA8 = color_command;
    state->unk1DC.unk00 = (u32)D_800EA000;
    dungeonSetupRunAndLoadTrack();
    flag_page = D_80080AA0 - 0xAA0;
    flag_page[0xAA0] = 0;
    {
        flag_page = D_800E3D20 - 0x3D20;

        flag_page[0x3D20] = 0;
        dungeonSetContinuationValue(D_800EA000 - 0x9C14);
    }
}

