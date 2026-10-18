#include "slus/sound_dma_lifecycle.h"

/* Starts a DMA transfer from SPU RAM to main RAM. */
void func_8005D124(s32 ram_address, s16 spu_address, s32 block_count)
{
    D_80079958->transfer_address.ordered = spu_address;
    delay_multiply_loop();
    D_80079958->control |= 0x30;
    delay_multiply_loop();
    func_8005D704();

    *D_8007995C = ram_address;
    *D_80079960 = ((u32)block_count << 16) | 0x10;
    D_800799A8 = 1;
    *D_80079964 = 0x01000200;
}
