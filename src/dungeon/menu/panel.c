/* One native TU; source order follows the complete ledger cohort. */
#include "dungeon/menu/panel.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/object_node.h"

void *allocate_list_node();
extern s32 register_node();
s32 decode_fullwidth_text();
s32 build_positioned_text_glyphs();
extern char * func_8004E5A0(int value, unsigned short width, char *buf);
s32 func_80069E98();
void *func_800B119C();
extern s32 allocate_panel_offset_or_zero(void);
void offset_record_coordinates();
void set_record_flags_and_negate_x();
extern M2C_UNK D_80077FEC;
extern void update_attached_effect_position();
extern s32 D_800DEFF8[];
extern s32 transform_linked_quad_batches(u8 *, s32, u8 *);
/* Creates an entity panel with numeric labels, centered text, and a shaded background. */
void *create_panel_effect_object(void *owner)
{
    s8 text_buf[16];
    s32 prim_index;
    s32 prim_flags;
    s32 count_or_color;
    s32 blue_color;
    s32 color_or_addr;
    s32 vertex_color;
    s32 text_width;
    s32 text_addr;
    s32 text_addr_2;
    s32 red_color;
    s32 red_color_2;
    u16 text_id;
    void *owner_pos;
    void *panel_pos;
    void *digits;
    void *prim;
    void *panel_data;
    s32 *color_ptr;
    void *entity;
    void *panel;
    SpriteFrameState *transform;
    entity = owner;
    panel = allocate_list_node(0x12, ((u8 *)(&scene_object_list_anchor)));
    if (panel != 0) {
        color_or_addr = 0x808080;
        transform = *((void **) (((s8 *) panel) + 0xC));
        panel_pos = *((void **) (((s8 *) panel) + 8));
        transform->scale_x = 0x1000;
        transform->scale_y = 0x1000;
        transform->color.word = color_or_addr;
        transform->angle_y = 0xFC00;
        owner_pos = *((void **) (((s8 *) entity) + (-0x18)));
        *((u16 *) (((s8 *) panel_pos) + 2)) = (u16) (*((u16 *) (((s8 *) owner_pos) + 2)));
        *((u16 *) (((s8 *) panel_pos) + 6)) = (u16) (*((u16 *) (((s8 *) owner_pos) + 6)));
        *((s16 *) (((s8 *) panel_pos) + 0xA)) = (s16) ((*((u16 *) (((s8 *) owner_pos) + 0xA)))
            - (entity_height_offsets[*((u8 *) (((s8 *) entity) + 0x13))] + 0x50));
        *((s32 **) (((s8 *) panel) + 0x10)) = update_attached_effect_position;
        register_node(panel, transform_linked_quad_batches, owner_pos, panel_pos);
        panel_data = panel + 0x20;
        *((void **) (((s8 *) panel_data) + 0x14)) = entity;
        *((void **) (((s8 *) panel) + 0x20)) = (void *) (panel + 0x70);
        *((void **) (((s8 *) panel_data) + 4)) = (void *) (panel + 0x58);
        *((s32 **) (((s8 *) panel) + 0x70)) = &D_80077FEC;
        *((s32 *) (((s8 *) panel) + 0x58)) = color_or_addr;
        prim = allocate_panel_offset_or_zero();
        *((void **) (((s8 *) panel_data) + 0x28)) = prim;
        if (prim != 0) {
            void *owner_pos;
            count_or_color = 3;
            {
                s32 text_style;
                s32 text_style_2;
                text_style_2 = 9;
                text_buf[2] = text_style_2;
                text_buf[0] = text_style_2;
                text_style = 0x38;
                digits = &text_buf[4];
                text_buf[3] = text_style;
                text_buf[1] = text_style;
            }
            func_8004E5A0(*((u8 *) (((s8 *) entity) + 0x28)), count_or_color, digits);
            *((s32 *) (((s8 *) panel) + 0x74)) = build_positioned_text_glyphs(prim, text_buf, 0);
            offset_record_coordinates(prim, 8, ((s32) (0 - (((s32) ((*((u8 *) (((s8 *) prim) + 3))) << 0x18)) >> 8))) >> 0x10);
            set_record_flags_and_negate_x(prim, 8);
            prim += 0x24;
            *((s32 *) (((s8 *) panel) + 0x5C)) = color_or_addr;
            func_8004E5A0(*((u8 *) (((s8 *) entity) + 0x25)), 3, digits);
            *((s32 *) (((s8 *) panel) + 0x78)) = build_positioned_text_glyphs(prim, text_buf, 0);
            offset_record_coordinates(prim, 8, (s32) ((s16) ((0 - ((s8) (*((u8 *) (((s8 *) prim) + 3))))) + 8)));
            set_record_flags_and_negate_x(prim, 8);
            prim += 0x24;
            *((s32 *) (((s8 *) panel) + 0x60)) = color_or_addr;
            text_id = *((u16 *) (((s8 *) entity) + 0x46));
            color_ptr = (s32 *)((u8 *)panel + 0x64);
            if (text_id & 0x8000) {
                *((s32 *) (((s8 *) panel) + 0x7C)) = decode_fullwidth_text(prim, D_800DEFF8[text_id & 0x3FFF] + 1, 0);
                text_addr = D_800DEFF8[(*((u16 *) (((s8 *) entity) + 0x46))) & 0x3FFF];
                prim_index = 4;
                text_width = func_80069E98(text_addr + 1);
    
            }
            else {
                s32 *text_table = D_800DEFF8;
                *((s32 *) (((s8 *) panel) + 0x7C)) = decode_fullwidth_text(prim, text_table[4] + 1, 0);
                text_addr_2 = text_table[4];
                prim_index = 4;
                text_width = func_80069E98(text_addr_2 + 1);
            }
            text_width *= 4;
                offset_record_coordinates(prim, (s16) ((((s32) (0x20 - text_width)) >> 1) + 0x80),
                    (s32) ((s16) ((0 - ((s8) (*((u8 *) (((s8 *) prim) + 3))))) + 0x11)));
                set_record_flags_and_negate_x(prim, 8);
                prim += 0x30;
            *color_ptr = 0x808080;
            *((void **) (((s8 *) ((prim_index * 4) + panel_data)) + 0x50)) = prim;
            *((u8 *) (((s8 *) prim) + 1)) = 0x38U;
            *((s8 *) (((s8 *) prim) + 2)) = -2;
            *((s8 *) (((s8 *) prim) + 3)) = -2;
            *((s8 *) (((s8 *) prim) + 9)) = 0;
            *((s8 *) (((s8 *) prim) + 8)) = 0;
            *((s8 *) (((s8 *) prim) + 0xB)) = 0x24;
            *((s8 *) (((s8 *) prim) + 0xA)) = 0x24;
            prim_flags = 0xC0;
            *((u8 *) (((s8 *) prim) + 0)) = prim_flags;
            count_or_color = 0x202020;
            blue_color = 0x402020;
            owner_pos = 0x204020;
            red_color = 0x200000;
            *((s32 *) (((s8 *) panel_data) + 0x18)) = count_or_color;
            red_color |= 0x2040;
            *((s32 *) (((s8 *) panel_data) + 0x1C)) = blue_color;
            *((s32 *) (((s8 *) panel_data) + 0x20)) = owner_pos;
            *((s32 *) (((s8 *) panel_data) + 0x24)) = red_color;
            vertex_color = *((s32 *) (((s8 *) panel_data) + 0x18));
            *((s32 *) (((s8 *) prim) + 4)) = vertex_color;
            vertex_color = *((s32 *) (((s8 *) panel_data) + 0x1C));
            *((s32 *) (((s8 *) prim) + 0xC)) = vertex_color;
            vertex_color = *((s32 *) (((s8 *) panel_data) + 0x20));
            prim_index++;
            *((s32 *) (((s8 *) prim) + 0x10)) = vertex_color;
            red_color_2 = *((s32 *) (((s8 *) panel_data) + 0x24));
            vertex_color = (u8) ((*((u8 *) (((s8 *) prim) + 1))) | 2);
            *((u8 *) (((s8 *) prim) + 1)) = vertex_color;
            *((s32 *) (((s8 *) prim) + 0x14)) = red_color_2;
            prim += 0x18;
            *((void **) (((s8 *) ((prim_index * 4) + panel_data)) + 0x50)) = prim;
            *((u8 *) (((s8 *) prim) + 1)) = 0x81;
            *((s16 *) (((s8 *) prim) + 4)) = 0x40;
            *((s16 *) (((s8 *) prim) + 6)) = 0;
            *((u8 *) (((s8 *) prim) + 0)) = prim_flags;
        }
    }
    return panel;
}
#include "common.h"

