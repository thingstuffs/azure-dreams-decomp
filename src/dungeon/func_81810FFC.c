#include "common.h"

extern void func_80025CD8();
extern void func_80025D28();
extern void strcpy();
extern s32 D_80025BF4[];

/* Initializes the object's range, value, and text fields. */
void func_80025FFC(void *object, s32 range_start, s32 initial_value, s32 text_addr)
{
    u8 *data = object;

    func_80025CD8(*(s32 *)(data + 0x74));
    func_80025D28(*(s32 *)(data + 0x74) + 0xC);
    *(s32 *)(data + 0x0C) = initial_value;
    *(s32 *)(data + 0x14) = range_start;
    *(s32 *)(data + 0x18) = range_start + 0x20;
    *(s32 *)(data + 0x88) = text_addr;
    strcpy(data + 0x78, text_addr);
    *(s32 **)(data - 0x10) = D_80025BF4;
}
