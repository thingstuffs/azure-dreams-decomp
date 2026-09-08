#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3_32;

extern s32 D_800814A0;

extern s32 func_800644B8(s32 angle);
extern s32 func_80064584(s32 angle);
extern s32 func_800C648C(void *arg0);
extern void func_80033D08(void *arg0);

/* Computes an offset position from the linked object, flagging failed validation. */
void func_800C6CE4(void *object, Vec3_32 *out_pos)
{
    void *linked_object = *(void **)((u8 *)object + 0x9C);
    Vec3_32 *base_pos = *(Vec3_32 **)((u8 *)linked_object - 0x18);

    if (func_800C648C(linked_object) == 0) {
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
    out_pos->x = base_pos->x + func_800644B8(*(s16 *)((u8 *)*(void **)((u8 *)object + 0x9C) + 0x72)) * 0x140;
    out_pos->y = base_pos->y + func_80064584(*(s16 *)((u8 *)*(void **)((u8 *)object + 0x9C) + 0x72)) * 0x140;
    out_pos->z = base_pos->z + (s32)0xFFE60000;
}
