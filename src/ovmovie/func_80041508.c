#include "common.h"

s32 printf(); /* extern, called with varying arg counts (2/5/8) - old-style unprototyped decl */
extern u32 D_8017683C;
extern u32 D_80176864;
extern u32 D_8017689C;
extern s32 *D_8017834C;
extern volatile u32 *D_80178354;
extern s32 *D_80178358;
extern u32 *D_80178360;
extern u32 *D_80178380;

/* Prints decoder diagnostics and resets the decoder and its DMA channels. */
s32 func_80041508(u32 diagnostic_value) {
    u32 decoder_status;
    u32 input_dma_busy;
    u32 output_dma_busy;
    s32 result;

    printf(&D_8017689C, diagnostic_value);
    decoder_status = *(volatile u32 *) D_80178380;
    input_dma_busy = (*D_80178354 >> 0x18) & 1;
    output_dma_busy = (*(volatile u32 *) D_80178360 >> 0x18) & 1;
    printf(&D_8017683C, input_dma_busy, output_dma_busy, *D_8017834C, *D_80178358);
    printf(&D_80176864, (u32) ~decoder_status >> 0x1F, (decoder_status >> 0x1E) & 1, (decoder_status >> 0x1D) & 1, (decoder_status >> 0x1C) & 1, (decoder_status >> 0x1B) & 1, (decoder_status >> 0x19) & 1, (decoder_status >> 0x17) & 1);
    *D_80178380 = 0x80000000;
    *D_80178354 = 0;
    *D_80178360 = 0;
    result = 0;
    (void) *(volatile u32 *) D_80178360;
    *D_80178380 = 0x60000000;
    return result;
}
