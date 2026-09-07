#include "common.h"

extern void func_80041284(void *arg0);
extern s32 func_8008B328(void);
extern void func_8008B534(void);

extern u8 D_800CF828[];
extern void *D_800CF838[];

void func_8008B4B0(void) {
    s32 i;
    u8 *flags;
    void **objects;
    register u8 *address ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    i = 0;
    flags = D_800CF828;
    objects = D_800CF838;
    do {
        u8 object_id;

        address = (u8 *)((unsigned long)i + (unsigned long)flags);
        ASM_KEEP(address);   /* MATCH pin: load-bearing for the whole function shape */
        object_id = *address;

        if (object_id != 0) {
            func_80041284(objects[object_id]);
        }
        i++;
    } while (i < 15);

    if (func_8008B328() != 0) {
        D_800CF828[0] = 1;
        D_800CF828[1] = 0;
        return;
    }
    D_800CF828[0] = 0;
}
