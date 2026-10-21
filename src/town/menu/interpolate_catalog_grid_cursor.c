/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80125800_1 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80125800_1;   /* obj in interpolate_catalog_grid_cursor */

typedef struct S_80125800_2 {
    u8 pad_00[0x184];
    void * unk_184;
} S_80125800_2;   /* ((S_80125800_1 *)obj)->unk_58 in interpolate_catalog_grid_cursor */

typedef struct S_80125800_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80125800_3;   /* ((S_80125800_2 *)(((S_80125800_1 *)obj)->unk_58))->unk_184 in interpolate_catalog_grid_cursor */




typedef struct SpriteFields {
    u32 pad0;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
} SpriteFields;

typedef struct DisplayPair {
    u32 pad0;
    SpriteFields *src;
    SpriteFields *dst;
} DisplayPair;

typedef struct TownSlots {
    void **slots[97];
    DisplayPair *display;
} TownSlots;

typedef struct TownObject {
    u8 pad0[4];
    s16 field4;
    s16 field6;
    u8 pad8[7];
    u8 digit;
    u8 row;
    u8 index;
    u8 column;
    u8 pad13[0x45];
    TownSlots *town;
} TownObject;

extern u8 is_catalog_entry_available(u8 value);
extern void *catalog_normal_digits[10];
extern s16 catalog_cursor_columns[8];
extern u8 catalog_number_marker[16];

typedef struct S_80125800_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x9];
    u8 unk_11;
    u8 unk_12;
} S_80125800_0;   /* obj in interpolate_catalog_grid_cursor */

/* Updates an available entry's number sprites and interpolates a display field. */
void interpolate_catalog_grid_cursor(TownObject *obj) {
    s32 row_offset;
    s32 slot_offset;
    s32 sprite_slot;
    s32 entry_id;

    row_offset = obj->row << 3;
    slot_offset = (row_offset + obj->column) * 3;
    sprite_slot = slot_offset + 33;
    entry_id = (obj->digit << 4) + row_offset + obj->column;
    if (is_catalog_entry_available((u8)entry_id) != 0) {
        s32 entry_number = entry_id + 1;

        *obj->town->slots[sprite_slot] = (void *)catalog_number_marker;
        sprite_slot = slot_offset + 34;
        *obj->town->slots[sprite_slot] = catalog_normal_digits[entry_number / 10];
        sprite_slot = slot_offset + 35;
        *obj->town->slots[sprite_slot] = catalog_normal_digits[entry_number % 10];
    }
    obj->town->display->src->fA =
        (s16) ((u16) catalog_cursor_columns[obj->column & 7]
        + (((s32) (catalog_cursor_columns[obj->index & 7]
        - catalog_cursor_columns[obj->column & 7]) / (s16) obj->field6) * obj->field4));
}
