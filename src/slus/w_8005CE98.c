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
    delayMultiplyLoop();

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
        delayMultiplyLoop();
        poll_count = 0;
        while (D_80079958->status.value & 0x400) {
            if (++poll_count >= 0xF01) {
                printf(D_800331F4, D_80033214);
                break;
            }
        }
        delayMultiplyLoop();
        delayMultiplyLoop();
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
