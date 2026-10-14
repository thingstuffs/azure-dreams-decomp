#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "shared/game_work.h"

   /* scratch in func_8002445C */

   /* the 0x8 bytes before arg0 in func_8002445C, addressed as arg0[-1] */

   /* arg0 in func_8002445C */

   /* arg1 in func_8002445C */

   /* context in func_8002445C */

   /* prim in func_8002445C */

   /* context2 in func_8002445C */

   /* next in func_8002445C */





#define setaddr(p, _addr) (((B22_81892C5C_P_TAG *)(p))->addr = (u32)(_addr))
#define getaddr(p) (u32)(((B22_81892C5C_P_TAG *)(p))->addr)
#define addPrim(ot, p) setaddr(p, getaddr(ot)), setaddr(ot, p)



/* Draw a red ring around the effect center using eight projected polylines. */
s32 func_8002445C(void *effect, B22_81892C5C_S_81892C5C_2 *center)
{
    u8 *scratch = (u8 *)0x1F800000;
    void *initial_context;
    s32 base_height;
    s32 radius;
    s32 segment;
    s32 angle_step;
    void **ot_ctx;

    ot_ctx = (void **)((u8 *)(&gameWork));
    initial_context = *ot_ctx;
    ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_18.s = (u8 *)initial_context + 0xB0;
    for (;;) {
        base_height = ((B22_81892C5C_S_81892C5C_1 *)effect)->unk_04;
        ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_68 = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_70 =
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_78 = center->unk_0A;
        radius = (s16)((base_height + 1) << 5);

        angle_step = 0x100;

        for (segment = 0; segment < 8; segment++) {
            void *render_context;
            s32 end_y_scaled;
            void *polyline;
            s32 start_angle;
            s32 angle_base;
            s32 mid_angle;
            s32 end_angle;
            s32 height;
            s32 x_trig;

            render_context = *ot_ctx;
            polyline = ((B22_81892C5C_S_81892C5C_3 *)render_context)->unk_8D0;
            ((B22_81892C5C_S_81892C5C_3 *)render_context)->unk_8D0 = (u8 *)polyline + 0x18;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_00.at03.v = 5;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_07 = 0x48;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_14 = 0x55555555;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_07 |= 2;
            angle_base = angle_step << 1;
            start_angle = segment * angle_base;
            height = ((B22_81892C5C_S_81892C5C_1 *)effect)->unk_04;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_05 = 0;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_06 = 0;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_04 =
                (s8)(-0x80 - (height << 4));

            x_trig = func_800644B8(start_angle);

            angle_base = segment * 2;
            mid_angle = (angle_base + 1) * angle_step;
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_64 = (s16)(center->unk_02 +
                (((x_trig >> 4) * radius) >> 8));
            x_trig = func_800644B8(mid_angle);

            end_angle = (angle_base + 2) * angle_step;
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_6C = (s16)(center->unk_02 +
                (((x_trig >> 4) * radius) >> 8));
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_74 = (s16)(center->unk_02 +
                (((func_800644B8(end_angle) >> 4) * radius) >> 8));
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_66 = (s16)(center->unk_06 +
                (((func_80064584(start_angle) >> 4) * radius) >> 8));
            ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_6E = (s16)(center->unk_06 +
                (((func_80064584(mid_angle) >> 4) * radius) >> 8));
            {

                end_y_scaled = (func_80064584(end_angle) >> 4) * radius;
                base_height = end_y_scaled >> 8;
                ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_76 = (s16)(center->unk_06 + base_height);
            }

            {
                u8 *start_vertex = scratch + 0x64;
                u8 *mid_vertex = scratch + 0x6C;
                u8 *end_vertex = scratch + 0x74;
                u8 *screen_start = scratch + 0xD8;
                ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_B4.s = func_80065530(
                    start_vertex, mid_vertex, end_vertex, screen_start, scratch + 0xDC, scratch + 0xE0,
                    scratch + 0x84, scratch + 0x88);
            }

            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_08 = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_D8;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_0A = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_DA;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_0C = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_DC;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_0E = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_DE;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_10 = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_E0;
            ((B22_81892C5C_S_81892C5C_4 *)polyline)->unk_12 = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_E2;

            {
                u32 otz = ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_B4.u;

                if (otz < 0x1E0) {
                    void *tpage;

                    addPrim(((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_18.u + ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_B4.u, polyline);

                    {
                        B22_81892C5C_S_81892C5C_5 *draw_context;

                        draw_context = ((struct B22_81892C5C_OtCtxS *)ot_ctx)->cur;
                        tpage = draw_context->unk_8D0;
                        draw_context->unk_8D0 = (u8 *)tpage + 0xC;
                    }
                    func_80067F20(tpage, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

                    addPrim(((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_18.u + ((B22_81892C5C_S_81892C5C_0 *)scratch)->unk_B4.u, tpage);
                }
            }

        }

        {
            void *next_effect = ((B22_81892C5C_S_81892C5C_1_pre *)effect)[-1].unk_00;
            if (next_effect == 0) {
                break;
            }
            effect = (u8 *)next_effect + 0x20;
            center = ((B22_81892C5C_S_81892C5C_7 *)next_effect)->unk_08;
        }
    }
    {
        s32 result = 0;
        return result;
    }
}
