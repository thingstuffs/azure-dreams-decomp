#include "common.h"
#include "shared/game_work.h"

typedef struct
{
    u16 x;
    u16 y;
}
DungeonPosition;
typedef struct
{
    u8 pad0[4];
    u16 flags;
    u16 texture;
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
    u8 x2;
    u8 y2;
    u16 count;
    s32 value0;
    s32 value1;
}
DungeonParameters;
typedef struct
{
    u8 pad[0x8D0];
    u8 *cursor;
}
DungeonState;
typedef struct
{
    u8 pad0[8];
    s32 tex_u;
    s32 tex_v;
    s32 tex_w;
    s32 tex_h;
    u8 pad18[0x58];
    union { s32 xy; struct { u16 x; u16 y; } v; } prev;
    u16 prev_z;
    u16 pad76;
    union { s32 xy; struct { u16 x; u16 y; } v; } cur;
    u16 cur_z;
}
EllipseWork;
extern s32 func_800644B8(s32 value);
extern s32 func_80064584(s32 value);
extern void func_8006658C(s32 arg0, u8 *arg1);
extern void func_8006671C(u8 *arg0);
/* Emit textured ellipse segments around the given position. */
void func_800B84E4(DungeonPosition *position, DungeonParameters *parameters, s32 draw_order, s32 blend_mode)
{
    EllipseWork *scratchpad;
    u8 *cursor;
    u8 *packet_code;
    s32 blend_setting;
    s32 segment;
    s32 outer_color2;
    s32 angle_step;
    s32 trig_value;
    s32 center_u;
    s32 center_v;
    s32 texture_page;
    s32 center_xy;
    s32 outer_color3;
    s32 offset;
    u8 *quad_packet;
    s32 packet_order;
    s32 scratch;
    DungeonState **state_slot;
    packet_order = (s32)(((u8 *)(&gameWork)) - 0x3160);
    cursor = (*((DungeonState **) (((u8 *)packet_order) + 0x3160)))->cursor;
    scratchpad = (EllipseWork *) 0x1F800000;
    scratchpad->prev_z = 0;
    scratchpad->cur_z = 0;
    offset = parameters->x2;
    scratchpad->cur.v.x = position->x + offset;
    scratchpad->cur.v.y = position->y;
    scratchpad->tex_u = parameters->x0;
    scratchpad->tex_v = parameters->y0;
    scratchpad->tex_w = parameters->x1;
    scratchpad->tex_h = parameters->y1;
    segment = 0;
    if (segment < (*(u16 *)((u8 *)parameters + 0xE))) {
        blend_setting = blend_mode & 0xFFFF;
        packet_code = cursor + 7;
        angle_step = segment;
loop_0:
        {
            state_slot = (DungeonState **)&gameWork;
            scratchpad->prev.xy = scratchpad->cur.xy;
            center_u = (u8)scratchpad->tex_u
                + (scratchpad->tex_w >> 1);
            *((u8 *) (((u8 *) packet_code) + 17)) = center_u;
            *((u8 *) (((u8 *) packet_code) + 5)) = center_u;
            center_v = (u8)scratchpad->tex_v
                + (scratchpad->tex_h >> 1);
            *((u8 *) (((u8 *) packet_code) + 18)) = center_v;
            *((u8 *) (((u8 *) packet_code) + 6)) = center_v;
            trig_value = func_80064584(angle_step / parameters->count);
            segment += 1;
            {
                offset = scratchpad->tex_w;
                scratch = offset * trig_value;
                offset = scratch >> 13;
                *((u8 *) (((u8 *) packet_code) + 41)) =
                    (*((u8 *) (((u8 *) packet_code) + 5))) + offset;
            }
            trig_value = func_800644B8(angle_step / parameters->count);
            angle_step += 0x1000;
            {
                offset = scratchpad->tex_h;
                scratch = offset * trig_value;
                offset = scratch >> 13;
                *((u8 *) (((u8 *) packet_code) + 42)) =
                    (*((u8 *) (((u8 *) packet_code) + 6))) + offset;
            }
            trig_value = func_80064584(angle_step / parameters->count);
            {
                offset = parameters->x2;
                scratch = offset * trig_value;
                offset = scratch >> 12;
                scratchpad->cur.v.x = position->x + offset;
            }
            trig_value = func_800644B8(angle_step / (*(u16 *)((u8 *)parameters + 0xE)));
            {
                offset = parameters->y2;
                scratch = offset * trig_value;
                offset = scratch >> 12;
                scratchpad->cur.v.y = position->y + offset;
            }
            center_xy = *((s32 *) (((u8 *) position) + 0));
            *((s32 *) (((u8 *) packet_code) + 13)) = center_xy;
            *((s32 *) (((u8 *) packet_code) + 1)) = center_xy;
            *((s32 *) (((u8 *) packet_code) + 25)) =
                scratchpad->cur.xy;
            *((s32 *) (((u8 *) packet_code) + 37)) = scratchpad->prev.xy;
            trig_value = func_80064584(angle_step / parameters->count);
            {
                offset = scratchpad->tex_w;
                scratch = offset * trig_value;
                offset = scratch >> 13;
                *((u8 *) (((u8 *) packet_code) + 29)) = (*((u8 *) (((u8 *) packet_code) + 5))) + offset;
            }
            trig_value = func_800644B8(angle_step / parameters->count);
            {
                offset = scratchpad->tex_h;
                scratch = offset * trig_value;
                offset = scratch >> 13;
                *((u8 *) (((u8 *) packet_code) + 30)) = (*((u8 *) (((u8 *) packet_code) + 6))) + offset;
            }
            *((u16 *) (((u8 *) packet_code) + 7)) = parameters->texture;
            texture_page = parameters->flags;
            *((u16 *) (((u8 *) packet_code) + 19)) = texture_page;
            if (blend_setting != 0) {
                *((u16 *) (((u8 *) packet_code) + 19)) = (texture_page & 0xFF9F) | ((blend_setting - 1) << 5);
            }
            *((s32 *) (((u8 *) (packet_code - 3)) + 0)) = parameters->value0;
            *((s32 *) (((u8 *) packet_code) + 9)) = parameters->value0;
            outer_color2 = parameters->value1;
            *((s32 *) (((u8 *) packet_code) + 21)) = outer_color2;
            quad_packet = cursor;
            outer_color3 = parameters->value1;
            *((s32 *) (((u8 *) packet_code) + 33)) = outer_color3;
            func_8006671C(quad_packet);
            if (blend_setting != 0) {
                *((u8 *) (((u8 *) packet_code) + 0)) |= 2;
                packet_order = draw_order;
            } else {
                packet_order = draw_order;
            }
            func_8006658C(packet_order, cursor);
            packet_code += 52;
            cursor += 52;
        }
        if (segment < parameters->count)
            goto loop_0;
    }
    (*state_slot)->cursor = cursor;
}
