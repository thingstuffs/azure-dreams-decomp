#include "common.h"


typedef struct Obj Obj;

typedef struct S_800255B8_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_800255B8_0;   /* *cur in func_800255B8 */

typedef struct S_800255B8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800255B8_1;   /* partA in func_800255B8 */

typedef struct S_800255B8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800255B8_2;   /* partB in func_800255B8 */

typedef struct S_800255B8_3 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0xC];
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[0x4];
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    u8 pad_44[0x2];
    s16 unk_46;
    s16 unk_48;
} S_800255B8_3;   /* tail in func_800255B8 */


extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u8 D_80082E80[];
extern u8 D_80083498[];
extern u8 D_8002501C[];
extern u8 D_800274C0[];
extern u8 D_80027580[];
extern u8 D_800C9034[];

extern s32 func_8003FA44(s32);
extern Obj *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

/* Creates twelve linked sprite pieces at an offset from the given position and angle. */
void *func_800255B8(s32 x, s32 y, s16 z, u16 angle) {
    void *objects[12];
    register s32 origin_x ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 origin_y ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 origin_z ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 heading;
    s32 piece_index;
    void **object_base;
    register void **object_slot ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 *x_offsets;
    register u8 *color_table;
    u8 *effect_state;
    register u8 *component_data ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *sprite;
    u8 color_first;
    u32 color_second;
    u32 offset_addr;
    s32 x_offset;
    s32 y_offset;
    u16 sprite_flags;

    origin_x = x;
    origin_y = y;
    origin_z = z;
    heading = angle;
    ASM_KEEP4_NV(origin_x, origin_y, origin_z, heading);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    if (func_8003FA44(12) == 0) {
        return 0;
    }

    piece_index = 0;
#ifdef NON_MATCHING
    x_offsets = D_8006CCD8;
    color_table = D_80082E80;
#else
    {
        u8 *page_base;

        page_base = (u8 *)0x80070000;
        ASM_KEEP_NV(page_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        x_offsets = (s16 *)(page_base - 0x3328);
        page_base = (u8 *)0x80080000;
        ASM_KEEP_NV(page_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        color_table = page_base + 0x2E80;
    }
#endif
    object_base = objects;
    object_slot = object_base;

loop:
        {
            void *template;
            u8 *template_page;

            if (piece_index != 0) {
                template = objects[0];
            } else {
#ifdef NON_MATCHING
                template = D_80083498;
#else
                template_page = (u8 *)0x80080000;
                ASM_KEEP_NV(template_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                template = template_page + 0x3498;
#endif
            }
            *object_slot = func_8003FD64(2, template);
        }

        {
            u8 *resource_page;

            component_data = D_8002501C;
#ifdef NON_MATCHING
            resource_page = D_800C9034 + 0x6FCC;
#else
            resource_page = (u8 *)0x800D0000;
#endif
            ASM_KEEP_NV(resource_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ((S_800255B8_0 *)(*object_slot))->unk_10 = component_data;
            func_8004491C(*object_slot, resource_page - 0x6FCC);
        }

        offset_addr = (heading >> 8) & 0xE;
        component_data = ((S_800255B8_0 *)(*object_slot))->unk_08;
        x_offset = x_offsets[offset_addr / 2] << 5;
        ((S_800255B8_1 *)component_data)->unk_02 = origin_x + x_offset;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        {
            s16 *y_offsets;

#ifdef NON_MATCHING
            y_offsets = D_8006CCE8;
#else
            y_offsets = (s16 *)0x80070000;
            ASM_KEEP_NV(y_offsets);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            y_offsets = (s16 *)((u8 *)y_offsets - 0x3318);
#endif
            offset_addr = offset_addr + (u32)y_offsets;
            y_offset = *(s16 *)offset_addr << 5;
        }
        ((S_800255B8_1 *)component_data)->unk_0A = origin_z;
        ((S_800255B8_1 *)component_data)->unk_06 = origin_y + y_offset;

        component_data = (u8 *)(piece_index << 4);
        sprite = ((S_800255B8_0 *)(*object_slot))->unk_0C;
        ((S_800255B8_2 *)sprite)->unk_20 = 0x1000;
        ((S_800255B8_2 *)sprite)->unk_1E = 0x1000;
        ((S_800255B8_2 *)sprite)->unk_1C = 0x1000;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        {
            u8 *sprite_table;

#ifdef NON_MATCHING
            sprite_table = D_800274C0;
#else
            sprite_table = (u8 *)0x80020000;
            ASM_KEEP_NV(sprite_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            sprite_table += 0x74C0;
#endif
            component_data = (u8 *)((u32)component_data + (u32)sprite_table);
            ((S_800255B8_2 *)sprite)->unk_08 = component_data;
        }
        sprite_flags = ((S_800255B8_2 *)sprite)->unk_14;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ((S_800255B8_2 *)sprite)->unk_10 = 0x20;
        ((S_800255B8_2 *)sprite)->unk_16 = 0x400;
        ((S_800255B8_2 *)sprite)->unk_1A = heading - 0x400;
        ((S_800255B8_2 *)sprite)->unk_14 = sprite_flags | 0xC;

        {
            void *object;

            object = *object_slot;
            effect_state = (u8 *)object + 0x20;
        }
        if (piece_index != 0) {
            register u32 link_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            register u8 *link_entry ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            link_value = (u32)D_80027580;
            link_entry = (u8 *)(piece_index + link_value);
            ASM_KEEP_NV(link_entry);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            link_value = *link_entry;
            ASM_KEEP_NV(link_value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (link_value != 0) {
                link_value = (u32)object_base[link_value - 1] & 0x7FFFFFFF;
            } else {
                link_value = (u32)object_slot[-1];
            }
            ((S_800255B8_3 *)effect_state)->unk_20 = (void *)link_value;
        }

        ((S_800255B8_3 *)effect_state)->unk_30 = 4;
        ((S_800255B8_3 *)effect_state)->unk_36 = 15;
        ((S_800255B8_3 *)effect_state)->unk_32 = 1;
        ((S_800255B8_3 *)effect_state)->unk_34 = heading;
        ((S_800255B8_3 *)effect_state)->unk_48 = piece_index;
        ((S_800255B8_3 *)effect_state)->unk_46 = 8;
        color_first = color_table[0x24];
        ((S_800255B8_3 *)effect_state)->unk_3C = color_first;
        ((S_800255B8_3 *)effect_state)->unk_40 = color_first;
        color_second = color_table[0x25];
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        piece_index++;
        ((S_800255B8_3 *)effect_state)->unk_42 = color_second;
        ((S_800255B8_3 *)effect_state)->unk_3E = color_second;
        object_slot++;
        if (piece_index < 12) {
            goto loop;
        }

    return objects[0];
}
