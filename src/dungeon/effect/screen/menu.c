#include "shared/sprite_frame_state.h"

struct ObjectPosition;
/* One native TU; source order follows the complete ledger cohort. */
#include "dungeon/effect/screen/menu.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/screen.h"
#include "dungeon/level.h"
#include "dungeon/menu.h"
#include "dungeon/player.h"



typedef struct {
    u8 pad0[3];
    u8 type;
    u32 command;
    u16 x;
    s16 y;
    u32 wordC;
} DungeonPacket;

typedef struct {
    u16 x;
    s16 y;
    union {
        u32 word4;
        struct {
            u16 z;
            u16 w;
        } half;
    } data;
} DungeonInput;

extern u8 upper_draw_context[16];

extern void SetDrawArea(void *, void *);
extern void AddPrim(void *, void *, ...);
struct DungeonPosition;
struct DungeonParameters;
extern void draw_textured_ellipse_segments(struct DungeonPosition *position, struct DungeonParameters *parameters, s32 draw_order, s32 blend_mode);

/* Draw at the rectangle center and optionally emit a filled rectangle. */
void draw_textured_ellipse(s32 draw_value, DungeonInput *rect, u16 fill_rect, u16 draw_mode) {
    GpuContext *initial_state;
    GpuContext *active_state;
    GpuContext **state_slot = &g_game_work.draw_buffer;
    u8 *draw_list;
    u8 *command_cursor;
    DungeonPacket *fill_packet;
    s16 center[2];
    s32 center_y;
    s32 packet_y;
    s16 offset_y;

    initial_state = g_game_work.draw_buffer;
    offset_y = initial_state != (GpuContext *)upper_draw_context ? 1 : 0;
    command_cursor = initial_state->packetCursor;
    draw_list = (u8 *)initial_state + 0x8B0;
    initial_state->packetCursor = command_cursor + 0xC;
    SetDrawArea(command_cursor, g_game_work.draw_buffer);
    AddPrim(draw_list, command_cursor);

    center[0] = rect->x + ((s32)(rect->data.half.z << 0x10) >> 0x11);
    center_y = (s32)rect->y + ((s32)(rect->data.half.w << 0x10) >> 0x11);
    if (offset_y) {
        center_y -= 0xE0;
    }
    center[1] = center_y;
    draw_textured_ellipse_segments(center, draw_value, draw_list, draw_mode & 0xFFFF);

    if ((fill_rect & 0xFFFF) != 0) {
        active_state = g_game_work.draw_buffer;
        fill_packet = (DungeonPacket *)active_state->packetCursor;
        active_state->packetCursor = (u8 *)fill_packet + 0x10;
        fill_packet->command = 0x60000000;
        fill_packet->type = 3;
        fill_packet->x = rect->x;
        packet_y = rect->y;
        if (offset_y) {
            packet_y -= 0xE0;
        }
        fill_packet->y = packet_y;
        fill_packet->wordC = rect->data.word4;
        AddPrim(draw_list, (u8 *)fill_packet);
    }

    active_state = *state_slot;
    command_cursor = active_state->packetCursor;
    active_state->packetCursor = command_cursor + 0xC;
    SetDrawArea(command_cursor, rect);
    AddPrim(draw_list, command_cursor);
}
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct DungeonPosition
{
    u16 x;
    u16 y;
}
DungeonPosition;
typedef struct DungeonParameters
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
extern s32 rsin(s32, ...);
extern s32 rcos(s32, ...);
extern void AddPrim(void *, void *, ...);
extern void SetPolyGT4(u8 *);
/* Emit textured ellipse segments around the given position. */
void draw_textured_ellipse_segments(DungeonPosition *position, DungeonParameters *parameters, s32 draw_order, s32 blend_mode)
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
    GpuContext **state_slot;
    packet_order = (s32)(((u8 *)(&g_game_work)) - 0x3160);
    cursor = (*((GpuContext **) (((u8 *)packet_order) + 0x3160)))->packetCursor;
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
    if (segment < (parameters->count)) {
        blend_setting = blend_mode & 0xFFFF;
        packet_code = cursor + 7;
        angle_step = segment;
loop_0:
        {
            state_slot = (GpuContext **)&g_game_work;
            scratchpad->prev.xy = scratchpad->cur.xy;
            center_u = (u8)scratchpad->tex_u
                + (scratchpad->tex_w >> 1);
            *((u8 *) (((u8 *) packet_code) + 17)) = center_u;
            *((u8 *) (((u8 *) packet_code) + 5)) = center_u;
            center_v = (u8)scratchpad->tex_v
                + (scratchpad->tex_h >> 1);
            *((u8 *) (((u8 *) packet_code) + 18)) = center_v;
            *((u8 *) (((u8 *) packet_code) + 6)) = center_v;
            trig_value = rcos(angle_step / parameters->count);
            segment += 1;
            {
                offset = scratchpad->tex_w;
                scratch = offset * trig_value;
                offset = scratch >> 13;
                *((u8 *) (((u8 *) packet_code) + 41)) =
                    (*((u8 *) (((u8 *) packet_code) + 5))) + offset;
            }
            trig_value = rsin(angle_step / parameters->count);
            angle_step += 0x1000;
            {
                offset = scratchpad->tex_h;
                scratch = offset * trig_value;
                offset = scratch >> 13;
                *((u8 *) (((u8 *) packet_code) + 42)) =
                    (*((u8 *) (((u8 *) packet_code) + 6))) + offset;
            }
            trig_value = rcos(angle_step / parameters->count);
            {
                offset = parameters->x2;
                scratch = offset * trig_value;
                offset = scratch >> 12;
                scratchpad->cur.v.x = position->x + offset;
            }
            trig_value = rsin(angle_step / (parameters->count));
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
            trig_value = rcos(angle_step / parameters->count);
            {
                offset = scratchpad->tex_w;
                scratch = offset * trig_value;
                offset = scratch >> 13;
                *((u8 *) (((u8 *) packet_code) + 29)) = (*((u8 *) (((u8 *) packet_code) + 5))) + offset;
            }
            trig_value = rsin(angle_step / parameters->count);
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
            SetPolyGT4(quad_packet);
            if (blend_setting != 0) {
                *((u8 *) (((u8 *) packet_code) + 0)) |= 2;
                packet_order = draw_order;
            } else {
                packet_order = draw_order;
            }
            AddPrim(packet_order, cursor);
            packet_code += 52;
            cursor += 52;
        }
        if (segment < parameters->count)
            goto loop_0;
    }
    (*state_slot)->packetCursor = cursor;
}
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct ShortVec {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

extern void *actor_direction_sprites;

extern void *resolve_record_orientation_or_fallback(void *, void *, ShortVec *, s16);
extern s32 rsin(s32, ...);
extern void spawn_blinking_sprite_flash(s16, s16, s16);
struct FuncInput;
extern void create_attenuating_moving_effect(s32 alloc_arg, s32 child_x, s32 child_y, s32 child_z,
                   struct FuncInput *input, s32 meta_value, s16 step_count, s32 range_value, s16 object_tag);


typedef struct S_800B8830_0_pre {
    u16 unk_00;
} S_800B8830_0_pre;   /* the 0x2 bytes before arg0 in update_arcing_effect, addressed as arg0[-1] */

typedef struct S_800B8830_0 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x10];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x4];
    union { s16 s; u16 u; } unk_26;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0x8];
    s16 unk_32;
} S_800B8830_0;   /* arg0 in update_arcing_effect */

typedef struct S_800B8830_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800B8830_1;   /* arg2 in update_arcing_effect */

typedef struct S_800B8830_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800B8830_2;   /* source in update_arcing_effect */

typedef struct S_800B8830_3 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_800B8830_3;   /* arg1 in update_arcing_effect */

   /* position in update_arcing_effect */

typedef struct S_800B8830_5 {
    s32 unk_00;
    s32 unk_04;
} S_800B8830_5;   /* target_node in update_arcing_effect */


typedef struct S_800B8830_8 {
    void * unk_00;
} S_800B8830_8;   /* (void *)index in update_arcing_effect */

typedef struct S_800B8830_9 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800B8830_9;   /* flags_page in update_arcing_effect */

typedef struct S_800B8830_10 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B8830_10;   /* ((S_800B8830_0 *)arg0)->unk_00 in update_arcing_effect */

typedef struct S_800B8830_11 {
    u16 unk_00;
} S_800B8830_11;   /* ((S_800B8830_0 *)arg0)->unk_08 in update_arcing_effect */

typedef struct S_800B8830_12 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B8830_12;   /* ((S_800B8830_0 *)arg0)->unk_04 in update_arcing_effect */

/* Follows the source position, then moves along an arc to the target and marks completion. */
void update_arcing_effect(void *motion, S_800B8830_3 *coords, S_800B8830_1 *render) {
    ShortVec delta;
    s32 target_pos[3];
    ShortVec current_pos;
    s16 state;
    s16 one;
    void *source;
    MovingPosition *pos_record;
    s32 curve;
    u16 render_flags;
    u16 counter;

    one = 1;
    state = ((S_800B8830_0 *)motion)->unk_20.s;
    switch (state) {
    case 0:
        render->unk_0C = render->unk_0D = render->unk_0E = 0x80;
        render_flags = render->unk_14;
        render->unk_1C = render->unk_1E = 0x1000;
        render->unk_14 = render_flags | 0xC;
        register_node((u8 *)motion - 0x20, project_sprite_chain);
        ((S_800B8830_0 *)motion)->unk_20.u++;
                /* fallthrough */
    case 1:
        source = ((S_800B8830_10 *)(((S_800B8830_0 *)motion)->unk_00))->unk_0C;
        if ((((S_800B8830_2 *)source)->unk_14 & 0x8000) ||
            resolve_record_orientation_or_fallback(((S_800B8830_2 *)source)->unk_08, source, &delta, 0) != NULL) {
            u16 source_z;

            pos_record = ((S_800B8830_10 *)(((S_800B8830_0 *)motion)->unk_00))->unk_08;
            coords->unk_00.at02.v = pos_record->x;
            coords->unk_04.at02.v = pos_record->y;
            source_z = pos_record->z;
            coords->unk_08.at02.v = source_z;

            if (!(((S_800B8830_2 *)source)->unk_14 & 0x8000)) {
                u16 offset_z;

                coords->unk_00.at02.v += (u16)delta.x;
                coords->unk_04.at02.v += (u16)delta.y;
                offset_z = coords->unk_08.at02.v + (u16)delta.z;
                coords->unk_08.at02.v = offset_z;
            } else {
                coords->unk_08.at02.v = source_z - 0x20;
            }
        }

        if (((S_800B8830_11 *)(((S_800B8830_0 *)motion)->unk_08))->unk_00 & 0x80) {
            ((S_800B8830_0 *)motion)->unk_26.s = 9;
            ((S_800B8830_0 *)motion)->unk_20.u++;
        }
        break;
    case 2:
    {
        void *entry;
        s32 entry_addr;
        s32 start_x;
        s32 start_y;
        s32 start_z;

        pos_record = ((S_800B8830_12 *)(((S_800B8830_0 *)motion)->unk_04))->unk_08;
        start_x = coords->unk_00.at02u.v;
        start_y = coords->unk_04.at02u.v;
        start_z = coords->unk_08.at02u.v;
        target_pos[0] = ((S_800B8830_5 *)pos_record)->unk_00;
        target_pos[1] = ((S_800B8830_5 *)pos_record)->unk_04;
        target_pos[2] = (((S_800B8830_0 *)motion)->unk_32 - 0x50) << 16;

        entry_addr = ((g_game_work.view.camera_rotation.parts.viewAngle +
                  primary_actor_record->facing + 0x100) >> 7) & 0x1C;
        entry_addr += (s32)actor_direction_sprites;
        entry = ((S_800B8830_8 *)((void *)entry_addr))->unk_00;
        if (resolve_record_orientation_or_fallback(entry, ((S_800B8830_12 *)(((S_800B8830_0 *)motion)->unk_04))->unk_0C, &delta, 0) != NULL) {
            target_pos[0] += (s32)delta.x << 16;
            target_pos[1] += (s32)delta.y << 16;
            target_pos[2] += (s32)delta.z << 16;
        }

        coords->unk_00.at00.v += (target_pos[0] - coords->unk_00.at00.v) / ((S_800B8830_0 *)motion)->unk_26.s;
        coords->unk_04.at00.v += (target_pos[1] - coords->unk_04.at00.v) / ((S_800B8830_0 *)motion)->unk_26.s;
        curve = rsin(((S_800B8830_0 *)motion)->unk_26.s * 170);
        coords->unk_08.at00.v +=
            (target_pos[2] - coords->unk_08.at00.v) / ((S_800B8830_0 *)motion)->unk_26.s - (curve << 7);

        current_pos.x = coords->unk_00.at02.v;
        current_pos.y = coords->unk_04.at02.v;
        current_pos.z = coords->unk_08.at02.v;
        create_attenuating_moving_effect((u8 *)motion - 0x20, start_x, start_y, start_z, &current_pos,
                      ((S_800B8830_0 *)motion)->unk_0C, 4, 0x1000, one);

        counter = ((S_800B8830_0 *)motion)->unk_26.u - 1;
        ((S_800B8830_0 *)motion)->unk_26.u = counter;
        if ((s16)counter > 0) {
            break;
        }

        coords->unk_00.at00.v = target_pos[0];
        coords->unk_04.at00.v = target_pos[1];
        coords->unk_08.at00.v = target_pos[2];
        spawn_blinking_sprite_flash(coords->unk_00.at02u.v, coords->unk_04.at02u.v, coords->unk_08.at02u.v);
        {
            void *flags_page;
            s32 final_flags;
            u16 object_flags;

            object_flags = ((S_800B8830_0_pre *)motion)[-1].unk_00;
            flags_page = (void *)0x80080000;
            object_flags |= 0x8000;
            ((S_800B8830_0_pre *)motion)[-1].unk_00 = object_flags;
            counter = ((S_800B8830_0 *)motion)->unk_20.u;
            final_flags = ((S_800B8830_9 *)flags_page)->unk_14A0;
            counter += 1;
            final_flags |= 0x8000;
            ((S_800B8830_0 *)motion)->unk_20.u = counter;
            ((S_800B8830_9 *)flags_page)->unk_14A0 = final_flags;
        }
        return;
    }
    default:
        break;
    }
    ((S_800B8830_0 *)motion)->unk_28++;
}
#include "common.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct Child {
    u8 pad0[8];
    void *value8;
    u8 padC[4];
    s16 value10;
} Child;

typedef struct Tail {
    void *owner;
    void *descriptor;
    s32 value8;
    void *valueC;
    u8 pad10[0x22];
    u16 value32;
} Tail;

typedef struct Object_800B34C0 {
    u8 pad0[0xC];
    Child *child;
    void *state;
    u8 pad14[0xC];
    Tail tail;
} Object_800B34C0;

struct S_800B8830_1;
extern void update_arcing_effect(void *motion, S_800B8830_3 *coords, struct S_800B8830_1 *render);
extern u8 D_800DF2F8[];
extern u8 D_800DF334[];

extern void *allocate_list_node();

