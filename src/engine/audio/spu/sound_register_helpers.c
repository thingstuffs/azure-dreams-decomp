/* SPU register access with address-unit scaling and DMA priority-bit updates. */
#include "engine/audio/spu/sound_register_helpers.h"
#include "engine/audio/spu.h"



/* Store a table entry, optionally shifting the value right by the global shift amount. */
void _spu_FsetRXX(s32 index, u32 value, s32 apply_shift)
{
    if (apply_shift == 0) {
        ((SoundRegister16 *)spu_registers)[index] = (u16)value;
    } else {
        ((SoundRegister16 *)spu_registers)[index] = (u16)(value >> spu_address_unit_shift);
    }
}

/* Read a table value and apply the global left shift unless shift mode is -1. */
s32 _spu_FgetRXXa(s32 index, s32 shift_mode)
{
    u16 value = spu_registers[index];

    if (shift_mode == -1) {
        return (s32)value;
    }
    return (s32)value << spu_address_unit_shift;
}

/* Replaces status bits 0x70000 with 0x30000 when use_status_3 is nonzero, otherwise 0x50000. */
void _spu_FsetPCR(s32 use_status_3) {
    *spu_dma_priority_register &= ~0x70000;
    if (use_status_3) {
        *spu_dma_priority_register |= 0x30000;
    } else {
        *spu_dma_priority_register |= 0x50000;
    }
}
