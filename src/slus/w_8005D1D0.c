/* func_8005D1D0 -- BYTE-EXACT, gcc 2.7.2 -O2 -G0, aspsx 2.56.
 *
 * Key shapes (see NOTES.txt for the full derivation and the negative sweep):
 *   `addr` carries BOTH of case 3's va_arg reads AND case 2's, so its pseudo is used
 *        in more than one basic block.  local-alloc's combine_regs then takes its
 *        `reg_qty[ureg] < 0` early-out and refuses to tie either the shift result or
 *        the andi result to the dying value -- which is what lets the block-count
 *        statements be written in retail's order (shift first) without the andi
 *        stealing $a0.  No ASM_REG pin is needed on it.
 *   NO ASM_REG pin is needed anywhere in the block-count code: once `addr` is the
 *        shared multi-block pseudo, the prior lane's `size`->$a0 and `blocks`->$v1
 *        pins are both dead (ablated, still MATCH) and were removed.
 *   The shift MUST be logical: `addr` is s32, so the (u32) casts are what make it
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

/* PsyQ 4.0 LIBSPU: SPU transfer-address / DMA driver. */
s32 func_8005D1D0(s32 cmd, ...)
{
    va_list_t ap;
    u16 want;
    u16 cur;
    u32 tries;
    u32 val;
    s32 addr;
    u16 rmw;
    u32 blocks;
    u32 rem;
    s32 mode;
    s32 chcr;

    VA_START(ap, cmd);

    switch (cmd) {
    case 2:
        addr = VA_ARG(ap, s32);
        val = (u32)addr >> D_80079980;
        D_80079970 = val;
        D_80079958->dt_addr = val;
        break;

    case 1:
        D_800799A8 = 0;
        want = D_80079970;
        tries = 0;
        while ((D_80079958->dt_addr & 0xFFFF) != want) {
            if (++tries >= 0xF01) {
                return -2;
            }
        }
        rmw = D_80079958->spucnt;
        rmw = (rmw & 0xFFCF) | 0x20;
        D_80079958->spucnt = rmw;
        break;

    case 0:
        D_800799A8 = 1;
        want = D_80079970;
        tries = 0;
        while ((D_80079958->dt_addr & 0xFFFF) != want) {
            if (++tries >= 0xF01) {
                return -2;
            }
        }
        rmw = D_80079958->spucnt;
        rmw |= 0x30;
        D_80079958->spucnt = rmw;
        break;

    case 3:
        mode = 0x20;
        if (D_800799A8 == 1) {
            mode = 0x30;
        }
        tries = 0;
        while ((D_80079958->spucnt & 0x30) != (mode & 0xFFFF)) {
            if (++tries >= 0xF01) {
                return -2;
            }
        }
        if (D_800799A8 == 1) {
            func_8005D704();
        } else {
            func_8005D6D8();
        }
        addr = VA_ARG(ap, s32);
        *(s32 *)&D_800799AC = addr;
        addr = VA_ARG(ap, s32);
        blocks = (u32)addr >> 6;
        rem = ((u32)addr & 0x3F) != 0;
        D_800799B0 = blocks + rem;
        *D_8007995C = D_800799AC;
        *D_80079960 = (D_800799B0 << 16) | 0x10;
        chcr = 0x1000201;
        if (D_800799A8 == 1) {
            chcr = 0x1000200;
        }
        *D_80079964 = chcr;
        break;
    }
    return 0;
}