extern ObjectNodeHeader * allocate_flagged_object_node();

/* Add 0x20 to a nonzero result from func_8003FC64(0), preserving zero. */
s32 allocate_panel_offset_or_zero(void) {
    s32 value;
    s32 adjusted_value;

    value = allocate_flagged_object_node(0);
    adjusted_value = 0;
    if (value != 0) {
        adjusted_value = value + 0x20;
    }
    return adjusted_value;
}
#include "common.h"

/* Offset the two coordinate bytes in each record through the end marker. */
void offset_record_coordinates(u8 *record, s32 x_offset, s32 y_offset) {
    u8 *record_y;

    while (1) {
        record_y = record + 3;
        record_y[-1] += x_offset;
        record_y[0] += y_offset;
        if (*(s8 *)record < 0) {
            break;
        }
        record += 0xC;
    }
}
#include "common.h"

/* Set record flags and negate each x coordinate when flag 4 is set. */
void set_record_flags_and_negate_x(u8 *record, s32 flags) {
    s32 record_flags = flags;
    u8 *record_x;
    flags &= 4;
    record_x = record + 2;

    for (;;) {
        record[0] = (u8)(record[0] | record_flags);
        if (flags != 0) {
            record_x[0] = (u8)(0 - record_x[0]);
        }
        if ((s8)record[0] < 0) {
            return;
        }
        record_x += 0xc;
        record += 0xc;
    }
}
/* Stamps one 16-bit value into every entry of a 12-byte record list.
 *
 * The list is walked from `list` in 12-byte steps; each entry's halfword at +6 is
 * overwritten, and the walk stops after the entry whose signed lead byte is negative
 * (the terminator is stamped too -- the store is unconditional, the test is not).
 *
 * family_delay_slot fixture - dungeon row at foff 0xCBC4C, 8 words.
 *
 * The row's rowbase record already fires: true link base 0x800B13AC (PROVEN
 * region xfer_dungeon_A3000), so owner decision B applies -- this TU defines
 * stamp_halfword_across_records and must never spell the synthetic row name anywhere in the
 * file (the collect/frontier naming screen, tools/codex_wave.py::_naming_defect,
 * matches on the raw text, comments included; the gate refuses the TU either
 * way).  Retail word 4 is `j 0x800B13AC` -- a jump to the function's OWN first
 * instruction, i.e. a LOOP BACK-EDGE, not a tail call.  The census candidate
 * modelled it as a self-recursive call `stamp_halfword_across_records()` (a fake zero-arg
 * extern that happens to name the function's own true address); maspsx LEAD 22
 * SHAPE A then flipped the jal to j and LEAD 19 elided the frame, reproducing
 * 7 of 8 words -- but a CALL's delay slot can never receive the loop induction
 * step, so word 5 stayed `nop` where retail has `addiu $a0,$a0,12`.
 *
 * Written as the loop it is, gcc's dbr fills the back-edge slot itself and the
 * leaf needs no frame at all -- no maspsx lever involved.
 *
 * 2026-09-22: the baseline audit's LABEL_AS_CALL site for this row targets the row's
 * OWN base, so census.live_sites was reading this file's definition header as a call of
 * itself and held the row at L0 long after the scaffolding was gone; fixed in
 * tools/census.py (DEF_HEADER_RE).  The C below has not changed since it was proven.
 *
 * Score with (the row identity is the synthetic name, which belongs on the
 * COMMAND LINE, never inside the TU):
 *   work/g3/overlay_func_compare.py --overlay dungeon --foff 0xCBC4C \
 *     --func "$(printf 'func_800%s' ABC4C)" \
 *     --c-file <this file> --match-config 2.7.2 \
 *     --container work/s3_splat/extract/DUNGEON_DUNGEON.BIN
 * -> MATCH ... size=32 words_off=0
 */
