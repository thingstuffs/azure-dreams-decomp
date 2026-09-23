#include "common.h"
extern u8 D_80083498[];
extern u8 D_80030000[];


typedef unsigned long uptr;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

typedef struct {
    u8 bytes[8];
} __attribute__((packed)) Copy8;

typedef struct {
    Copy12 first;
    Copy12 second;
    Copy8 third;
} __attribute__((packed)) Copy32;

typedef struct {
    u8 pad0[8];
    void *part8;
    void *partC;
    void *part10;
} Object;

extern Object *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

extern Copy32 D_80024028[];
extern u8 D_80025800[];
extern void *D_80028630;
extern u8 D_80028664[];
extern s32 D_800814A0;
extern u8 D_800C9034[];


typedef struct S_80025CE8_0 {
    s16 unk_00;
    u16 unk_02;
    u8 pad_04[0x1C];
    Object * unk_20;
    u8 pad_24[0xC];
    s16 unk_30;
    u8 pad_32[0x4];
    u16 unk_36;
    s16 unk_38;
    s16 unk_3A;
} S_80025CE8_0;   /* entry in func_80025CE8 */

typedef struct S_80025CE8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80025CE8_1;   /* part8 in func_80025CE8 */

typedef struct S_80025CE8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_80025CE8_2;   /* partC in func_80025CE8 */

typedef struct S_80025CE8_3_pre {
    void * unk_00;
    u8 pad_04[0x79CC];
} S_80025CE8_3_pre;   /* the 0x79D0 bytes before alloc_page in func_80025CE8, addressed as alloc_page[-1] */

typedef struct S_80025CE8_4 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80025CE8_4;   /* cleanup in func_80025CE8 */

/* Creates 21 linked objects at an angle-dependent offset, marking them for cleanup if allocation fails. */
s32 func_80025CE8(u16 x, u16 y, u16 z, u16 angle) {
    Object *objects[21];
    Copy32 direction_offsets;
    u8 *table_page;
    u32 object_index;
    Object **slot;
    Object *new_object;
    Object *cleanup_object;
    Object *current_object;
    S_80025CE8_1 *position;
    S_80025CE8_2 *render;
    s32 x_offset;
    u16 y_offset;
    u8 *data_entry;
    u8 *data_entry_2;
    register s32 previous_index ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 slot_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 asset_offset;
    u16 render_flags;
    u16 cleanup_flags;
    s32 color;
    Object *alloc_parent;
    u8 *alloc_page;

    *(Copy32 *)&direction_offsets = *(Copy32 *)&D_80024028;
    object_index = 0;
    do {
        if (((u32)(u16)object_index << 16) != 0) {
            alloc_page = (u8 *)0x80080000;
            alloc_parent = objects[0];
            goto call_alloc;
        }
        alloc_page = (u8 *)0x80080000;
        alloc_parent = (Object *)D_80083498;
    call_alloc:
        new_object = func_8003FD64(0x12, alloc_parent);
        slot_offset = ((s32)(s16)object_index) << 2;
        slot = (Object **)((uptr)slot_offset + (uptr)objects);
        *slot = new_object;
        if (new_object != 0) {
            color = 0x800000;
            new_object->part10 = D_80025800;
            color |= 0x8080;
            data_entry_2 = (u8 *)&direction_offsets + ((angle >> 7) & 0x1C);
            x_offset = ((S_80025CE8_0 *)data_entry_2)->unk_00;
            position = (*slot)->part8;
            position->unk_02 = x + (x_offset << 7);
            y_offset = ((S_80025CE8_0 *)data_entry_2)->unk_02;
            position->unk_0A = z - 0x90;
            position->unk_06 = y + (((s32)y_offset << 16) >> 9);

            render = (*slot)->partC;
            asset_offset = (s32)(s16)object_index * 0x10;
            render->unk_1A = angle - 0x400;
            render->unk_16 = 0x400;
            render->unk_20 = 0x1000;
            render->unk_1E = 0x1000;
            render->unk_1C = 0x1000;
            render->unk_08 = D_80028664 + asset_offset;
            render_flags = render->unk_14;
            render->unk_10 = 0x20;
            render->unk_0C = color;
            render_flags |= 0xC;
            render->unk_14 = render_flags;
#ifndef NON_MATCHING
            func_8004491C(*slot, (void *)D_800C9034);
#else
            func_8004491C(*slot, D_800C9034);
#endif

            current_object = *slot;
            data_entry = (u8 *)current_object + 0x20;
            if ((s16)object_index != 0) {
                ((S_80025CE8_0 *)data_entry)->unk_20 = objects[0];
                goto shared_tail;
            }
            alloc_page = (u8 *)D_80030000;
            ((S_80025CE8_3_pre *)alloc_page)[-1].unk_00 = position;
        shared_tail:
            render->unk_1E = 0;
            render->unk_1C = 0;
            render->unk_20 = 0;
            ((S_80025CE8_0 *)data_entry)->unk_30 = 0x3C;
            ((S_80025CE8_0 *)data_entry)->unk_36 = angle;
            ((S_80025CE8_0 *)data_entry)->unk_3A = 0;
            ((S_80025CE8_0 *)data_entry)->unk_38 = 0xF;
            goto continue_loop;
        }
        slot_offset = object_index - 1;
        object_index = slot_offset;
        if ((s32)((u32)slot_offset << 16) >= 0) {
            do {
                slot_offset = (s32)((u32)object_index << 16);
                previous_index = object_index - 1;
                object_index = previous_index;
                slot_offset >>= 14;
                alloc_page = (u8 *)((uptr)slot_offset + (uptr)objects);
                previous_index = (s32)((u32)previous_index << 16);
                cleanup_object = *(Object **)alloc_page;
                cleanup_flags = ((S_80025CE8_4 *)cleanup_object)->unk_1E;
                slot_offset = D_800814A0;
                slot_offset |= 0x8000;
                D_800814A0 = slot_offset;
                cleanup_flags |= 0x8000;
                ((S_80025CE8_4 *)cleanup_object)->unk_1E = cleanup_flags;
            } while (previous_index >= 0);
            return 0;
        } else {
            return 0;
        }
        continue_loop:
        slot_offset = object_index + 1;
        object_index = slot_offset;
    } while ((s16)slot_offset < 21);
    return (s32)objects[0];
}
