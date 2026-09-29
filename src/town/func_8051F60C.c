#include "shared/record_ptrs.h"
#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
/* Scale the linked object's value at offset 8 by 64 and add 0x220. */
void func_80016E0C(void)
{
    void *object_data;
    object_data = *(void **) ((s8 *) *((int *)(&D_80016000)) + 0x1C);
    *(s32 *) ((s8 *) object_data + 8) =
        (*(s32 *) ((s8 *) object_data + 8) << 6) + 0x220;
}
