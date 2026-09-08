#include "common.h"

#define VOLATILE_FIELD(ptr, type, off) \
    (*(volatile type *)((u8 *)(ptr) + (off)))

extern void func_8005D704(void);
extern void func_8005D730(void);
extern void *D_80079958;
extern s32 *D_8007995C;
extern s32 * volatile D_80079960;
extern s32 *D_80079964;
extern s32 D_800799A8;

/* Starts a DMA transfer from SPU RAM to main RAM. */
void func_8005D124(s32 ram_address, s16 spu_address, s32 block_count)
{
    VOLATILE_FIELD(D_80079958, s16, 0x1A6) = spu_address;
    func_8005D730();
    VOLATILE_FIELD(D_80079958, u16, 0x1AA) |= 0x30;
    func_8005D730();
    func_8005D704();

    *D_8007995C = ram_address;
    *D_80079960 = ((u32)block_count << 16) | 0x10;
    D_800799A8 = 1;
    *D_80079964 = 0x01000200;
}