#include "common.h"

void stamp_halfword_across_records(void *list, s16 value) {
    for (;;) {
        s32 tag = *(s8 *)list;
        *(s16 *)((u8 *)list + 6) = value;
        if (tag < 0) {
            return;
        }
        list = (u8 *)list + 12;
    }
}
#include "common.h"

/* Applies a flag mask to each record through the terminal record. */
void apply_record_flags_through_end(void *record, s32 flag_mask) {
    u16 *flags;

    for (;;) {
        flags = (u16 *)((u8 *)record + 4);
        *flags = (u16)(*flags | flag_mask);
        if (*(s8 *)record < 0) {
            return;
        }
        record = (u8 *)record + 12;
    }
}
#include "common.h"

/* Set flags in the second byte of each record through the end marker. */
void set_record_byte_flags_through_end(u8 *record, s32 flags) {
    for (;;) {
        record[1] = record[1] | flags;
        if ((s8)record[0] < 0) {
            return;
        }
        record += 12;
    }
}
#include "common.h"

/* Copy records through the end marker and return the next destination slot. */
void *copy_records_through_end(void *dest, void *src) {
    void *src_tail = src + 8;
    void *dest_tail = dest + 8;

    do {
        *(s32 *)dest = *(s32 *)src;
        *(s32 *)(dest + 4) = *(s32 *)(src + 4);
        *(s32 *)(dest + 8) = *(s32 *)(src + 8);
        dest += 0xC;
        if (*(s8 *)src < 0) {
            return dest;
        }
        dest_tail += 0xC;
        src_tail += 0xC;
        src += 0xC;
    } while (1);
}
#include "common.h"

/* Find the first record with its end marker set. */
s8 *find_first_ended_record(s8 *record) {
    if (*record >= 0) {
        record += 0xC;
        while (*record >= 0) {
            record += 0xC;
        }
    }
    return record;
}
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

/* Returns whether the global record's unk_104 field is zero. */
s32 check_global_record_field_zero(void) {
    return ((PlayerRecord *)dungeon_actor_ring_anchor)->unk_104 == 0;
}
#include "common.h"

extern u8 held_item_kind_alias;

/* Returns whether D_80081485 is zero. */
s32 check_global_data_byte_zero(void) {
    return held_item_kind_alias == 0;
}
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

/* Return whether the current record's unk_9A value differs from 0x29. */
s32 check_current_record_value_not_29(void) {
    return dungeon_actor_ring_anchor->unk_9A != 0x29;
}
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800B14FC_0 {
    u8 pad_00[0x20];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    union { s16 s; u16 u; } unk_22;   /* accessed as both */
    s16 unk_24;
    union { s16 s; u16 u; } unk_26;   /* accessed as both */
} S_800B14FC_0;   /* base in update_fading_effect_scale */

typedef struct S_800B14FC_1 {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { u32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xE];
    u16 unk_1E;
    u8 pad_20[0x30];
    void * unk_50;
} S_800B14FC_1;   /* render.p in update_fading_effect_scale */

typedef struct S_800B14FC_2 {
    u8 pad_00[0x28];
    void * unk_28;
} S_800B14FC_2;   /* slot in update_fading_effect_scale */

typedef struct S_800B14FC_3_pre {
    u16 unk_00;
} S_800B14FC_3_pre;   /* the 0x2 bytes before object in update_fading_effect_scale, addressed as object[-1] */

#include "dungeon/menu/panel_callbacks.h"

extern void func_8004E994(void *object);

