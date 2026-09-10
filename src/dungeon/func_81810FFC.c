#include "common.h"

extern void func_80025CD8();
extern void func_80025D28();
extern void strcpy();
extern s32 D_80025BF4[];

/* Initializes the object's range, value, and text fields. */
void func_80025FFC(void *object, s32 range_start, s32 initial_value, s32 text_addr)
{
    u8 *data = object;
    s32 saved_value = initial_value;
    s32 saved_text = text_addr;

    func_80025CD8(*(s32 *)(data + 0x74));
    func_80025D28(*(s32 *)(data + 0x74) + 0xC);
    *(s32 *)(data + 0x14) = range_start;
    *(s32 *)(data + 0x0C) = saved_value;
    *(s32 *)(data + 0x18) = range_start + 0x20;
    *(s32 *)(data + 0x88) = saved_text;
    strcpy(data + 0x78, saved_text);
    do {
        ASM_KEEP(saved_value);
    } while (0);
    *(s32 **)(data - 0x10) = D_80025BF4;
}

/* MECHANISM: Four call-crossing inputs produce the retail 0x28 frame and s0-s3 saves.
   Guarded initial_value->$s2 holding fixes the s2/s3 coloring and exact prologue emission order.
   The natural stores then place text_addr's 0x88 write in strcpy's delay slot. */
