#include "common.h"

extern u32 func_8009FD68();
extern void *D_8001029C;

/* Process table entries referenced by objects of type 0x13. */
void func_8009FE84(void) {
    void **object_entry;
    u8 *object;
    s32 object_type;
    u32 table_base;

    if (D_8001029C != 0) {
        object_type = 0x13;

        table_base = 0x800102F0;

        object_entry = (void **)0x8001029C;
        do {
            object = *object_entry;
            if (object[1] == object_type) {
                func_8009FD68((void *)((object[3] & 0x1F) * 84 + table_base));
            }
            object_entry++;
        } while (*object_entry != 0);
    }
}
