#include "common.h"
#include "shared/game_work.h"
#include "frontend/settings.h"
#include "sdk/libgpu.h"

typedef struct S_8008896C_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_8008896C_0;   /* line in queue_settings_sprite_grid */

typedef struct S_8008896C_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_8008896C_1;   /* scroll_data in queue_settings_sprite_grid */

typedef struct S_8008896C_2_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8008896C_2_pre;   /* the 0x8 bytes before entry_data in queue_settings_sprite_grid, addressed as entry_data[-1] */

typedef struct S_8008896C_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_8008896C_3;   /* next in queue_settings_sprite_grid */


typedef struct PacketTag {
    unsigned addr : 24;
    unsigned len : 8;
} PacketTag;

#define PTR32(address) ((u32)(unsigned long)(address))
#define setaddr(packet, address) (((PacketTag *)(packet))->addr = PTR32(address))
#define getaddr(packet) ((u32)(((PacketTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) \
(setaddr((primitive), getaddr(ordering_table)), \
    setaddr((ordering_table), (primitive)))

typedef struct RenderState {
    u8 pad0[0x82C];
    u32 ordering_table;
    u8 pad830[0xA0];
    u8 *next_prim;
} RenderState;

typedef struct MainState {
    RenderState *render_state;
} MainState;

/* Queue a 2x2 grid of textured sprites for each linked entry. */
s32 queue_settings_sprite_grid(u8 *entry_data, u8 *scroll_data)
{
    MainState *main_state;
    u8 *sprite;
    u8 *draw_mode;
    u8 *next_entry;
    s32 row;
    s32 column;
    s32 texture_page;
    s32 texture_x;
    s32 base_y;

    main_state = ((MainState *)&g_game_work);
    for (;;) {
        row = 0;
        do {
            column = 1;
            base_y = row << 8;
            texture_x = 0x280;
            do {
                sprite = main_state->render_state->next_prim;
                main_state->render_state->next_prim = sprite + 0x14;
                ((S_8008896C_0 *)sprite)->unk_04 = 0x808080;
                SetSprt(sprite);
                SetShadeTex(sprite, 1);
                ((S_8008896C_0 *)sprite)->unk_08 = column << 8;
                ((S_8008896C_0 *)sprite)->unk_0A = base_y - ((S_8008896C_1 *)scroll_data)->unk_06;
                ((S_8008896C_0 *)sprite)->unk_10 = 0x100;
                ((S_8008896C_0 *)sprite)->unk_12 = 0x100;
                ((S_8008896C_0 *)sprite)->unk_0C = 0;
                ((S_8008896C_0 *)sprite)->unk_0E = GetClut(0, 0x1F0);
                addPrim(&main_state->render_state->ordering_table, sprite);

                draw_mode = main_state->render_state->next_prim;
                main_state->render_state->next_prim = draw_mode + 0xC;
                texture_page = GetTPage(1, 0, texture_x, base_y);
                SetDrawMode(draw_mode, 0, 0, texture_page & 0xFFFF, 0);
                column--;
                addPrim(&main_state->render_state->ordering_table, draw_mode);
                texture_x -= 0x80;
            } while (column >= 0);
            row++;
        } while (row < 2);

        next_entry = ((S_8008896C_2_pre *)entry_data)[-1].unk_00;
        if (next_entry == 0) {
            return 0;
        }
        entry_data = next_entry + 0x20;
        scroll_data = ((S_8008896C_3 *)next_entry)->unk_08;
    }
}