/* Create an object with default child and tail data when none are supplied. */
void create_timed_model_effect(void *owner, s32 value, void *child_data, void *tail_data)
{
    Object_800B34C0 *object;
    Child *child;
    void *descriptor;
    ActorRecord *header;

    {
        u8 *call_page;
        s32 kind;

        call_page = (u8 *)0x80080000;
        kind = 0x12;
        object = allocate_list_node(kind, (u8 *)((u8 *)(&scene_object_list_anchor)));
    }
    if (object != 0) {
        child = object->child;
        object->state = update_arcing_effect;

        if (child_data != 0) {
            child->value8 = child_data;
        } else {
            child->value8 = D_800DF2F8;
        }

        child->value10 = 0x60;
        object = (Object_800B34C0 *)&object->tail;

        if (tail_data != 0) {
            ((Tail *)object)->valueC = tail_data;
        } else {
            u8 *fallback;

            fallback = D_800DF334 - 0x3C;
            ((Tail *)object)->valueC = fallback;
        }
        descriptor = (void *)&scene_object_list_anchor;
        header = primary_actor_record;
        ((Tail *)object)->owner = owner;
        ((Tail *)object)->descriptor = descriptor;
        ((Tail *)object)->value32 = ((u16)header->ground_height);
        ((Tail *)object)->value8 = value;
    }
}
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800B8CF0_0_pre {
    u16 unk_00;
} S_800B8CF0_0_pre;   /* the 0x2 bytes before arg0 in update_blinking_sprite_flash, addressed as arg0[-1] */

typedef struct S_800B8CF0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B8CF0_0;   /* arg0 in update_blinking_sprite_flash */

typedef struct S_800B8CF0_1 {
    u8 pad_00[0xC];
    union {
        struct { s8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } unk_0C;   /* overlapping accesses */
} S_800B8CF0_1;   /* arg2 in update_blinking_sprite_flash */


/* Count down the effect, alternating its shade until marking it finished. */
void update_blinking_sprite_flash(void *state, s32 unused, void *primitive) {
    s32 ticks_left;

    ticks_left = ((S_800B8CF0_0 *)state)->unk_02 - 1;
    ((S_800B8CF0_0 *)state)->unk_02 = (u16) ticks_left;
    if (((ticks_left << 16) >> 16) <= 0) {
        (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800B8CF0_0_pre *)state)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    if (ticks_left & 1) {
        s8 shade = (s8) ((((ticks_left << 16) >> 16) << 3) | 0x20);
        ((S_800B8CF0_1 *)primitive)->unk_0C.at00.v = shade;
        ((S_800B8CF0_1 *)primitive)->unk_0C.at02.v = shade;
        ((S_800B8CF0_1 *)primitive)->unk_0C.at01.v = shade;
        return;
    }
    ((S_800B8CF0_1 *)primitive)->unk_0C.at00u.v = 0x00101010;
}
#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

extern void update_blinking_sprite_flash(void *state, s32 unused, void *primitive);
extern M2C_UNK visual_object_sprite_data;

typedef struct S_800B8D64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)(void *, s32,  void *);
    u8 pad_14[0xE];
    s16 unk_22;
} S_800B8D64_0;

typedef struct S_800B8D64_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800B8D64_1;

typedef struct S_800B8D64_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800B8D64_2;

/* Create and initialize an effect at the given position. */
void spawn_blinking_sprite_flash(s16 x, s16 y, s16 z) {
    S_800B8D64_0 *effect;
    S_800B8D64_1 *position;
    S_800B8D64_2 *sprite;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        effect->unk_10 = update_blinking_sprite_flash;
        register_node(effect, project_sprite_chain);
        position = effect->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        sprite = effect->unk_0C;
        sprite->unk_08 = &visual_object_sprite_data;
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        effect->unk_22 = 6;
    }
}
#include "common.h"
#include "shared/object_flags.h"

typedef struct Object_800B36B8 {
    u8 pad0[2];
    s16 field2;
} Object_800B36B8;

typedef struct Effect {
    u8 pad0[0xC];
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF[0xD];
    u16 field1C;
    u16 field1E;
} Effect;


/* Attenuates an effect and sets object and global flags when its byte level reaches zero. */
void attenuate_effect_scale_and_brightness(Object_800B36B8 *object, s32 unused, Effect *effect) {
    u16 magnitude;
    u8 level;
    ObjectFlagBlock *state_flags = &object_flag_block;

    magnitude = effect->field1E;
    magnitude = magnitude - ((magnitude * object->field2) / 24);
    effect->field1E = magnitude;
    effect->field1C = magnitude;
    level = effect->fieldE - (object->field2 * 8);
    effect->fieldE = level;
    effect->fieldD = level;
    effect->fieldC = level;
    if (!(level & 0xFF)) {
        *(u16 *)((u8 *)object - 2) = (u16)(*(u16 *)((u8 *)object - 2) | 0x8000);
        state_flags->flags = state_flags->flags | 0x8000;
    }
}
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct FuncInput {
    u16 unk0;
    u16 unk2;
    u16 unk4;
} FuncInput;

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[2];
    u16 unkA;
    u8 padC[2];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} FuncChild;

typedef struct {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s16 unk10;
    u8 pad12[2];
    u16 unk14;
    u8 pad16[6];
    s16 unk1C;
    s16 unk1E;
    u8 pad20[2];
    s16 unk22;
} FuncMeta;

typedef struct {
    u8 pad0[8];
    FuncChild *child;
    FuncMeta *meta;
    void *unk10;
    u8 pad14[14];
    s16 unk22;
} FuncObject;

extern s32 process_linked_mesh_states_mode_0(void *initial_state, s32 value, void *data);
struct Object_800B36B8;
struct Effect;
extern void attenuate_effect_scale_and_brightness(struct Object_800B36B8 *object, s32 unused, struct Effect *effect);
extern void *allocate_list_node();

/* Allocate and initialize a type-0x12 object with child and metadata values. */
void create_attenuating_moving_effect(s32 alloc_arg, s32 child_x, s32 child_y, s32 child_z,
                   FuncInput *input, s32 meta_value, s16 step_count, s32 range_value, s16 object_tag) {
    FuncMeta *meta;
    FuncObject *object;
    FuncChild *child;
    u16 input_z;
    s32 signed_count;

    object = allocate_list_node(0x12, alloc_arg);
    if (object != NULL) {
        object->unk10 = attenuate_effect_scale_and_brightness;
        register_node(object, process_linked_mesh_states_mode_0);
        child = object->child;
        child->unk2 = input->unk0;
        child->unk6 = input->unk2;
        input_z = input->unk4;
        child->unkE = child_x;
        child->unk12 = child_y;
        child->unk16 = child_z;
        child->unkA = input_z;
        meta = object->meta;
        meta->unk8 = meta_value;
        meta->unk1E = range_value;
        meta->unk1C = range_value;
        meta->unkC = 0x808080;
        signed_count = ((s32) step_count << 16) >> 16;
        if (signed_count != 0) {
            meta->unk10 = (s16) ((signed_count - 1) << 5);
            meta->unk14 = (u16) (meta->unk14 | 0xC);
        }
        object->unk22 = object_tag;
    }
}
#include "common.h"
#include "shared/game_work.h"

typedef struct Position {
    u16 x;
    s16 y;
} Position;

typedef struct {
    u8 pad0[3];
    u8 size;
    u32 code;
    u16 x;
    s16 y;
    u32 data;
} Packet;

typedef struct DrawContext {
    u8 pad[0x8B0];
    u8 ordering_table[0x20];
    Packet *next_packet;
} DrawContext;

extern void AddPrim(void *, void *, ...);
extern void SetDrawArea(void *, void *);
extern void draw_transformed_sprite_parts(void *position, void *context, s32 depth, s16 draw_mode);
extern u8 upper_draw_context[16];

/* Queue a clipped sprite with an optional black background, adjusting Y for the active buffer. */
void draw_transformed_sprite_with_clip_rect(s32 sprite, Position *clip_rect, Position *screen_pos, s32 clear_bg, s16 draw_flags)
{
    Position draw_pos;
    DrawContext *context;
    void *draw_context;
    void *ordering_table;
    Packet *area_packet;
    u16 saved_clear_bg;
    s16 shift_y;
    s32 y;

    context = (DrawContext *)g_game_work.draw_buffer;
    saved_clear_bg = clear_bg;
    shift_y = context != (DrawContext *)upper_draw_context;
    area_packet = context->next_packet;
    ordering_table = context->ordering_table;
    context->next_packet = (Packet *)((u8 *)area_packet + 0xC);
    draw_context = g_game_work.draw_buffer;
    SetDrawArea(area_packet, draw_context);
    AddPrim(ordering_table, area_packet);

    draw_pos.x = screen_pos->x;
    y = screen_pos->y;
    {
        DrawContext **context_slot;

        if (shift_y) {
            y -= 0xE0;
        }
        context_slot = (DrawContext **)&g_game_work.draw_buffer;
        draw_pos.y = y;
        draw_transformed_sprite_parts(&draw_pos, sprite, ordering_table, draw_flags);

        if ((u16)saved_clear_bg != 0) {
            Packet *clear_packet;

            context = *context_slot;
            clear_packet = context->next_packet;
            context->next_packet = (Packet *)((u8 *)clear_packet + 0x10);
            clear_packet->code = 0x60000000;
            clear_packet->size = 3;
            clear_packet->x = clip_rect->x;
            y = clip_rect->y;
            if (shift_y) {
                y -= 0xE0;
            }
            clear_packet->y = y;
            clear_packet->data = *(u32 *)((u8 *)clip_rect + 4);
            AddPrim(ordering_table, clear_packet);
        }

        context = *context_slot;
        area_packet = context->next_packet;
        context->next_packet = (Packet *)((u8 *)area_packet + 0xC);
        SetDrawArea(area_packet, clip_rect);
        AddPrim(ordering_table, area_packet);
    }
}

#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"




/* Scratchpad used by draw_transformed_sprite_parts. The projection helper
 * writes one XY/depth pair per corner; texture arithmetic also reads the low
 * halfwords of its 32-bit working values. */
typedef struct SpritePartWork {
    s16 input_x;
    s16 input_y;
    u8 pad_04[4];
    union { s32 value; u16 low; } texture_u;
    union { s32 value; u16 low; } texture_v;
    union { s32 value; u16 low; } texture_width;
    union { s32 value; u16 low; } texture_height;
    u8 pad_18[8];
    s32 ordering_table;
    u16 sprite_flags;
    u8 pad_26[0xA];
    s32 scale_x;
    s32 scale_y;
    s32 scale_z;
    u8 pad_3C[4];
    s32 translate_x;
    s32 translate_y;
    s32 translate_z;
    u8 pad_4C[4];
    u8 matrix[0x20];
    struct { u16 x, y, z, pad; } corners[4];
    u8 pad_90[4];
    s32 unk_94;
    struct { s32 xy, depth; } projected[4];
    u8 pad_B8[8];
    s32 unk_C0;
    u8 pad_C4[0x44];
    u16 sprite_width;
    u16 sprite_height;
} SpritePartWork;




extern void PushMatrix();
extern void PopMatrix(void);
extern void TransMatrix(void *, void *, s32, s32);
extern void *ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern void func_80065320(void *, void *, void *);
extern void *RotMatrix(void *, void *);
extern void AddPrim(void *, void *, ...);
extern void func_80067EF4(void *, s32, s32, ...);

