#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"

extern u8 D_80027374[12];
typedef struct TextureConfig {
    u8 pad0[4];
    u16 word4;
    u16 word6;
    u8 byte8;
    u8 byte9;
    u8 byteA;
    u8 byteB;
} TextureConfig;

static __inline__ u16 translate_x(s32 x, u16 offset) { x -= 0xA0; return offset + x; }

/* Builds and submits a shaded textured quad at the requested screen position. */
void dungeonBuildShadedTexturedQuad(s32 y_offset, Input *origin, Input *quad_data, s32 draw_depth) {
    Root *root = gameWork.unk_000;
    Record *record;
    Record *quad_packet;
    Input *quad_input = quad_data;
    GameWork *globals;
    TableEntry *vertex_table;
    Bank56_8196096C_Scratch *scratch;
    register void *rotation;
    register void *matrix;
    s32 saved_y_offset = y_offset;
    TextureConfig *texture_config;
    u16 texture_word;
    s32 corner_uv;
    s32 neutral_color;
    s32 shade;

    record = root->record;
    globals = &gameWork;
    scratch = (Bank56_8196096C_Scratch *)0x1F800000;
    scratch->value = draw_depth;
    vertex_table = ((struct TableEntry *)globals->map.unk_08);
    func_800649A0();
    rotation = (void *)0x1F800028;
    matrix = (void *)0x1F800050;
    scratch->w6C = 0;
    scratch->w68 = 0;
    scratch->w64 = 0;
    scratch->h2C = 0;
    scratch->h2A = 0;
    scratch->h28 = 0;
    func_80065820(rotation, matrix);
    func_80064D80(&scratch->w50);
    func_80064CF0(&scratch->w50);
    scratch->h8C = 0x800;
    scratch->h84 = 0x800;
    scratch->h7C = 0x800;
    scratch->h74 = 0x800;
    if (quad_input != 0) {
        scratch->w70 = vertex_table[quad_input->index0].value;
        scratch->w78 = vertex_table[quad_input->index1].value;
        scratch->w80 = vertex_table[quad_input->index2].value;
        scratch->w88 = vertex_table[quad_input->index3].value;
        record->fC.w = quad_input->value8;
        record->f14.w = quad_input->valueC;
        record->f1C.h[0] = quad_input->value12;
        neutral_color = 0x808080;
        corner_uv = quad_input->value14;
        quad_packet = record;
        record->f4.w = neutral_color;
        record->f24.h[0] = corner_uv;
        func_800666F4(record);
    } else {
        scratch->w78 = 0x40;
        scratch->w70 = 0;
        scratch->w80 = 0x400000;
        scratch->w88 = 0x400040;
        texture_config = (TextureConfig *)D_80027374;
        texture_word = texture_config->word4;
        record->f14.h[1] = texture_word;
        texture_word = texture_config->word6;
        record->fC.h[1] = texture_word;
        record->f1C.b[0] = texture_config->byte8;
        record->fC.b[0] = record->f1C.b[0];
        record->f24.b[0] = texture_config->byte8 + texture_config->byteA;
        record->f14.b[0] = record->f24.b[0];
        record->f14.b[1] = texture_config->byte9;
        record->fC.b[1] = record->f14.b[1];
        record->f24.b[1] = texture_config->byte9 + texture_config->byteB;
        record->f1C.b[1] = record->f24.b[1];
        shade = ((u8)D_800273A8 << 7) / 240;
        *(u8 *)&record->f4.b[0] = shade;
        *(u8 *)&record->f4.b[2] = shade;
        *(u8 *)&record->f4.b[1] = shade;
        func_800666F4(record);
    }
    func_800654B0((void *)((u32)scratch | 0x70),
                  (void *)((u32)scratch | 0x78),
                  (void *)((u32)scratch | 0x80),
                  (void *)((u32)scratch | 0x88),
                  &record->f8.h[0], &record->f10.h[0],
                  &record->f18.h[0], &record->f20.h[0],
                  &scratch->w90, &scratch->w94);

    record->f8.h[0] = translate_x(record->f8.h[0], origin->index0);
    record->f18.h[0] = translate_x(record->f18.h[0], origin->index0);
    record->f10.h[0] = translate_x(record->f10.h[0], origin->index0);
    record->f20.h[0] = translate_x(record->f20.h[0], origin->index0);
    {
        s32 coord_y;
        coord_y = record->f8.h[1] - 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f8.h[1] = coord_y;
        coord_y = record->f10.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f10.h[1] = coord_y;
        coord_y = record->f18.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f18.h[1] = coord_y;
        coord_y = record->f20.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f20.h[1] = coord_y;
    }
    func_8006658C(scratch->value, record);
    func_80064A40();
    record = (Record *)((u8 *)record + 0x28);
    ((Root *)globals->unk_000)->record = record;
}
