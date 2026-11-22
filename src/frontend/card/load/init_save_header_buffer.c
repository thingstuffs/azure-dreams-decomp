#include "frontend/card/save_image.h"
#include "sdk/libc.h"
#include "common.h"
#include "frontend/card/load.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"

extern int D_80010208;

/* Initialize the destination from templates, apply index data, and set the mode flag. */
void init_save_header_buffer(CardDevSaveWork *save, int index, int mode)
{
    unsigned char index_data[16];
    CardDevSaveWork *dest_start;

    dest_start = save;
    memcpy(dest_start, D_80408EC8, 0x200);
    memcpy(dest_start->header.title_and_reserved, D_8040077C, 39);
    func_8003830C(index + 1, index_data);
    func_8007BF50(dest_start->header.title_and_reserved, index_data);
    D_80010208 = (mode == 2);
}
