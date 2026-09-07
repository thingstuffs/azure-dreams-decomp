#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u32 word[3];
} __attribute__((packed)) PackedVec3;

typedef struct {
    u8 pad0[6];
    s16 field6;
    void *vector;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scaleY;
    s16 scaleX;
} Display;

extern u8 D_8002525C[];
extern PackedVec3 D_80026978;
extern u8 D_80045340[];

extern void *func_8003FC64(u32);
extern void func_8004491C(void *, void *);

void func_8196BD3C(void *arg0) {
    void *obj;
    u8 *work;
    Display *display;
    void *from;
    void *to;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        FIELD(work, s16, 0x2C) = 0xB;
        FIELD(work, void *, 0x7C) = arg0;
        FIELD(obj, void *, 0x10) = D_8002525C;
        func_8004491C(obj, D_80045340);

        display = FIELD(obj, void *, 0xC);
        display->field10 = 0x20;
        display->field6 = 0;
        display->flags |= 0xC;

        from = FIELD(arg0, void *, -0x18);
        to = FIELD(obj, void *, 8);
        ((s32 *)to)[0] = ((s32 *)from)[0];
        ((s32 *)to)[1] = ((s32 *)from)[1];
        ((s32 *)to)[2] = ((s32 *)from)[2];

        display = FIELD(obj, void *, 0xC);
        display->scaleX = 0;
        display->scaleY = 0;
        display->blue = 0;
        display->green = 0;
        display->red = 0;

        *(PackedVec3 *)((u8 *)obj + 0x58) = D_80026978;
        display->vector = (u8 *)obj + 0x58;
    }
}
