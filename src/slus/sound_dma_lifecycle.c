#include "slus/sound_dma_lifecycle.h"

#include "slus/sound_dma_lifecycle.h"

/* Initialize the SPU, resetting voice settings on a cold start. */
s32 initialize_spu_registers_and_voices(s32 warm)
{
    s32 entry_index;
    s32 result;
    u32 status_polls;
    volatile u16 *clear_entry;
    SoundTransferRegisters *spu_regs;

    *spu_dma_priority_register |= 0xB0000;
    spu_transfer_uses_fifo = 0;
    D_80079978 = 0;
    spu_transfer_address_units = 0;
    spu_registers->mvoll = 0;
    spu_registers->mvolr = 0;
    spu_registers->control = 0;
    delay_multiply_loop();
    spu_registers->mvoll = 0;
    spu_registers->mvolr = 0;
    status_polls = 0;
    while (spu_registers->status.ordered & 0x7FF) {
        if (++status_polls >= 0xF01) {
            printf(spu_timeout_format, spu_init_timeout_label);
            break;
        }
    }
    spu_address_alignment_enabled = 2;
    spu_address_unit_shift = 3;
    spu_address_alignment = 8;
    spu_address_alignment_mask = 7;
    spu_registers->transfer_control = 4;
    spu_registers->rvoll = 0;
    spu_registers->rvolr = 0;
    spu_registers->keyoff_lo = 0xFFFF;
    spu_registers->keyoff_hi = 0xFFFF;
    spu_registers->rev_lo = 0;
    spu_registers->rev_hi = 0;
    entry_index = 0;
    clear_entry = spu_keyon_shadow;
    for (; entry_index < 10; entry_index++) {
        *clear_entry = 0;
        clear_entry++;
    }
    if (warm == 0) {
        spu_transfer_address_units = 0x200;
        spu_registers->fm_lo = 0;
        spu_registers->fm_hi = 0;
        spu_registers->noise_lo = 0;
        spu_registers->noise_hi = 0;
        spu_registers->cdvoll = 0;
        spu_registers->cdvolr = 0;
        spu_registers->extvoll = 0;
        spu_registers->extvolr = 0;
        write_spu_transfer_fifo_in_chunks(spu_cold_start_sample, 0x10);
        spu_regs = spu_registers;
        for (entry_index = 0; entry_index < 24; entry_index++) {
            spu_regs->voice[entry_index].voll = 0;
            spu_regs->voice[entry_index].volr = 0;
            spu_regs->voice[entry_index].pitch = 0x3FFF;
            spu_regs->voice[entry_index].addr = 0x200;
            spu_regs->voice[entry_index].adsr1 = 0;
            spu_regs->voice[entry_index].adsr2 = 0;
        }
        spu_registers->keyon_lo = 0xFFFF;
        spu_registers->keyon_hi = 0xFF;
        delay_multiply_loop();
        delay_multiply_loop();
        delay_multiply_loop();
        delay_multiply_loop();
        spu_registers->keyoff_lo = 0xFFFF;
        spu_registers->keyoff_hi = 0xFF;
        delay_multiply_loop();
        delay_multiply_loop();
        delay_multiply_loop();
        delay_multiply_loop();
    }
    result = 0;
    spu_transfer_complete = 1;
    spu_registers->control = 0xC000;
    spu_transfer_callback = 0;
    D_80079994 = 0;
    return result;
}
#include "slus/sound_dma_lifecycle.h"

/* Writes source data to SPU RAM through the transfer FIFO and waits for completion. */
void write_spu_transfer_fifo_in_chunks(u16 *src, u32 bytes_left)
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
    initial_status = spu_registers->status.value;
    spu_registers->transfer_address.value = spu_transfer_address_units;
    saved_status = initial_status & 0x7FF;
    delay_multiply_loop();

    while (bytes_left != 0) {
        chunk_bytes = 0x40;
        if (bytes_left < 0x41) {
            chunk_bytes = bytes_left;
        }
        for (byte_offset = 0; byte_offset < chunk_bytes; byte_offset += 2) {
            spu_registers->transfer_fifo = *src_pos++;
        }
        control = spu_registers->control;
        control = (control & 0xFFCF) | 0x10;
        spu_registers->control = control;
        delay_multiply_loop();
        poll_count = 0;
        while (spu_registers->status.value & 0x400) {
            if (++poll_count >= 0xF01) {
                printf(spu_timeout_format, spu_fifo_busy_timeout_label);
                break;
            }
        }
        delay_multiply_loop();
        delay_multiply_loop();
        bytes_left -= chunk_bytes;
    }

    expected_status = saved_status;
    poll_count = 0;
    control = spu_registers->control;
    control &= 0xFFCF;
    spu_registers->control = control;
    while ((spu_registers->status.value & 0x7FF) != expected_status) {
        if (++poll_count >= 0xF01) {
            printf(spu_timeout_format, spu_fifo_status_timeout_label);
            break;
        }
    }
}
#include "slus/sound_dma_lifecycle.h"