/* Build transformed textured quads from sprite parts and append them to the draw list. */
void draw_transformed_sprite_parts(void *position, void *context, s32 depth, s16 draw_mode)
{
    s32 (*callback)(void *, s32, void *, void *, void *);
    SpritePartWork *scratch = (SpritePartWork *)0x1F800000;
    SpriteFrameState *sprite = ((ObjectNodeHeader *)((u8 *)context - 0x20))->sprite;
    s32 callback_arg = (s32)((ObjectNodeHeader *)((u8 *)context - 0x20))->position;
    s16 saved_mode = draw_mode;
    GpuContext *root = g_game_work.draw_buffer;
    SpritePartCommand *part = sprite->source;
    GpuContext **global_slot = ((GpuContext * *)(&g_game_work));
    u8 *scratch_base;
    SpritePartQuad *packet;
    s32 mode_bits;
    s32 extent;
    u8 edge_byte;
    s32 tex_result;
    s32 y_component;

    scratch->corners[3].z = 0;
    scratch->corners[2].z = 0;
    scratch->corners[1].z = 0;
    scratch->corners[0].z = 0;
    packet = (SpritePartQuad *)root->packetCursor;
    mode_bits = draw_mode << 16;
    scratch->ordering_table = depth;
    scratch->unk_C0 = 0;
    if (mode_bits != 0) {
        func_80067EF4(packet, 0, 0, mode_bits);
        AddPrim(scratch->ordering_table, packet);
        packet = (SpritePartQuad *)((u8 *)packet + 12);
    }
    PushMatrix();

    {
        u16 *input = position;
        s32 x;
        s32 y;
        s32 raw_x;
        s32 raw_y;
        s32 x_component;

        raw_x = input[0];
        scratch->input_x = raw_x;
        raw_y = input[1];
        x = (s16)raw_x;
        scratch->input_y = raw_y;
        scratch_base = (u8 *)0x1F800000;
        x_component = sprite->scale_x;
        y = (s16)raw_y;
        scratch->scale_x = x_component;
        y_component = sprite->scale_y;
        x_component = 0x1000;
        scratch->scale_z = x_component;
        scratch->scale_y = y_component;
        x_component = sprite->offset_x;
        scratch->sprite_width = x_component;
        x_component = (s16)x_component;
        y_component = sprite->offset_y;
        x += x_component;
        scratch->translate_x = x;
        scratch->translate_z = 0;
        scratch->sprite_height = y_component;
        y_component <<= 16;
        y_component >>= 16;
        y += y_component;
        scratch->translate_y = y;
        TransMatrix(scratch->matrix, &scratch->translate_x,
                      x, y);
        RotMatrix(&sprite->angle_x, scratch_base + 0x50);
        ScaleMatrix(scratch_base + 0x50, &scratch->scale_x);
        SetRotMatrix(scratch_base + 0x50);
        SetTransMatrix(scratch_base + 0x50);
        scratch->sprite_flags = sprite->flags;
        scratch_base += 0x94;
    }

    do {
        scratch = (SpritePartWork *)0x1F800000;
        if (!(part->flags & 0x20)) {
            s32 edge;
            s16 edge1;
            s16 edge2;
            scratch->texture_u.value = part->data.texture.u;
            scratch->texture_v.value = part->data.texture.v;
            scratch->texture_width.value = part->data.texture.width;
            scratch->texture_height.value = part->data.texture.height;

            {
                if (((part->flags ^ scratch->sprite_flags) & 1) != 0) {

                    edge_byte = part->offset_x;
                    y_component = scratch->sprite_width;
                    extent = scratch->texture_width.low;
                    edge1 = (s8)edge_byte;
                    edge1 = -edge1 - y_component;
                    scratch->corners[2].x = edge1;
                    scratch->corners[0].x = edge1;
                    edge1 -= extent;
                    scratch->corners[3].x = edge1;
                    scratch->corners[1].x = edge1;
                } else {

                    edge_byte = part->offset_x;
                    y_component = scratch->sprite_width;
                    extent = scratch->texture_width.low;
                    edge1 = (s8)edge_byte;
                    edge1 -= y_component;
                    scratch->corners[2].x = edge1;
                    scratch->corners[0].x = edge1;
                    edge1 += extent;
                    scratch->corners[3].x = edge1;
                    scratch->corners[1].x = edge1;
                }
            }

            {
                if (((part->flags ^ scratch->sprite_flags) & 2) != 0) {

                    edge_byte = part->offset_y;
                    y_component = scratch->sprite_height;
                    extent = scratch->texture_height.low;
                    edge2 = (s8)edge_byte;
                    edge2 = -edge2 - y_component;
                    scratch->corners[1].y = edge2;
                    scratch->corners[0].y = edge2;
                    edge2 -= extent;
                    scratch->corners[3].y = edge2;
                    scratch->corners[2].y = edge2;
                } else {

                    edge_byte = part->offset_y;
                    y_component = scratch->sprite_height;
                    extent = scratch->texture_height.low;
                    edge2 = (s8)edge_byte;
                    edge2 -= y_component;
                    scratch->corners[1].y = edge2;
                    scratch->corners[0].y = edge2;
                    edge2 += extent;
                    scratch->corners[3].y = edge2;
                    scratch->corners[2].y = edge2;
                }
            }

            func_80065320(&scratch->corners[0], &scratch->projected[0], scratch_base);
            func_80065320(&scratch->corners[1], &scratch->projected[1], scratch_base);
            func_80065320(&scratch->corners[2], &scratch->projected[2], scratch_base);
            func_80065320(&scratch->corners[3], &scratch->projected[3], scratch_base);

            {
                s32 vertex_xy;

                vertex_xy = scratch->projected[0].xy;
                packet->vertex[0].xy.word = vertex_xy;
                vertex_xy = scratch->projected[1].xy;
                packet->vertex[1].xy.word = vertex_xy;
                vertex_xy = scratch->projected[2].xy;
                packet->vertex[2].xy.word = vertex_xy;
                depth = scratch->projected[3].xy;
                vertex_xy = 9;
                packet->tag.bytes.length = vertex_xy;
                packet->vertex[3].xy.word = depth;
            }

            {
                s32 tex_extent;

                tex_extent = scratch->texture_width.value;
                y_component = scratch->texture_u.value;
                tex_extent -= 1;
                tex_result = tex_extent + y_component;
                scratch->texture_width.value = tex_result;
                if (tex_result & 0x100) {
                    tex_extent = tex_result - 1;
                    scratch->texture_width.value = tex_extent;
                }
            }
            {
                s32 tex_extent;

                tex_extent = scratch->texture_height.value;
                y_component = scratch->texture_v.value;
                tex_extent -= 1;
                tex_result = tex_extent + y_component;
                scratch->texture_height.value = tex_result;
                if (tex_result & 0x100) {
                    tex_extent = tex_result - 1;
                    scratch->texture_height.value = tex_extent;
                }
            }

            scratch->texture_height.value <<= 8;
            scratch->texture_v.value <<= 8;

            {
                s32 clut;
                s32 clut_offset = sprite->clut;
                if (clut_offset != 0) {
                    if (scratch->sprite_flags & 0x100) {
                        packet->vertex[0].uv.bytes.attr = clut_offset;
                    } else {
                        clut = part->clut;
                        packet->vertex[0].uv.bytes.attr = clut_offset + clut;
                    }
                } else {
                    clut = part->clut;
                    packet->vertex[0].uv.bytes.attr = clut;
                }
            }

            packet->vertex[0].uv.pair = scratch->texture_v.low + scratch->texture_u.low;
            packet->vertex[1].uv.pair = scratch->texture_v.low + scratch->texture_width.low;

            {
                s32 page_input;
                s32 page_offset = sprite->tpage_abr;
                if (page_offset != 0) {
                    page_input = part->tpage;
                    page_input &= 0xFF9F;
                    edge = page_offset + page_input;
                } else {
                    edge = part->tpage;
                }
                packet->vertex[1].uv.bytes.attr = edge;
            }
            {
                s16 edge_work;
                s32 uv_work;
                s32 uv_work_2;
                u16 right_u;
                s32 left_x;

                edge_work = scratch->texture_height.low;
                uv_work = scratch->texture_u.low;
                left_x = packet->vertex[0].xy.parts.x;
                edge_work |= uv_work;
                packet->vertex[2].uv.pair = edge_work;
                uv_work_2 = scratch->texture_height.low;
                right_u = scratch->texture_width.low;
                edge_work = packet->vertex[3].xy.parts.x;
                uv_work_2 |= right_u;
                edge_work = edge_work < left_x;
                packet->vertex[3].uv.pair = uv_work_2;
                if (edge_work != 0) {
                    uv_work = packet->vertex[3].uv.bytes.u;
                    edge_work = uv_work + 0xFF;
                    packet->vertex[3].uv.bytes.u = edge_work;
                    packet->vertex[1].uv.bytes.u = uv_work;
                }
            }
            {
                s32 bottom_y;
                s32 top_y;
                top_y = packet->vertex[0].xy.parts.y;
                bottom_y = packet->vertex[3].xy.parts.y;
                if (bottom_y < top_y) {
                    top_y = packet->vertex[3].uv.bytes.v;
                    bottom_y = top_y + 0xFF;
                    packet->vertex[3].uv.bytes.v = bottom_y;
                    packet->vertex[2].uv.bytes.v = top_y;
                }
            }

            {
                s32 part_code = part->code;
                s32 draw_code;
                s32 draw_flags;
                sprite->color.c.code = part_code;
                draw_flags = scratch->sprite_flags;
                draw_code = draw_flags & 8;
                if (draw_code != 0) {
                    draw_code = draw_flags & 4;
                    if (draw_code == 0) {
                        draw_code = part_code & 0xFD;
                    } else {
                        draw_code = part_code | 2;
                    }
                    sprite->color.c.code = draw_code;
                }
            }

            {
                u8 *draw_packet;
                s32 color_code;
                color_code = sprite->color.word;
                draw_packet = (u8 *)packet;
                packet->color = color_code;
                AddPrim(scratch->ordering_table, draw_packet);
                packet++;

            }
        } else {
            callback = part->data.callback;
            if (callback != 0) {
                register s32 callback_result;
                callback_result = callback(context, callback_arg, sprite, part, packet);
                if (callback_result > 0) {
                    u32 cached_base = 0x80000000;
                    part = (SpritePartCommand *)(callback_result | cached_base);
                } else {
                    packet = (SpritePartQuad *)callback_result;
                }
            }
        }

        if ((s8)part++->flags < 0) {
            break;
        }
    } while (1);
    {
        s32 end_mode_bits = saved_mode << 16;
        if (end_mode_bits != 0) {
            func_80067EF4(packet, 0, 1);
            AddPrim(scratch->ordering_table, packet);
            packet = (SpritePartQuad *)((u8 *)packet + 12);
        }
    }
    PopMatrix();
    (*global_slot)->packetCursor = (u8 *)packet;
    return;
}
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"


extern void *screen_effect_target[];

extern s32 play_sound_if_enabled(s32 query_value);
extern void advance_sprite_animation_and_textures(void *);

/* Updates a target marker's position, scale, color, and rotation. */
void update_familiar_selection_marker(FamiliarMarkerWork *state, ObjectPosition *position_arg, SpriteFrameState *marker_arg) {
    ActorRecord *target;
    ObjectPosition *target_pos;

    if (state->phase.s == 0) {
        ActorRecord *tracked_target = *state->target;
        if (tracked_target != 0) {
            if (screen_effect_target[0] != tracked_target) {
                play_sound_if_enabled(0x507);
                state->frames_left.s = 4;
                screen_effect_target[0] = *state->target;
            }
        } else {
            void *fallback_target;
            u16 phase;
            state->frames_left.s = 4;
            fallback_target = dungeon_actor_ring_anchor;
            phase = state->phase.u;
            screen_effect_target[0] = fallback_target;
            state->phase.u = phase + 1;
        }
        if (marker_arg->scale_x < 0x1000) {
            u16 next_scale = marker_arg->scale_y + 0x200;
            marker_arg->scale_y = next_scale;
            marker_arg->scale_x = next_scale;
            if (next_scale >= 0x1001) {
                marker_arg->scale_y = 0x1000;
                marker_arg->scale_x = 0x1000;
            }
        }
    } else {
        s16 frames_left = state->frames_left.s;
        if (frames_left != 0) {
            u16 scale = marker_arg->scale_y;
            u16 next_scale = (u16)((s32)scale - (s32)scale / frames_left);
            marker_arg->scale_y = next_scale;
            marker_arg->scale_x = next_scale;
        } else {
            marker_arg->scale_y = 0;
            marker_arg->scale_x = 0;
        }
    }

    {
        ActorRecord *tracked_target = *state->target;
        if (tracked_target == 0) {
            marker_arg->color.word = 0x808080;
        } else if (tracked_target == dungeon_actor_ring_anchor->unk_AC) {
            marker_arg->color.word = 0x101080;
        } else {
            marker_arg->color.word = 0x801010;
        }
    }
    target = screen_effect_target[0];
    target_pos = ((ObjectNodeHeader *)((u8 *)target - 0x20))->position;
    if (state->frames_left.s != 0) {
        position_arg->x.v = position_arg->x.v + (target_pos->x.v
            - position_arg->x.v) / state->frames_left.s;
        position_arg->y.v = position_arg->y.v + (target_pos->y.v
            - position_arg->y.v) / state->frames_left.s;
        position_arg->z.v = position_arg->z.v + (((s32)(target->ground_height
            - position_arg->z.w.i)) << 16) / state->frames_left.s;
        {
            s16 frames_left = state->frames_left.u - 1;
            state->frames_left.u = frames_left;
            if (frames_left == 0) {
                if (state->phase.s == 0) {
                    position_arg->x.w.i = (u16)target_pos->x.w.i;
                    position_arg->y.w.i = (u16)target_pos->y.w.i;
                    position_arg->z.w.i = (u16)target->ground_height;
                } else {
                    ((ObjectNodeHeader *)((u8 *)state - 0x20))->flags = ((ObjectNodeHeader *)((u8 *)state - 0x20))->flags | 0x8000;
                    g_dungeon_status.active_actor = 0;
                    object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
                }
            }
        }
    }
    marker_arg->angle_z = marker_arg->angle_z + 0x40;
    advance_sprite_animation_and_textures(marker_arg);
}
#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"

typedef struct SubA_800B4204 {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    s16 fA;
} SubA_800B4204;

typedef struct SubB_800B4204 {
    u8 pad0[6];
    u16 f6;
    u8 pad8[4];
    u32 fC;
    u16 f10;
    u8 pad12[2];
    u16 f14;
    u8 pad16[6];
    u16 f1C;
    u16 f1E;
} SubB_800B4204;

typedef struct Obj_800B4204 {
    u8 pad0[8];
    SubA_800B4204 *sub1;
    SpriteFrameState *sub2;
    void (*stateFn)(FamiliarMarkerWork *, ObjectPosition *, SpriteFrameState *);
    u8 pad14[0x20 - 0x14];
    void *owner;
} Obj_800B4204;

typedef struct EntityHdr {
    u8 pad[0x88];
    u16 f88;
} EntityHdr;

extern u8 menu_effect_sprite_entries[];
extern s16 camera_depth_target[5];

extern void *allocate_list_node();
extern s32 draw_linked_sprites_clipped();
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);

/* Creates and initializes a display object attached to the entity. */
void *create_familiar_selection_marker(EntityHdr **entity_ref) {
    Obj_800B4204 *object;
    SubA_800B4204 *transform;
    SpriteFrameState *sprite;
    FamiliarMarkerWork *owner_data;

    object = allocate_list_node(18, &scene_object_list_anchor.next);
    if (object != 0) {
        owner_data = (FamiliarMarkerWork *)((u8 *)object + 0x20);
        register_node(object, (void *)draw_linked_sprites_clipped);
        object->stateFn = update_familiar_selection_marker;

        transform = object->sub1;
        sprite = object->sub2;
        transform->f2 = ((u16)view_reference_entity.x.w.i);
        transform->f6 = ((u16)view_reference_entity.y.w.i);
        transform->fA = (*entity_ref)->f88;
        select_record_entry_and_value(sprite, menu_effect_sprite_entries, 0);

        {
            u32 color;
            u16 flags;

            color = 0x2c808080;
            sprite->scale_y = 256;
            sprite->scale_x = 256;
            sprite->tpage_abr = 32;
            flags = sprite->flags;
            sprite->color.word = color;
            sprite->depth_bias = 4;
            sprite->flags = flags | 0xC;
            owner_data->frames_left.s = 4;
            owner_data->target = entity_ref;

            g_dungeon_status.active_actor = object;
            select_nearby_target_and_initialize_slot(object, transform, 8, camera_depth_target[0]);
        }
    }

    return (void *)object;
}
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
extern u8 D_800E0000[];
extern u8 resident_globals_page[];

typedef struct Entity {
    u8 pad00[0x13];
    u8 kind;
    u8 pad14[8];
    u32 flags;
    u8 pad20[0x68];
    s16 height;
} Entity;

typedef struct Node {
    Entity *entity;
} Node;

typedef union WorkY {
    s32 whole;
    struct {
        u16 lo;
        s16 angle;
    } half;
} WorkY;

typedef struct Work {
    Node *node;
    s32 x;
    WorkY y;
    s16 state;
    s16 timer;
    u16 counter;
    s16 mode;
    s32 cur_x;
    s32 cur_y;
    s16 amp;
    s16 pad1e;
    s16 bias;
    u16 pad22;
    u16 phase;
    u8 pad26[6];
    s32 handle;
} Work;

typedef struct Render {
    void *primitive;
    u8 pad04[8];
    s32 flags;
    u8 pad10[8];
    s16 rot_x;
    s16 rot_y;
} Render;

typedef struct Out {
    u8 pad00[2];
    s16 x;
    u8 pad04[2];
    s16 y;
    s32 z;
} Out;

typedef struct GlobalObj {
    u8 pad00[0xAC];
    Entity *left;
    Entity *right;
} GlobalObj;


extern s32 rsin(s32, ...);
extern s32 rcos(s32, ...);
extern s32 get_special_table_data_index(s32 dataAddress);
struct S_800BA33C_0;
extern s32 is_selectable_menu_target(struct S_800BA33C_0 *object);
extern void advance_sprite_animation_and_textures();
extern void append_packed_action_record();
extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);

