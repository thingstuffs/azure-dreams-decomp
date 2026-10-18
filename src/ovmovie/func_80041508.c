#include "modules/ovmovie_libpress.h"


/* Prints decoder diagnostics and resets the decoder and its DMA channels. */
static s32 report_decoder_error_and_reset(const char *diagnostic_value) {
    u32 decoder_status;
    u32 input_dma_busy;
    u32 output_dma_busy;
    s32 result;

    printf(&D_8017689C, diagnostic_value);
    decoder_status = *(volatile u32 *) D_80178380;
    input_dma_busy = (*(volatile u32 *)D_80178354 >> 0x18) & 1;
    output_dma_busy = (*(volatile u32 *) D_80178360 >> 0x18) & 1;
    printf(&D_8017683C, input_dma_busy, output_dma_busy, *D_8017834C, *D_80178358);
    printf(&D_80176864, (u32) ~decoder_status >> 0x1F, (decoder_status >> 0x1E) & 1, (decoder_status >> 0x1D) & 1,
           (decoder_status >> 0x1C) & 1, (decoder_status >> 0x1B) & 1, (decoder_status >> 0x19) & 1,
           (decoder_status >> 0x17) & 1);
    *D_80178380 = 0x80000000;
    *D_80178354 = 0;
    *D_80178360 = 0;
    result = 0;
    (void) *(volatile u32 *) D_80178360;
    *D_80178380 = 0x60000000;
    return result;
}