/* Updates effect scale and brightness, then releases its objects when fading out ends. */
void update_fading_effect_scale(void *effect, s32 unused, void *render_arg)
{
    struct { void *p; } render = {render_arg};
    hud_fade_predicate_fn *dispatch_table;
    s32 dispatch_entry;
    s16 state;

    dispatch_table = D_800DF030;
    dispatch_entry = ((S_800B14FC_0 *)effect)->unk_24;
    dispatch_entry = (u32)&dispatch_table[dispatch_entry];

    if ((*(hud_fade_predicate_fn *)dispatch_entry)() != 0 &&
        ((S_800B14FC_0 *)effect)->unk_20.s < 2) {
        ((S_800B14FC_0 *)effect)->unk_22.s = 4;
        ((S_800B14FC_0 *)effect)->unk_20.s = 2;
    }

    state = ((S_800B14FC_0 *)effect)->unk_20.s;
    switch (state) {
    case 1:
        return;
    case 0:
        {
            s16 steps;
            s16 countdown = ((S_800B14FC_0 *)effect)->unk_26.s;
            u16 countdown_value = ((S_800B14FC_0 *)effect)->unk_26.u;

            if (countdown != 0) {
                countdown_value -= 1;
                ((S_800B14FC_0 *)effect)->unk_26.u = countdown_value;
                return;
            }

            steps = ((S_800B14FC_0 *)effect)->unk_22.s;
            if (steps == 0) {
                return;
            }

            {
                u16 scale = ((S_800B14FC_1 *)render.p)->unk_1E;
                ((S_800B14FC_1 *)render.p)->unk_1E = scale + (0x1000 - scale) / steps;
            }

            {
                u8 brightness = ((S_800B14FC_1 *)render.p)->unk_0C.at02.v;
                steps = ((S_800B14FC_0 *)effect)->unk_22.s;
                brightness += (0x80 - brightness) / steps;
                ((S_800B14FC_1 *)render.p)->unk_0C.at02.v = brightness;
                ((S_800B14FC_1 *)render.p)->unk_0C.at01.v = brightness;
                ((S_800B14FC_1 *)render.p)->unk_0C.at00.v = brightness;
            }

            {
                s16 remaining_steps = ((S_800B14FC_0 *)effect)->unk_22.u - 1;
                ((S_800B14FC_0 *)effect)->unk_22.u = remaining_steps;
                if ((s16)remaining_steps != 0) {
                    return;
                }
            }

            ((S_800B14FC_1 *)render.p)->unk_1E = 0x1000;
            ((S_800B14FC_1 *)render.p)->unk_0C.at00u.v = 0x00808080;
            ((S_800B14FC_0 *)effect)->unk_20.u = ((S_800B14FC_0 *)effect)->unk_20.u + 1;
            return;
        }

    case 2:
        {
            s16 steps;
            steps = ((S_800B14FC_0 *)effect)->unk_22.s;
            if (steps != 0) {
                u16 scale = ((S_800B14FC_1 *)render.p)->unk_1E;
                ((S_800B14FC_1 *)render.p)->unk_1E = scale + (-(s32)scale / steps);

                {
                    u8 brightness = ((S_800B14FC_1 *)render.p)->unk_0C.at02.v;
                    steps = ((S_800B14FC_0 *)effect)->unk_22.s;
                    brightness += (-(s32)brightness / steps);
                    ((S_800B14FC_1 *)render.p)->unk_0C.at02.v = brightness;
                    ((S_800B14FC_1 *)render.p)->unk_0C.at01.v = brightness;
                    ((S_800B14FC_1 *)render.p)->unk_0C.at00.v = brightness;
                }
            }

            {
                u16 remaining_steps = ((S_800B14FC_0 *)effect)->unk_22.u - 1;
                ((S_800B14FC_0 *)effect)->unk_22.u = remaining_steps;
                if ((s16)remaining_steps > 0) {
                    return;
                }
            }

            render.p = effect;
            for (;;) {
                void *object = ((S_800B14FC_1 *)render.p)->unk_50;

                if ((s32)object > 0) {
                    render.p = (u8 *)render.p + 4;
                    func_8004E994(object);
                    continue;
                }
                render.p = (u8 *)render.p + 4;
                if (object == (void *)0) {
                    break;
                }
            }

            {
                s32 slot_index = 0;
                u32 *flags_page = (u32 *)0x80080000;
                void *slot = effect;
                for (; slot_index < 4; slot_index++, slot = (u8 *)slot + 4) {
                    void *object = ((S_800B14FC_2 *)slot)->unk_28;

                    if (object != (void *)0) {
                        ((S_800B14FC_3_pre *)object)[-1].unk_00 |= 0x8000;
                        flags_page[0x14A0 / 4] |= 0x8000;
                    }
                }
            }
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
    }
}
#include "common.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct AcHeader {
    u8 pad00[2];
    s16 field02;
    u8 pad04[2];
    s16 field06;
    u8 pad08[2];
    s16 field0A;
} AcHeader;

typedef struct AcMeta {
    u8 pad00[0x0C];
    u32 field0C;
    u8 pad10[4];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
} AcMeta;

typedef struct AcSub AcSub;

struct AcSub {
    void *field00;
    void *field04;
    u16 field08;
    s16 field0A;
    s16 field0C;
    u8 pad0E[2];
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1C;
    u8 pad20[2];
    u16 field22;
    s16 field24;
    u16 field26;
    void *field28;
    u8 pad2C[0x0C];
    u32 field38;
    u32 field3C;
    u8 pad40[0x10];
    void *slots[4];
};

typedef struct AcObject {
    u8 pad00[8];
    AcHeader *header;
    AcMeta *meta;
    void *field10;
    u8 pad14[0x0C];
    AcSub sub;
} AcObject;

extern void *D_80073618[];
extern s32 transform_linked_quad_batches(u8 *, s32, u8 *);
extern void update_fading_effect_scale(void *effect, s32 unused, void *render_arg);
extern s32 D_800DF03C[];

extern void * allocate_list_node();
extern s32 register_node();
extern s32 build_positioned_text_glyphs(void *, s32, s32);
extern s32 func_80069E98(s32);
extern s32 allocate_panel_offset_or_zero(void);
extern void offset_record_coordinates(u8 *, s32, s32);
extern void set_record_flags_and_negate_x(u8 *record, s32 flags);
extern void apply_record_flags_through_end(void *, s32);
extern void set_record_byte_flags_through_end(u8 *record, s32 flags);
extern void *copy_records_through_end(void *, void *);

