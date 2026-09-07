#include "common.h"

typedef struct {
    u32 unk00;
    u8 pad04[0x10];
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
} InitBlock;

typedef struct {
    u8 pad00[0xA8];
    u32 unkA8;
    u8 padAC[0x130];
    InitBlock unk1DC;
} GlobalState;

extern GlobalState D_80083160;
extern u8 D_80080AA0[16];
extern u8 D_800EA000[16];

extern void func_80018A70(void *, u32, u32);
extern void func_80099188(void *);

/* Initializes the global state block and clears associated flags. */
void func_800161D8(void) {
    u32 color_command = 0x2C808080;
    GlobalState *state = &D_80083160;
    InitBlock *init_block = &state->unk1DC;
    u32 block_extent = 0x3F;
    u32 block_offset = 6;

    ASM_KEEP(color_command);   /* MATCH pin: retail immediate-load split depends on it */
    ASM_KEEP(init_block);   /* MATCH pin: retail schedule: same instructions, different order without it */

    init_block->unk14 = block_offset;
    ASM_KEEP(block_offset);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    init_block->unk16 = 6;
    init_block->unk1C = 0x180;
    init_block->unk1E = 0x180;
    init_block->unk18 = block_extent;
    init_block->unk1A = block_extent;
    state->unkA8 = color_command;
    state->unk1DC.unk00 = (u32)D_800EA000;
    func_80018A70(state, block_extent, color_command);
    D_80080AA0[0] = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    {
        u8 *flag_page = (u8 *)0x800E0000;

        ASM_KEEP(flag_page);   /* MATCH pin: retail schedule: same instructions, different order without it */
        flag_page[0x3D20] = 0;
        func_80099188(D_800EA000 - 0x9C14);
    }
}

