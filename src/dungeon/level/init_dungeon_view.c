#include "dungeon/level/init_dungeon_view.h"


/* Initializes dungeon projection, lighting, draw colors, screen clipping, and the default monster
   spawn table. */
void init_dungeon_view(void)
{
    GameWork *render_data = &g_game_work;
    u8 *render_state = (u8 *)render_data + 0x18;
    void *light_matrix;

    ((S_804FE87C_0 *)render_state)->unk_88 = 0x200;
    func_80064F20(0x200);

    ((S_804FE87C_0 *)render_state)->unk_78 = 0;
    ((S_804FE87C_0 *)render_state)->unk_7C = 0;
    ((S_804FE87C_0 *)render_state)->unk_80 = 0;
    func_80064EE0(0, 0, 0);

    ((S_804FE87C_0 *)render_state)->unk_58 = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_5E = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_64 = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_5A = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_60 = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_66 = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_5C = 0;
    ((S_804FE87C_0 *)render_state)->unk_62 = 0;
    ((S_804FE87C_0 *)render_state)->unk_68 = 0;
    func_80064D50(&render_data->view.color_matrix_00);

    light_matrix = &render_data->view.light_matrix_00;
    set_light_vectors((S_804FE87C_0 *)render_state, -0x800, 0x800);
    func_80064D20(light_matrix);

    ((S_804FE87C_0 *)render_state)->unk_84 = 0x1000;
    func_80064624(0x1000, ((S_804FE87C_0 *)render_state)->unk_88);
    func_80064EC0(0xA0, 0xA0, 0xA0);

    upper_draw_context[0x19] = 0;
    upper_draw_context[0x1A] = 0;
    upper_draw_context[0x1B] = 0;
    lower_draw_context[0x19] = 0;
    lower_draw_context[0x1A] = 0;
    lower_draw_context[0x1B] = 0;
    func_80064F00(0xA0, 0x78);

    render_data->view.clip_x = -0xBC;
    render_data->view.clip_y = -0x88;
    render_data->view.clip_width = 0x172;
    render_data->view.clip_height = 0x19A;
    g_dungeon_status.monster_spawn_table = monster_spawn_records;
}
