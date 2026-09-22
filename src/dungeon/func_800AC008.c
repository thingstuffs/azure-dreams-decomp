#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct AcHeader {
    u8 pad00[2];
    s16 field02;
    u8 pad04[2];
    s16 field06;
    u8 pad08[2];
    s16 field0A;
} AcHeader;

typedef struct AcMeta {
    u8 pad00[0x0C];
    u32 field0C;
    u8 pad10[4];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
} AcMeta;

typedef struct AcSub AcSub;

struct AcSub {
    void *field00;
    void *field04;
    u16 field08;
    s16 field0A;
    s16 field0C;
    u8 pad0E[2];
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1C;
    u8 pad20[2];
    u16 field22;
    s16 field24;
    u16 field26;
    void *field28;
    u8 pad2C[0x0C];
    u32 field38;
    u32 field3C;
    u8 pad40[0x10];
    void *slots[4];
};

typedef struct AcObject {
    u8 pad00[8];
    AcHeader *header;
    AcMeta *meta;
    void *field10;
    u8 pad14[0x0C];
    AcSub sub;
} AcObject;

extern u8 D_80083498[];
extern void *D_80073618[];
extern u8 D_800B06F0[];
extern u8 D_800B14FC[];
extern s32 D_800DF03C[];

extern AcObject *func_8003FD64(s32, void *, s32);
extern void func_8004491C(AcObject *, void *, AcMeta *);
extern s32 func_8004E298(void *, s32, s32);
extern s32 func_80069E98(s32);
extern void *func_800B12F4(void);
extern void func_800B1320(u8 *, s32, s32);
extern void func_800B135C(void *, s32);
extern void func_800B13CC(void *, s32);
extern void func_800B1400(void *, s32);
extern void *func_800B1434(void *, void *);

