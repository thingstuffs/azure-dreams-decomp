#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/dir_step.h"


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


extern u8 D_800274C0[];
extern u8 D_80027580[];

extern s32 func_8003FA44(s32);

static __inline__ s16 dir_step(s16 *table, u16 offset) {
    return *(s16 *)(offset + (u32)table);
}

/* Creates twelve linked sprite pieces at an offset from the given position and angle. */
void *func_800255B8(s16 x, s16 y, s16 z, s16 heading) {
    void *objects[12];
    s32 piece_index;
    s16 *x_offsets;
    TileObject *color_table;
    u8 *effect_state;
    u8 *link_data;
    u8 *component_data;
    u8 color_first;
    u32 color_second;
    u32 offset_addr;
    s32 x_offset;
    s32 y_offset;
    u16 sprite_flags;

    if (func_8003FA44(12) == 0) {
        return 0;
    }

    piece_index = 0;
    x_offsets = dirStepX;
    color_table = &D_80082E80;
    do {
        {
            void *template;

            if (piece_index != 0) {
                template = objects[0];
            } else {
                template = ((u8 *)(&D_80083498));
            }
            objects[piece_index] = func_8003FD64(2, template);
        }
        ((S_800255B8_0 *)objects[piece_index])->unk_10 = func_8002501C;
        func_8004491C(objects[piece_index], func_800C9034);

        offset_addr = (heading >> 8) & 0xE;
        component_data = ((S_800255B8_0 *)objects[piece_index])->unk_08;
        x_offset = dir_step(x_offsets, offset_addr) << 5;
        ((S_800255B8_1 *)component_data)->unk_02 = x + x_offset;
        y_offset = dir_step(dirStepY, offset_addr) << 5;
        ((S_800255B8_1 *)component_data)->unk_0A = z;
        ((S_800255B8_1 *)component_data)->unk_06 = y + y_offset;

        effect_state = ((S_800255B8_0 *)objects[piece_index])->unk_0C;
        ((S_800255B8_2 *)effect_state)->unk_20 = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_1E = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_1C = 0x1000;
        ((S_800255B8_2 *)effect_state)->unk_08 = D_800274C0 + (piece_index << 4);
        sprite_flags = ((S_800255B8_2 *)effect_state)->unk_14;
        ((S_800255B8_2 *)effect_state)->unk_10 = 0x20;
        ((S_800255B8_2 *)effect_state)->unk_16 = 0x400;
        ((S_800255B8_2 *)effect_state)->unk_1A = heading - 0x400;
        ((S_800255B8_2 *)effect_state)->unk_14 = sprite_flags | 0xC;

        effect_state = (u8 *)objects[piece_index] + 0x20;
        if (piece_index != 0) {
            u32 link_value;

            link_data = D_80027580 + piece_index;
            link_value = *link_data;
            if (link_value != 0) {
                link_data = (u8 *)0x7FFFFFFF;
                link_value = (u32)objects[link_value - 1] & (u32)link_data;
            } else {
                link_value = (u32)objects[piece_index - 1];
            }
            ((S_800255B8_3 *)effect_state)->unk_20 = (void *)link_value;
        }

        ((S_800255B8_3 *)effect_state)->unk_30 = 4;
        ((S_800255B8_3 *)effect_state)->unk_36 = 15;
        ((S_800255B8_3 *)effect_state)->unk_32 = 1;
        ((S_800255B8_3 *)effect_state)->unk_34 = heading;
        ((S_800255B8_3 *)effect_state)->unk_48 = piece_index;
        ((S_800255B8_3 *)effect_state)->unk_46 = 8;
        color_first = color_table->tileX;
        ((S_800255B8_3 *)effect_state)->unk_3C = color_first;
        ((S_800255B8_3 *)effect_state)->unk_40 = color_first;
        color_second = color_table->tileY;
        ((S_800255B8_3 *)effect_state)->unk_3E = color_second;
        ((S_800255B8_3 *)effect_state)->unk_42 = color_second;
        piece_index++;
    } while (piece_index < 12);

    return objects[0];
}

