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
extern PackedVec3 D_800256E0;
extern u8 D_80045340[];
extern s32 D_800814A0;
extern void *D_800814A8;

extern void *func_8003FC64(u32);
extern void func_8004491C(void *, void *);
extern void func_800B8FC8(void *, Rect16 *, void *, s32, s32);

/* Creates a display effect in a free slot and expires the owner when its timer ends. */
void func_80024104(void *owner) {
    s16 center[2];
    RectTable rect_table;
    u8 *copy_src;
    u8 *copy_dst;
    u8 *copy_end;
    s16 slot;
    s32 rect_offset;
    Rect16 *rect;
    void *effect;
    u8 *effect_work;
    Display *display;
    void *vector_src;
    void *vector_dst;
    u16 timer;

    copy_dst = (u8 *)&rect_table;
    copy_src = (u8 *)&D_80024004;
    if ((u32)copy_src & 3) {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(PackedBlock *)copy_dst = *(PackedBlock *)copy_src;
            copy_src += sizeof(PackedBlock);
            copy_dst += sizeof(PackedBlock);
        } while (copy_src != copy_end);
    } else {
        copy_end = copy_src + sizeof(RectTable);
        do {
            *(AlignedBlock *)copy_dst = *(AlignedBlock *)copy_src;
            copy_src += sizeof(AlignedBlock);
            copy_dst += sizeof(AlignedBlock);
        } while (copy_src != copy_end);
    }

    slot = 0;
slot_loop:
    if ((*(s16 *)((u8 *)owner + 0x46 + (((s32)slot << 16) >> 15))) != 0) {
        slot++;
        if (slot < 8) {
            goto slot_loop;
        }
    }

    if (slot != 8) {
        (*(s16 *)((u8 *)owner + 0x46 + slot * 2)) = 1;
        rect_offset = (s32)slot << 3;
        rect = (Rect16 *)((u8 *)&rect_table + rect_offset);
        center[0] = rect->x + ((s16)rect->w >> 1);
        center[1] = rect->y + 0x30;
        func_800B8FC8(D_800814A8, rect, center, 1, 1);

        effect = func_8003FC64(0x212);
        if (effect != 0) {
            effect_work = (u8 *)effect + 0x20;
            ((S_80024104_0 *)effect_work)->unk_2A = 7;
            ((S_80024104_0 *)effect_work)->unk_2C = 7;
            ((S_80024104_0 *)effect_work)->unk_32 = slot;
            ((S_80024104_0 *)effect_work)->unk_60 = owner;
            ((S_80024104_1 *)effect)->unk_10 = D_8002405C;
            func_8004491C(effect, D_80045340);

            display = ((S_80024104_1 *)effect)->unk_0C;
            display->field6 = 4;
            display->flags &= 0xFFF3;

            vector_src = ((S_80024104_2_pre *)D_800814A8)[-1].unk_00;
            vector_dst = ((S_80024104_1 *)effect)->unk_08;
            ((s32 *)vector_dst)[0] = ((s32 *)vector_src)[0];
            ((s32 *)vector_dst)[1] = ((s32 *)vector_src)[1];
            ((s32 *)vector_dst)[2] = ((s32 *)vector_src)[2];

            display = ((S_80024104_1 *)effect)->unk_0C;
            display->scaleX = 0x1000;
            display->scaleY = 0x1000;
            display->blue = 0x80;
            display->green = 0x80;
            display->red = 0x80;

            *(PackedVec3 *)((u8 *)effect + 0x92) = D_800256E0;
            display->vector = (u8 *)effect + 0x92;
            ((S_80024104_0 *)effect_work)->unk_7A = (u8)rect->x - 0x40;
            ((S_80024104_0 *)effect_work)->unk_7B = (u8)rect->y;
        }
    }

    timer = (*(u16 *)((u8 *)owner + 0x2A)) - 1;
    (*(u16 *)((u8 *)owner + 0x2A)) = timer;
    if ((s16)timer <= 0) {
        (*(u16 *)((u8 *)owner + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
