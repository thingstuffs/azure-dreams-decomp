#include "common.h"

typedef struct S_8196BD3C_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    u8 pad_2E[0x4E];
    void * unk_7C;
} S_8196BD3C_0;   /* work in func_8196BD3C */

typedef struct S_8196BD3C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8196BD3C_1;   /* obj in func_8196BD3C */

typedef struct S_8196BD3C_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8196BD3C_2_pre;   /* the 0x18 bytes before arg0 in func_8196BD3C, addressed as arg0[-1] */



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
        ((S_8196BD3C_0 *)work)->unk_2C = 0xB;
        ((S_8196BD3C_0 *)work)->unk_7C = arg0;
        ((S_8196BD3C_1 *)obj)->unk_10 = D_8002525C;
        func_8004491C(obj, D_80045340);

        display = ((S_8196BD3C_1 *)obj)->unk_0C;
        display->field10 = 0x20;
        display->field6 = 0;
        display->flags |= 0xC;

        from = ((S_8196BD3C_2_pre *)arg0)[-1].unk_00;
        to = ((S_8196BD3C_1 *)obj)->unk_08;
        ((s32 *)to)[0] = ((s32 *)from)[0];
        ((s32 *)to)[1] = ((s32 *)from)[1];
        ((s32 *)to)[2] = ((s32 *)from)[2];

        display = ((S_8196BD3C_1 *)obj)->unk_0C;
        display->scaleX = 0;
        display->scaleY = 0;
        display->blue = 0;
        display->green = 0;
        display->red = 0;

        *(PackedVec3 *)((u8 *)obj + 0x58) = D_80026978;
        display->vector = (u8 *)obj + 0x58;
    }
}