/* Build the floating number/icon widget: allocate it and lay out its digit sprites for the given style. */
void build_floating_number_widget(s16 icon, s32 value_a, s32 value_b, s32 style, s16 compact, u16 unused_flags) {
    s32 tmp;
    s32 tmp2;
    s32 offset_x;
    s32 gap;
    s32 base_offset;
    s32 slot_x;
    s8 slot_y;
    s32 y_offset;
    s16 icon_held = icon;
    u8 *cursor;
    s32 style_hold = style;
    s32 count = 0;
    s16 style_byte;
    AcObject *obj;
    AcHeader *header;
    SpriteFrameState *meta;
    AcSub *sub;
    s32 *table_entry;
    u8 *base;
    u8 * base_2;
    void *new_buf;
    void *buf;
    void *prev_arg;
    register s32 hard_zero;
    u32 color1;
    u32 color2;
    u8 tail_flags;
    u32 tail_field1c;

    obj = allocate_list_node(0x12, ((u8 *)(&scene_object_list_anchor)));
    if (obj != NULL) {
        meta = obj->meta;
        header = obj->header;
        sub = &obj->sub;
        if ((compact << 0x10) != 0) {
            meta->flags |= 1;
        }
        header->field02 = value_a;
        sub->field0A = value_a;
        header->field06 = value_b;
        sub->field0C = value_b;
        header->field0A = 0;
        sub->field08 = 1;
        meta->scale_x = 0x1000;
        meta->color.word = 0;
        obj->field10 = update_fading_effect_scale;
        base = (u8 *)&sub->field38;
        register_node(obj, transform_linked_quad_batches);
        style_byte = style_hold & 0xFF;
        cursor = base;
        sub->field24 = (s16)((style_hold << 0x10) >> 0x18);
        sub->field00 = (u8 *)&sub->slots[0];
        sub->field04 = cursor;
        buf = allocate_panel_offset_or_zero();
        sub->field28 = buf;
        if (buf != NULL) {
            if (icon_held != 0) {
                count = 1;
                cursor = (u8 *)obj + 0x5C;
                slot_x = (s32)buf;
                obj->sub.slots[0] = (void *)slot_x;
                value_a = count;
                buf = D_80073618[icon_held];
                buf = copy_records_through_end((void *)slot_x, buf);
                obj->sub.field38 = 0x808080;
            } else {
                value_a = 0;
            }
            slot_x = (s32)buf;
            base_2 = (u8 *)D_800DF03C;
            table_entry = (s32 *)((style_byte * 4) + (s32)base_2);
            hard_zero = 0;
            *(void **)((u8 *)sub + 0x50 + count * 4) = (void *)build_positioned_text_glyphs((void *)slot_x, *table_entry, hard_zero);
            style_hold = func_80069E98(*table_entry) * 8;
            count++;
            tmp = value_a << 2;
            tmp += value_a;
            tmp2 = tmp << 1;
            offset_x = tmp2 + 0x80;
            if (((u16)compact << 0x10) != 0) {
                tmp = tmp2 + 0x76;
                tmp -= style_hold;
                offset_x = (s16)tmp;
            }
            offset_record_coordinates(buf, offset_x, (s16)((0 - (s8)((u8 *)buf)[3]) - 9));
            gap = 8;
            if (compact != 0) {
                gap = 4;
            }
            set_record_flags_and_negate_x(buf, gap);
            apply_record_flags_through_end(buf, 0x20);
            set_record_byte_flags_through_end(buf, 2);
            color1 = 0x808080;
            *(u32 *)cursor = color1;
            cursor += 4;
            buf = (u8 *)buf + 0x60;
            *(void **)((u8 *)sub + 0x50 + count++ * 4) = buf;
            slot_x = (s32)buf;
            prev_arg = (u8 *)buf - 0x60;
            new_buf = copy_records_through_end((void *)slot_x, prev_arg);
            slot_x = (s32)buf;
            buf = new_buf;
            offset_record_coordinates((void *)slot_x, 1, 1);
            color2 = 0x80808;
            tmp = count << 2;
            count++;
            base_offset = -0xA;
            tmp += (s32)sub;
            *(u32 *)cursor = color2;
            *(void **)((u8 *)tmp + 0x50) = buf;
            ((u8 *)buf)[1] = 0x38;
            if (value_a == 0) {
                base_offset = -2;
            }
            y_offset = base_offset;
            if (compact != 0) {
                y_offset -= 2;
            }
            tmp = value_a << 1;
            tmp += value_a;
            tmp <<= 3;
            slot_x = style_hold + tmp;
            ((s8 *)buf)[2] = y_offset;
            ((s8 *)buf)[3] = -0xE;
            ((s8 *)buf)[9] = 0;
            ((s8 *)buf)[8] = 0;
            if (value_a == 0) {
                slot_x += 4;
            }
            slot_y = slot_x;
            if (compact != 0) {
                slot_x = 0x80000;
                slot_y -= 2;
                color2 = slot_x;
            } else {
                color2 = 0x80000;
            }
            ((s8 *)buf)[0xA] = slot_y;
            slot_y = 0x10;
            slot_x = 0xC0;
            ((s8 *)buf)[0xB] = slot_y;
            ((u8 *)buf)[0] = slot_x;
            sub->field10 = 0;
            sub->field14 = 0;
            color2 |= 0x4008;
            sub->field18 = color2;
            sub->field1C = color2;
            *(s32 *)((u8 *)buf + 4) = sub->field10;
            *(s32 *)((u8 *)buf + 0xC) = sub->field14;
            *(s32 *)((u8 *)buf + 0x10) = sub->field18;
            tail_flags = ((u8 *)buf)[1];
            tail_field1c = sub->field1C;
            tail_flags |= 2;
            ((u8 *)buf)[1] = tail_flags;
            *(s32 *)((u8 *)buf + 0x14) = tail_field1c;
            buf = (u8 *)buf + 0x18;
            *(void **)((u8 *)sub + 0x50 + count * 4) = buf;
            ((u8 *)buf)[1] = 0x81;
            *(s16 *)((u8 *)buf + 4) = 0x20;
            *(s16 *)((u8 *)buf + 6) = 0;
            ((u8 *)buf)[0] = slot_x;
        }
        sub->field22 = 4;
        sub->field26 = unused_flags;
    }
}
#include "common.h"
#include "shared/object_node.h"
typedef struct S_800B1B10_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x34];
    s32 unk_58;
    u8 pad_5C[0x14];
    s32 unk_70;
    s32 unk_74;
} S_800B1B10_0;   /* obj in build_owned_floating_number_widget */

typedef struct S_800B1B10_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800B1B10_1;   /* header in build_owned_floating_number_widget */

