#include "modules/ovmovie_libpress.h"


/* Starts a DMA transfer to memory in 32-word blocks. */
static void func_80177B30(s32 dest_addr, u32 word_count) {
    func_80177C58();
    *D_80178384 |= 0x88;
    *D_80178360 = 0;
    *D_80178358 = dest_addr;
    *D_8017835C = ((word_count >> 5) << 0x10) | 0x20;
    *D_80178360 = 0x01000200;
}
