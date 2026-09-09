#include "common.h"

typedef struct S_80024104_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x4];
    s16 unk_32;
    u8 pad_34[0x2C];
    void * unk_60;
    u8 pad_64[0x16];
    u8 unk_7A;
    u8 unk_7B;
} S_80024104_0;   /* work in func_80024104 */

typedef struct S_80024104_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024104_1;   /* obj in func_80024104 */

typedef struct S_80024104_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80024104_2_pre;   /* the 0x18 bytes before D_800814A8 in func_80024104, addressed as D_800814A8[-1] */



typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} Rect16;

typedef struct {
    Rect16 rect[8];
} RectTable;

typedef struct {
    u32 word[3];
} __attribute__((packed)) PackedVec3;

typedef struct {
    u32 word[4];
} __attribute__((packed)) PackedBlock;

typedef struct {
    u32 word[4];
} AlignedBlock;

typedef struct {
    u8 pad0[6];
    s16 field6;
    void *vector;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    s16 scaleY;
    s16 scaleX;
} Display;

extern RectTable D_80024004;
extern u8 D_8002405C[];
extern PackedVec3 D_8002533C;
extern s16 D_80025384;
extern u8 D_80045340[];
extern s32 D_800814A0;
extern void *D_800814A8;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_800B8FC8(void *, Rect16 *, void *, s32, s32);

void func_80024104(void *arg0) {
    s16 center[2];
    RectTable table;
    u8 *src;
    u8 *dst;
    u8 *end;
    s16 index;
    s32 rectOffset;
    Rect16 *rect;
    void *obj;
    u8 *work;
    Display *display;
    void *from;
    void *to;
    u16 timer;

    dst = (u8 *)&table;
    src = (u8 *)&D_80024004;
    if ((u32)src & 3) {
        end = src + sizeof(RectTable);
        do {
            *(PackedBlock *)dst = *(PackedBlock *)src;
            src += sizeof(PackedBlock);
            dst += sizeof(PackedBlock);
        } while (src != end);
    } else {
        end = src + sizeof(RectTable);
        do {
            *(AlignedBlock *)dst = *(AlignedBlock *)src;
            src += sizeof(AlignedBlock);
            dst += sizeof(AlignedBlock);
        } while (src != end);
    }

    D_80025384 = 1;

    index = 0;
slot_loop:
    if ((*(s16 *)((u8 *)arg0 + 0x46 + (((s32)index << 16) >> 15))) != 0) {
        index++;
        if (index < 8) {
            goto slot_loop;
        }
    }

    if (index != 8) {
        (*(s16 *)((u8 *)arg0 + 0x46 + index * 2)) = 1;
        rectOffset = (s32)index << 3;
        rect = (Rect16 *)((u8 *)&table + rectOffset);
        center[0] = rect->x + ((s16)rect->w >> 1);
        center[1] = rect->y + 0x30;
        func_800B8FC8(D_800814A8, rect, center, 1, 1);

        obj = func_8003FC64(0x212);
        if (obj != 0) {
            work = (u8 *)obj + 0x20;
            ((S_80024104_0 *)work)->unk_2A = 7;
            ((S_80024104_0 *)work)->unk_2C = 7;
            ((S_80024104_0 *)work)->unk_32 = index;
            ((S_80024104_0 *)work)->unk_60 = arg0;
            ((S_80024104_1 *)obj)->unk_10 = D_8002405C;
            func_8004491C(obj, D_80045340);

            display = ((S_80024104_1 *)obj)->unk_0C;
            display->field6 = 4;
            display->flags &= 0xFFF3;

            from = ((S_80024104_2_pre *)D_800814A8)[-1].unk_00;
            to = ((S_80024104_1 *)obj)->unk_08;
            ((s32 *)to)[0] = ((s32 *)from)[0];
            ((s32 *)to)[1] = ((s32 *)from)[1];
            ((s32 *)to)[2] = ((s32 *)from)[2];

            display = ((S_80024104_1 *)obj)->unk_0C;
            display->scaleX = 0x1000;
            display->scaleY = 0x1000;
            display->blue = 0x80;
            display->green = 0x80;
            display->red = 0x80;

            *(PackedVec3 *)((u8 *)obj + 0x92) = D_8002533C;
            display->vector = (u8 *)obj + 0x92;
            ((S_80024104_0 *)work)->unk_7A = (u8)rect->x - 0x40;
            ((S_80024104_0 *)work)->unk_7B = (u8)rect->y;
        }
    }

    timer = (*(u16 *)((u8 *)arg0 + 0x2A)) - 1;
    (*(u16 *)((u8 *)arg0 + 0x2A)) = timer;
    if ((s16)timer <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: The 0x80-byte frame, sibling table/center locals, packed copies,
   held object roles, and noreturn tail shape preserve the seed's 184-word body.
   A block-local $v1 page pin lets LEAD27 sink lui 0x8002 into the tail-j slot. */
