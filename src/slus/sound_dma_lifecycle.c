#include "slus/sound_dma_lifecycle.h"

#include "slus/sound_dma_lifecycle.h"

/* Initialize the SPU, resetting voice settings on a cold start. */
s32 func_8005CC04(s32 warm)
{
    s32 entry_index;
    s32 result;
    u32 status_polls;
    volatile u16 *clear_entry;
    SoundTransferRegisters *spu_regs;

    *D_80079968 |= 0xB0000;
    D_80079974 = 0;
    D_80079978 = 0;
    D_80079970 = 0;
    D_80079958->mvoll = 0;
    D_80079958->mvolr = 0;
    D_80079958->control = 0;
    delay_multiply_loop();
    D_80079958->mvoll = 0;
    D_80079958->mvolr = 0;
    status_polls = 0;
    while (D_80079958->status.ordered & 0x7FF) {
        if (++status_polls >= 0xF01) {
            printf(D_800331F4, D_80033204);
            break;
        }
    }
    D_8007997C = 2;
    D_80079980 = 3;
    D_80079984 = 8;
    D_80079988 = 7;
    D_80079958->transfer_control = 4;
    D_80079958->rvoll = 0;
    D_80079958->rvolr = 0;
    D_80079958->keyoff_lo = 0xFFFF;
    D_80079958->keyoff_hi = 0xFFFF;
    D_80079958->rev_lo = 0;
    D_80079958->rev_hi = 0;
    entry_index = 0;
    clear_entry = D_80086D58;
    for (; entry_index < 10; entry_index++) {
        *clear_entry = 0;
        clear_entry++;
    }
    if (warm == 0) {
        D_80079970 = 0x200;
        D_80079958->fm_lo = 0;
        D_80079958->fm_hi = 0;
        D_80079958->noise_lo = 0;
        D_80079958->noise_hi = 0;
        D_80079958->cdvoll = 0;
        D_80079958->cdvolr = 0;
        D_80079958->extvoll = 0;
        D_80079958->extvolr = 0;
        func_8005CE98(D_80079998, 0x10);
        spu_regs = D_80079958;
        for (entry_index = 0; entry_index < 24; entry_index++) {
            spu_regs->voice[entry_index].voll = 0;
            spu_regs->voice[entry_index].volr = 0;
            spu_regs->voice[entry_index].pitch = 0x3FFF;
            spu_regs->voice[entry_index].addr = 0x200;
            spu_regs->voice[entry_index].adsr1 = 0;
            spu_regs->voice[entry_index].adsr2 = 0;
        }
        D_80079958->keyon_lo = 0xFFFF;
        D_80079958->keyon_hi = 0xFF;
        delay_multiply_loop();
        delay_multiply_loop();
        delay_multiply_loop();
        delay_multiply_loop();
        D_80079958->keyoff_lo = 0xFFFF;
        D_80079958->keyoff_hi = 0xFF;
        delay_multiply_loop();
        delay_multiply_loop();
        delay_multiply_loop();
        delay_multiply_loop();
    }
    result = 0;
    D_8007998C = 1;
    D_80079958->control = 0xC000;
    D_80079990 = 0;
    D_80079994 = 0;
    return result;
}
#include "slus/sound_dma_lifecycle.h"

/* Writes source data to SPU RAM through the transfer FIFO and waits for completion. */
void func_8005CE98(u16 *src, u32 bytes_left)
{
    u16 *src_pos;
    u16 initial_status;
    u16 saved_status;
    s32 chunk_bytes;
    s32 byte_offset;
    u32 poll_count;
    u32 expected_status;
    u16 control;

    src_pos = src;
    initial_status = D_80079958->status.value;
    D_80079958->transfer_address.value = D_80079970;
    saved_status = initial_status & 0x7FF;
    delay_multiply_loop();

    while (bytes_left != 0) {
        chunk_bytes = 0x40;
        if (bytes_left < 0x41) {
            chunk_bytes = bytes_left;
        }
        for (byte_offset = 0; byte_offset < chunk_bytes; byte_offset += 2) {
            D_80079958->transfer_fifo = *src_pos++;
        }
        control = D_80079958->control;
        control = (control & 0xFFCF) | 0x10;
        D_80079958->control = control;
        delay_multiply_loop();
        poll_count = 0;
        while (D_80079958->status.value & 0x400) {
            if (++poll_count >= 0xF01) {
                printf(D_800331F4, D_80033214);
                break;
            }
        }
        delay_multiply_loop();
        delay_multiply_loop();
        bytes_left -= chunk_bytes;
    }

    expected_status = saved_status;
    poll_count = 0;
    control = D_80079958->control;
    control &= 0xFFCF;
    D_80079958->control = control;
    while ((D_80079958->status.value & 0x7FF) != expected_status) {
        if (++poll_count >= 0xF01) {
            printf(D_800331F4, D_80033228);
            break;
        }
    }
}
#include "slus/sound_dma_lifecycle.h"