/* Updates entity selection, interpolates its position, and animates the rendered output. */
void update_item_target_marker(Work *work, Out *out, Render *render_arg)
{
    register Render *render;
    GameWork *controls;
    u8 *counter_base_2;
    s32 result;
    s32 height_step;
    s32 trig_value;
    u32 input;
    u8 *height_addr;
    Entity *entity;

    render = render_arg;
    controls = &g_game_work;

    {
        Node *node;
        s32 *target_pos;
        node = work->node;
        target_pos = *(s32 **)((u8 *)node->entity - 0x18);
        if (work->timer != 0) {
            work->cur_x += (target_pos[0] - work->cur_x) / work->timer;
            work->cur_y += (target_pos[1] - work->cur_y) / work->timer;
            if ((work->mode) != 2) {
                u8 *height_base;
                s32 current_height;
                trig_value = rsin(work->timer << 8);
                height_base = (u8 *)work->node;
                current_height = work->y.whole;
                entity = ((Node *)height_base)->entity;
                entity = (Entity *)(u32)entity->kind;
                entity = (Entity *)((u8 *)entity + (u32)entity_height_offsets);
                height_step = (target_pos[2] - ((s32)*(u8 *)entity << 16) - current_height) / (work->timer);
                height_step -= (trig_value * work->timer) << 6;
                work->y.whole += height_step;
                if (work->node->entity->flags & 0x80000) {
                    work->y.half.angle -= 0x80;
                }
            } else {
                work->y.whole += (((s32)work->node->entity->height << 16) - work->y.whole) / work->timer;
            }
        }

        if (--work->timer <= 0) {
            work->cur_x = target_pos[0];
            work->cur_y = target_pos[1];
            if (work->mode != 2) {
                u8 *height_base;
                s32 target_height;
                height_base = (u8 *)work->node;
                entity = ((Node *)height_base)->entity;
                height_addr = (u8 *)(u32)entity->kind;
                target_height = entity->height;
                height_addr += (u32)((u8 *)entity_height_offsets);
                height_base = (u8 *)(u32)*height_addr;
                target_height -= (s32)(u32)height_base;
                if (entity->flags & 0x40000) {
                    target_height -= 0x40;
                }
                work->y.half.angle = target_height;
                if (work->node->entity->flags & 0x80000) {
                    work->y.half.angle = target_height - 0x80;
                }
            } else {
                work->y.half.angle = work->node->entity->height;
            }
            work->timer = 0;
        }
    }

    if (work->state == 0) {
        if (work->timer == 0) {
            if ((((u32)controls->pressed_buttons) & 2) != 0) {
                u8 *status_page;
                s32 new_timer;
                GlobalObj *object;
                Entity *left;
                left = (*(GlobalObj **)((GlobalObj * *)(&dungeon_actor_ring_anchor)))->left;
                if (is_selectable_menu_target(left)) {
                    status_page = resident_globals_page;
                    if ((*(GlobalObj **)(status_page + 0x14A8))->left != work->node->entity) {
                        new_timer = 8;
                        object = *(GlobalObj **)((GlobalObj * *)(&dungeon_actor_ring_anchor));
                        work->timer = new_timer;
                        work->node = (Node *)&object->left;
                        if (work->mode == 2) {
                            ((Render *)render)->flags = 0x00101080;
                        }
                    }
                }
            }
            if ((((u32)controls->pressed_buttons) & 1) != 0) {
                u8 *status_page;
                s32 new_timer;
                GlobalObj *object;
                Entity *right;
                right = (*(GlobalObj **)((GlobalObj * *)(&dungeon_actor_ring_anchor)))->right;
                if (is_selectable_menu_target(right)) {
                    status_page = resident_globals_page;
                    if ((*(GlobalObj **)(status_page + 0x14A8))->right != work->node->entity) {
                        new_timer = 8;
                        object = *(GlobalObj **)((GlobalObj * *)(&dungeon_actor_ring_anchor));
                        work->timer = new_timer;
                        work->node = (Node *)&object->right;
                        if (work->mode == 2) {
                            ((Render *)render)->flags = 0x00801010;
                        }
                    }
                }
            }
        }

        input = ((u32)controls->pressed_buttons);
        if (input & 0x20) {
            if (work->mode == 0) {
                (g_dungeon_status.activity_counts.parts.pending_action_count)--;
            }
            {
                u8 *flags_page;
                u16 work_flags;
                work_flags = (*(u16 *)((u8 *)work + -2));
                flags_page = (u8 *)0x80080000;
                (*(u16 *)((u8 *)work + -2)) = work_flags | 0x8000;
                *(u32 *)(flags_page + 0x14A0) |= 0x8000;
            }
            return;
        }
        if (input & 0x40) {
            work->state = 1;
            if (work->mode == 0) {
                if (work->node->entity->kind == 0) {
                    s32 action;
                    s32 amount;
                    GlobalObj *object;
                    result = get_special_table_data_index(((Work *)work)->handle);
                    action = 0x48;
                    result = (s32)((u32)result << 16);
                    amount = result >> 16;
                    object = *(GlobalObj **)((GlobalObj * *)(&dungeon_actor_ring_anchor));
                    append_packed_action_record(object, action, amount, 0);
                } else {
                    s32 amount;
                    GlobalObj *object;
                    result = get_special_table_data_index((work->handle));
                    amount = (s16)result;
                    object = *(GlobalObj **)((GlobalObj * *)(&dungeon_actor_ring_anchor));
                    append_packed_action_record(object, 0x50,
                                  work->node->entity == object->right, amount);
                }
            }
        }
    } else {
        if (work->mode == 0) {
            Node *state_node;
            s32 count;
            Entity *target_entity;
            s32 *target_pos;
            count = 8;
            state_node = (*(Node **)((u8 *)work + 0));
            counter_base_2 = (u8 *)D_800E0000;
            target_entity = state_node->entity;
            target_pos = *(s32 **)((u8 *)target_entity - 0x18);
            select_nearby_target_and_initialize_slot((u8 *)target_entity - 0x20, target_pos, count,
                          *(s16 *)(counter_base_2 - 0x319A));
            result = dispatch_dungeon_category_action(work->node->entity, work->handle, 0x15, 0);
            if ((s16)result < 0) {
                return;
            }
            (g_dungeon_status.activity_counts.parts.pending_action_count)--;
        }
        {
            u8 *flags_page;
            u16 work_flags;
            work_flags = (*(u16 *)((u8 *)work + -2));
            flags_page = (u8 *)0x80080000;
            (*(u16 *)((u8 *)work + -2)) = work_flags | 0x8000;
            *(u32 *)(flags_page + 0x14A0) |= 0x8000;
        }
        return;
    }

    work->counter++;
    if (work->mode == 2) {
        render->rot_y += 0x40;
    } else {
        trig_value = rsin((s16)work->counter << 7);
        work->x += trig_value << 5;
    }
    if (work->mode == 0) {
        work->phase &= 0x1F;
        if ((s16)work->phase < 0x10) {
            render->rot_x += 0x80;
        }
        render->rot_x = ((render->rot_x + 0x400) & 0x7FF) - 0x400;
        work->phase++;
    }
    if (render->primitive != 0) {
        advance_sprite_animation_and_textures(render);
    }
    trig_value = rcos(controls->view.camera_rotation.parts.viewAngle);
    out->x = (trig_value * work->amp >> 11) + *(u16 *)((u8 *)&work->cur_x + 2);
    trig_value = rsin(controls->view.camera_rotation.parts.viewAngle);
    out->y = (trig_value * work->amp >> 11) + *(u16 *)((u8 *)&work->cur_y + 2);
    out->z = work->x + work->y.whole + (work->bias << 15);
    return;
}
#include "shared/object_node.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

typedef struct SubA_800B4914 {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
} SubA_800B4914;

typedef struct SubB_800B4914 {
    u8 pad0[6];
    s16 f6;
    void *f8;
    u32 fC;
    u8 pad10[4];
    u16 f14;
    u8 pad16[6];
    s16 f1C;
    s16 f1E;
} SubB_800B4914;

typedef struct Obj_800B4914 {
    u8 pad0[8];
    SubA_800B4914 *subA;
    SubB_800B4914 *subB;
    void *state;
} Obj_800B4914;

typedef struct Aux {
    void *f0;
    u8 pad4[6];
    s16 fA;
    u8 padC[2];
    s16 fE;
    u8 pad10[2];
    s16 f12;
    u8 pad14[2];
    u16 f16;
    u8 pad18[2];
    u16 f1A;
    u8 pad1C[0xC];
    void *f28;
    void *f2C;
} Aux;

typedef struct D_80083780_t {
    u8 pad0[2];
    u16 f2;
    u8 pad4[2];
    u16 f6;
    u8 pad8[2];
    u16 fA;
} D_80083780_t;

extern s32 has_enough_available_runtime_nodes(s32);
extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);
extern s32 lookup_item_category_mapped_value(u8, u8);
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void *func_800BA110();
extern void *func_800BA1D0();
extern void *func_800BA224();
extern void func_800BA2A0(void);
extern void func_800BA308(void);
struct S_800BA33C_0;
extern s32 is_selectable_menu_target(struct S_800BA33C_0 *object);
extern void build_owned_floating_number_widget(void *owner, s32 value_a, s32 value_b, s32 style, s16 compact, u16 flags);

extern s32 draw_linked_sprites_clipped();
extern u8 menu_effect_sprite_entries[];
struct Work;
struct Out;
struct Render;
extern void update_item_target_marker(struct Work *work, struct Out *out, struct Render *render_arg);
extern s16 camera_depth_target[5];
extern u8 D_800DF368[];


typedef struct S_800BA074_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800BA074_0;   /* current in create_item_target_selector */

typedef struct S_800BA074_1 {
    u8 pad_00[0x3D7C];
    u8 * unk_3D7C;
} S_800BA074_1;   /* page in create_item_target_selector */

typedef struct S_800BA074_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    s32 unk_B0;
} S_800BA074_2;   /* ((S_800BA074_1 *)page)->unk_3D7C in create_item_target_selector */

/* Creates three linked display objects for the selection and initializes their appearance. */
void *create_item_target_selector(u8 *selection_data) {
    Obj_800B4914 *objects[3];
    ObjectPosition *layout;
    Obj_800B4914 **object_slot;
    s32 part_index;
    u8 *global_page;
    s32 last_part;


    if (has_enough_available_runtime_nodes(3) == 0) {
        return 0;
    }

    part_index = 0;
    last_part = 2;
    layout = &view_reference_entity;
    global_page = (u8 *)0x800E0000;
    object_slot = objects;
    do {
        *object_slot = allocate_flagged_object_node(0x12);
        if (*object_slot != 0) {
            SubA_800B4914 *transform;
            SubB_800B4914 *sprite;

            (*object_slot)->state = update_item_target_marker;
            if (part_index == last_part) {
                register_node(objects[2], draw_linked_sprites_clipped);
            } else {
                Obj_800B4914 *object;
                void *state_def;
                object = *object_slot;
                state_def = project_sprite_chain;
                register_node(object, state_def);
            }
            transform = (*object_slot)->subA;
            transform->f2 = ((u16)layout->x.w.i);
            transform->f6 = ((u16)layout->y.w.i);
            sprite = (*object_slot)->subB;
            sprite->f1E = 0x1000;
            sprite->f1C = 0x1000;
            sprite->fC = 0x2C808080;
            sprite->f6 = 4;

            if (part_index == 0) {
                select_nearby_target_and_initialize_slot(objects[0], transform, 8, camera_depth_target[0]);
                sprite->f8 = (void *)lookup_item_category_mapped_value(selection_data[1], selection_data[0]);
            } else if (part_index == 1) {
                sprite->f8 = D_800DF368;
            } else {
                select_record_entry_and_value(sprite, menu_effect_sprite_entries, 0);
                sprite->f14 |= 0xC;
            }
            {
                Obj_800B4914 *object;
                Aux *part_state;

                object = *object_slot;
                part_state = (Aux *)((u8 *)object + 0x20);
                part_state->fA = ((u16)layout->z.w.i) - entity_height_offsets[0];
                ((S_800BA074_0 *)object)->unk_20 = &primary_actor_record;
                part_state->f12 = part_index;
                part_state->f16 = transform->f2;
                part_state->f1A = transform->f6;
                if (part_index != 0) {
                    part_state->f28 = objects[0];
                } else {
                    part_state->f2C = selection_data;
                }
                if (is_selectable_menu_target(((S_800BA074_2 *)(((S_800BA074_1 *)global_page)->unk_3D7C))->unk_AC) != 0) {
                    part_state->fE = 8;
                    part_state->f0 = ((S_800BA074_1 *)global_page)->unk_3D7C + 0xAC;
                    if (part_state->f12 == last_part) {
                        sprite->fC = 0x101080;
                    }
                } else if (is_selectable_menu_target(((S_800BA074_2 *)(((S_800BA074_1 *)global_page)->unk_3D7C))->unk_B0) != 0) {
                    part_state->fE = 8;
                    part_state->f0 = ((S_800BA074_1 *)global_page)->unk_3D7C + 0xB0;
                    if (part_state->f12 == last_part) {
                        sprite->fC = 0x801010;
                    }
                }
            }
        }

        part_index++;
        object_slot++;
    } while (part_index < 3);

    {
        g_dungeon_status.activity_counts.parts.pending_action_count += 1;
    }
    build_floating_number_widget(0, 0x27, 0x40, 0x209, 0, 0);
    build_owned_floating_number_widget(selection_data, 0x4C, 0x50, 0x200, 0, 2);
    return objects[0];
}
#include "common.h"


#ifndef NULL
#define NULL 0
#endif


typedef struct S_800BA33C_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x95];
    u8 unk_B5;
} S_800BA33C_0;   /* arg0 in is_selectable_menu_target */

/* Test flag 0x20000 for a valid object outside the excluded state. */
s32 is_selectable_menu_target(S_800BA33C_0 *object) {
    s32 code;
    if ((object == NULL) || ((object->unk_13 == 0x18) && (object->unk_B5 == 1))) {
        return 0;
    }
    if ((object->unk_1C & 0x20000)) {
        return 1;
    }
    return 0;
}
#include "common.h"

struct S_800BA414_1;
extern void draw_projected_quad_with_depth_bias(void *unused, struct S_800BA414_1 *position, void *owner_data, s16 depth_bias);

/* Initialize scratchpad quad coordinates and process each linked node. */
s32 draw_linked_quad_chain(void *node_payload, s32 node_value, u8 *node_data) {
    s16 *scratch = (s16 *)0x1F800000;
    register u8 *next_ptr;
    s32 next_value;
    s32 result;

    scratch[0x46] = 0;
    scratch[0x42] = 0;
    scratch[0x3E] = 0;
    scratch[0x3A] = 0;
    scratch[0x40] = -31;
    scratch[0x38] = -31;
    scratch[0x44] = 31;
    scratch[0x3C] = 31;
    scratch[0x3D] = -31;
    scratch[0x39] = -31;
    scratch[0x45] = 31;
    scratch[0x41] = 31;

    for (;;) {
        draw_projected_quad_with_depth_bias(node_payload, node_value, node_data, *(s16 *)(node_data + 6));
        next_ptr = *(u8 **)((u8 *)node_payload - 8);
        node_payload = next_ptr + 32;
        if (next_ptr == 0) {
            break;
        }
        node_value = *(s32 *)(next_ptr + 8);
        next_ptr = *(u8 **)(next_ptr + 12);
        node_data = next_ptr;
    }
    result = 0;
    return result;
}
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_800BA414_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x9C];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u32 unk_100;
    u16 unk_104;
} S_800BA414_0;   /* scratch in draw_projected_quad_with_depth_bias */

typedef struct S_800BA414_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BA414_1;   /* arg1 in draw_projected_quad_with_depth_bias */

   /* state in draw_projected_quad_with_depth_bias */

typedef struct S_800BA414_3 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
} S_800BA414_3;   /* prim in draw_projected_quad_with_depth_bias */

typedef struct S_800BA414_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BA414_4;   /* owner in draw_projected_quad_with_depth_bias */

   /* *global in draw_projected_quad_with_depth_bias */


extern void *CompMatrix(void *, void *, void *);
extern void PushMatrix();
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern u32 RotAverage4(void *, void *, void *, void *, void *, void *,
                         void *, void *, void *, void *);
extern void *RotMatrix(void *, void *);
extern void AddPrim(void *, void *, ...);
extern void SetPolyF4(void *);
extern void SetDrawMode(void *, s32, s32, s32, s32);

