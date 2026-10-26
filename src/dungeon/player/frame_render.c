/* Object render dispatch and framebuffer strips
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00244 - CL:dungeon/func_80083E28, CL:dungeon/func_80084084.
 * CL:dungeon/func_80083E28
 * CL:dungeon/func_80084084
 */
#include "dungeon/player.h"

/* Private declarations retained from the member sources. */
/* Object render dispatch and framebuffer strips */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00244 - CL:dungeon/func_80083E28, CL:dungeon/func_80084084. */

#include "common.h"
#include "shared/object_flags.h"
#include "shared/game_work.h"
#include "records/Rec_D_80083160.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"

typedef struct {
    u8 before_flags[0x1C];
    u32 flags;
} DungeonControl;

typedef struct S_80089588_3 {
    s32 unk_00;
} S_80089588_3;

typedef struct S_80089588_4 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80089588_4;

typedef struct S_80089588_2 {
    s32 unk_00;
} S_80089588_2;

struct S_8003E2D8;

typedef struct S_8003E2D8 S_8003E2D8;

/* Draw callbacks receive a registered node's body (after its 0x20-byte header), position and sprite slots. */
typedef s32 (*Callback)(void *, struct ObjectPosition *, struct SpriteFrameState *);

extern s32 D_800814A0;
extern u8 node_update_mode;
extern u16 system_update_flags;
extern void run_active_node_callbacks(void);
extern void remove_marked_active_nodes(void);
extern void integrate_active_node_vectors(void);
extern void run_view_callbacks(void);
extern void process_current_facing_directions(void);
extern void render_map_cell_mesh(void);
extern void append_draw_mode_primitive(void);
extern u8 upper_draw_context[16];
s32 AddPrim(void *, void *);
s32 SetDrawArea(void *, s32);
s32 func_80067EF4(void *, s32, s32);
s32 SetDrawMode(void *, s32, s32, s32, s32);
extern s32 is_frame_packet_arena_overflowed(s32);
extern Callback D_800DCF80[];
extern u8 D_800E0000[];

/* Updates and cleans active nodes, advances motion and the view, then dispatches object and
   framebuffer rendering. */
void update_active_nodes_and_render_frame(void) {
    GameWork *work = &g_game_work;
    run_active_node_callbacks();
    if (D_800814A0 & OBJECT_REMOVE_PENDING) {
        remove_marked_active_nodes();
    }
    D_800814A0 = 0;
    if (node_update_mode == 0) {
        integrate_active_node_vectors();
        if (system_update_flags & 2) {
            return;
        }
        if (work->map.cells != 0) {
            run_view_callbacks();
            process_current_facing_directions();
            if (!(primary_actor_record->flags1C & 0x10)) {
                render_map_cell_mesh();
            }
        }
    }
    dispatch_object_renderers();
    append_draw_mode_primitive();
    queue_framebuffer_strip_quads();
}