/* Clears the SPU transfer mode, waits for it to clear, and signals completion. */
void complete_spu_dma_and_signal_event(void)
{
    u32 poll_count;
    u32 event_class;
    SoundTransferRegisters *spu_regs;

    if (spu_dma_read_direction == 0) {
        delay_multiply_loop();
    }

    spu_regs = spu_registers;
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
    if (spu_transfer_callback != 0) {
        spu_transfer_callback(event_class);
    } else {
        DeliverEvent(event_class | 9, 0x20);
    }
}
#include "slus/sound_dma_lifecycle.h"

/* Starts a DMA transfer from SPU RAM to main RAM. */
void submit_spu_dma_read_blocks(s32 ram_address, s16 spu_address, s32 block_count)
{
    spu_registers->transfer_address.ordered = spu_address;
    delay_multiply_loop();
    spu_registers->control |= 0x30;
    delay_multiply_loop();
    select_spu_dma_read_channel_flags();

    *spu_dma_ram_address_register = ram_address;
    *spu_dma_block_control_register = ((u32)block_count << 16) | 0x10;
    spu_dma_read_direction = 1;
    *spu_dma_channel_control_register = 0x01000200;
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
s32 dispatch_spu_dma_transfer_command(s32 command, ...)
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
        spu_addr = (u32)transfer_arg >> spu_address_unit_shift;
        spu_transfer_address_units = spu_addr;
        spu_registers->transfer_address.ordered = spu_addr;
        break;

    case 1:
        spu_dma_read_direction = 0;
        expected_addr = spu_transfer_address_units;
        poll_count = 0;
        while ((spu_registers->transfer_address.ordered & 0xFFFF) != expected_addr) {
            if (++poll_count >= 0xF01) {
                return -2;
            }
        }
        spu_control = spu_registers->control;
        spu_control = (spu_control & 0xFFCF) | 0x20;
        spu_registers->control = spu_control;
        break;

    case 0:
        spu_dma_read_direction = 1;
        expected_addr = spu_transfer_address_units;
        poll_count = 0;
        while ((spu_registers->transfer_address.ordered & 0xFFFF) != expected_addr) {
            if (++poll_count >= 0xF01) {
                return -2;
            }
        }
        spu_control = spu_registers->control;
        spu_control |= 0x30;
        spu_registers->control = spu_control;
        break;

    case 3:
        transfer_mode = 0x20;
        if (spu_dma_read_direction == 1) {
            transfer_mode = 0x30;
        }
        poll_count = 0;
        while ((spu_registers->control & 0x30) != (transfer_mode & 0xFFFF)) {
            if (++poll_count >= 0xF01) {
                return -2;
            }
        }
        if (spu_dma_read_direction == 1) {
            select_spu_dma_read_channel_flags();
        } else {
            select_spu_dma_write_channel_flags();
        }
        transfer_arg = VA_ARG(args, s32);
        *(s32 *)&spu_dma_ram_address = transfer_arg;
        transfer_arg = VA_ARG(args, s32);
        block_count = (u32)transfer_arg >> 6;
        partial_block = ((u32)transfer_arg & 0x3F) != 0;
        spu_dma_block_count = block_count + partial_block;
        *spu_dma_ram_address_register = spu_dma_ram_address;
        **(s32 **)&spu_dma_block_control_register = (spu_dma_block_count << 16) | 0x10;
        dma_control = 0x1000201;
        if (spu_dma_read_direction == 1) {
            dma_control = 0x1000200;
        }
        *spu_dma_channel_control_register = dma_control;
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