/* Project a quad and enqueue it with its draw mode when depth and screen bounds allow. */
void draw_projected_quad_with_depth_bias(void *unused, S_800BA414_1 *position, void *owner_data, s16 depth_bias)
{
    u8 *scratch;
    u8 *prim;
    u8 **state_slot;
    S_800BA414_4 *owner;
    s16 depth_offset;
    u8 *rotation;
    u8 *local_matrix;
    u8 *view_matrix;
    u8 *combined_matrix;
    u8 *vertex_0;
    u8 *vertex_1;
    u8 *vertex_2;
    u8 *mode_ptr;
    u8 *mode_zero;
    u8 *vertex_3;
    u8 *transform_flags;
    u8 *depth_cue;
    u8 *state;
    u8 *quad;
    u8 *draw_mode;
    u32 ot_index;
    u32 clip_test;
    s32 first_pair_visible;
    s32 first_three_visible;
    s32 third_visible;
    s32 corner_visible;

    (void)unused;
    state = *(u8 **)((s8 *)(&g_game_work));
    scratch = (u8 *)0x1F800000;
    owner = owner_data;
    depth_offset = depth_bias;
    ((S_800BA414_0 *)scratch)->unk_20 = state + 0xB0;
    ((S_800BA414_0 *)scratch)->unk_E4 = position->unk_02;
    ((S_800BA414_0 *)scratch)->unk_E8 = position->unk_06;
    ((S_800BA414_0 *)scratch)->unk_EC = position->unk_0A;
    prim = ((GpuContext *)state)->packetCursor;
    state_slot = (u8 **)((s8 *)(&g_game_work));

    PushMatrix();
    rotation = scratch;
    rotation = (u8 *)((u32)rotation | 0x100);
    local_matrix = scratch;
    local_matrix = (u8 *)((u32)local_matrix | 0xD0);
    ((S_800BA414_0 *)scratch)->unk_100 = 0;
    ((S_800BA414_0 *)scratch)->unk_104 = 0;
    RotMatrix(rotation, local_matrix);
    view_matrix = scratch;
    view_matrix = (u8 *)((u32)view_matrix | 0x11C);
    ReadRotMatrix(view_matrix);
    view_matrix = scratch;
    view_matrix = (u8 *)((u32)view_matrix | 0x11C);
    local_matrix = scratch;
    local_matrix = (u8 *)((u32)local_matrix | 0xD0);
    combined_matrix = scratch;
    combined_matrix = (u8 *)((u32)combined_matrix | 0x50);
    CompMatrix(view_matrix, local_matrix, combined_matrix);
    combined_matrix = scratch;
    combined_matrix = (u8 *)((u32)combined_matrix | 0x50);
    SetTransMatrix(combined_matrix);
    combined_matrix = scratch;
    combined_matrix = (u8 *)((u32)combined_matrix | 0x50);
    SetRotMatrix(combined_matrix);

    depth_cue = scratch;
    depth_cue = (u8 *)((u32)depth_cue | 0x90);
    transform_flags = scratch;
    transform_flags = (u8 *)((u32)transform_flags | 0x94);
    vertex_0 = scratch;
    vertex_0 = (u8 *)((u32)vertex_0 | 0x70);
    vertex_1 = scratch;
    vertex_1 = (u8 *)((u32)vertex_1 | 0x78);
    vertex_2 = scratch;
    vertex_2 = (u8 *)((u32)vertex_2 | 0x80);
    vertex_3 = scratch;
    vertex_3 = (u8 *)((u32)vertex_3 | 0x88);
    ot_index = (RotAverage4(vertex_0, vertex_1, vertex_2, vertex_3,
                              prim + 8, prim + 0xC, prim + 0x10, prim + 0x14,
                              depth_cue, transform_flags) -
                depth_offset) - 8;
    ((S_800BA414_0 *)scratch)->unk_C0 = ot_index;

    if (ot_index < 0x1E0U) {
        first_pair_visible = 0;
        clip_test = ((S_800BA414_3 *)prim)->unk_08;
        clip_test = (u16)(clip_test + 0x20);
        if (clip_test < 0x181U) {
            clip_test = ((S_800BA414_3 *)prim)->unk_0A;
            clip_test = (u16)(clip_test + 0x20);
            first_pair_visible = clip_test < 0x121U;
        }
        corner_visible = 0;
        clip_test = ((S_800BA414_3 *)prim)->unk_0C;
        clip_test = (u16)(clip_test + 0x20);
        if (clip_test < 0x181U) {
            clip_test = ((S_800BA414_3 *)prim)->unk_0E;
            clip_test = (u16)(clip_test + 0x20);
            corner_visible = clip_test < 0x121U;
        }
        first_three_visible = 0;
        first_pair_visible |= corner_visible;
        clip_test = ((S_800BA414_3 *)prim)->unk_10;
        clip_test = (u16)(clip_test + 0x20);
        if (clip_test < 0x181U) {
            clip_test = ((S_800BA414_3 *)prim)->unk_12;
            clip_test = (u16)(clip_test + 0x20);
            first_three_visible = clip_test < 0x121U;
        }
        corner_visible = 0;
        third_visible = first_three_visible;
        first_three_visible = first_pair_visible | third_visible;
        clip_test = ((S_800BA414_3 *)prim)->unk_14;
        clip_test = (u16)(clip_test + 0x20);
        if (clip_test < 0x181U) {
            clip_test = ((S_800BA414_3 *)prim)->unk_16;
            clip_test = (u16)(clip_test + 0x20);
            corner_visible = clip_test < 0x121U;
        }
        clip_test = first_three_visible | corner_visible;

        if (clip_test != 0) {
            ((S_800BA414_3 *)prim)->unk_04.at00.v = owner->unk_0C;
            SetPolyF4(prim);
            quad = prim;
            draw_mode = prim + 0x18;
            ((S_800BA414_3 *)prim)->unk_04.at03.v |= 2;
            prim += 0x24;
            AddPrim(((S_800BA414_0 *)scratch)->unk_20 +
                          ((S_800BA414_0 *)scratch)->unk_C0 * 4,
                          quad);
            mode_ptr = draw_mode;
            mode_zero = 0;
            SetDrawMode(mode_ptr, (s32)mode_zero, (s32)mode_zero, 0x20, 0);
            AddPrim(((S_800BA414_0 *)scratch)->unk_20 +
                          ((S_800BA414_0 *)scratch)->unk_C0 * 4,
                          draw_mode);
        }
    }

    ((GpuContext *)(*state_slot))->packetCursor = prim;
    PopMatrix();
}
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_800BA6B8_0_pre {
    u16 unk_00;
} S_800BA6B8_0_pre;   /* the 0x2 bytes before arg0 in update_pulsing_sprite_color, addressed as arg0[-1] */

typedef struct S_800BA6B8_0 {
    u8 pad_00[0x30];
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
} S_800BA6B8_0;   /* arg0 in update_pulsing_sprite_color */

typedef struct S_800BA6B8_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800BA6B8_1;   /* arg2 in update_pulsing_sprite_color */


extern s32 rsin(s32, ...);
extern u16 D_800DF37C;

/* Updates enabled output channels with a shared value and sets flags when active. */
void update_pulsing_sprite_color(void *channel_config, void *unused, void *output) {
    s8 channel_value;

    if (D_800DF37C != 0) {
        (*(u16 *)((u8 *)channel_config + -2)) = (u16) (((S_800BA6B8_0_pre *)channel_config)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    channel_value = (rsin(g_game_work.unk_004 << 8) >> 7) - 0x80;
    if (((S_800BA6B8_0 *)channel_config)->unk_30 != 0) {
        ((S_800BA6B8_1 *)output)->unk_0C = channel_value;
    }
    if (((S_800BA6B8_0 *)channel_config)->unk_31 != 0) {
        ((S_800BA6B8_1 *)output)->unk_0D = channel_value;
    }
    if (((S_800BA6B8_0 *)channel_config)->unk_32 != 0) {
        ((S_800BA6B8_1 *)output)->unk_0E = channel_value;
    }
}
#include "shared/object_node.h"
#include "common.h"

/* Externals (never defined here -- the overlay gate's linker resolves them). */
extern s32 draw_linked_quad_chain(void *node_payload, s32 node_value, u8 *node_data);
extern void update_pulsing_sprite_color(void *channel_config, void *unused, void *output);

typedef struct S_func_800BA764_0 {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x4];
    void (*unk_10)(void *, void *, void *);
    u8 pad_14[0x3C];
    s32 unk_50;
} S_func_800BA764_0;

typedef struct S_func_800BA764_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_800BA764_1;

/* Creates an object at the tile center with the supplied Z coordinate and user data. */
void *create_pulsing_tile_sprite(u16 tile_x, u16 tile_y, s16 coord_z, s32 user_data) {
    S_func_800BA764_0 *object;
    S_func_800BA764_1 *position;
    u32 tile_x_u32;
    u32 tile_y_u32;

    object = allocate_flagged_object_node(0x202);
    if (object != 0) {
        object->unk_10 = update_pulsing_sprite_color;
        register_node(object, draw_linked_quad_chain);
        position = object->unk_08;
        tile_x_u32 = (u32)tile_x & 0xFFFFU;
        position->unk_02 = (tile_x_u32 * 64) + 0x20;
        tile_y_u32 = (u32)tile_y & 0xFFFFU;
        position->unk_06 = (tile_y_u32 * 64) + 0x20;
        position->unk_0A = coord_z;
        object->unk_50 = user_data;
    }
    return object;
}
#include "common.h"
#include "shared/def_table.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

typedef struct S_800BA810_0 {
    void * unk_00;
} S_800BA810_0;   /* arg0 in update_selection_tile_markers; pointer addresses record offset 0x18 */

typedef struct S_800BA810_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800BA810_1;

typedef struct S_800BA810_2 {
    void * unk_00;
} S_800BA810_2;   /* Pointer addresses record offset 0x18. */

typedef struct S_800BA810_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800BA810_3;


/* cfail-repair: tf7-phase1-cache-v3 */
extern void update_pulsing_sprite_color(void *channel_config, void *unused, void *output);
void mark_active_nodes_by_callback(s32 *);                  /* extern */
typedef struct S_8006DE24_Entry {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} S_8006DE24_Entry;
extern void * create_pulsing_tile_sprite(u16 tile_x, u16 tile_y, s16 coord_z, s32 user_data);
s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);                   /* extern */
typedef struct S_800B50B0_Entity {
    u8 pad00[0x13];
    u8 kind13;
    u8 pad14[0x16];
    u16 angle2a;
    u8 pad2c[0x1c];
    u8 kind48;
    u8 pad49[0x17];
    void *child60;
    u8 pad64[0x24];
    s16 height88;
} S_800B50B0_Entity;
extern S_800B50B0_Entity *menu_effect_cached_actor;
extern u16 D_800DF378;
extern u16 D_800DF37A;
extern u8 D_800DF380[];

/* Updates marked dungeon tiles for the selected entity, mode, and facing. */
void update_selection_tile_markers(S_800B50B0_Entity *entity, s32 selection) {
    s16 surface_height;
    s32 height;
    s16 forward_height;
    s16 adjacent_height;
    s16 range_height;
    s32 *tile_list;
    register s32 direction;
    s32 mode;
    s32 entry_value;
    s16 mode_index;
    s32 forward_steps;
    s32 adjacent_steps;
    u32 tile_z;
    u32 tile_x;
    u8 entry_id;
    u8 entry_type;
    u16 angle;
    void *child;
    S_800BA810_3 *child_position;
    S_800BA810_1 *position;

    if (entity == NULL) {
        menu_effect_cached_actor = NULL;
        mark_active_nodes_by_callback(update_pulsing_sprite_color);
        return;
    }
    tile_list = update_pulsing_sprite_color;
    if (menu_effect_cached_actor != entity || D_800DF37A != (s16) entity->angle2a || D_800DF378 != (selection & 0xFFFF)) {
        angle = entity->angle2a;
        menu_effect_cached_actor = entity;
        D_800DF378 = selection;
        D_800DF37A = angle;
        mark_active_nodes_by_callback(update_pulsing_sprite_color);
        direction = (entity->angle2a >> 9) & 7;
        mode = selection & 0x3FFF;
        position = ((S_800BA810_0 *)((u8 *)entity - 0x18))->unk_00;
        height = entity->height88;
        tile_x = (u16) position->unk_02 >> 6;
        tile_z = (u16) position->unk_06 >> 6;
        mode_index = mode;
        if (mode_index == 8) {
            forward_steps = 1;
            if ((entity->kind13 == 0x16) && (entity->kind48 == 0xF)) {
                forward_steps = 0xA;
            }
            if (forward_steps > 0) {
                do {
                    forward_height = height - 0x20;
                    tile_x += (s16) dir_step_x[direction];
                    tile_z += (s16) dir_step_y[direction];
                    surface_height = sample_terrain_surface_height(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_z << 6) + 0x20) & 0xFFE0,
                        forward_height);
                    height = surface_height;
                    if (height >= 0x201) {
                        break;
                    }
                    create_pulsing_tile_sprite(tile_x & 0xFFFF, tile_z & 0xFFFF, height, 0xFF);
                    forward_steps -= 1;
                } while (forward_steps > 0);
            } else {
                return;
            }
            return;
        }
        if (mode_index == 11) {
            adjacent_steps = 1;
            do {
                adjacent_height = height - 0x20;
                tile_x += (s16) dir_step_x[direction];
                tile_z += (s16) dir_step_y[direction];
                surface_height = sample_terrain_surface_height(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_z << 6) + 0x20) & 0xFFE0,
                    adjacent_height);
                height = surface_height;
                if (height >= 0x201) {
                    break;
                }
                create_pulsing_tile_sprite(tile_x & 0xFFFF, tile_z & 0xFFFF, height, 0xFF00);
                adjacent_steps -= 1;
            } while (adjacent_steps > 0);
            return;
        }
        if (mode_index == 12) {
            create_pulsing_tile_sprite(tile_x & 0xFFFF, tile_z & 0xFFFF, height, 0xFFFF);
            return;
        }
        if ((u32) (mode - 1) >= 3U) {
            return;
        }
        entry_value = (mode_index - 1) * 3;
        entry_id = *((u8 *) entity + entry_value + 8);
        entry_type = item_action_definitions[entry_id].kind;
        if (entry_type == 1) {
            forward_steps = D_800DF380[entry_id] & 0x1F;
            if (forward_steps > 0) {
                do {
                    range_height = height - 0x20;
                    tile_x += (s16) dir_step_x[direction];
                    tile_z += (s16) dir_step_y[direction];
                    surface_height = sample_terrain_surface_height(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_z << 6) + 0x20) & 0xFFE0,
                        range_height);
                    height = surface_height;
                    if (height >= 0x201) {
                        break;
                    }
                    create_pulsing_tile_sprite(tile_x & 0xFFFF, tile_z & 0xFFFF, height, 0xFF);
                    forward_steps -= 1;
                } while (forward_steps > 0);
            }
        } else if (entry_type == 2) {
            child = entity->child60;
            if (child != NULL) {
                child_position = ((S_800BA810_2 *)((u8 *)child - 0x18))->unk_00;
                create_pulsing_tile_sprite((u16) child_position->unk_02 >> 6, (u16) child_position->unk_06 >> 6,
                    ((S_800B50B0_Entity *)child)->height88, 0xFF);
            }
        }
    }
}
/* Warning: struct S_8006DE24_Entry is not defined (only forward-declared) */
#include "common.h"
#include "shared/game_work.h"


typedef struct DungeonRoot DungeonRoot;
struct DungeonRoot {
    u8 pad[0x8D0];
    s32 cursor;
};

typedef struct DungeonObject DungeonObject;
struct DungeonObject {
    void *state;
    u8 pad04[0x0A];
    s16 coord;
    u8 active;
    u8 count;
    s8 level;
};

