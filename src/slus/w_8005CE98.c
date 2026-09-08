#include "common.h"

/* SPU hardware register mirror reached through D_80079958 (base 0x1F801C00). */
typedef struct {
    u8  pad000[0x1A6];
    volatile u16 dt_addr;   /* 0x1A6 */
    volatile u16 dt_fifo;   /* 0x1A8 */
    volatile u16 spucnt;    /* 0x1AA */
    u16 pad1AC;
    volatile u16 spustat;   /* 0x1AE */
} SpuRegs;

extern SpuRegs *D_80079958;
extern u16 D_80079970;
extern char D_800331F4[];
extern char D_80033214[];
extern char D_80033228[];

extern void func_8005D730(void);
extern void printf();

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
    initial_status = D_80079958->spustat;
    D_80079958->dt_addr = D_80079970;
    saved_status = initial_status & 0x7FF;
    func_8005D730();

    while (bytes_left != 0) {
        chunk_bytes = 0x40;
        if (bytes_left < 0x41) {
            chunk_bytes = bytes_left;
        }
        for (byte_offset = 0; byte_offset < chunk_bytes; byte_offset += 2) {
            D_80079958->dt_fifo = *src_pos++;
        }
        control = D_80079958->spucnt;
        control = (control & 0xFFCF) | 0x10;
        D_80079958->spucnt = control;
        func_8005D730();
        poll_count = 0;
        while (D_80079958->spustat & 0x400) {
            if (++poll_count >= 0xF01) {
                printf(D_800331F4, D_80033214);
                break;
            }
        }
        func_8005D730();
        func_8005D730();
        bytes_left -= chunk_bytes;
    }

    expected_status = saved_status;
    poll_count = 0;
    control = D_80079958->spucnt;
    control &= 0xFFCF;
    D_80079958->spucnt = control;
    while ((D_80079958->spustat & 0x7FF) != expected_status) {
        if (++poll_count >= 0xF01) {
            printf(D_800331F4, D_80033228);
            break;
        }
    }
}
