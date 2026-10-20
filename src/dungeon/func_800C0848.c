#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

extern u8 D_80081468[];
extern u16 D_8008146C;
extern u8 D_80082E6B;
extern s16 D_800DCED4[];
extern u8 D_800DCF4F;
extern u8 D_800E0458[];
extern u8 D_800E0B65[];
extern u8 D_800E0B73[];
extern u8 D_800E0BA1[];

void func_800419EC();
void func_80040AA0();
s32 get_entity_class();
void mark_sprite_resources_for_purge();
void snapshot_inventory_and_familiars();
void snapshot_inventory_familiar_records();
s32 get_unused_text_buffer(void);
s32 expand_text_control_codes();
s32 copy_four_text_bytes();
void func_80099290();
s32 write_text_byte_and_advance();
void unlink_entity_node();
void update_map_cell_flags_with_item_limit();
void refresh_packed_grid_nibbles();
s32 find_active_monster_record();
void detach_record_and_update_slot_state();
extern s32 play_sound_if_enabled();
void display_text_with_fullwidth_adjustment();
void check_action_boundary_and_set_flag();
s32 generate_random_value(void);
void remove_floor_items_at_tile(s16, s16);
void process_active_slots_at_coordinates(s16, s16);
void teleport_familiar_near_player();
void create_orbiting_teleport_effect();

#define CELL(xx, yy) (cells + 6 * ((xx) + ((yy) << *(s16 *)(fld + 20))))

void dispatch_action_callback_by_opcode(u8 *w) {
    GameWork *ctx;
    u8 *cells;
    u8 *fld;
    s32 st;
    u8 *sys;
    u8 *room;
    u8 *cnt;
    u8 *cnt2;
    u8 *rooms;
    u8 *rbase;
    u8 *rm;
    u8 *e;
    u8 *ep;
    u8 *o;
    u8 *q;
    EntityRec *p;
    s16 *tbl;
    s32 phase0;
    s32 phase;
    s32 hnd;
    s32 r;
    s32 v;
    s32 x, y, x1, y1, k;
    s32 t16;
    s32 mode;
    s16 t;
    s32 rv;
    s32 cc;
    s32 ic;
    s32 ea;
    s32 eb;
    s32 ch;
    u16 f;
    u16 a;

    ctx = &g_game_work;
    phase0 = *(s16 *)w;
    cells = ((u8 *)ctx->map.cells);
    fld = (u8 *)ctx + 0x1DC;
    if (phase0 == 0) {
        st = (s32) ((u8 *)(&g_dungeon_status));
        f = *(u16 *)((u8 *) st + 2);
        if (f & 0x10) {
            *(u16 *)((u8 *) st + 2) = f | 0x200;
        }
        a = *(u16 *)((u8 *) st + 2);
        if (!(a & 0x200)) {
            return;
        }
        if ((((u32)ctx->buttons) & 0x800) && !(*(u16 *)0x80013714 & 8)) {
            return;
        }
        if (*(s32 *)((u8 *) st + 12) != 0) {
            return;
        }
        if (*(s32 *)((u8 *) st + 16) != 0) {
            return;
        }
        if (a & 8) {
            return;
        }
        if (*(s16 *)((u8 *) st + 8) != 0) {
            return;
        }
        if (*(s16 *)((u8 *) st + 20) != 0) {
            return;
        }
        if (((u32)D_800E296C) & 0x100000) {
            return;
        }
        if (*(s16 *)((u8 *) st + 10) != 0) {
            return;
        }
        if (a & 0x2C01) {
            return;
        }
        *(u16 *)((u8 *) st + 2) = a & 0xFDFF;
        if (*(s16 *)(w + 22) != 0) {
            *(u16 *)(w + 22) = *(u16 *)(w + 22) - 1;
            return;
        }
        play_sound_if_enabled(0x818);
        func_800419EC(0x20, 8);
        *(u16 *)(w + 20) = *(u16 *)(w + 20) + 1;
        sys = (u8 *)0x80010000;
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            ic = *(u16 *)((u8 *) st + 10);
            D_800DCF4F = 1;
            *(u16 *)((u8 *) st + 10) = ic + 1;
        }
        phase = 1;
        hnd = get_unused_text_buffer();
        v = *(s16 *)(w + 20);
        if (v == phase) {
            r = expand_text_control_codes(D_800E0B65, hnd);
            if (!(*(u16 *)(sys + 0x3714) & 1)) {
                r = write_text_byte_and_advance(0x11, r);
                r = write_text_byte_and_advance(0x4C, r);
                r = copy_four_text_bytes(D_800E0458, r);
            }
            func_80099290(r);
            display_text_with_fullwidth_adjustment(hnd);
            *(s16 *)(w + 22) = 0x80;
            return;
        }
        if (v != 2) {
            goto L_third;
        }
        r = expand_text_control_codes(D_800E0B73, hnd);
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            r = write_text_byte_and_advance(0x11, r);
            r = write_text_byte_and_advance(0x4C, r);
            r = copy_four_text_bytes(D_800E0458, r);
        }
        func_80099290(r);
        display_text_with_fullwidth_adjustment(hnd);
        *(s16 *)(w + 22) = 0x40;
        return;
