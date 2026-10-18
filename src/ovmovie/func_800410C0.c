#include "modules/ovmovie_libpress.h"
/* Send the output DMA request to the decoder. */
void request_decoder_output_dma(s32 destination, u32 words) { start_decoder_output_dma(destination, words); }
