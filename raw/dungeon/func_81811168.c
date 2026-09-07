#include "common.h"

typedef struct DungeonSub81811168 {
    u8 pad00[0x50];
    s32 value50;
    s32 value54;
} DungeonSub81811168;

typedef struct DungeonObj81811168 {
    u8 pad00[0xC];
    void *field0C;
    u8 pad10[0xE];
    u16 flags1E;
    DungeonSub81811168 sub20;
} DungeonObj81811168;

extern DungeonObj81811168 *func_8003FC64(s32);
extern s32 func_800260CC(DungeonSub81811168 *, s32);
extern s32 func_80025D74(s32);
extern void func_80026084(DungeonSub81811168 *, s32, s32, s32);
extern void func_8004491C(DungeonObj81811168 *, void *);
extern void func_80026314(DungeonObj81811168 *);
extern void func_8002622C(void) __attribute__((noreturn));
extern void func_8004B248(void *);
extern u8 D_8004CAA0[9];
extern s32 D_800814A0[3];

DungeonObj81811168 *func_80026168(s32 arg0, s32 arg1, s32 arg2)
{
    DungeonObj81811168 *obj;
    DungeonSub81811168 *sub;
    register DungeonObj81811168 *ret ASM_REG("$2");

    obj = func_8003FC64(0);
    sub = &obj->sub20;
    if (obj != 0) {
        if (func_800260CC(sub, 13) != 0) {
            obj->field0C = (u8 *)obj + 0x64;
            sub->value50 = func_80025D74(sub->value54);
            func_80026084(sub, arg0, arg1, arg2);
            func_8004491C(obj, D_8004CAA0);
            func_80026314(obj);
            ret = obj;
            ASM_TAILSLOT_PIN(ret);
            func_8002622C();
        } else {
            func_8004B248((u8 *)obj + 0x78);
            obj->flags1E |= 0x8000;
            obj = 0;
            D_800814A0[0] |= 0x8000;
        }
    }
    return obj;
}
