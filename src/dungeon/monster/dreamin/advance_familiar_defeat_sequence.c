#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void select_sprite_entry(void *, s32, s32);
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void spend_actor_mp(void *, s32);
extern void try_apply_action_by_chance(void *, s32, s32);

extern void *actor_update_node_cursor;
extern u8 D_80170854[];
extern u8 D_80170E68;
extern u8 D_801738A4[];

/* Run the actor's two-step death sequence: post its message, then spawn the drop and release it. */
void advance_familiar_defeat_sequence(void *work, void *part_a, SpriteFrameState *part_b, void *actor)
{
    s32 first;
    s32 result;
    s32 saved_first;
    void *object;
    u8 state;

    state = U8(work, 0x9B);
    switch (state) {
    case 0:
        result = append_entity_display_text(actor, first = get_unused_text_buffer());
        saved_first = first;
        first = result;
        clear_byte_and_advance(expand_text_control_codes(D_80170854, first));
        display_text_with_fullwidth_adjustment(saved_first);
        object = scan_actor_along_heading(actor, part_b->unk_24, part_b->unk_25,
                               S16(actor, 0x2A), 0x10);
        PTR(actor, 0x60) = object;
        part_b->frameTable = D_801738A4;
        select_sprite_entry(part_b,
            D_801738A4[((g_game_work.view.camera_rotation.parts.viewAngle + S16(actor, 0x2A) + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x812);
        U8(work, 0x9B) = U8(work, 0x9B) + 1;
        S32(part_a, 0x14) = 0;
        S32(part_a, 0x10) = 0;
        S32(part_a, 0x0C) = 0;
        return;
    case 1:
        if (!(part_b->flags & 0xE000)) {
            return;
        }
        spend_actor_mp(actor, 0xC00);
        PTR(work, 0x8C) = &D_80170E68;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (S8(actor, 0x6D) == 0) {
            U16(actor, 0x46) &= 0x7FFF;
        } else {
            actor_update_node_cursor = (u8 *)actor - 0x20;
        }
        object = PTR(actor, 0x60);
        if (object != 0) {
            try_apply_action_by_chance(object, 0x10, 0x10);
        }
        break;
    }
}

/* MECHANISM: True-space advance_familiar_defeat_sequence turns 0x80173780/0x80173798 into local CFG joins
   and orders state-zero before state-one, preserving the 0x30 frame and five held bases.
   Byte-scaled table indexing keeps lbu/shift-nine; distinct result/saved_first lifetimes
   emit retail's a1<-v0 and call-delay s0<-a1 around append_entity_display_text. */
