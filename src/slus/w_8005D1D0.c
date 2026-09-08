/* func_8005D1D0 -- BYTE-EXACT, gcc 2.7.2 -O2 -G0, aspsx 2.56.
 *
 * Key shapes (see NOTES.txt for the full derivation and the negative sweep):
 *   `transfer_arg` carries BOTH of case 3's va_arg reads AND case 2's, so its pseudo is used
 *        in more than one basic block.  local-alloc's combine_regs then takes its
 *        `reg_qty[ureg] < 0` early-out and refuses to tie either the shift result or
 *        the andi result to the dying value -- which is what lets the block-count
 *        statements be written in retail's order (shift first) without the andi
 *        stealing $a0.  No ASM_REG pin is needed on it.
 *   NO ASM_REG pin is needed anywhere in the block-count code: once `transfer_arg` is the
 *        shared multi-block pseudo, the prior lane's `size`->$a0 and `blocks`->$v1
 *        pins are both dead (ablated, still MATCH) and were removed.
 *   The shift MUST be logical: `transfer_arg` is s32, so the (u32) casts are what make it
 *        `srl` rather than `sra`.
 *   Semantics carried from the prior lane: CHCR default 0x1000201 with 0x1000200 when
 *        D_800799A8 == 1; the block count is srl/andi/sltu/addu, branchless.
 *   D_800799AC is declared a volatile OBJECT with the store cast back to non-volatile
 *        so the reload survives cse without costing the bne's delay-slot fill.
 */
#include "common.h"

typedef struct {
    u8  pad000[0x1A6];
    volatile u16 dt_addr;   /* 0x1A6 */
    u8  pad1A8[2];
    volatile u16 spucnt;    /* 0x1AA */
} SpuRegs;

extern SpuRegs *D_80079958;
extern s32 *D_8007995C;
extern s32 *D_80079960;
extern s32 *D_80079964;
extern u16 D_80079970;
extern s32 D_80079980;
extern s32 D_800799A8;
extern volatile s32 D_800799AC;
extern s32 D_800799B0;

extern void func_8005D6D8(void);
extern void func_8005D704(void);

typedef char *va_list_t;
#define VA_START(ap, last) (ap = (char *)&(last) + sizeof(s32))
#define VA_ARG(ap, T)      (ap += sizeof(T), *(T *)(ap - sizeof(T)))

/* Sets the SPU transfer address or direction, or starts a DMA transfer. */
s32 func_8005D1D0(s32 command, ...)
{
    va_list_t args;
    u16 expected_addr;
    u16 current_addr;
    u32 poll_count;
    u32 spu_addr;
    s32 transfer_arg;
    u16 spu_control;
    u32 block_count;
    u32 partial_block;
    s32 transfer_mode;
    s32 dma_control;

    VA_START(args, command);

    switch (command) {
    case 2:
        transfer_arg = VA_ARG(args, s32);
        spu_addr = (u32)transfer_arg >> D_80079980;
        D_80079970 = spu_addr;
        D_80079958->dt_addr = spu_addr;
        break;

    case 1:
        D_800799A8 = 0;
        expected_addr = D_80079970;
        poll_count = 0;
        while ((D_80079958->dt_addr & 0xFFFF) != expected_addr) {
            if (++poll_count >= 0xF01) {
                return -2;
            }
        }
        spu_control = D_80079958->spucnt;
        spu_control = (spu_control & 0xFFCF) | 0x20;
        D_80079958->spucnt = spu_control;
        break;

    case 0:
        D_800799A8 = 1;
        expected_addr = D_80079970;
        poll_count = 0;
        while ((D_80079958->dt_addr & 0xFFFF) != expected_addr) {
            if (++poll_count >= 0xF01) {
                return -2;
            }
        }
        spu_control = D_80079958->spucnt;
        spu_control |= 0x30;
        D_80079958->spucnt = spu_control;
        break;

    case 3:
        transfer_mode = 0x20;
        if (D_800799A8 == 1) {
            transfer_mode = 0x30;
        }
        poll_count = 0;
        while ((D_80079958->spucnt & 0x30) != (transfer_mode & 0xFFFF)) {
            if (++poll_count >= 0xF01) {
                return -2;
            }
        }
        if (D_800799A8 == 1) {
            func_8005D704();
        } else {
            func_8005D6D8();
        }
        transfer_arg = VA_ARG(args, s32);
        *(s32 *)&D_800799AC = transfer_arg;
        transfer_arg = VA_ARG(args, s32);
        block_count = (u32)transfer_arg >> 6;
        partial_block = ((u32)transfer_arg & 0x3F) != 0;
        D_800799B0 = block_count + partial_block;
        *D_8007995C = D_800799AC;
        *D_80079960 = (D_800799B0 << 16) | 0x10;
        dma_control = 0x1000201;
        if (D_800799A8 == 1) {
            dma_control = 0x1000200;
        }
        *D_80079964 = dma_control;
        break;
    }
    return 0;
}