typedef struct Scratch_800B5448 Scratch_800B5448;

typedef struct S_800BABA8_0_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800BABA8_0_pre;   /* the 0x4 bytes before dst in draw_particle_effect_primitives, addressed as dst[-1] */

typedef struct S_800BABA8_0 {
    s8 unk_00;
    u8 pad_01[0xC];
    s8 unk_0D;
    s8 unk_0E;
    s8 unk_0F;
    u8 pad_10[0x5];
    s8 unk_15;
    s8 unk_16;
    s8 unk_17;
} S_800BABA8_0;   /* dst in draw_particle_effect_primitives */

typedef struct S_800BABA8_1 {
    u8 pad_00[0x8D0];
    s32 unk_8D0;
} S_800BABA8_1;   /* *(DungeonRoot **)global_field in draw_particle_effect_primitives */

struct Scratch_800B5448 {
    u16 values[3];
    u8 pad06[0x1A];
    u8 *base;
    u8 pad24[0x4C];
    u16 x70;
    u16 y72;
    u16 z74;
    u8 pad76[2];
    u16 x78;
    u16 y7A;
    u16 z7C;
    u8 pad7E[0x42];
    s32 length;
};


extern s32 rsin(s32, ...);
extern s32 rcos(s32, ...);
extern s32 RotTransPers(void *, void *, ...);
extern void AddPrim(void *, void *, ...);
extern void SetDrawMode(void *, s32, s32, s32, s32);
extern s16 func_80069EF8(void);

/* Advances particle levels and emits colored effect primitives into the dungeon display list. */
s32 draw_particle_effect_primitives(DungeonObject *object, u16 *position) {
    DungeonRoot *root =
        *(DungeonRoot **)((u8 *)(&g_game_work));
    GameWork *root_slot = &g_game_work;
    s32 packet_cursor = root->cursor;
    Scratch_800B5448 *scratch;
    s16 particle = 0;
    u8 *scratch_90 = (u8 *)0x1F800090;
    u8 *scratch_94;
    void *packet;

    object->count = 0;
    scratch = (Scratch_800B5448 *)0x1F800000;
    scratch->base = ((u8 *)root_slot->draw_buffer) + 0xB0;
    scratch->values[0] = position[1];
    scratch_94 = (u8 *)scratch;
    scratch->values[1] = position[3];
    scratch_94 = (u8 *)((u32)scratch_94 | 0x94);
    scratch->values[2] = position[5];
    do {
        {
            DungeonObject *level_entry = (DungeonObject *)((u8 *)object + (s16)particle);
            level_entry->level += 4;
            if ((s8)level_entry->level >= 48) {
                if (object->active != 0) {
                    level_entry->level = 48;
                    continue;
                }
                level_entry->level = 0;
            }
        }
        {
            s32 particle_index = particle;
            (*(s32 *)((u8 *)((void *)(packet_cursor + 7)) + -3)) = 0;
            (*(s32 *)((u8 *)((void *)(packet_cursor + 7)) + 5)) = 0;
            scratch->x70 = scratch->values[0] +
                ((rcos((particle_index + (object->coord << 6)) << 7) << 4) >> 11);
            scratch->x78 = scratch->x70;
            scratch->y72 = scratch->values[1] +
                ((rsin((particle_index + (object->coord << 6)) << 7) << 4) >> 11);
            scratch->y7A = scratch->y72;
            scratch->z74 = scratch->values[2] -
                *(s8 *)((u8 *)object + particle_index + 0x12) * 2;
            scratch->z7C = scratch->z74 + 64;

            {
                s16 intensity = func_80069EF8();
                s8 particle_level = *(s8 *)((u8 *)object + particle_index + 0x12);
                if (particle_level >= 33) {
                    intensity = intensity / (particle_level - 32);
                } else if (particle_level < 16) {
                    intensity = intensity / (16 - particle_level);
                }
                ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_0D = (*(s32 *)((u8 *)object->state + 0x14) & 1)
                    ? intensity : 0;
                ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_15 =
                    ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_0D;
                ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_0E = (*(s32 *)((u8 *)object->state + 0x14) & 4)
                    ? intensity : 0;
                ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_16 =
                    ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_0E;
                ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_0F = (*(s32 *)((u8 *)object->state + 0x14) & 2)
                    ? intensity : 0;
                ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_17 =
                    ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_0F;
            }

            scratch->length = RotTransPers(&scratch->x70, (void *)(packet_cursor + 8),
                scratch_90, scratch_94);
            (*(s32 *)((u8 *)((void *)(packet_cursor + 7)) + 9)) = (*(s32 *)((u8 *)((void *)(packet_cursor + 7)) + 1));
            (*(u16 *)((u8 *)((void *)(packet_cursor + 7)) + 9)) += 4;
            scratch->length += RotTransPers(&scratch->x78, (void *)(packet_cursor + 24),
                scratch_90, scratch_94);
            (*(s32 *)((u8 *)((void *)(packet_cursor + 7)) + 25)) = (*(s32 *)((u8 *)((void *)(packet_cursor + 7)) + 17));
            (*(u16 *)((u8 *)((void *)(packet_cursor + 7)) + 25)) += 2;
            scratch->length >>= 1;
            ((S_800BABA8_0_pre *)((void *)(packet_cursor + 7)))[-1].unk_00 = 8;
            ((S_800BABA8_0 *)((void *)(packet_cursor + 7)))->unk_00 = 58;
            packet = (void *)((s8 *)((void *)((s8 *)((void *)(packet_cursor + 7)) + 36)) + 12);
            AddPrim((void *)(scratch->base + scratch->length * 4),
                (void *)packet_cursor);
            packet_cursor += 36;
            SetDrawMode((void *)packet_cursor, 0, 0, 96, 0);
            AddPrim((void *)(scratch->base + scratch->length * 4),
                (void *)packet_cursor);
            {
                u8 drawn_count = object->count;
                packet_cursor += 12;
                object->count = drawn_count + 1;
            }
        }
    } while ((particle = particle + 1) < 32);
    ((S_800BABA8_1 *)(root_slot->draw_buffer))->unk_8D0 = packet_cursor;
    {
        s32 result = 0;
        return result;
    }
}
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

s32 rand();                                /* extern */
struct DungeonObject;
extern s32 draw_particle_effect_primitives(struct DungeonObject *object, u16 *position);


typedef struct S_800BAF04_0_pre {
    u16 unk_00;
} S_800BAF04_0_pre;   /* the 0x2 bytes before arg0 in advance_particle_effect_state, addressed as arg0[-1] */

typedef struct S_800BAF04_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    s8 unk_10;
    u8 unk_11;
    u8 pad_12[0x20];
    u8 unk_32;
} S_800BAF04_0;   /* arg0 in advance_particle_effect_state */

typedef struct S_800BAF04_1 {
    u8 pad_00[0x12];
    s8 unk_12;
} S_800BAF04_1;

