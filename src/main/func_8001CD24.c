#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001CD24_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8001CD24_0;   /* arg0 in func_8001CD24 */


M2C_UNK func_80403CD4();                         /* extern */
extern s32 D_8008DAB4;

/* Process embedded data and set object and global flags when the object exists. */
void func_8001CD24(void *object) {
    if (object != NULL) {
        func_80403CD4(object + 0x20);
        (*(u16 *)((u8 *)object + 0x1E)) = (u16) (((S_8001CD24_0 *)object)->unk_1E | 0x8000);
        D_8008DAB4 |= 0x8000;
    }
}
