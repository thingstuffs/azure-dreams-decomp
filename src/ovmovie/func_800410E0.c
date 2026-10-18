#include "modules/ovmovie_libpress.h"


/* Read status bit 29, or refresh and hand back the refresher's status. */
s32 read_decoder_input_dma_status(s32 read_status_bit) {
    if (read_status_bit != 0) {
        return (read_decoder_status_register() >> 0x1D) & 1;
    }
    return wait_for_decoder_input_dma();
}