L_found:
        *(s16 *)(w + 6) = phase;
        t = *(u16 *)(room + 0);
        t = t - 1;
        *(s16 *)(w + 8) = t;
        *(s16 *)(w + 12) = t + *(u16 *)(room + 4) + 2;
        t = *(u16 *)(room + 2);
        t = t - 1;
        *(s16 *)(w + 10) = t;
        *(s16 *)(w + 14) = t + *(u16 *)(room + 6) + 2;
        goto L_zero;
L_third:
        r = expand_text_control_codes(D_800E0BA1, hnd);
        *(s16 *)(w + 22) = 0;
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            r = write_text_byte_and_advance(0x11, r);
            r = write_text_byte_and_advance(0x4C, r);
            r = copy_four_text_bytes(D_800E0458, r);
        }
        func_80099290(r);
        display_text_with_fullwidth_adjustment(hnd);
        *(s16 *)w = phase;
        *(u16 *)((u8 *) st + 10) = *(u16 *)((u8 *) st + 10) + 1;
        *(u16 *)(w + 4) = *(u16 *)(w + 4) + 1;
        rv = generate_random_value() & 0xFFFF;
        cnt = D_80081468;
        cc = *(s16 *)(cnt + 6);
        phase = rv % cc;
        st = cc;
        if (st > 0) {
            rbase = D_800E2970;
            cnt2 = cnt;
            do {
                room = (u8 *)(phase * 20 + (s32)rbase);
                if (*(s16 *)(room + 10) != 0) {
                    goto L_found;
                }
                st = st - 1;
                phase = (phase + 1) % *(s16 *)(cnt2 + 6);
            } while (st > 0);
        }
