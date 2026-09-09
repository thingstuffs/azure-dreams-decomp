#include "common.h"

extern void file_load_com(void *arg0);
extern s32 func_8008B328(void);

extern u8 D_800CF828[];
extern void *D_800CF838[];

/* Process the 15 object slots and update the first slot from the status check. */
void func_8008B4B0(void) {
    s32 slot;
    u8 *object_ids;
    void **objects;
    register u8 *id_ptr ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    slot = 0;
    object_ids = D_800CF828;
    objects = D_800CF838;
    do {
        u8 object_id;

        id_ptr = (u8 *)((unsigned long)slot + (unsigned long)object_ids);
        ASM_KEEP(id_ptr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        object_id = *id_ptr;

        if (object_id != 0) {
            file_load_com(objects[object_id]);
        }
        slot++;
    } while (slot < 15);

    if (func_8008B328() != 0) {
        D_800CF828[0] = 1;
        D_800CF828[1] = 0;
        return;
    }
    D_800CF828[0] = 0;
}
