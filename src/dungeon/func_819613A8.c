#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad0[8];
    void *field8;
    void *fieldC;
    void *field10;
    u8 pad14[0xC];
    u32 field20;
} TempObj;

typedef struct {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[2];
    s16 fieldA;
} TempBuffer;

typedef struct {
    u8 pad0[8];
    void *field8;
    u8 padC[8];
    s16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} TempChild;

typedef struct {
    u8 pad0[4];
    s16 field4;
    u8 pad6[2];
    s8 field8;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    u8 padC[4];
    s16 field10;
    s16 field12;
    s16 field14;
    u8 pad16[2];
    s16 field18;
    s16 field1A;
    s16 field1C;
    u8 pad1E[2];
    s16 field20;
    s16 field22;
    s16 field24;
    u8 pad26[2];
    s16 field28;
    s16 field2A;
    s16 field2C;
    u8 pad2E[0x1E];
    s16 field4C;
} TempOutput;

extern s8 D_8002745C[];
TempObj *func_8003FC64();
s32 func_8004491C();
extern M2C_UNK D_800264D4;
extern M2C_UNK D_800269CC;
extern s16 D_800273BC[5];

typedef struct S_819613A8_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_819613A8_0;   /* arg2 in func_819613A8 */

/* Creates a terrain tile quad using grid heights and the supplied origin. */
void func_819613A8(s16 tile_x, s32 tile_y, S_819613A8_0 *origin) {
    s16 left_x;
    s16 right_x;
    s16 top_y;
    s16 bottom_y;
    s32 row;
    s32 bottom_offset;
    s32 bottom_heights_addr;
    s32 y_offset;
    s32 column;
    s32 x_offset;
    s32 x_or_height;
    register s32 y_or_color ASM_REG("$4");
    s32 height;
    s32 height_tr;
    s32 height_bl;
    s32 height_br;
    s32 origin_height;
    s16 saved_row;
    s8 *height_row;
    register void *output ASM_REG("$6");
    s16 *top_heights;
    s16 *top_row;
    s32 height_or_child;
    TempObj *object;

    object = func_8003FC64(0x202);
    saved_row = tile_y;
    if (object != NULL) {
        s32 local_x_or_height;
        s32 local_height;
        y_or_color = (s32)(object);
        height_row = &D_800264D4;
        object->field10 = height_row;
        func_8004491C((TempObj *)y_or_color, &D_800269CC);
        column = (s16) tile_x;
        x_offset = (column - 3);
        x_offset <<= 6;
        row = (u32) tile_y << 16;
        row >>= 16;
        height_row = D_8002745C;
        tile_y = row;
        tile_y <<= 4;
        top_heights = (s16 *)(tile_y + (s32)height_row);
        top_row = top_heights;
        bottom_heights_addr = column << 1;
        top_heights = (s16 *)(bottom_heights_addr + (s32)top_row);
        height_row += 0x10;
        height_row = (s8 *)(tile_y + (s32)height_row);
        bottom_heights_addr += (s32)height_row;
        y_offset = (row - 3) << 6;
        output = object->field8;
        local_x_or_height = ((s16 *)origin)[1];
        y_or_color = ((s16 *)origin)[3];
        local_height = top_heights[0];
        height_tr = (u16)top_heights[1];
        height_tr = (u32)height_tr << 16;
        height_tr >>= 16;
        height_bl = (u16) ((s16 *)bottom_heights_addr)[0];
        height_bl = (u32)height_bl << 16;
        height_bl >>= 16;
        height_br = (u16)((s16 *)bottom_heights_addr)[1];
        height_br = (u32)height_br << 16;
        height_br >>= 16;
        origin_height = (u16)((s16 *)origin)[5];
        origin_height = (u32)origin_height << 16;
        origin_height >>= 16;
        local_x_or_height += x_offset;
        y_or_color += y_offset;
        local_height += height_tr;
        local_height += height_bl;
        local_height += height_br;
        local_height >>= 2;
        local_height += origin_height;
        ((TempBuffer *)output)->fieldA = local_height;
        ((TempBuffer *)output)->field2 = local_x_or_height;
        ((TempBuffer *)output)->field6 = y_or_color;
        height_or_child = (s32)object->fieldC;
        output = (void *)&object->field20;
        ((TempChild *)height_or_child)->field1E = 0x800;
        ((TempChild *)height_or_child)->field1C = 0x800;
        ((TempChild *)height_or_child)->field14 = 0xC;
        left_x = ((u16) origin->unk_02 + x_offset) - 0x20;
        ((TempOutput *)output)->field20 = left_x;
        ((TempOutput *)output)->field10 = left_x;
        right_x = ((u16) origin->unk_02 + ((column - 2) << 6)) - 0x20;
        ((TempOutput *)output)->field28 = right_x;
        ((TempOutput *)output)->field18 = right_x;
        top_y = ((u16) origin->unk_06 + y_offset) - 0x20;
        ((TempOutput *)output)->field1A = top_y;
        ((TempOutput *)output)->field12 = top_y;
        bottom_offset = (row - 2) << 6;
        bottom_y = ((u16) origin->unk_06 + bottom_offset) - 0x20;
        ((TempOutput *)output)->field2A = bottom_y;
        ((TempOutput *)output)->field22 = bottom_y;
        ((TempOutput *)output)->field14 = (s16) ((u16) origin->unk_0A + (u16) top_heights[0]);
        ((TempOutput *)output)->field1C = (s16) ((u16) origin->unk_0A + (u16) top_heights[1]);
        tile_y -= 0x80;
        height = (u16) origin->unk_0A;
        x_or_height = (u16) ((s16 *)bottom_heights_addr)[0];
        height += x_or_height;
        ((TempOutput *)output)->field24 = height;
        height = (u16) origin->unk_0A;
        x_or_height = (u16) ((s16 *)bottom_heights_addr)[1];
        height += x_or_height;
        ((TempOutput *)output)->field2C = height;
        y_or_color = 0xF8F82CC0;
        height = 0x13D;
        object->field20 = y_or_color;
        ((TempOutput *)output)->field4 = height;
        height = column * 0x10;
        ((TempOutput *)output)->field8 = (s8) height;
        height = 6;
        ((TempOutput *)output)->field9 = (s8) tile_y;
        if (column == height) {
            height = 0xF;
        } else {
            height = 0x10;
        }
        height_bl = (s8)height;
        ((TempOutput *)output)->fieldA = height_bl;
        height = saved_row;
        x_or_height = 6;
        if (height == x_or_height) {
            height = 0xF;
        } else {
            height = 0x10;
        }
        height_tr = height;
        height_tr = (u32)height_tr << 24;
        height_tr >>= 24;
        ((TempOutput *)output)->fieldB = height_tr;
        ((TempChild *)height_or_child)->field8 = output;
        ((TempOutput *)output)->field4C = 8;
        (*(s16 *)D_800273BC) = (s16) ((*(u16 *)D_800273BC) + 1);
    }
}
