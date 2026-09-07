#include "common.h"

typedef struct CallbackSlot {
    s8 type;
    s8 value;
} CallbackSlot;

typedef struct CallbackObject {
    u8 pad_00[0x2C];
    CallbackSlot slots[4];
} CallbackObject;

typedef struct CallbackGlobals {
    u16 flags;
    u8 pad_02[8];
} CallbackGlobals;

extern CallbackGlobals D_80013714;

extern s32 func_80042518(CallbackObject *object, s32 type);
extern void func_800A48F0(CallbackObject *object, s32 type, s32 value);

void func_80042560(CallbackObject *object)
{
    CallbackSlot slots[4];
    s32 initial_type = 0x1B;
    s32 i = 0;
    CallbackGlobals *globals = &D_80013714;
    u16 saved_flags;

    ASM_KEEP(initial_type);   /* MATCH pin: slus-diff */
    saved_flags = globals->flags;
    globals->flags = saved_flags | 2;
    func_80042518(object, initial_type);

    for (; i < 4; i++) {
        slots[i] = object->slots[i];
        if (slots[i].type != 0) {
            func_80042518(object, slots[i].type);
        }
    }

    for (i = 0; i < 4; i++) {
        if (slots[i].type != 0) {
            func_800A48F0(object, slots[i].type, slots[i].value);
        }
    }

    D_80013714.flags = saved_flags;
}