typedef struct S_800B1B10_2 {
    u8 pad_00[0x4];
    void * unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
    union { s32 n; s32 v; } unk_18;   /* accessed as both */
    union { s32 n; s32 v; } unk_1C;   /* accessed as both */
    u8 pad_20[0x2];
    s16 unk_22;
    s16 unk_24;
    u16 unk_26;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
} S_800B1B10_2;   /* sub in build_owned_floating_number_widget */

typedef struct S_800B1B10_4 {
    u8 unk_00;
    u8 unk_01;
} S_800B1B10_4;   /* owner_held in build_owned_floating_number_widget */

typedef struct S_800B1B10_5 {
    u8 unk_00;
    union { u8 n; u8 v; } unk_01;   /* accessed as both */
    s8 unk_02;
    union { u8 u; s8 s; } unk_03;   /* accessed as both */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_04;   /* overlapping accesses */
    s8 unk_08;
    s8 unk_09;
    s8 unk_0A;
    s8 unk_0B;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B1B10_5;   /* (void *) b_held in build_owned_floating_number_widget */

typedef struct S_800B1B10_6 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800B1B10_6;   /* ((style_held++ * 4) + sub) in build_owned_floating_number_widget */

typedef struct S_800B1B10_7 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800B1B10_7;   /* ((style_held * 4) + sub) in build_owned_floating_number_widget */

extern void * allocate_list_node();
extern s32 register_node();
s32 decode_fullwidth_text();
s32 func_80069E98();
s32 get_unused_text_buffer();
s8 *append_typed_formatted_value();
extern s32 allocate_panel_offset_or_zero(void);
void offset_record_coordinates();
void set_record_flags_and_negate_x();
void set_record_byte_flags_through_end();
void *copy_records_through_end();
extern void update_fading_effect_scale(void *effect, s32 unused, void *render_arg);
extern s32 transform_linked_quad_batches(u8 *, s32, u8 *);

/* Build the floating number/icon widget for the owner: allocate it and lay out its digit sprites. */
void build_owned_floating_number_widget(void *owner, s32 value_a, s32 value_b, s32 style, s16 compact, u16 flags) {
    u16 subroutine_arg4;
    S_800B1B10_4 *owner_held = owner;
    s32 a_held = value_a;
    s32 b_held = value_b;
    s32 style_held = style;
    s16 compact_held = compact;
    u16 flags_held = flags;
    register s16 compact_s16;
    s32 offset;
    s32 obj;
    s32 obj_2;
    s32 style_byte;
    s32 geom;
    s32 call_kind;
    ObjectNodeHeader *alloc_data;
    s32 copy_a;
    s32 copy_b;
    s32 value_4;
    s32 value_5;
    s32 tail;
    void *sub;
    s32 *slots;
    S_800B1B10_1 *header;
    void *part;
    SpriteFrameState *meta;

    call_kind = 0x12;
    subroutine_arg4 = flags_held;
    alloc_data = &scene_object_list_anchor;
    obj = (s32) allocate_list_node(call_kind, alloc_data);
    compact_s16 = compact_held;
    if (obj != 0) {
        meta = ((S_800B1B10_0 *)obj)->unk_0C;
        header = ((S_800B1B10_0 *)obj)->unk_08;
        sub = obj + 0x20;
        header->unk_02 = a_held;
        header->unk_06 = b_held;
        ((S_800B1B10_2 *)sub)->unk_08 = 1;
        meta->scale_x = 0x1000;
        meta->color.word = 0;
        ((S_800B1B10_0 *)obj)->unk_10 = update_fading_effect_scale;
        register_node(obj, transform_linked_quad_batches);
        call_kind = 3;
        style_byte = (s32) (style_held << 0x10) >> 0x18;
        ((S_800B1B10_2 *)sub)->unk_24 = (s16) style_byte;
        ((S_800B1B10_2 *)sub)->unk_0A = a_held;
        ((S_800B1B10_2 *)sub)->unk_0C = b_held;
        ((S_800B1B10_0 *)obj)->unk_20 = (void *) (obj + 0x70);
        ((S_800B1B10_2 *)sub)->unk_04 = (void *) (obj + 0x58);
        if (has_enough_available_runtime_nodes(call_kind) != 0) {
            a_held = (s32) allocate_panel_offset_or_zero();
            slots = (s32 *) (obj + 0x5C);
            ((S_800B1B10_2 *)sub)->unk_28 = a_held;
            b_held = a_held;
            ((S_800B1B10_0 *)obj)->unk_70 = b_held;
            part = lookup_item_category_mapped_value(owner_held->unk_01, owner_held->unk_00);
            style_held = 2;
            b_held = (s32) copy_records_through_end((void *) b_held, part);
            apply_record_flags_through_end((void *) a_held, 0x20);
            set_record_byte_flags_through_end((void *) a_held, style_held);
            {
                s32 color_v0;
                color_v0 = 0x808080;
                ((S_800B1B10_0 *)obj)->unk_58 = color_v0;
            }
            value_4 = get_unused_text_buffer();
            *append_typed_formatted_value(owner_held, value_4) = 0;
            value_5 = decode_fullwidth_text((void *) b_held, value_4, 0);
            {
                s32 mask_v1;
                mask_v1 = 0x7FFFFFFF;
                ((S_800B1B10_0 *)obj)->unk_74 = value_5 & mask_v1;
            }
            obj_2 = func_80069E98(value_4) * 4;
            if ((compact_held << 0x10) != 0) {
                tail = 0x89 - obj_2;
                offset = (s16) tail;
            } else {
                offset = 0x8A;
            }
            offset_record_coordinates((void *) b_held, offset, (s16) ((0 - (s8) ((S_800B1B10_5 *)((void *) b_held))->unk_03.u)
                - 0xE));
            offset = 8;
            if ((compact_s16 << 0x10) != 0) {
                offset = 4;
            }
            set_record_flags_and_negate_x((void *) b_held, offset);
            apply_record_flags_through_end((void *) b_held, 0x20);
            set_record_byte_flags_through_end((void *) b_held, 2);
            {
                s32 color_v0;
                color_v0 = 0x808080;
                *slots = color_v0;
            }
            slots++;
            func_80069E98(value_4);
            b_held = (s32) allocate_panel_offset_or_zero();
            ((S_800B1B10_2 *)sub)->unk_2C = b_held;
            {
                s32 mask_v0;
                mask_v0 = 0x7FFFFFFF;
                ((S_800B1B10_6 *)(((style_held++ * 4) + sub)))->unk_50 = b_held & mask_v0;
            }
            copy_records_through_end((void *) b_held, value_5);
            offset_record_coordinates(value_5, 1, 1);
            b_held = (s32) allocate_panel_offset_or_zero();
            ((S_800B1B10_2 *)sub)->unk_30 = b_held;
            *slots = 0x80808;
            geom = 0x80000;
            ((S_800B1B10_7 *)(((style_held * 4) + sub)))->unk_50 = b_held;
            ((S_800B1B10_5 *)((void *) b_held))->unk_01.n = 0x38U;
            ((S_800B1B10_5 *)((void *) b_held))->unk_02 = -0xA;
            ((S_800B1B10_5 *)((void *) b_held))->unk_03.s = -0x10;
            ((S_800B1B10_5 *)((void *) b_held))->unk_0A = (s8) (obj_2 + 0x18);
            ((S_800B1B10_5 *)((void *) b_held))->unk_09 = 0;
            ((S_800B1B10_5 *)((void *) b_held))->unk_08 = 0;
            ((S_800B1B10_5 *)((void *) b_held))->unk_0B = 0x14;
            ((S_800B1B10_5 *)((void *) b_held))->unk_00 = 0xC0;
            ((S_800B1B10_2 *)sub)->unk_10 = 0;
            ((S_800B1B10_2 *)sub)->unk_14 = 0;
            geom |= 0x4008;
            ((S_800B1B10_2 *)sub)->unk_18.n = geom;
            ((S_800B1B10_2 *)sub)->unk_1C.n = geom;
            ((S_800B1B10_5 *)((void *) b_held))->unk_04.at00.v = (s32) ((S_800B1B10_2 *)sub)->unk_10;
            ((S_800B1B10_5 *)((void *) b_held))->unk_0C = (s32) ((S_800B1B10_2 *)sub)->unk_14;
            copy_a = ((S_800B1B10_2 *)sub)->unk_18.v;
            style_held++;
            ((S_800B1B10_5 *)((void *) b_held))->unk_10 = copy_a;
            copy_b = ((S_800B1B10_2 *)sub)->unk_1C.v;
            ((S_800B1B10_5 *)((void *) b_held))->unk_01.n |= 2;
            ((S_800B1B10_5 *)((void *) b_held))->unk_14 = copy_b;
            b_held += 0x18;
            ((S_800B1B10_7 *)(((style_held * 4) + sub)))->unk_50 = b_held;
            ((S_800B1B10_5 *)((void *) b_held))->unk_01.n = 0x81;
            ((S_800B1B10_5 *)((void *) b_held))->unk_04.at00u.v = 0x20;
            ((S_800B1B10_5 *)((void *) b_held))->unk_04.at02.v = 0;
            ((S_800B1B10_5 *)((void *) b_held))->unk_00 = 0xC0;
        }
        ((S_800B1B10_2 *)sub)->unk_22 = 4;
        flags_held = subroutine_arg4;
        ((S_800B1B10_2 *)sub)->unk_26 = flags_held;
    }
}
#include "common.h"
#include "m2c_compat.h"

void upload_vram_row_and_cache(); /* extern */
extern u8 D_800DF068[];

typedef struct S_800B1E80_0 {
    u16 unk_00;
    u16 unk_02;
} S_800B1E80_0;   /* arg0 in advance_cyclic_panel_entry */

/* Advance the cyclic table index every four ticks and apply the selected entry. */
void advance_cyclic_panel_entry(S_800B1E80_0 *state) {
    u16 ticks_left;
    u16 entry_index;

    ticks_left = state->unk_00 - 1;
    state->unk_00 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        state->unk_00 = 4U;
        entry_index = state->unk_02 + 8;
        state->unk_02 = entry_index;
        if ((s16) entry_index >= 0x60) {
            state->unk_02 = 0U;
        }
        upload_vram_row_and_cache(((s16) state->unk_02 * 4) + D_800DF068, 0x7340, 1, 2);
    }
}
#include "shared/object_node.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
struct S_800B1E80_0;
extern void advance_cyclic_panel_entry(struct S_800B1E80_0 *state);

