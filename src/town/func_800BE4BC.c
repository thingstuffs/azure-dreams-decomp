#include "shared/object_node.h"
#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct
{
    u8 pad0[8];
    s32 *field_0x8;
    u8 pad0xC[4];
    void *field_0x10;
}
S_800BE4BC;
extern void func_80033B78(s32 flag_id);
extern void *func_8003FD64(s32 flags, void *list_head);
extern u8 D_800BBCA0[16];
/* Creates an object and initializes its data pointer and three input values. */
s32 func_800BBC1C(s32 *values)
{
    S_800BE4BC *object;
    u8 (*object_data)[16];
    S_800BE4BC *created_object;
    s32 *values_src;
    u8 (*init_data)[16];
    func_80033B78(0x97);
    init_data = ((u8 *)(&D_80083498));
    object = func_8003FD64(0x312, init_data);
    created_object = object;
    if (created_object != 0) {
        object_data = &D_800BBCA0;
        object->field_0x10 = object_data;
        object->field_0x8[0] = values[0];
        values_src = values;
        object->field_0x8[1] = values_src[1];
        object->field_0x8[2] = values_src[2];
    }
    if (object) {
        return 0;
    }
    else {
        return 0;
    }
}