/* Build the floating number/icon widget: allocate it and lay out its digit sprites for the given style. */
void func_800B1768(s16 icon, s32 value_a, s32 value_b, s32 style, s16 compact, u16 unused_flags) {
    s32 tmp;
    s32 tmp2;
    s32 offset_x;
    s32 gap;
    s32 base_offset;
    register s32 slot_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s8 slot_y;
    s32 y_offset;
    s16 icon_held = icon;
    s32 index = value_a;
    register u8 *cursor ASM_REG("$21") = (u8 *)value_b;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 style_hold = style;
    s32 count = 0;
    s16 style_byte;
    AcObject *obj;
    AcHeader *header;
    AcMeta *meta;
    AcSub *sub;
    s32 *table_entry;
    u8 *base;
    u8 * base_2;
    void *new_buf;
    void *buf;
    void *call_arg;
    void *prev_arg;
    register s32 hard_zero;
    u32 color1;
    u32 color2;
    u8 tail_flags;
    u32 tail_field1c;

    obj = func_8003FD64(0x12, D_80083498, (s32)cursor);
    if (obj != NULL) {
        meta = obj->meta;
        header = obj->header;
        sub = &obj->sub;
        if ((compact << 0x10) != 0) {
            meta->field14 |= 1;
        }
        header->field02 = index;
        sub->field0A = index;
        header->field06 = (s32)cursor;
        sub->field0C = (s32)cursor;
        header->field0A = 0;
        sub->field08 = 1;
        meta->field1C = 0x1000;
        meta->field0C = 0;
        obj->field10 = D_800B14FC;
        func_8004491C(obj, D_800B06F0, meta);
        style_byte = style_hold & 0xFF;
        base = (u8 *)&sub->field38;
        ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        cursor = base;
        sub->field24 = (s16)((style_hold << 0x10) >> 0x18);
        sub->field00 = (u8 *)&sub->slots[0];
        sub->field04 = cursor;
        buf = func_800B12F4();
        sub->field28 = buf;
        if (buf != NULL) {
            if (icon_held != 0) {
                count = 1;
                cursor = (u8 *)obj + 0x5C;
                call_arg = buf;
                *(void **)((u8 *)obj + 0x70) = call_arg;
                buf = func_800B1434(call_arg, D_80073618[icon_held]);
                index = count;
                *(u32 *)((u8 *)obj + 0x58) = 0x808080;
                goto shared_setup;
            }
            index = 0;
shared_setup:
            call_arg = buf;
            base_2 = (u8 *)D_800DF03C;
            table_entry = (s32 *)((style_byte * 4) + (s32)base_2);
            hard_zero = 0;
            *(void **)((u8 *)sub + 0x50 + count * 4) = (void *)func_8004E298(call_arg, *table_entry, hard_zero);
            style_hold = func_80069E98(*table_entry) * 8;
            count++;
            tmp = index << 2;
            tmp += index;
            tmp2 = tmp << 1;
            offset_x = tmp2 + 0x80;
            if (((u16)compact << 0x10) != 0) {
                tmp = tmp2 + 0x76;
                tmp -= style_hold;
                offset_x = (s16)tmp;
            }
            func_800B1320(buf, offset_x, (s16)((0 - (s8)((u8 *)buf)[3]) - 9));
            gap = 8;
            if (compact != 0) {
                gap = 4;
            }
            func_800B135C(buf, gap);
            func_800B13CC(buf, 0x20);
            func_800B1400(buf, 2);
            color1 = 0x808080;
            *(volatile u32 *)cursor = color1;
            cursor += 4;
            do {
                buf = (u8 *)buf + 0x60;
            } while (0);
            *(void **)((u8 *)sub + 0x50 + count++ * 4) = buf;
            call_arg = buf;
            prev_arg = (u8 *)buf - 0x60;
            new_buf = func_800B1434(call_arg, prev_arg);
            call_arg = buf;
            buf = new_buf;
            func_800B1320(call_arg, 1, 1);
            color2 = 0x80808;
            tmp = count << 2;
            count++;
            base_offset = -0xA;
            tmp += (s32)sub;
            *(volatile u32 *)cursor = color2;
            *(void **)((u8 *)tmp + 0x50) = buf;
            ((u8 *)buf)[1] = 0x38;
            if (index == 0) {
                base_offset = -2;
            }
            y_offset = base_offset;
            if (compact != 0) {
                y_offset -= 2;
            }
            tmp = index << 1;
            tmp += index;
            tmp <<= 3;
            slot_x = style_hold + tmp;
            ((s8 *)buf)[2] = y_offset;
            ((s8 *)buf)[3] = -0xE;
            ((s8 *)buf)[9] = 0;
            ((s8 *)buf)[8] = 0;
            if (index == 0) {
                slot_x += 4;
            }
            slot_y = slot_x;
            if (compact != 0) {
                slot_y -= 2;
                color2 = 0x80000;
            } else {
                color2 = 0x80000;
            }
            ((s8 *)buf)[0xA] = slot_y;
            slot_y = 0x10;
            slot_x = 0xC0;
            ((s8 *)buf)[0xB] = slot_y;
            ((u8 *)buf)[0] = slot_x;
            sub->field10 = 0;
            sub->field14 = 0;
            color2 |= 0x4008;
            sub->field18 = color2;
            sub->field1C = color2;
            *(s32 *)((u8 *)buf + 4) = sub->field10;
            *(s32 *)((u8 *)buf + 0xC) = sub->field14;
            *(s32 *)((u8 *)buf + 0x10) = sub->field18;
            tail_flags = ((u8 *)buf)[1];
            tail_field1c = sub->field1C;
            tail_flags |= 2;
            ((u8 *)buf)[1] = tail_flags;
            *(s32 *)((u8 *)buf + 0x14) = tail_field1c;
            buf = (u8 *)buf + 0x18;
            *(void **)((u8 *)sub + 0x50 + count * 4) = buf;
            ((u8 *)buf)[1] = 0x81;
            *(s16 *)((u8 *)buf + 4) = 0x20;
            *(s16 *)((u8 *)buf + 6) = 0;
            ((u8 *)buf)[0] = slot_x;
        }
        sub->field22 = 4;
        sub->field26 = unused_flags;
    }
}