/* Initializes random values, advances counters, and flags the object when inactive. */
void advance_particle_effect_state(void *object) {
    s16 next_index;
    s16 state;
    s16 sample_index;
    u16 cycle_tick;
    u8 ramp_step;

    state = ((S_800BAF04_0 *)object)->unk_0A;
    if (state != 0) {
        if (state != 1) {
            return;
        }
    } else {
        sample_index = 0;
        do {
            ((S_800BAF04_1 *)((object + sample_index)))->unk_12 = (s8) (rand() & 0x1F);
            next_index = sample_index + 1;
            sample_index = next_index;
        } while (next_index < 0x40);
        ((S_800BAF04_0 *)object)->unk_0E = 0U;
        ((S_800BAF04_0 *)object)->unk_10 = 0;
        ((S_800BAF04_0 *)object)->unk_32 = 0U;
        ((S_800BAF04_0 *)object)->unk_11 = 1U;
        register_node(object - 0x20, draw_particle_effect_primitives);
        ((S_800BAF04_0 *)object)->unk_0A = (s16) ((u16) ((S_800BAF04_0 *)object)->unk_0A + 1);
    }
    cycle_tick = ((S_800BAF04_0 *)object)->unk_0E + 1;
    ((S_800BAF04_0 *)object)->unk_0E = cycle_tick;
    if ((s16) cycle_tick >= 0x11) {
        ((S_800BAF04_0 *)object)->unk_0E = 0U;
    }
    ramp_step = ((S_800BAF04_0 *)object)->unk_32 + 1;
    ((S_800BAF04_0 *)object)->unk_32 = ramp_step;
    if ((s8) ramp_step >= 0x21) {
        ((S_800BAF04_0 *)object)->unk_32 = 0x20U;
        ((S_800BAF04_0 *)object)->unk_10 = 1;
    }
    if (((S_800BAF04_0 *)object)->unk_11 == 0) {
        ((S_800BAF04_0_pre *)object)[-1].unk_00 = (u16) (((S_800BAF04_0_pre *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "common.h"

typedef struct S_800BB044_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    void (*unk_10)(void *);
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x8];
    u16 unk_2C;
} S_800BB044_0;

typedef struct S_800BB044_1 {
    s32 unk_00;
    u8 pad_04[0x3E];
    u16 unk_42;
} S_800BB044_1;   /* arg0 in create_actor_linked_effect; pointer addresses record offset 0x18 */


extern void *allocate_list_node();
extern s32 play_sound_if_enabled(s32 query_value);
extern void advance_particle_effect_state(void *object);

/* Creates an object linked to the source data and copies its record fields. */
void create_actor_linked_effect(void *sourceData) {
    S_800BB044_0 *createdObject;

    createdObject = allocate_list_node(0x202, sourceData - 0x20);
    if (createdObject != 0) {
        createdObject->unk_10 = advance_particle_effect_state;
        createdObject->unk_20 = sourceData;
        createdObject->unk_08 = (s32) ((S_800BB044_1 *)((u8 *)sourceData - 0x18))->unk_00;
        createdObject->unk_2C = (u16) ((S_800BB044_1 *)((u8 *)sourceData - 0x18))->unk_42;
        play_sound_if_enabled(0x703);
    }
}
#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[0x10];
    s16 unk10;
    s16 unk12;
    u8 pad14[6];
    u16 unk1A;
    s16 unk1C;
    u16 unk1E;
    s16 unk20;
} Func800B5948Object;

extern void update_map_cell_flags_with_item_limit(s16, s16, s32);
extern void clear_slot_and_detach_entity(s16);

/* Updates the object's countdown and triggers an effect when it expires. */
void update_timed_tile_effect(Func800B5948Object *object, s32 unused, Func800B5948Object *related_object) {
    u16 ticks_left;

    if (g_dungeon_status.flags & 0x10) {
        ticks_left = object->unk1E - 1;
        object->unk1E = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            if (object->unk1C == 1) {
                update_map_cell_flags_with_item_limit(object->unk10, object->unk12, 2);
            } else {
                update_map_cell_flags_with_item_limit(object->unk10, object->unk12, 0x10);
            }
            clear_slot_and_detach_entity(object->unk20);
            return;
        }
    }
    related_object->unk1A = related_object->unk1A + 0x40;
}
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
typedef struct
{
    void *next;
    u8 pad04[0x0D - 4];
    u8 field0D;
    u8 pad0E[0x14 - 0x0E];
    s16 state;
    s16 count;
    u16 flags;
    s16 phase;
}
S_800BB14C;
typedef struct
{
    u8 pad00[0x0C];
    s8 valueC;
    s8 valueD;
    s8 valueE;
    u8 pad0F[0x1E - 0x0F];
    u16 amount;
}
S_800BB14C_TARGET;
/* Animates the target amount and selected channels, then marks the effect finished after fading. */
void update_pulsing_color_fade(void *effect_data, register S_800BB14C *effect, S_800BB14C_TARGET *target)
{
    s16 state;
    effect = (S_800BB14C *) effect_data;
    state = effect->state;
    switch (state) {
    case 0:
    {
        s16 phase = effect->phase;
        u16 amount = target->amount + (phase * 0x10);
        target->amount = amount;
        if (amount < 0x4001U) {
            target->amount = 0x4000;
            effect->state = ((s16) effect->state) + 1;
        }
    }
    case 1:
        if ((((S_800BB14C_TARGET *) effect->next)->amount & 0x8000) != 0) {
            effect->count = 4;
            effect->state = 2;
        }
        break;
    case 2:
    {
        s16 fade_ticks = effect->count;
        if (fade_ticks != 0) {
            u16 amount = target->amount;
            target->amount = amount - (((s32) amount) / fade_ticks);
        }
    }
        {
            s16 fade_ticks = ((u16) effect->count) - 1;
            effect->count = fade_ticks;
            if (fade_ticks < 0) {
                u16 header_flags = ((u16 *) effect)[-1];
                ((u16 *) effect)[-1] = header_flags | NODE_REMOVE;
                object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
                return;
            }
        }
        break;
    }
    {
        u16 phase;
        s8 pulse_value;
        u8 pulse_step;
        phase = effect->phase;
        phase += 1;
        pulse_value = (effect->field0D - 4) & 0xBF;
        do {
            effect->phase = phase;
        }
        while (0);
        effect->field0D = pulse_value;
        pulse_step = effect->phase;
        pulse_step &= 0x1F;
        if ((phase & 0x20) != 0) {
            pulse_value = 0x30 - pulse_step;
        }
        else {
            pulse_value = pulse_step + 0x10;
        }
        if (effect->flags & 1) {
            target->valueC = pulse_value;
        }
        if (effect->flags & 2) {
            target->valueD = pulse_value;
        }
        if (effect->flags & 4) {
            target->valueE = pulse_value;
        }
    }

    return;
}
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

   /* state in draw_content_or_rect */

typedef struct S_800BB2E4_1 {
    u16 unk_00;
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u16 unk_04;
    u16 unk_06;
} S_800BB2E4_1;   /* arg2_r in draw_content_or_rect */

typedef struct S_800BB2E4_2 {
    u8 pad_00[0x3];
    s8 unk_03;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_0C;   /* overlapping accesses */
} S_800BB2E4_2;   /* packet in draw_content_or_rect */


typedef struct {
    s16 x;
    s16 y;
} CoordPair;

extern void AddPrim(void *, void *, ...);
extern void SetDrawArea(void *, void *);
extern void func_80067EF4(void *, s32, s32, ...);
struct Position;
struct Position;
extern void draw_transformed_sprite_with_clip_rect(s32 sprite, struct Position *clip_rect, struct Position *screen_pos, s32 clear_bg, s16 draw_flags);

extern u8 upper_draw_context[16];


/* Queues a line or filled rectangle with optional content and drawing state commands. */
void draw_content_or_rect(s32 *line_start, s32 *line_end, u8 *rect, s16 fill, s32 content_id)
{
    CoordPair bottom_center;
    u8 **state_addr;
    u8 *state;
    u8 *buf;
    u8 *ordering_table;
    u8 *packet;
    u8 *primitive;
    s32 y;
    s16 odd;

    state_addr = (u8 **)((u8 *)(&g_game_work));
    state = *(u8 **)((u8 *)(&g_game_work));
    ordering_table = state + 0x8B0;
    odd = state != upper_draw_context;

    if (content_id != 0) {
        primitive = ((GpuContext *)state)->packetCursor;
        ((GpuContext *)state)->packetCursor = primitive + 0xC;
        func_80067EF4(primitive, 0, 0);
        AddPrim(ordering_table, primitive);

        bottom_center.x = ((S_800BB2E4_1 *)rect)->unk_00 + (s16)((S_800BB2E4_1 *)rect)->unk_04 / 2;
        bottom_center.y = ((S_800BB2E4_1 *)rect)->unk_02.u + ((S_800BB2E4_1 *)rect)->unk_06;
        draw_transformed_sprite_with_clip_rect(content_id, rect, &bottom_center, 0, 0);
        buf = *(u8 **)((u8 *)(&g_game_work));
        primitive = ((GpuContext *)buf)->packetCursor;
        ((GpuContext *)buf)->packetCursor = primitive + 0xC;
        func_80067EF4(primitive, 1, 0);
        AddPrim(ordering_table, primitive);
    } else if (fill == 0) {
        packet = ((GpuContext *)state)->packetCursor;
        ((GpuContext *)state)->packetCursor = packet + 0x10;
        ((S_800BB2E4_2 *)packet)->unk_08.at00.v = *line_start;
        ((S_800BB2E4_2 *)packet)->unk_0C.at00.v = *line_end;
        if (odd) {
            ((S_800BB2E4_2 *)packet)->unk_08.at02.v -= 0xE0;
            ((S_800BB2E4_2 *)packet)->unk_0C.at02.v -= 0xE0;
        }
        ((S_800BB2E4_2 *)packet)->unk_03 = 3;
        ((S_800BB2E4_2 *)packet)->unk_04.at00.v = 0;
        ((S_800BB2E4_2 *)packet)->unk_04.at03.v = 0x40;
        AddPrim(ordering_table, packet);

        buf = *(u8 **)((u8 *)(&g_game_work));
        primitive = ((GpuContext *)buf)->packetCursor;
        ((GpuContext *)buf)->packetCursor = primitive + 0xC;
        func_80067EF4(primitive, 0, 0);
        AddPrim(ordering_table, primitive);
    }

    if (fill != 0) {
        buf = *state_addr;
        packet = ((GpuContext *)buf)->packetCursor;
        ((GpuContext *)buf)->packetCursor = packet + 0x10;
        ((S_800BB2E4_2 *)packet)->unk_04.at00.v = 0x60000000;
        ((S_800BB2E4_2 *)packet)->unk_03 = 3;
        ((S_800BB2E4_2 *)packet)->unk_08.at00u.v = ((S_800BB2E4_1 *)rect)->unk_00;
        y = ((S_800BB2E4_1 *)rect)->unk_02.s;
        if (odd) {
            y -= 0xE0;
        }
        ((S_800BB2E4_2 *)packet)->unk_08.at02u.v = y;
        ((S_800BB2E4_2 *)packet)->unk_0C.at00u.v = ((S_800BB2E4_1 *)rect)->unk_04;
        ((S_800BB2E4_2 *)packet)->unk_0C.at02.v = ((S_800BB2E4_1 *)rect)->unk_06;
        AddPrim(ordering_table, packet);

        buf = *state_addr;
        primitive = ((GpuContext *)buf)->packetCursor;
        ((GpuContext *)buf)->packetCursor = primitive + 0xC;
        func_80067EF4(primitive, 0, 1);
        AddPrim(ordering_table, primitive);

        buf = *state_addr;
        primitive = ((GpuContext *)buf)->packetCursor;
        ((GpuContext *)buf)->packetCursor = primitive + 0xC;
        SetDrawArea(primitive, rect);
        AddPrim(ordering_table, primitive);
    }
}
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

extern s32 rsin(s32, ...);
extern s32 rcos(s32, ...);
s16 calculate_planar_heading(s16 start_x, s16 start_y, s16 end_x, s16 end_y);
extern s32 play_sound_if_enabled(s32 query_value);
extern void * create_orbiting_color_particle(s16 x, s16 y, s16 z, s16 angle, s16 value_50, s16 value_58, s32 state_word, s16 value_48);

typedef struct DungeonWork {
    u8 pad_00[0x30];
    s16 field_30[5];
    u8 pad_3A[2];
    s16 field_3C[5];
} DungeonWork;


typedef struct S_800BB55C_0_pre {
    s32 unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800BB55C_0_pre;   /* the 0x14 bytes before arg0 in update_five_point_effect, addressed as arg0[-1] */

typedef struct S_800BB55C_0 {
    u8 pad_00[0x4A];
    union { s16 s; u16 u; } unk_4A;   /* accessed as both */
    s16 unk_4C;
    u16 unk_4E;
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
    u8 pad_5A[0x2];
    s32 unk_5C;
    s32 (*unk_60)();
    u16 unk_64;
} S_800BB55C_0;   /* arg0 in update_five_point_effect */

typedef struct S_800BB55C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BB55C_2;   /* arg1 in update_five_point_effect */

typedef struct S_800BB55C_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_800BB55C_3;

typedef struct S_800BB55C_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BB55C_4;   /* global_ptr in update_five_point_effect */

/* Draws a growing five-point pattern and updates its rotating fade-out effect. */
void update_five_point_effect(void *effect, S_800BB55C_2 *position, s32 restore_link) {
    s32 draw_params[2];
    s16 start_xy[2];
    s16 end_xy[2];
    s16 end_y;
    s16 line_angle;
    s16 arc_length;
    s32 arc_angle;
    s32 base_angle;
    s32 start_angle = -0x400;
    s32 radius_decay;
    register s32 packet_or_angle;
    s32 packet_or_angle_2;
    s32 saved_link;
    s32 segment_index;
    s32 point_index;
    u16 rotation;
    u16 phase_ticks;
    u16 next_phase;
    u16 fade_ticks;
    u8 red;
    u8 green;
    u8 blue;
    S_800BB55C_3 *color;

    draw_params[0] = 0x01000340;
    draw_params[1] = 0x460044;
    packet_or_angle_2 = effect + 0xC;
    advance_sprite_animation_and_textures(packet_or_angle_2);
    saved_link = restore_link;
    ((S_800BB55C_0_pre *)effect)[-1].unk_00 = packet_or_angle_2;
    draw_content_or_rect(NULL, NULL, draw_params, 0, effect);
    base_angle = start_angle;
    for (point_index = 0; point_index < 5; point_index++) {
        packet_or_angle = base_angle << 0x10;
        packet_or_angle >>= 0x10;
        start_xy[0] = (rcos(packet_or_angle) >> 7) + 0x362;
        start_xy[1] = (rsin(packet_or_angle) >> 7) + 0x122;
        packet_or_angle += 0x999;
        end_xy[0] = (rcos(packet_or_angle) >> 7) + 0x362;
        end_y = (rsin(packet_or_angle) >> 7) + 0x122;
        end_xy[1] = end_y;
        arc_angle = calculate_planar_heading(start_xy[0], start_xy[1], end_xy[0], end_y);
        line_angle = arc_angle;
        end_xy[0] = (u16) start_xy[0] + ((s32) (rcos(line_angle) * ((DungeonWork *)effect)->field_30[point_index])
            >> 0xB);
        end_xy[1] = (u16) start_xy[1] + ((s32) (rsin(line_angle) * ((DungeonWork *)effect)->field_30[point_index])
            >> 0xB);
        ((DungeonWork *)effect)->field_3C[point_index] = base_angle;
        base_angle += 0x999;
        draw_content_or_rect(start_xy, end_xy, draw_params, 0, NULL);
    }
    base_angle = start_angle;
    for (point_index = 0; point_index < 5; point_index++) {
        packet_or_angle = base_angle << 0x10;
        packet_or_angle >>= 0x10;
        start_xy[0] = (rcos((s16) packet_or_angle) >> 7) + 0x362;
        start_xy[1] = (rsin((s16) packet_or_angle) >> 7) + 0x122;
        arc_angle = base_angle;
        for (segment_index = 0; segment_index < ((DungeonWork *)effect)->field_30[point_index]; segment_index++) {
            packet_or_angle = arc_angle + 0x19;
            arc_angle = packet_or_angle;
            packet_or_angle <<= 16;
            packet_or_angle >>= 16;
            end_xy[0] = (rcos(packet_or_angle) >> 7) + 0x362;
            end_xy[1] = (rsin((s16)packet_or_angle) >> 7) + 0x122;
            draw_content_or_rect(start_xy, end_xy, draw_params, 0, NULL);
            start_xy[0] = (u16) end_xy[0];
            start_xy[1] = (u16) end_xy[1];
        }
        arc_length = (u16) ((DungeonWork *)effect)->field_30[point_index] + 1;
        ((DungeonWork *)effect)->field_30[point_index] = arc_length;
        base_angle += 0x333;
        if (arc_length >= 0x1F) {
            ((DungeonWork *)effect)->field_30[point_index] = 0x1F;
            if (((S_800BB55C_0 *)effect)->unk_4A.s == 0) {
                if (((S_800BB55C_0 *)effect)->unk_60() != 0) {
                    ((S_800BB55C_0 *)effect)->unk_50 = 0x120;
                    ((S_800BB55C_0 *)effect)->unk_4A.s = (s16) ((u16) ((S_800BB55C_0 *)effect)->unk_4A.s + 1);
                    play_sound_if_enabled(0x603);
                }
            }
            ((S_800BB55C_0 *)effect)->unk_4C = 0x20;
        }
    }
    draw_content_or_rect(NULL, NULL, draw_params, 1, NULL);
    ((S_800BB55C_0_pre *)effect)[-1].unk_00 = saved_link;
    if (((S_800BB55C_0 *)effect)->unk_4A.s != 0) {
        ((S_800BB55C_0 *)effect)->unk_4E = (u16) (((S_800BB55C_0 *)effect)->unk_4E + 0x100);
        point_index = 0;
        do {
            point_index = point_index + 1;
            rotation = ((S_800BB55C_0 *)effect)->unk_4E + 0x400;
            ((S_800BB55C_0 *)effect)->unk_4E = rotation;
            create_orbiting_color_particle(position->unk_02, position->unk_06, position->unk_0A, (s16) rotation,
                (s32) ((S_800BB55C_0 *)effect)->unk_50, (s32) ((S_800BB55C_0 *)effect)->unk_58,
                ((S_800BB55C_0 *)effect)->unk_5C, 6);
        } while (point_index < 4);
        if (((S_800BB55C_0 *)effect)->unk_58 < 0x20) {
            ((S_800BB55C_0 *)effect)->unk_58 = (s16) ((u16) ((S_800BB55C_0 *)effect)->unk_58 + 1);
        }
        if (((S_800BB55C_0 *)effect)->unk_4A.s == 1) {
            phase_ticks = ((S_800BB55C_0 *)effect)->unk_64 + 1;
            ((S_800BB55C_0 *)effect)->unk_64 = phase_ticks;
            if ((s16) phase_ticks >= 0x21) {
                next_phase = ((S_800BB55C_0 *)effect)->unk_4A.u + 1;
                ((S_800BB55C_0 *)effect)->unk_64 = 0x10U;
                ((S_800BB55C_0 *)effect)->unk_4A.u = next_phase;
                return;
            }
        } else {
            red = (u8) ((S_800BB55C_0 *)effect)->unk_5C;
            color = effect + 0x5C;
            color->unk_00 = (u8) (red - ((s32) red / (s16) ((S_800BB55C_0 *)effect)->unk_64));
            green = color->unk_01;
            color->unk_01 = (u8) (green - ((s32) green / (s16) ((S_800BB55C_0 *)effect)->unk_64));
            blue = color->unk_02;
            color->unk_02 = (u8) (blue - ((s32) blue / (s16) ((S_800BB55C_0 *)effect)->unk_64));
            radius_decay = (s16) ((S_800BB55C_0 *)effect)->unk_50 / (s16) ((S_800BB55C_0 *)effect)->unk_64;
            ((S_800BB55C_0 *)effect)->unk_50 = (s16) ((u16) ((S_800BB55C_0 *)effect)->unk_50 - radius_decay);
            fade_ticks = ((S_800BB55C_0 *)effect)->unk_64 - 1;
            ((S_800BB55C_0 *)effect)->unk_64 = fade_ticks;
            if ((fade_ticks << 0x10) <= 0) {
                g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
                ((S_800BB55C_0_pre *)effect)[-1].unk_12 = (u16) (((S_800BB55C_0_pre *)effect)[-1].unk_12 | 0x8000);
                object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            }
        }
    }
}
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern s32 draw_linked_sprites_clipped();
/* Pass the buffer, value, and data to draw_linked_sprites_clipped and return zero. */
s32 process_linked_menu_effect(u8 *buffer, s32 value, void *data) {
    draw_linked_sprites_clipped(buffer, value, data);
    return 0;
}
#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"

extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void *allocate_list_node();
extern s32 play_sound_if_enabled(s32 query_value);
extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);
struct S_800BB55C_2;
extern void update_five_point_effect(void *effect, struct S_800BB55C_2 *position, s32 restore_link);
extern s32 process_linked_menu_effect(u8 *buffer, s32 value, void *data);
extern M2C_UNK familiar_restore_sprite_data;

typedef struct S_800BBA40_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)(void *, S_800BB55C_2 *, s32);
} S_800BBA40_0;

typedef struct S_800BBA40_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BBA40_1;

typedef struct S_800BBA40_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    s32 * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BBA40_2;

typedef struct S_800BBA40_3 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0xC];
    s16 unk_28;
    s16 unk_2A;
    u8 pad_2C[0x10];
    s16 unk_3C;
    u8 pad_3E[0x1E];
    s32 unk_5C;
    s32 unk_60;
} S_800BBA40_3;

/* Creates an effect at the tile center and initializes its rendering and five angles. */
void *create_five_point_effect(s16 tile_x, s16 tile_y, s16 pos_z, void *transform_data, s16 scale, s32 setup_word_5c,
    s32 setup_word_60) {
    s32 call_data[2];
    s16 angle;
    void *effect;
    S_800BBA40_1 *position;
    S_800BBA40_2 *render_data;
    s16 held_pos_z = pos_z;
    void *held_transform = transform_data;
    void *setup_base;

    call_data[0] = 0x01000340;
    call_data[1] = 0x01000080;
    draw_content_or_rect(0, 0, call_data, 1, 0);
    effect = allocate_list_node(0x12, ((s32 *)&scene_object_list_anchor.next));
    if (effect != NULL) {
        s32 angle_index;
        void *setup_cursor;

        play_sound_if_enabled(0x704);
        ((S_800BBA40_0 *)effect)->unk_10 = update_five_point_effect;
        register_node(effect, process_linked_menu_effect);
        position = ((S_800BBA40_0 *)effect)->unk_08;
        position->unk_02 = (s16) (((s32) (tile_x << 0x10) >> 0xA) + 0x20);
        position->unk_06 = (s16) (((s32) (tile_y << 0x10) >> 0xA) + 0x20);
        position->unk_0A = held_pos_z;
        render_data = ((S_800BBA40_0 *)effect)->unk_0C;
        render_data->unk_08 = &familiar_restore_sprite_data;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_0C = 0x808080;
        render_data->unk_06 = 8;
        setup_base = effect + 0x20;
        select_record_entry_and_value(effect + 0x2C, held_transform, 0);
        setup_cursor = setup_base;
        ((S_800BBA40_3 *)setup_cursor)->unk_2A = (s16) scale;
        ((S_800BBA40_3 *)setup_cursor)->unk_28 = (s16) scale;
        ((S_800BBA40_3 *)setup_cursor)->unk_18 = 0x808080;
        angle = -0x400;
        ((S_800BBA40_3 *)setup_cursor)->unk_5C = setup_word_5c;
        angle_index = 0;
        ((S_800BBA40_3 *)setup_cursor)->unk_60 = setup_word_60;
        do {
            ((S_800BBA40_3 *)(setup_base + angle_index * 2))->unk_3C = angle;
            angle += 0x999;
            angle_index += 1;
        } while (angle_index < 5);
        select_nearby_target_and_initialize_slot(((s32 *)&scene_object_list_anchor.next), &view_reference_entity.x.v, 8, 0x300);
    }
    return effect;
}
#include "common.h"
#include "shared/object_flags.h"

