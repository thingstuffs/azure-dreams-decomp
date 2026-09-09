#include "common.h"

extern s32 D_800786E8[];

/* Set the object color, optional display table, and display dimensions. */
void func_800241D4(s32 object_addr, s32 enable_table) {
    s8 *object_data;
    void *display_data;

    if (object_addr != 0) {
        object_data = (s8 *) object_addr + 0x20;
        display_data = *(void **) (object_data + 0x280);
        *(s32 *) (object_data + 0x224) = 0x808080;
        if (enable_table != 0) {
            *(s32 **) display_data = D_800786E8;
        } else {
            *(s32 *) display_data = 0;
        }
        *(s16 *) (*(s8 **) ((s8 *) display_data + 4) + 8) = 0x60;
        *(s16 *) (*(s8 **) ((s8 *) display_data + 4) + 0xA) = 0x18;
    }
}
