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
M2C_UNK func_80026D84() __attribute__((noreturn));
TempObj *func_8003FC64();
M2C_UNK func_8004491C();
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
    register s32 row_or_bottom_y ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 bottom_heights_addr ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 row_offset ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 y_offset;
    s32 column;
    register s32 x_offset ASM_REG("$10");   /* MATCH pin: load-bearing for the whole function shape */
    s32 x_or_height;
    register s32 y_or_color ASM_REG("$4");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 height ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 height_bl ASM_REG("$13");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 height_br ASM_REG("$14");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 origin_height ASM_REG("$15");   /* MATCH pin: load-bearing for the whole function shape */
    u16 saved_row;
    register s32 texture_value ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register TempObj *init_object ASM_REG("$4");   /* MATCH pin: retail immediate-load split depends on it */
    register void *object_handler ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s8 *height_row;
    register void *output ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    register s16 *top_heights ASM_REG("$11");   /* MATCH pin: load-bearing for the whole function shape */
    s32 height_or_child;
    TempObj *object;

    object = func_8003FC64(0x202);
    if (object != NULL) {
        saved_row = tile_y;
        ASM_KEEP(saved_row);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        row_offset = tile_y;
        init_object = object;
        object_handler = &D_800264D4;
        object->field10 = object_handler;
        func_8004491C(init_object, &D_800269CC);
        column = (s16) tile_x;
        x_offset = (column - 3) << 6;
        ASM_KEEP(x_offset);   /* MATCH pin: retail schedule: same instructions, different order without it */
        row_or_bottom_y = (s16) row_offset;
        height_row = D_8002745C;
        row_offset = row_or_bottom_y * 0x10;
        top_heights = (s16 *)(row_offset + (s32)height_row);
        bottom_heights_addr = column * 2;
        top_heights = (s16 *)(bottom_heights_addr + (s32)top_heights);
        height_row += 0x10;
        height_row = (s8 *)(row_offset + (s32)height_row);
        bottom_heights_addr += (s32)height_row;
        y_offset = (row_or_bottom_y - 3) << 6;
        output = object->field8;
        x_or_height = ((s16 *)origin)[1];
        y_or_color = ((s16 *)origin)[3];
        height = top_heights[0];
        height_or_child = top_heights[1];
        height_bl = ((s16 *)bottom_heights_addr)[0];
        height_br = ((s16 *)bottom_heights_addr)[1];
        origin_height = ((s16 *)origin)[5];
        x_or_height += x_offset;
        y_or_color += y_offset;
        height += height_or_child;
        height += height_bl;
        height += height_br;
        height >>= 2;
        height += origin_height;
        ((TempBuffer *)output)->fieldA = height;
        ((TempBuffer *)output)->field2 = x_or_height;
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
        row_or_bottom_y = (row_or_bottom_y - 2) << 6;
        bottom_y = ((u16) origin->unk_06 + row_or_bottom_y) - 0x20;
        ((TempOutput *)output)->field2A = bottom_y;
        ((TempOutput *)output)->field22 = bottom_y;
        ((TempOutput *)output)->field14 = (s16) ((u16) origin->unk_0A + (u16) top_heights[0]);
        ((TempOutput *)output)->field1C = (s16) ((u16) origin->unk_0A + (u16) top_heights[1]);
        row_offset -= 0x80;
        height = (u16) origin->unk_0A;
        x_or_height = (u16) ((s16 *)bottom_heights_addr)[0];
        height += x_or_height;
        ((TempOutput *)output)->field24 = height;
        height = (u16) origin->unk_0A;
        x_or_height = (u16) ((s16 *)bottom_heights_addr)[1];
        height += x_or_height;
        ((TempOutput *)output)->field2C = height;
        y_or_color = 0xF8F82CC0;
        texture_value = 0x13D;
        object->field20 = y_or_color;
        ((TempOutput *)output)->field4 = texture_value;
        texture_value = column * 0x10;
        ((TempOutput *)output)->field8 = (s8) texture_value;
        texture_value = 6;
        ((TempOutput *)output)->field9 = (s8) row_offset;
        if (column == texture_value) {
            texture_value = 0xF;
            ASM_TAILSLOT_PIN(texture_value);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80026D84(y_or_color, row_or_bottom_y, output, bottom_heights_addr);
            return;
        }
        ((TempOutput *)output)->fieldA = 0x10;
        texture_value = (s16) saved_row;
        x_or_height = 6;
        if (texture_value == x_or_height) {
            texture_value = 0xF;
        } else {
            texture_value = 0x10;
        }
        ((TempOutput *)output)->fieldB = texture_value;
        ((TempChild *)height_or_child)->field8 = output;
        ((TempOutput *)output)->field4C = 8;
        (*(s16 *)D_800273BC) = (s16) ((*(u16 *)D_800273BC) + 1);
    }
}
