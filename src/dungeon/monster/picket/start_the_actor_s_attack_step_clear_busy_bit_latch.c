#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/dungeon_trail_views.h"

typedef struct S_80047784 S_80047784;

typedef struct {
    s32 value;
} __attribute__((packed)) Packed4;

/* owner in start_the_actor_s_attack_step_clear_hex_71_busy_bit_latch */
typedef struct S_80174234_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80174234_0;

/* part in start_the_actor_s_attack_step_clear_hex_71_busy_bit_latch */
typedef struct S_80174234_1 {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} S_80174234_1;

/* actor in start_the_actor_s_attack_step_clear_hex_71_busy_bit_latch.  0x48 is written as one packed word (retail's
   lwl/lwr + swl/swr pair) and read one byte deep at 0x49, so the two views
   share a union rather than overlapping members. */
typedef struct S_80174234_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x1C];
    union {
        Packed4 at48;
        struct {
            u8 pad_48[0x1];
            u8 at49;
        } bytes;
    } unk_48;
    u8 pad_4C[0x21];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80174234_2;

/* the counter block at D_80083460 */


extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);         /* extern */
void *get_unused_text_buffer();                                /* extern */
u8 *expand_text_control_codes();                  /* extern */
void *clear_byte_and_advance();                         /* extern */
void *write_text_byte_and_advance();                    /* extern */
u8 *append_typed_formatted_value();                 /* extern */
u8 *append_entity_display_text();                     /* extern */
#include "dungeon/player/object/action_state.h"
s32 display_text_with_fullwidth_adjustment();                         /* extern */
s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */                                /* extern */
void *func_80170908(); /* Slot contract: loading images do not establish one callee contract. */                /* extern */
extern u8 D_8017089C[];
extern u8 D_801708AC[];
extern u8 D_801708B8[];
extern u8 D_801708BC[];
extern u8 picket_frame_set_8[];

/* Start the actor's attack step: clear its 0x71 busy bit, latch the 0x400 link flag with a random facing nudge, run the animation chain for the sprite record it owns, then arm owner state 0x17 and point the part at the direction table. */
void start_the_actor_s_attack_step_clear_hex_71_busy_bit_latch(S_80174234_0 *owner, void *unused, S_80174234_1 *part, S_80174234_2 *actor) {
    void *session;
    void *anim;
    s32 link_flags;
    void *sprite;

    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 0x10) == 0)) {
        if (actor->unk_1C & 0x400) {
            link_flags = actor->unk_14;
            if (!(link_flags & 0x80000000)) {
                link_flags |= 0x80000000;
                actor->unk_14 = (s32)link_flags;
                actor->unk_2A = (u16) (actor->unk_2A + ((generate_random_value() & 7) << 9));
            }
        }
        session = get_unused_text_buffer();
        if (actor->unk_48.bytes.at49 == 0) {
            sprite = func_80170908(part, actor);
            if (sprite != NULL) {
                actor->unk_48.at48 = *(Packed4 *) sprite;
                anim = append_typed_formatted_value(sprite, expand_text_control_codes(&D_801708AC, write_text_byte_and_advance(0xA, expand_text_control_codes(&D_8017089C,
                    append_entity_display_text(actor, session)))));
                anim = expand_text_control_codes(&D_801708B8, anim);
            } else {
                anim = expand_text_control_codes(&D_801708BC, append_entity_display_text(actor, session));
            }
        } else {
            anim = expand_text_control_codes(&D_801708BC, append_entity_display_text(actor, session));
        }
        clear_byte_and_advance(anim);
        display_text_with_fullwidth_adjustment(session);
        owner->unk_9A = 0x17;
        owner->unk_8C = 0;
        owner->unk_9B = 0;
        part->unk_2C = picket_frame_set_8;   /* the struct-member form `part->unk_2C = ...` is NOT byte-exact here: reorder-only 4 (same-multiset, one addiu+sw pair drifts) */
        select_sprite_entry(part, picket_frame_set_8[((g_game_work.view.camera_rotation.parts.viewAngle + (s16) actor->unk_2A + 0x100) >> 9) & 7], 0);
        actor->unk_6D = (u8) (actor->unk_6D - 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    }
}

/* MECHANISM: The four-argument ABI and true-space merge preserve retail's s1/a3, s4/a2, s3/a0, s2/s0
   roles. A packed four-byte assignment restores lwl/lwr/swl/swr; byte-table indexing plus a held
   D_80083460 base fixes the tail and its one-word displacement cascade. The final packed-copy scratch
   is v0 only at 2.7.2-cdk-G0; 2.8.1-G0 leaves the four-word t0 residue. */
