#include "common.h"

typedef struct {
    s32 v;
    s32 pad[2];
} D_8008DAB4_View; /* real D_8008DAB4 is >8B so hi/lo addressing is used */

/* Set bit 0x8000 in the object and global flags when the object exists. */
void func_8001DDBC(void *object) {
    if (object != 0) {
        u16 *flags_ptr = (u16 *)((u8 *)object + 0x1E);
        u16 object_flags = *flags_ptr;
        s32 global_flags;
        {
            extern s32 D_8008DAB4;
            global_flags = D_8008DAB4;
        }
        object_flags |= 0x8000;
        global_flags |= 0x8000;
        *flags_ptr = object_flags;
        {
            extern D_8008DAB4_View D_8008DAB4;
            D_8008DAB4.v = global_flags;
        }
    }
}
