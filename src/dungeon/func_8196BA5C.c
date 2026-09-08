#include "common.h"

typedef struct S_8196BA5C_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x10];
    u8 unk_40;
    u8 unk_41;
    u8 pad_42[0xE];
    s16 unk_50;
    u8 pad_52[0x2A];
    void * unk_7C;
} S_8196BA5C_0;   /* work in func_8196BA5C */

typedef struct S_8196BA5C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8196BA5C_1;   /* obj in func_8196BA5C */

typedef struct S_8196BA5C_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8196BA5C_2_pre;   /* the 0x18 bytes before D_800814A8 in func_8196BA5C, addressed as D_800814A8[-1] */



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

extern RectTable D_80024024;
extern u8 D_8002407C[];
extern PackedVec3 D_80026978;
extern s16 D_800269B4;
extern u8 D_80045340[];
extern s32 D_800814A0;
extern void *D_800814A8;

extern void func_80025320(void) __attribute__((noreturn));
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_800B8FC8(void *, Rect16 *, void *, s32, s32);

/* Creates an object in the first free rectangle slot and marks completion when the timer expires. */
void func_8196BA5C(void *owner) {
    s16 center[2];
    RectTable slot_rects;
    u8 *copy_src;
    u8 *copy_dst;
    u8 *copy_end;
    s16 slot;
    s32 rect_offset;
    Rect16 *rect;
    void *child;
    u8 *child_work;
    Display *display;
    void *source_vector;
    void *child_vector;
    u16 ticks_left;

    copy_dst = (u8 *)&slot_rects;
    copy_src = (u8 *)&D_80024024;
    if ((u32)copy_src & 3) {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(PackedBlock *)copy_dst = *(PackedBlock *)copy_src;
            copy_src += sizeof(PackedBlock);
            copy_dst += sizeof(PackedBlock);
        } while (copy_src != copy_end);
        {
            register u32 page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            page = 0x80020000;
            ASM_PAGEBASE_PIN(page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80025320();
        }
    } else {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(AlignedBlock *)copy_dst = *(AlignedBlock *)copy_src;
            copy_src += sizeof(AlignedBlock);
            copy_dst += sizeof(AlignedBlock);
        } while (copy_src != copy_end);
    }

    D_800269B4 = 1;

    slot = 0;
slot_loop:
    if ((*(s16 *)((u8 *)owner + 0x64 + (((s32)slot << 16) >> 15))) != 0) {
        slot++;
        if (slot < 8) {
            goto slot_loop;
        }
    }

    if (slot != 8) {
        (*(s16 *)((u8 *)owner + 0x64 + slot * 2)) = 1;
        rect_offset = (s32)slot << 3;
        rect = (Rect16 *)((u8 *)&slot_rects + rect_offset);
        center[0] = rect->x + ((s16)rect->w >> 1);
        center[1] = rect->y + 0x30;
        func_800B8FC8(D_800814A8, rect, center, 1, 1);

        child = func_8003FC64(0x212);
        if (child != 0) {
            child_work = (u8 *)child + 0x20;
            ((S_8196BA5C_0 *)child_work)->unk_2C = 7;
            ((S_8196BA5C_0 *)child_work)->unk_2E = 7;
            ((S_8196BA5C_0 *)child_work)->unk_50 = slot;
            ((S_8196BA5C_0 *)child_work)->unk_7C = owner;
            ((S_8196BA5C_1 *)child)->unk_10 = D_8002407C;
            func_8004491C(child, D_80045340);

            display = ((S_8196BA5C_1 *)child)->unk_0C;
            display->field6 = 4;
            display->flags &= 0xFFF3;

            source_vector = ((S_8196BA5C_2_pre *)D_800814A8)[-1].unk_00;
            child_vector = ((S_8196BA5C_1 *)child)->unk_08;
            ((s32 *)child_vector)[0] = ((s32 *)source_vector)[0];
            ((s32 *)child_vector)[1] = ((s32 *)source_vector)[1];
            ((s32 *)child_vector)[2] = ((s32 *)source_vector)[2];

            display = ((S_8196BA5C_1 *)child)->unk_0C;
            display->scaleX = 0x1000;
            display->scaleY = 0x1000;
            display->blue = 0x80;
            display->green = 0x80;
            display->red = 0x80;

            *(PackedVec3 *)((u8 *)child + 0x58) = D_80026978;
            display->vector = (u8 *)child + 0x58;
            ((S_8196BA5C_0 *)child_work)->unk_40 = (u8)rect->x - 0x40;
            ((S_8196BA5C_0 *)child_work)->unk_41 = (u8)rect->y;
        }
    }

    ticks_left = (*(u16 *)((u8 *)owner + 0x2C)) - 1;
    (*(u16 *)((u8 *)owner + 0x2C)) = ticks_left;
    if ((s16)ticks_left <= 0) {
        (*(u16 *)((u8 *)owner + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: The 0x80-byte frame, sibling table/center locals, packed copies,
   held object roles, and noreturn tail shape preserve the seed's 184-word body.
   A block-local $v1 page pin lets LEAD27 sink lui 0x8002 into the tail-j slot. */
