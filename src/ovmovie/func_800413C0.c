#include "modules/ovmovie_libpress.h"


static s32 wait_for_decoder_input_dma(void) {
    volatile s32 polls_left = 0x100000;
    if (*D_80178380 & 0x20000000) {
        do {
            if (--polls_left == -1) {
                report_decoder_error_and_reset((const char *)&D_8017681C);
                return -1;
            }
        } while (*D_80178380 & 0x20000000);
    }
    return 0;
}
