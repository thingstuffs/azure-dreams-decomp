/* Relink of matched dungeon/func_80F8A8F4; every changed retail word is a paired relocation. */
#define D_80170854 D_8016A854
#define D_80174B0C D_8016EB0C
#include "modules/dungeon_ovl_fa7000.h"
#include "dungeon/actor/hit_reaction_slot_f.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_801740F4_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_801740F4_1;   /* work in func_8016E0F4 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes();
extern s32 clear_byte_and_advance();
extern s32 append_entity_display_text();
#include "dungeon/player/object/action_state.h"
extern s32 display_text_with_fullwidth_adjustment();
extern s32 generate_random_value(void);

extern const u8 D_8016A854[20];
extern u8 D_8016EB0C[];

/* Start the actor's hit reaction, then build and post the damage message for it. */
void begin_actor_hit_reaction_slot_f(void *work, void *part_a, void *part_b, EntityRec *actor) {
    s32 flags;
    void *call_arg;
    u32 pass_result;
    s32 raw_result;
    s32 result;
    s32 field_60;
    u8 *table_base;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 0x10) == 0)) {
        ((S_801740F4_1 *)work)->unk_8C = 0;
        ((S_801740F4_1 *)work)->unk_9A = 0x17;
        ((S_801740F4_1 *)work)->unk_9B = 0;
        if (actor->flags1C & 0x400) {
            flags = actor->flags14;
            if (!(flags & 0x80000000)) {
                flags |= 0x80000000;
                actor->flags14 = (s32)flags;
                actor->facing = (u16)(((u16)actor->facing) + ((generate_random_value() & 7) << 9));
            }
        }
        field_60 = func_800A04F0(actor, ((Rec_D_80082E80 *)part_b)->unk_24, ((Rec_D_80082E80 *)part_b)->unk_25,
            (s16)((u16)actor->facing));
        table_base = D_8016EB0C;
        actor->target = field_60;
        (*(u8 **)((u8 *)part_b + 0x2C)) = table_base;
        func_80047784(part_b, table_base[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + (s16)((u16)actor->facing) + 0x100)
            >> 9) & 7], 0);
        actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        raw_result = get_unused_text_buffer();
        call_arg = actor;
        pass_result = raw_result;
        result = pass_result;
        raw_result = append_entity_display_text(call_arg, pass_result);
        clear_byte_and_advance(expand_text_control_codes(&D_8016A854, raw_result));
        display_text_with_fullwidth_adjustment(result);
    }
}

