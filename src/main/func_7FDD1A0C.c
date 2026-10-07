#include "common.h"
#include "shared/game_work.h"

typedef struct S_8008896C_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_8008896C_0;   /* line in func_8008896C */

typedef struct S_8008896C_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_8008896C_1;   /* scroll_data in func_8008896C */

typedef struct S_8008896C_2_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8008896C_2_pre;   /* the 0x8 bytes before entry_data in func_8008896C, addressed as entry_data[-1] */

typedef struct S_8008896C_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_8008896C_3;   /* next in func_8008896C */


typedef struct PacketTag {
    unsigned addr : 24;
    unsigned len : 8;
} PacketTag;

#ifdef NON_MATCHING
#define PTR32(address) ((u32)(unsigned long)(address))
#else
#define PTR32(address) ((u32)(address))
#endif
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


extern s32 func_80066460(s32 texture_depth, s32 blend_mode, s32 texture_x, s32 texture_y);
extern s16 func_8006649C(s32 clut_x, s32 clut_y);
extern void func_80066668(void *primitive, s32 raw_texture);
extern void func_80066758(void *sprite);
extern void func_80067F20(void *draw_mode, s32 draw_in_display_area, s32 dither, u16 texture_page, s32 texture_window);

/* Queue a 2x2 grid of textured sprites for each linked entry. */
s32 func_8008896C(u8 *entry_data, u8 *scroll_data)
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

    main_state = ((MainState *)&gameWork);
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
                func_80066758(sprite);
                func_80066668(sprite, 1);
                ((S_8008896C_0 *)sprite)->unk_08 = column << 8;
                ((S_8008896C_0 *)sprite)->unk_0A = base_y - ((S_8008896C_1 *)scroll_data)->unk_06;
                ((S_8008896C_0 *)sprite)->unk_10 = 0x100;
                ((S_8008896C_0 *)sprite)->unk_12 = 0x100;
                ((S_8008896C_0 *)sprite)->unk_0C = 0;
                ((S_8008896C_0 *)sprite)->unk_0E = func_8006649C(0, 0x1F0);
                addPrim(&main_state->render_state->ordering_table, sprite);

                draw_mode = main_state->render_state->next_prim;
                main_state->render_state->next_prim = draw_mode + 0xC;
                texture_page = func_80066460(1, 0, texture_x, base_y);
                func_80067F20(draw_mode, 0, 0, texture_page & 0xFFFF, 0);
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
