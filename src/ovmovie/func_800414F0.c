#include "modules/ovmovie_libpress.h"


/* Return the value pointed to by D_80178380. */
static u32 read_decoder_status_register(void) {
    return *(s32 *)D_80178380;
}