typedef struct S_800B1F00_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800B1F00_0;

/* Create an object and assign advance_cyclic_panel_entry to its data pointer. */
void create_entity_panel_object(void) {
    S_800B1F00_0 *object;

    object = allocate_flagged_object_node(0);
    if (object != 0) {
        object->unk_10 = advance_cyclic_panel_entry;
    }
}
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_800B1F34_0 {
    s16 * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u16 unk_06;
} S_800B1F34_0;   /* arg0 in advance_timed_panel_motion */

typedef struct S_800B1F34_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800B1F34_1;   /* arg1 in advance_timed_panel_motion */

typedef struct S_800B1F34_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B1F34_2;   /* global in advance_timed_panel_motion */

/* Advances timed motion phases, updates the output offset, and sets the global update flag. */
void advance_timed_panel_motion(S_800B1F34_0 *animation, S_800B1F34_1 *motion)
{
    s16 state;
    u16 countdown;
    S_800B1F34_2 *update_state;

    state = animation->unk_04.s;
    switch (state) {
    case 0:
        animation->unk_06 = 0x10;
        animation->unk_04.u++;
    case 1:
        motion->unk_14 -= 0x4000;
        countdown = animation->unk_06 - 1;
        animation->unk_06 = countdown;
        if ((s16)countdown < 0) {
            animation->unk_06 = 0x40;
            animation->unk_04.u++;
        }
        break;
    case 2:
        motion->unk_14 += 0x6000;
        countdown = animation->unk_06 - 1;
        animation->unk_06 = countdown;
        if ((s16)countdown < 0) {
            animation->unk_06 = 0x3C;
            animation->unk_04.u++;
        }
    case 3:
        countdown = animation->unk_06 - 1;
        animation->unk_06 = countdown;
        if ((s16)countdown < 0) {
            motion->unk_14 = 0;
            animation->unk_06 = 0x3C;
            animation->unk_04.u++;
        }
        break;
    }
    update_state = primary_actor_record;
    motion->unk_08.at00.v -= motion->unk_14;
    update_state->unk_1C |= 0x40000000;
    *animation->unk_00 = 0x20 - motion->unk_08.at02.v;
}
#include "shared/object_node.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
extern s32 register_node();
void play_sound_if_enabled(s32);
extern int draw_linked_lit_meshes();
struct S_800B1F34_0;
struct S_800B1F34_1;
extern void advance_timed_panel_motion(struct S_800B1F34_0 *animation, struct S_800B1F34_1 *motion);

