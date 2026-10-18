#include "common.h"
#include "m2c_compat.h"

void file_load_com(void *packed_data);
extern M2C_UNK D_800D1B64;

/* Pass D_800D1B64 to file_load_com. */
void load_resource_data(void) {
    file_load_com(&D_800D1B64);
}