/* Clears the SPU transfer mode, waits for it to clear, and signals completion. */
void func_8005D064(void)
{
    u32 poll_count;
    u32 event_class;
    SoundTransferRegisters *spu_regs;

    if (D_800799A8 == 0) {
        delay_multiply_loop();
    }

    spu_regs = D_80079958;
    spu_regs->control &= 0xFFCF;
    poll_count = 0;
    while (spu_regs->control & 0x30) {
        poll_count++;
        if (poll_count >= 0xF01) {
            break;
        }
    }

    event_class = 0xF0000000 + (u32)spu_regs;
    event_class -= (u32)spu_regs;
    if (D_80079990 != 0) {
        D_80079990(event_class);
    } else {
        DeliverEvent(event_class | 9, 0x20);
    }
}
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
/* func_8005D1D0 -- BYTE-EXACT, gcc 2.7.2 -O2 -G0, aspsx 2.56.
 *
 * Key shapes (see NOTES.txt for the full derivation and the negative sweep):
 *   `transfer_arg` carries BOTH of case 3's va_arg reads AND case 2's, so its pseudo is used
 *        in more than one basic block.  local-alloc's combine_regs then takes its
 *        `reg_qty[ureg] < 0` early-out and refuses to tie either the shift result or
 *        the andi result to the dying value -- which is what lets the block-count
 *        statements be written in retail's order (shift first) without the andi
 *        stealing $a0.  No register pin is needed on it.
 *   NO register pin is needed anywhere in the block-count code: once `transfer_arg` is the
 *        shared multi-block pseudo, the prior lane's `size`->$a0 and `blocks`->$v1
 *        pins are both dead (ablated, still MATCH) and were removed.
 *   The shift MUST be logical: `transfer_arg` is s32, so the (u32) casts are what make it
 *        `srl` rather than `sra`.
 *   Semantics carried from the prior lane: CHCR default 0x1000201 with 0x1000200 when
 *        D_800799A8 == 1; the block count is srl/andi/sltu/addu, branchless.
 *   D_800799AC is declared a volatile OBJECT with the store cast back to non-volatile
 *        so the reload survives cse without costing the bne's delay-slot fill.
 */
#include "slus/sound_dma_lifecycle.h"

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
        D_80079958->transfer_address.ordered = spu_addr;
        break;

    case 1:
        D_800799A8 = 0;
        expected_addr = D_80079970;
        poll_count = 0;
        while ((D_80079958->transfer_address.ordered & 0xFFFF) != expected_addr) {
            if (++poll_count >= 0xF01) {
                return -2;
            }
        }
        spu_control = D_80079958->control;
        spu_control = (spu_control & 0xFFCF) | 0x20;
        D_80079958->control = spu_control;
        break;

    case 0:
        D_800799A8 = 1;
        expected_addr = D_80079970;
        poll_count = 0;
        while ((D_80079958->transfer_address.ordered & 0xFFFF) != expected_addr) {
            if (++poll_count >= 0xF01) {
                return -2;
            }
        }
        spu_control = D_80079958->control;
        spu_control |= 0x30;
        D_80079958->control = spu_control;
        break;

    case 3:
        transfer_mode = 0x20;
        if (D_800799A8 == 1) {
            transfer_mode = 0x30;
        }
        poll_count = 0;
        while ((D_80079958->control & 0x30) != (transfer_mode & 0xFFFF)) {
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
        **(s32 **)&D_80079960 = (D_800799B0 << 16) | 0x10;
        dma_control = 0x1000201;
        if (D_800799A8 == 1) {
            dma_control = 0x1000200;
        }
        *D_80079964 = dma_control;
        break;
    }
    return 0;
}
#include "slus/sound_dma_lifecycle.h"

/* Multiplies a volatile stack value by 13 sixty times, then discards the result. */
void delay_multiply_loop(void) {
    volatile s32 iteration;
    volatile s32 product;

    product = 13;
    for (iteration = 0; iteration < 60; iteration++) {
        product = product * 13;
    }
}
