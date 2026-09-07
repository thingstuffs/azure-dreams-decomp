#include "common.h"

#include "common.h"

typedef struct Func800398BCOwner {
    u8 pad_00[0x10];
    s32 field_10;
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u8 *object_80;
    u8 pad_84[0x04];
    s8 field_88;
} Func800398BCOwner;

extern s32 func_80053EF0(s32 arg0);
extern s32 func_80039884(Func800398BCOwner *arg0);
extern void func_8003F540(s32 arg0, s32 arg1, u32 arg2, u32 arg3);
extern s16 func_80053DA8(s32 arg0);
extern s32 D_800721C0[32];
extern s32 D_8006CD50[];

void func_800398BC(Func800398BCOwner *arg0)
{
    s32 state;
    s32 gate;
    u8 *cursor;
    u8 *cursor4;
    u32 word0;
    u32 word1;
    u32 index;

    state = func_80053EF0(4);
    gate = func_80039884(arg0);
    if (gate != 0) {
        if (state == 0) {
            goto decode;
        }
        goto rewind;
    }
    if (state == 0x100) {
        goto rewind;
    }
    if (state != 3) {
        goto decode;
    }

rewind:
    arg0->field_10 = 0;
    arg0->read_ptr--;
    goto done;

decode:
    cursor = arg0->read_ptr;
    word0 = cursor[0] + (cursor[1] << 8) +
            (cursor[2] << 16) + (cursor[3] << 24);
    cursor4 = cursor + 4;
    arg0->read_ptr = cursor4;
    word1 = cursor[4] + (cursor4[1] << 8) +
            (cursor4[2] << 16) + (cursor4[3] << 24);
    arg0->read_ptr = cursor + 8;
    index = (word0 >> 19) & 0x1F;
    word0 &= 0xFF07FFFF;

    func_8003F540(arg0->object_80[0x3C],
                  D_8006CD50[D_800721C0[index]],
                  word0,
                  word1);
    func_80053DA8(0x300);
    arg0->field_10 = 0;
done:
    return;
}
