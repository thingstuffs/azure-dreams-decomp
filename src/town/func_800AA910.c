#include "common.h"

typedef struct {
    u8 pad_00[0x72];
    s16 angle;
} Inner;

typedef struct {
    u8 pad_00[8];
    u16 *coords;
    u8 pad_0C[0x14];
    Inner inner;
} Object;

typedef struct {
    s32 unk_0;
    Object *object;
} ObjectSlot;

extern s32 func_800352FC(void);
extern void func_80033D08(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_800A8164(void);

extern s32 D_800814A0[3];
extern ObjectSlot D_80082660[];

void func_800A8070(u16 *arg0, u16 *arg1)
{
    u8 index = ((u8 *)arg0)[0x60];
    Object *object;
    Inner *inner;
    u16 *coords;

    if (func_800352FC() == 0) {
        func_80033D08(arg0);
        arg0[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    if (index != 0) {
        object = D_80082660[index].object;
        if (object != 0) {
            inner = &object->inner;
            coords = object->coords;
            arg1[1] = coords[1] + func_800644B8(inner->angle + 0x200) / 170;
            arg1[3] = coords[3] + func_80064584(inner->angle + 0x200) / 170;
            arg1[5] = coords[5] - 46;
        }
    }
}
