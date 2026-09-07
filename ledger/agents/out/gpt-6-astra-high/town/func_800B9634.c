#include "common.h"

extern void *func_80040574(s32 size);
extern void bzero(void *dst, s32 size);
extern void func_80067014(s32 arg0);
extern void func_800672D8(s16 *rect, void *data);

/* Clear the texture's rectangle with zeroed image data. */
void func_800B6D94(void *texture) {
    s16 rect[4];
    void *clear_data;

    clear_data = func_80040574(0x200);
    bzero(clear_data, 0x200);
    func_80067014(0);

    rect[0] = (*(u8 *)((u8 *)texture + 8) >> 2)
            + ((*(u16 *)((u8 *)texture + 4) << 6) & 0x3C0);
    rect[1] = ((*(u16 *)((u8 *)texture + 4) << 4) & 0x100)
            + *(u8 *)((u8 *)texture + 9);
    rect[2] = *(u8 *)((u8 *)texture + 10) >> 2;
    rect[3] = *(u8 *)((u8 *)texture + 11);

    func_800672D8(rect, clear_data);
    func_80067014(0);
}
