#include "modules/ovmovie_libpress.h"


/* Apply the requested mode, performing setup when it is zero. */
void set_movie_decode_mode(s32 mode) {
    if (mode == 0) {
        func_8005FFFC();
    }
    reset_decoder_and_load_tables(mode);
}
