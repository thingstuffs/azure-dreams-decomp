#include "slus/gp_shared_slots.h"

void func_8003CB08(void)
{
    void **draw_buffer = &D_80083160[0];

    if ((D_80082E60.field_0 & 3) == 1) {
        u8 field_id = (u8)((u32)VSync(1) >> 8);

        if (field_id != D_80080AAA) {
            u8 *next_buffer;
            s32 layer;
            s32 trig_value;
            s32 wave_offset;
            s32 center_offset;

            D_80080AAA = field_id;
            PutDispEnv((u8 *)D_80083160[0] + 0x5C);
            PutDrawEnv(*draw_buffer);

            next_buffer = D_801C9E40[0];
            if (*draw_buffer == D_801C9E40[0]) {
                next_buffer += 0x108D4;
            }
            D_80083160[0] = next_buffer;
            *(u32 *)(next_buffer + 0x8D0) = (u32)next_buffer + 0x8D4;

            if (D_80080AA6 != D_80083960[0]) {
                D_80080AA6 = D_80083960[0];
                D_80080AA8 = 8;
            }

            layer = 63;
            {
                s16 *y_history = D_800838D8;
                s16 *y_dst = y_history + 63;
                s16 *y_src = y_history + 62;
                s16 *x_history = D_80083858;
                s16 *x_dst = x_history + 63;
                s16 *x_src = x_history + 62;

                do {
                    *x_dst = *x_src;
                    x_src--;
                    layer--;
                    *y_dst = *y_src;
                    y_src--;
                    x_dst--;
                    y_dst--;
                } while (layer > 0);
            }

            layer = 3;
            trig_value = rcos(D_80080AA4 * 80);
            {
                s16 *x_head = D_80083858;
                wave_offset = trig_value >> 7;
                center_offset = shift10(trig_value) + 0x100;
                *x_head = (s16)(wave_offset + center_offset);
            }

            trig_value = rsin(D_80080AA4 * 80);
            {
                s16 *y_head = D_800838D8;
                s32 center_offset;
                wave_offset = trig_value >> 7;
                center_offset = shift10(trig_value) + 0xB0;
                *y_head = (s16)(wave_offset + center_offset);
            }

            func_8003D0F0();
            for (; layer >= 0; layer--) {
                func_8003CCB0(layer);
            }

            if (D_80080AA8 != 0) {
                D_80080AA8--;
            }
            DrawSync(0);
            D_80080AA4++;
        }
    }
}
