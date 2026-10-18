#include "slus/gp_shared_8152c.h"

void runtime_no_op_callback(void)
{
    D_8008152C = upload_image_tiles(&D_80016000, 0xB, 0x7900, 0xD, &D_80023000);
}
