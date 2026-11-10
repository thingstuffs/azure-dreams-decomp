#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8001E869;

/* Returns the default request data. */
void *initialize_request(void) {
    return &D_8001E869;
}