typedef struct S_800B2074_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    u16 * unk_20;
} S_800B2074_1;

typedef struct S_800B2074_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_800B2074_3;

typedef struct S_800B2074_4 {
    s16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800B2074_4;

typedef struct S_800B2074_5 {
    u8 pad_00[0xE];
    u16 unk_0E;
    u8 pad_10[0x1A];
    u16 unk_2A;
} S_800B2074_5;

typedef union { void *pointer; u32 word; } InitSlot;
/* Creates an object at the given map position and updates its tile record. */
s32 create_map_position_object(s32 world_x, s32 world_z) {
    s32 tile_addr;
    void *object;
    s32 pos_x;
    s32 pos_z;
    void *init_object;
    void *init_data;

    S_800B2074_5 *state_fields;
    u16 inherited_value;
    S_800B2074_3 *transform;
    SpriteFrameState *render_state;

    pos_x = world_x;
    pos_z = world_z;
    tile_addr = g_game_work.map.cells;
    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        init_object = object;
        {
            InitSlot slot = { advance_timed_panel_motion };
            init_data = draw_linked_lit_meshes;
            ((S_800B2074_1 *)object)->unk_10 = slot.pointer;
            register_node(init_object, init_data);
        }
        render_state = ((S_800B2074_1 *)object)->unk_0C;
        render_state->unk_20 = 0x1000;
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->source = 2;
        render_state->color.word = 0x808080;
        transform = ((S_800B2074_1 *)object)->unk_08;
        transform->unk_16 = 6;
        transform->unk_02 = pos_x;
        transform->unk_06 = pos_z;
        tile_addr += (((s32) (pos_x << 0xA) >> 0x10) + (((s32) (pos_z << 0xA) >> 0x10) << g_game_work.map.shiftX)) * 6;
        ((S_800B2074_1 *)object)->unk_20 = (u16 *) (tile_addr + 2);
        ((S_800B2074_4 *)tile_addr)->unk_00 = 3;
        transform->unk_0A = (s16) (0 - *((S_800B2074_1 *)object)->unk_20);
        ((S_800B2074_4 *)tile_addr)->unk_02 = (u16) (((S_800B2074_4 *)tile_addr)->unk_02 + 0x20);
        ((S_800B2074_4 *)tile_addr)->unk_04 = (u16) (((S_800B2074_4 *)tile_addr)->unk_04 | 1);
        state_fields = object + 0x20;
        play_sound_if_enabled(0x603);
        inherited_value = ((u16)primary_actor_record->facing);
        state_fields->unk_0E = inherited_value;
    }
}
#include "common.h"

extern void advance_sprite_animation_and_textures(s32);
extern struct { s32 unk0; s32 pad[2]; } D_800814A0;

/* Advances the accumulator and decrements the counter, setting flags on underflow. */
void advance_panel_accumulator(void *counter_state, void *accumulator, s32 update_arg) {
    s16 remaining;

    *((s32 *) accumulator + 2) = *((s32 *) accumulator + 2) + 0x8000;
    advance_sprite_animation_and_textures(update_arg);
    remaining = *(u16 *) ((u8 *) counter_state + 6) - 1;
    *(u16 *) ((u8 *) counter_state + 6) = remaining;
    if (remaining < 0) {
        *(u16 *) ((u8 *) counter_state - 2) |= 0x8000;
        D_800814A0.unk0 = D_800814A0.unk0 | 0x8000;
    }
}
#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct {
    s32 word[6];
} CopyBlock;

typedef struct {
    u8 pad00[0x0C];
    s32 color;
    u8 pad10[0x0C];
    u16 scale_x;
    u16 scale_y;
} RenderPart;

typedef struct {
    u8 pad00[8];
    CopyBlock *copy_dst;
    RenderPart *part;
    void *callback;
    u8 pad14[0x12];
    u16 kind;
} Object;

extern s32 register_node();
extern void select_record_entry_and_value(RenderPart *part, void *data, s32 index);

extern void advance_panel_accumulator(void *counter_state, void *accumulator, s32 update_arg);
extern u8 D_800DEC70[16];

/* Creates an object from the source block and initializes its render part. */
void create_rendered_panel_object(CopyBlock *source)
{
    Object *object;
    SpriteFrameState *part;

    object = (Object *)allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->callback = advance_panel_accumulator;
        register_node(object, project_sprite_chain);
        *object->copy_dst = *source;

        part = object->part;
        part->color.word = 0x00808080;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        select_record_entry_and_value(part, D_800DEC70, 0);
        object->kind = 0x20;
    }
}
