#include "common.h"
#include "shared/menu_display.h"
#include "shared/object_payload.h"

typedef struct {
    s32 tint_color;
    s32 scale_xy;
    s32 pos_xy;
    s32 depth_and_mode;
} Template0;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 x;
    s16 y;
    s16 depth;
    u8 unkE;
    u8 mode;
} Record0;

typedef struct {
    s16 rot_x;
    s16 rot_y;
    s16 rot_z;
    s16 unk6;
    s32 offset_yz;
} Record1;

typedef struct {
    s32 unk0;
    Record0 *block;
    Record1 *vector;
} Header;

/* Initialize the header and its two records from default templates. */
void initialize_catalog_view_records(Header *header, Template0 *primary_record, Record1 *secondary_record) {
    MenuDisplayBlock *primary_defaults = &display_block_defaults;
    DisplayPositionWords *secondary_defaults = &display_vector_defaults;
    s32 *default_word;

    primary_record->tint_color = primary_defaults->words[0];
    default_word = &secondary_defaults->unk0;
    primary_record->scale_xy = primary_defaults->words[1];
    primary_record->pos_xy = primary_defaults->words[2];
    primary_record->depth_and_mode = primary_defaults->words[3];

    ((CatalogRecordDefaults *)secondary_record)->unk0 = *default_word;
    ((CatalogRecordDefaults *)secondary_record)->unk4 = secondary_defaults->unk4;
    secondary_record->offset_yz = secondary_defaults->unk8;

    header->block = (Record0 *)primary_record;
    header->vector = secondary_record;
    header->unk0 = 0;

    header->block->x = -0xA0;
    header->block->y = -0x78;
    header->block->depth = 0x200;
    header->block->mode = 8;
    header->vector->rot_x = 0;
    header->vector->rot_y = 0;
    header->vector->rot_z = 0;
}