L_zero:
        if (st == 0) {
            *(s16 *)(w + 6) = -1;
        }
        v = *(s16 *)(w + 6);
        *(s16 *)(w + 2) = 0x20;
        *(s16 *)(w + 16) = 1;
        *(s16 *)(w + 4) = 1;
        if (v >= 0) {
            x = *(s16 *)(w + 8);
            x1 = *(s16 *)(w + 12);
            y1 = *(s16 *)(w + 14);
            if (x < x1) {
                do {
                    y = *(s16 *)(w + 10);
                    if (y < y1) {
                        do {
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            process_active_slots_at_coordinates(x, y);
                            remove_floor_items_at_tile(x, y);
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                } while (x < x1);
            }
        } else {
            x = 1;
            y1 = x1 = 63;
            do {
                y = 1;
                if (y < y1) {
                    do {
                        *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                        *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                        process_active_slots_at_coordinates(x, y);
                        remove_floor_items_at_tile(x, y);
                        y = y + 1;
                    } while (y < y1);
                }
                x = x + 1;
            } while (x < x1);
        }
        tbl = D_800DCED4;
        phase = *(s16 *)(w + 6);
        e = ((u8 *)D_800E3D7C);
        *(s16 *)(w + 18) = 0;
        do {
            ep = *(u8 **)(e - 20);
            if (phase == (s16)find_active_monster_record(*(u8 *)(ep + 36), *(u8 *)(ep + 37))) {
                if (*(u8 *)(e + 19) == 0) {
                    D_800E296C |= 0x2000;
                    create_orbiting_teleport_effect(e, tbl[get_entity_class(e)], 0, 0);
                    p = D_800E3D7C;
                    q = ((u8 *)p->unk_AC);
                    if (q != 0) {
                        create_orbiting_teleport_effect(q, tbl[get_entity_class(q)], 0, 0);
                    }
                    {
                        EntityRec *p2 = D_800E3D7C;
                        q = ((u8 *)p2->unk_B0);
                    }
                    if (q != 0) {
                        create_orbiting_teleport_effect(q, tbl[get_entity_class(q)], 1, 0);
                    }
                    *(s16 *)(w + 18) = 1;
                } else if (*(u32 *)(e + 20) & 0x4000) {
                    if (*(s16 *)(w + 18) == 0) {
                        teleport_familiar_near_player(e, *(u8 **)(((u8 *)D_800E3D7C) + 172) != e);
                    }
                } else {
                    if (*(s16 *)(w + 18) != 0) {
                        *(s16 *)(e + 108) = 0;
                    }
                    o = e;
                    ea = *(u8 *)(ep + 36);
                    eb = *(u8 *)(ep + 37);
                    mode = 0x3000;
                    e = *(u8 **)(o + 88) + 32;
                    if (*(u32 *)(o + 28) & 0x2000) {
                        mode = 0x300;
                    }
                    update_map_cell_flags_with_item_limit(ea, eb, mode);
                    if ((*(u32 *)(o + 20) & 0x20000000) && *(u8 *)(o + 19) == 30) {
                        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
                    }
                    detach_record_and_update_slot_state(o);
                    unlink_entity_node(o);
                    *(u16 *)(o - 2) |= 0x8000;
                    object_flag_block.flags |= 0x8000;
                }
            }
            e = *(u8 **)(e + 92) + 32;
        } while (e != ((u8 *)D_800E3D7C));
        if (phase < 0) {
            return;
        }
        rooms = D_800E2970;
        rm = rooms + phase * 20;
        *(s16 *)(rm + 10) = 0;
        return;
    }
    if (phase0 == 1) {
        if (*(s16 *)(w + 6) >= 0) {
            x = *(s16 *)(w + 8);
            x1 = *(s16 *)(w + 12);
            y1 = *(s16 *)(w + 14);
            k = 0;
            if (*(s16 *)(w + 4) > 0) {
                do {
                    y = *(s16 *)(w + 10);
                    if (y < y1) {
                        do {
                            s32 mul8 = 8 - (generate_random_value() & 7);
                            s32 dec = *(s16 *)(w + 4) - 1;
                            *(u16 *)(CELL(x, y) + 2) -= mul8 * (dec - k);
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                    if (x >= x1) {
                        break;
                    }
                    k = k + 1;
                } while (k < *(s16 *)(w + 4));
            }
        } else {
            x = 1;
            y1 = x1 = 63;
            k = 0;
            if (*(s16 *)(w + 4) > 0) {
                do {
                    y = 1;
                    if (y < y1) {
                        do {
                            s32 mul8 = 8 - (generate_random_value() & 7);
                            s32 dec = *(s16 *)(w + 4) - 1;
                            *(u16 *)(CELL(x, y) + 2) -= mul8 * (dec - k);
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                    if (x >= x1) {
                        break;
                    }
                    k = k + 1;
                } while (k < *(s16 *)(w + 4));
            }
        }
        t16 = *(u16 *)(w + 16) - 1;
        *(u16 *)(w + 16) = t16;
        if ((s16) t16 > 0) {
            return;
        }
        *(s16 *)(w + 16) = 1;
        *(u16 *)(w + 4) = *(u16 *)(w + 4) + 1;
        refresh_packed_grid_nibbles();
        if (!((x1 + 16) < *(s16 *)(w + 4))) {
            return;
        }
        if (*(s16 *)(w + 18) == 0) {
            *(s16 *)w = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
            return;
        }
        ctx->view.slot[0].callback = 0;
        ctx->view.slot[2].callback = 0;
        *(u16 *)w = *(u16 *)w + 1;
        return;
    }
    o = (u8 *)0x80010000;
    if (*(u16 *)(o + 0x3714) & 4) {
        func_80040AA0(3);
        return;
    }
    snapshot_inventory_and_familiars(((u8 *)D_800E3D7C));
    snapshot_inventory_familiar_records();
    check_action_boundary_and_set_flag();
    {
        u8 code;

        ch = *(u32 *)(o + 0x234);
        code = D_80082E6B;
        ch++;
        *(u32 *)(o + 0x234) = ch;
        ch = code;
    }
    D_8008146C = *(u16 *)(o + 0x234);
    func_80040AA0(ch);
    mark_sprite_resources_for_purge();
    *(u16 *)(w - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
}
