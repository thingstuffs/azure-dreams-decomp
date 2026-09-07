#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003DE58();
extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 func_80047784();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80175C60;
extern s32 D_80175D74;

void func_80175DD0(void *arg0, void *arg1, void *arg2, s16 arg3) {
    u16 position[3];
    u16 angle;
    s32 table_offset;
    void *coords;
    void *object_data;
    void *object;

    if (func_8003DE58(FIELD(arg2, s32, 8), arg2, position, arg3) != 0) {
        object = func_8003FD64(0x300, (u8 *)arg0 - 0x20);
        if ((object != NULL) &&
            ((object_data = FIELD(object, void *, 0xC),
              coords = FIELD(object, void *, 8),
              FIELD(object, void *, 0x10) = &D_80175C60,
              FIELD(object_data, s16, 0x1E) = 0x400,
              FIELD(object_data, s16, 0x1C) = 0x400,
              FIELD(object_data, s32, 0xC) = 0x808080,
              FIELD(object_data, s32, 0x28) = FIELD(arg2, s32, 0x28),
              FIELD(coords, s16, 2) = FIELD(arg1, u16, 2) + position[0],
              FIELD(coords, s16, 6) = FIELD(arg1, u16, 6) + position[1],
              FIELD(coords, s16, 0xA) = FIELD(arg1, u16, 0xA) + position[2],
              table_offset = (FIELD(arg0, u16, 0x2A) >> 8) & 0xE,
              FIELD(coords, u16, 0xE) = *(u16 *)(&D_8006CCD8 + table_offset),
              FIELD(coords, u16, 0x12) = *(u16 *)(&D_8006CCE8 + table_offset),
              FIELD(object, s16, 0x40) = 0x10,
              FIELD(object, s16 *, 0x20) = (s16 *)((u8 *)arg0 + 0x2A),
              func_80047784(object_data, 0x45, 0, coords),
              func_8004491C(object, &D_80175D74),
              angle = ((((D_80083228 + *FIELD(object, s16 *, 0x20) + 0x100) >> 9) & 7) + 2) << 9,
              FIELD(object_data, s16, 0x18) = angle,
              angle == 0x400) ||
             (angle == 0xC00))) {
            FIELD(object_data, s16, 0x18) = angle + 0x100;
        }
    }
}