/* Queue draw settings and horizontal strips for both ordering tables. */
void queue_framebuffer_strip_quads(void) {
    s32 draw_area[2];
    u8 alternate_buffer;
    s16 saved_alternate;
    u16 strip_y;
    u16 other_strip_y;
    void *packet;
    u8 * context_slot;

    alternate_buffer = (s32) g_game_work.draw_buffer != (s32) upper_draw_context;
    packet = ((Rec_D_80083160 *)g_game_work.draw_buffer)->unk_8D0;
    SetDrawArea(packet, g_game_work.draw_buffer);
    AddPrim((u8 *)g_game_work.draw_buffer + 0x7B0, packet);
    packet += 0xC;
    SetDrawArea(packet, g_game_work.draw_buffer);
    AddPrim((u8 *)g_game_work.draw_buffer + 0x830, packet);
    packet += 0xC;
    func_80067EF4(packet, 0, 0);
    AddPrim((u8 *)g_game_work.draw_buffer + 0x830, packet);
    packet += 0xC;
    {
        s32 cmd_value;
        cmd_value = 0x2A000000;
        (*(s32 *)((u8 *)packet + 4)) = cmd_value;
        cmd_value = 1;
        (*(s16 *)((u8 *)packet + 0x10)) = cmd_value;
        (*(s16 *)((u8 *)packet + 8)) = cmd_value;
        cmd_value = 0x100;
        (*(s16 *)((u8 *)packet + 0x14)) = cmd_value;
        (*(s16 *)((u8 *)packet + 0xC)) = cmd_value;
    }
    context_slot = (u8 *)(&g_game_work.draw_buffer);
    saved_alternate = alternate_buffer != 0;
    {
        register s32 strip_top;
        if (saved_alternate != 0) {
            (*(u16 *)((u8 *)packet + 0xE)) = 0xE0;
        } else {
            (*(u16 *)((u8 *)packet + 0xE)) = 0x1C0;
        }
    }
    strip_y = (*(u16 *)((u8 *)packet + 0xE));
    (*(s8 *)((u8 *)packet + 3)) = 5;
    (*(u16 *)((u8 *)packet + 0xA)) = strip_y;
    (*(s16 *)((u8 *)packet + 0x16)) = strip_y + 0xE;
    (*(s16 *)((u8 *)packet + 0x12)) = strip_y + 0xE;
    AddPrim(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0x18;
    {
        s32 cmd_value;
        cmd_value = 0x2A000000;
        (*(s32 *)((u8 *)packet + 4)) = cmd_value;
        cmd_value = 1;
        (*(s16 *)((u8 *)packet + 0x10)) = cmd_value;
        (*(s16 *)((u8 *)packet + 8)) = cmd_value;
        cmd_value = 0x100;
        (*(s16 *)((u8 *)packet + 0x14)) = cmd_value;
        (*(s16 *)((u8 *)packet + 0xC)) = cmd_value;
    }
    {
        s32 strip_top;
        strip_top = saved_alternate;
        if (strip_top != 0) {
            (*(u16 *)((u8 *)packet + 0xE)) = 0xE0;
        } else {
            (*(u16 *)((u8 *)packet + 0xE)) = 0x1C0;
        }
    }
    other_strip_y = (*(u16 *)((u8 *)packet + 0xE));
    (*(s8 *)((u8 *)packet + 3)) = 5;
    (*(u16 *)((u8 *)packet + 0xA)) = other_strip_y;
    (*(s16 *)((u8 *)packet + 0x16)) = other_strip_y + 0xE;
    (*(s16 *)((u8 *)packet + 0x12)) = other_strip_y + 0xE;
    AddPrim(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0x18;
    func_80067EF4(packet, 0, 1);
    AddPrim(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    SetDrawMode(packet, 0, 0, 0x20, 0);
    AddPrim(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0xC;
    SetDrawMode(packet, 0, 0, 0x20, 0);
    AddPrim(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    draw_area[0] = 0x01C00000;
    draw_area[1] = 0x100100;
    SetDrawArea(packet, (s32) draw_area);
    AddPrim(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0xC;
    SetDrawArea(packet, (s32) draw_area);
    AddPrim(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    ((S_80089588_4 *)(((S_80089588_3 *)context_slot)->unk_00))->unk_8D0 = packet;
}

/* Dispatch eligible entry_m callbacks according to the current mode. */
void dispatch_object_renderers(void)
{
    ObjectNodeHeader *entry_m;
    Callback callback;
    if (dungeon_floor_flags & 0x02000000) {
        Callback *callback_slot;
        register Callback *callback_base;
        register Callback *special_start;
        Callback *sentinel_scan;

        register ObjectNodeHeader **entry_slot;

        callback_base = (Callback *)registered_draw_callbacks;
        special_start = D_800DCF80 + 9;
        callback_slot = callback_base;
        entry_slot = registered_draw_objects;
        do {
            callback = *callback_slot;
            if (callback != 0) {
                entry_m = *entry_slot;
                if (entry_m != 0) {
                    if (!(entry_m->flags & 0x800)) {
                        register Callback *special_scan;

                        sentinel_scan = (Callback *)(D_800E0000 - 0x3080);
                        special_scan = special_start;
first_scan:
                        if (*special_scan == callback) {
                            callback(entry_m + 1, entry_m->position, entry_m->sprite);
                        } else if (*sentinel_scan != 0) {
                            sentinel_scan++;
                            special_scan++;
                            goto first_scan;
                        }
                    }
                } else {
                    *callback_slot = 0;
                }
            }
            callback_slot++;
            entry_slot++;
        } while ((s32)callback_slot < (s32)(callback_base + 0x20));
        return;
    }

    if (*(s32 *)((u8 *)primary_actor_record + 0x1C) & 0x10) {
        s32 i;
        Callback *special_scan;

        ObjectNodeHeader *saved;

        for (i = 0; i < 0x20; i++) {
            Callback *special_start = D_800DCF80;

            callback = registered_draw_callbacks[i];
            if (callback != 0) {
                entry_m = registered_draw_objects[i];
                if (entry_m != 0) {
                    if (!(entry_m->flags & 0x800)) {
                        special_scan = special_start + 1;
                        if (*special_start == callback) {
                            entry_m = &scene_object_list_anchor;
                            if (entry_m->draw_prev != 0) {
                                saved = entry_m->chain_next;
                                entry_m->chain_next = 0;
                                callback(entry_m + 1, entry_m->position, entry_m->sprite);
                                entry_m->chain_next = saved;
                            }
                        } else {
                            for (;;) {
                                if (*special_scan == callback) {
                                    callback(entry_m + 1, entry_m->position, entry_m->sprite);
                                    break;
                                }
                                if (*special_scan == 0) {
                                    break;
                                }
                                special_scan++;
                            }
                        }
                    }
                } else {
                    registered_draw_callbacks[i] = 0;
                }
            }
        }
        return;
    }

    {
        Callback *callback_slot;

        register ObjectNodeHeader **entry_slot;
        s32 slot_index;
        u8 *render_page;
        s32 stop_dispatch;

        slot_index = 0;
        callback_slot = (Callback *)registered_draw_callbacks;
        entry_slot = registered_draw_objects;
loop_third:
        callback = *callback_slot;
        if (callback != 0) {
            entry_m = *entry_slot;
            if (entry_m != 0) {
                if (!(entry_m->flags & 0x800)) {
                    callback(entry_m + 1, entry_m->position, entry_m->sprite);
                    stop_dispatch = is_frame_packet_arena_overflowed(
                        *(s32 *)((u8 *)g_game_work.draw_buffer + 0x8D0));
                    if (stop_dispatch != 0) {
                        return;
                    }
                }
            } else {
                *callback_slot = 0;
            }
        }
        callback_slot++;
        entry_slot++;
        if (++slot_index < 0x20) {
            goto loop_third;
        }
    }
}