typedef struct State {
    u8 target0[3];
    u8 pad03;
    u16 value4;
    u16 value6;
    u8 pad08[0x40];
    s16 shift;
    s16 mode;
    s16 count;
    s16 angle;
    u8 pad50[8];
    u16 delta;
} State;

typedef struct Output {
    u8 pad00[2];
    s16 value2;
    u8 pad06[2];
    s16 value6;
} Output;

typedef struct Interp {
    u8 pad00[0x0c];
    u8 value0c;
    u8 value0d;
    u8 value0e;
    u8 pad0f[0x0b];
    s16 value1a;
} Interp;

extern s32 rsin(s32, ...);
extern s32 rcos(s32, ...);

/* Updates angular motion and fades three channels in, holds them, then fades them out. */
void update_orbiting_color_particle(State *state, Output *output, Interp *interp) {
    output->value2 = state->value4 + (rcos(state->angle) >> state->shift);
    output->value6 = state->value6 + (rsin(state->angle) >> state->shift);
    state->angle = state->angle + state->delta;
    interp->value1a = state->angle + 0x400;

    if (state->mode == 0) {
        interp->value0c = interp->value0c + (state->target0[0] - interp->value0c) / state->count;
        interp->value0d = interp->value0d + (state->target0[1] - interp->value0d) / state->count;
        interp->value0e = interp->value0e + (state->target0[2] - interp->value0e) / state->count;
        state->count = state->count - 1;
        if (state->count <= 0) {
            state->count = 8;
            state->mode = state->mode + 1;
        }
    } else if (state->mode == 1) {
        state->count = state->count - 1;
        if (state->count <= 0) {
            state->count = 4;
            state->mode = state->mode + 1;
        }
    } else {
        interp->value0c = interp->value0c - interp->value0c / state->count;
        interp->value0d = interp->value0d - interp->value0d / state->count;
        interp->value0e = interp->value0e - interp->value0e / state->count;
        state->count = state->count - 1;
        if (state->count <= 0) {
            *((u16 *)state - 1) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_800BBDEC_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x4C];
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_800BBDEC_0;   /* scratch in draw_shaded_vertical_quad */

typedef struct S_800BBDEC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BBDEC_1;   /* arg1 in draw_shaded_vertical_quad */

   /* *global in draw_shaded_vertical_quad */

typedef struct S_800BBDEC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_800BBDEC_3;   /* arg2 in draw_shaded_vertical_quad */

typedef struct S_800BBDEC_4 {
    u8 pad_00[0x50];
    u16 unk_50;
} S_800BBDEC_4;   /* arg0 in draw_shaded_vertical_quad */

typedef struct S_800BBDEC_5 {
    u8 pad_00[0x4];
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800BBDEC_5;   /* prim in draw_shaded_vertical_quad */


extern void *CompMatrix(void *, void *, void *);
extern void PushMatrix();
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern u32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void *RotMatrix(void *, void *);
extern void AddPrim(void *, void *, ...);
extern void SetPolyG4(void *);
extern void SetDrawMode(void *, s32, s32, s32, s32);

/* Projects and queues a shaded quad with optional semitransparency. */
void draw_shaded_vertical_quad(S_800BBDEC_4 *object, S_800BBDEC_1 *position, S_800BBDEC_3 *appearance, s32 unused_draw_value)
{
    u8 *scratch = (u8 *)0x1F800000;
    void **render_ctx = (void **)((u8 *)(&g_game_work));
    u8 *prim;
    u32 depth_index;
    s32 color_word;
    s16 end_z;

    ((S_800BBDEC_0 *)scratch)->unk_20 = (u8 *)*render_ctx + 0xB0;
    ((S_800BBDEC_0 *)scratch)->unk_E4 = position->unk_02;
    ((S_800BBDEC_0 *)scratch)->unk_E8 = position->unk_06;
    ((S_800BBDEC_0 *)scratch)->unk_EC = position->unk_0A;
    prim = ((GpuContext *)(*render_ctx))->packetCursor;

    PushMatrix();

    ((S_800BBDEC_0 *)scratch)->unk_100 = appearance->unk_16;
    ((S_800BBDEC_0 *)scratch)->unk_104 = appearance->unk_1A;
    ((S_800BBDEC_0 *)scratch)->unk_102 = appearance->unk_18;
    RotMatrix(scratch + 0x100, scratch + 0xD0);
    ReadRotMatrix(scratch + 0x11C);
    CompMatrix(scratch + 0x11C, scratch + 0xD0, scratch + 0x50);
    SetTransMatrix(scratch + 0x50);
    SetRotMatrix(scratch + 0x50);

    ((S_800BBDEC_0 *)scratch)->unk_7C = 0;
    ((S_800BBDEC_0 *)scratch)->unk_74 = 0;
    end_z = -object->unk_50;
    ((S_800BBDEC_0 *)scratch)->unk_88 = 0x10;
    ((S_800BBDEC_0 *)scratch)->unk_78 = 0x10;
    ((S_800BBDEC_0 *)scratch)->unk_80 = 0;
    ((S_800BBDEC_0 *)scratch)->unk_70 = 0;
    ((S_800BBDEC_0 *)scratch)->unk_7A = 0;
    ((S_800BBDEC_0 *)scratch)->unk_72 = 0;
    ((S_800BBDEC_0 *)scratch)->unk_8A = 0;
    ((S_800BBDEC_0 *)scratch)->unk_82 = 0;
    ((S_800BBDEC_0 *)scratch)->unk_8C = end_z;
    ((S_800BBDEC_0 *)scratch)->unk_84 = end_z;

    depth_index = RotAverage4(scratch + 0x70, scratch + 0x78,
                          scratch + 0x80, scratch + 0x88,
                          prim + 8, prim + 0x10, prim + 0x18, prim + 0x20,
                          scratch + 0x90, scratch + 0x94);
    ((S_800BBDEC_0 *)scratch)->unk_C0 = depth_index;

    if (depth_index < 0x1E0U) {
        color_word = appearance->unk_0C;
        ((S_800BBDEC_5 *)prim)->unk_14 = 0;
        ((S_800BBDEC_5 *)prim)->unk_1C = 0;
        ((S_800BBDEC_5 *)prim)->unk_04.at00.v = color_word;
        ((S_800BBDEC_5 *)prim)->unk_0C = ((S_800BBDEC_5 *)prim)->unk_04.at00u.v >> 2;
        ((S_800BBDEC_5 *)prim)->unk_0D = ((S_800BBDEC_5 *)prim)->unk_04.at01.v >> 2;
        ((S_800BBDEC_5 *)prim)->unk_0E = ((S_800BBDEC_5 *)prim)->unk_04.at02.v >> 2;
        SetPolyG4(prim);

        if (appearance->unk_14 & 4) {
            ((S_800BBDEC_5 *)prim)->unk_04.at03.v |= 2;
        }

        AddPrim((u8 *)((S_800BBDEC_0 *)scratch)->unk_20 +
                      ((S_800BBDEC_0 *)scratch)->unk_C0 * 4,
                      prim);
        prim += 0x24;

        if (appearance->unk_14 & 4) {
            SetDrawMode(prim, 0, 0, 0x20, 0);
            AddPrim((u8 *)((S_800BBDEC_0 *)scratch)->unk_20 +
                          ((S_800BBDEC_0 *)scratch)->unk_C0 * 4,
                          prim);
            prim += 0xC;
        }
    }

    PopMatrix();
    ((GpuContext *)(*render_ctx))->packetCursor = prim;
}
#include "common.h"

struct S_800BBDEC_4;
struct S_800BBDEC_1;
struct S_800BBDEC_3;
extern void draw_shaded_vertical_quad(struct S_800BBDEC_4 *object, struct S_800BBDEC_1 *position, struct S_800BBDEC_3 *appearance, s32 unused_draw_value);

/* Process each linked state using the signed halfword at data offset 6. */
s32 draw_shaded_quad_chain(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        draw_shaded_vertical_quad(state, context, data, *(s16 *)((s8 *)data + 6));
        next_node = *(void **)((s8 *)state - 8);
        if (next_node == 0) {
            return 0;
        }
        state = (void *)((s8 *)next_node + 32);
        context = (void *)((s32 *)next_node)[2];
        data = (void *)((s32 *)next_node)[3];
    }
}
#include "common.h"
#include "shared/object_node.h"

extern void *allocate_list_node();
struct State;
struct Output;
struct Interp;
extern void update_orbiting_color_particle(struct State *state, struct Output *output, struct Interp *interp);
extern s32 draw_shaded_quad_chain(void *initial_state, void *context, void *data);

typedef struct S_800BC0A8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)(State *, Output *, Interp *);
    u8 pad_14[0xC];
    s32 unk_20;
} S_800BC0A8_0;

typedef struct S_800BC0A8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC0A8_1;

typedef struct S_800BC0A8_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x3E];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
} S_800BC0A8_2;

typedef struct S_800BC0A8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_800BC0A8_3;

/* Creates an object and initializes its position, angle, and state. */
void *create_orbiting_color_particle(s16 x, s16 y, s16 z, s16 angle, s16 value_50, s16 value_58, s32 state_word, s16 value_48) {
    s16 saved_value_50 = value_50;
    s16 saved_value_58 = value_58;
    s16 saved_value_48 = value_48;
    S_800BC0A8_3 *transform;
    S_800BC0A8_2 *state;
    void *object;
    S_800BC0A8_1 *position;

    object = allocate_list_node(0x202, ((s32 *)&scene_object_list_anchor.next));
    if (object != 0) {
        ((S_800BC0A8_0 *)object)->unk_10 = update_orbiting_color_particle;
        register_node(object, draw_shaded_quad_chain);
        position = ((S_800BC0A8_0 *)object)->unk_08;
        state = object + 0x20;
        position->unk_02 = x;
        state->unk_04 = x;
        position->unk_06 = y;
        state->unk_06 = y;
        position->unk_0A = z;
        state->unk_08 = z;
        transform = ((S_800BC0A8_0 *)object)->unk_0C;
        transform->unk_1A = (s16) (angle + 0x400);
        transform->unk_14 = (u16) (transform->unk_14 | 0xC);
        state->unk_4E = angle;
        state->unk_4C = 4;
        state->unk_50 = (s16) saved_value_50;
        ((S_800BC0A8_0 *)object)->unk_20 = state_word;
        state->unk_58 = (s16) saved_value_58;
        state->unk_48 = (s16) saved_value_48;
    }
    return object;
}
#include "common.h"


extern void MoveImage();

// Updates the wrapped scroll offset and copies its source rectangle to two destinations.
void update_wrapped_texture_scroll(void *scrollState) {
    s16 sourceRect[4];

    {
        s32 destinationX;
        s32 destinationY;
        s32 offsetOrRectValue;
        s32 scrollStepOrSourceY;

        destinationX = 0x270;
        offsetOrRectValue = *(u16 *)((unsigned char *)scrollState + 2);
        scrollStepOrSourceY = *(u16 *)((unsigned char *)scrollState + 0xC);
        destinationY = 0x100;
        offsetOrRectValue = (offsetOrRectValue - scrollStepOrSourceY) & 0x1F;
        *(u16 *)((unsigned char *)scrollState + 2) = (u16)offsetOrRectValue;
        offsetOrRectValue = destinationX;
        sourceRect[0] = offsetOrRectValue;
        scrollStepOrSourceY = *(u16 *)((unsigned char *)scrollState + 2);
        offsetOrRectValue = 0x10;
        sourceRect[2] = offsetOrRectValue;
        offsetOrRectValue = 0x20;
        sourceRect[3] = offsetOrRectValue;
        scrollStepOrSourceY = scrollStepOrSourceY + 0x140;
        sourceRect[1] = scrollStepOrSourceY;
        MoveImage(sourceRect, destinationX, destinationY, scrollState);
    }
    MoveImage(sourceRect, 0x270, 0x120);
}
#include "shared/object_node.h"
#include "common.h"
extern void update_wrapped_texture_scroll(void *scrollState);

typedef struct S_800BC228_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void *);
    u8 pad_14[0x18];
    s16 unk_2C;
} S_800BC228_0;

/* Create an object with update_wrapped_texture_scroll as its data pointer and store the supplied value. */
void create_wrapped_texture_scroll(s16 value) {
    S_800BC228_0 *object;

    object = allocate_flagged_object_node(0);
    if (object != 0) {
        object->unk_10 = update_wrapped_texture_scroll;
        object->unk_2C = value;
    }
}
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BC26C_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800BC26C_0;   /* result in create_tracked_effect */

typedef struct S_800BC26C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} S_800BC26C_1;   /* fields in create_tracked_effect */


extern void *allocate_list_node();
extern void retire_effect_when_owner_or_value_ends(void *context);

/* Creates an object and initializes its owner, parameter, and mode-dependent fields. */
void *create_tracked_effect(s32 owner, s16 mode, s32 param)
{
    void *object;
    u8 *fields;
    s16 saved_mode;

    object = allocate_list_node(0x110, (void *)owner);
    saved_mode = mode;
    if (object != NULL) {
        ((S_800BC26C_0 *)object)->unk_10 = retire_effect_when_owner_or_value_ends;
        register_node(object, traverse_nodes_and_render_unflagged);
        fields = (u8 *)object + 0x20;
        ((S_800BC26C_0 *)object)->unk_20 = owner;
        ((S_800BC26C_1 *)fields)->unk_04 = param;
        if (mode != 0) {
            ((S_800BC26C_1 *)fields)->unk_0C = 0x7F80;
        } else {
            ((S_800BC26C_1 *)fields)->unk_0C = 0x7FC0;
        }
        ((S_800BC26C_1 *)fields)->unk_0E = saved_mode;
    }
    return object;
}
#include "common.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8003FFF0 S_8003FFF0;
struct S_8003FFF0 {
    S_8003FFF0 *next;
    u8 unk04[0x0c];
    u8 *kind;
    u8 unk14[0x0a];
    u16 flags;
    s32 id;
};

extern S_8003FFF0 *active_node_list_head[4];
extern void retire_effect_when_owner_or_value_ends(void *context);

// Set bit 0x8000 in the first matching node's flags and the shared flags.
void retire_tracked_effect_by_id(s32 targetId) {
    S_8003FFF0 *node;

    node = *active_node_list_head;
    if (node != NULL) {
        do {
            if ((node->kind == retire_effect_when_owner_or_value_ends) && (node->id == targetId)) {
                u16 nodeFlags = node->flags;
                s32 sharedFlags = object_flag_block.flags;

                node->flags = nodeFlags | 0x8000;
                object_flag_block.flags = sharedFlags | 0x8000;
                return;
            }
            node = node->next;
        } while (node != NULL);
    }
}
#include "common.h"
#include "shared/object_flags.h"
#include "engine/node.h"


/* Mark completion when the referenced object is flagged or the tracked value is zero. */
void retire_effect_when_owner_or_value_ends(void *context)
{
    void *object = *(void **)context;
    if ((*(u16 *)((u8 *)object + 0x1E) & 0x8000) || (*(*(s32 **)((u8 *)context + 4)) == 0)) {
        *(u16 *)((u8 *)context - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
