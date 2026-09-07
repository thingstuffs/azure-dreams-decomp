#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8002453C(void *, void *);
extern void func_80025AD8(s16, s16);
extern void func_80025C8C(void);
extern void func_80026064(s16 *, s32);
extern void func_800A56E0(s32);
extern void func_800B835C(void *, s16 *, s32, s32);

extern s32 D_80027328;
extern void *D_8002732C;
extern s16 D_80027330;
extern u8 D_80027374[];
extern u8 D_80027398[];
extern s32 D_800273A8;
extern s16 D_800273BC;
extern u8 D_800273BE;
extern void *D_800273C0;
extern s32 D_800274DC[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u8 D_80083160[];
typedef struct {
    u8 pad[0xA];
    u16 field_a;
    s32 field_c;
} D83460;
extern D83460 D_80083460;
extern u8 *D_800E3D7C;
extern void *D_80024008[];

void func_8002401C(void *arg0)
{
    u8 *obj = arg0;
    u8 *palette = D_80083160;
    u8 *source;
    s32 *row;
    s32 *clear_row;
    s32 *clear_cell;
    s32 *cell;
    s16 rect[4];
    register s32 outer ASM_REG("$20");
    register s32 inner ASM_REG("$16");
    s32 x;
    s32 y;
    s32 cell_value;
    register s32 unit ASM_REG("$22");
    s32 index;
    u16 *map_data;
    register s16 *rect_arg ASM_REG("$4");
    u8 obj_byte9;
    void *created;
    void *display;
    register void *obj0 ASM_REG("$4");
    register s32 obj_scratch ASM_REG("$8");
    s32 state;
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4
    };

    (void)jt_keep;

    state = FIELD(obj, s16, 0xA);
    if ((u32)state >= 5) {
        goto dispatch_done;
    }
    goto *D_80024008[(u32)state];

jt_c0:
        outer = 0;
        D_800273BC = 1;
        obj_byte9 = FIELD(obj, u8, 9);
        D_80027328 = 0;
        ASM_SCHED_BARRIER();
        ASM_KEEP_MEM_NV(obj_byte9, D_800273BE);
        obj0 = FIELD(obj, void *, 0);
        ASM_SCHED_BARRIER();
        ASM_KEEP_MEMDEP(obj_byte9, obj_scratch, D_800814A8);
        D_800273BE = obj_byte9;
        D_800273C0 = FIELD(obj, void *, 0);
        D_8002732C = obj0;

        FIELD(D_800814A8, s32, 0xF4) = 0;
        FIELD(D_800814A8, u8, 0x102) = 1;
        FIELD(D_800814A8, u8, 0xA8) = FIELD(obj, u8, 8);

        clear_row = D_800274DC;
jt_zero_outer:
        inner = 6;
        clear_cell = clear_row + 6;
jt_zero_inner:
        *clear_cell = 0;
        clear_cell--;
        inner--;
        if (inner >= 0) {
            goto jt_zero_inner;
        }
        outer++;
        if (outer < 7) {
            clear_row += 8;
            goto jt_zero_outer;
        }

        D_800273A8 = 0;
        ASM_MEM_BARRIER();
        map_data = (u16 *)D_800E3D7C;
        index = (map_data[0x15] >> 8) & 0xE;
        func_80025AD8(
            (s16)(D_80082E80[0x24] +
                  (*(s16 *)((u8 *)D_8006CCD8 + index) * 4)),
            (s16)(D_80082E80[0x25] +
                  (*(s16 *)((u8 *)D_8006CCE8 + index) * 4)));
        FIELD(obj, u16, 0xA)++;
        /* fallthrough */

jt_c1:
        if ((FIELD(FIELD(obj, u8 *, 4), u16, 0) & 0x80) != 0) {
            source = FIELD(obj, u8 *, 0);
            created = func_8002453C(FIELD(source, void *, -0x18), source);
            FIELD(obj, void *, 0xC) = created;
            if (created != 0) {
                display = D_800814A8;
                FIELD(obj, s16, 0x1C) = 0x10;
                FIELD(display, u16, 0xA6)--;
                FIELD(obj, u16, 0xA)++;
            }
        }
        goto dispatch_done;

jt_c2:
        FIELD(obj, u16, 0x1C)--;
        if (FIELD(obj, s16, 0x1C) < 0) {
            func_800A56E0(0x300);
            FIELD(obj, u16, 0xA)++;
            /* fallthrough */

jt_c3:
            if (D_800273BC == 0) {
                func_80025C8C();
                FIELD(obj, u16, 0xA)++;
            }
        }
        goto dispatch_done;

jt_c4:
        if (D_80027330 == 0) {
            D_80083460.field_c = 0;
            D_80083460.field_a--;
            FIELD(obj, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        goto dispatch_done;

dispatch_done:

    rect[0] = 0x340;
    rect[1] = 0x180;
    rect[2] = 0x70;
    rect[3] = 0x70;
    func_800B835C(D_80027398, rect, 0, 2);

    for (outer = 0, unit = 0x10, row = D_800274DC, y = 0x180;
         outer < 7; outer++) {
        for (inner = 0, cell = row, x = 0x340; inner < 7;) {
            rect_arg = rect;
            ASM_KEEP(rect_arg);
            rect[0] = x;
            rect[1] = y;
            rect[2] = unit;
            rect[3] = unit;
            cell_value = *cell++;
            x += 0x10;
            ASM_SCHED_BARRIER();
            func_80026064(rect_arg, cell_value);
            inner++;
        }
        row += 8;
        y += 0x10;
    }

    D_80027330 = 0;
    D_80027374[8] = (palette[4] & 0x1F) + 0x80;
    D_80027374[9] = palette[4] & 0x1F;
}
