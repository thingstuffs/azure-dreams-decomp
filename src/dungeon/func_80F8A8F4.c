#include "common.h"
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
} S_801740F4_1;   /* work in start_bank_actor_hit_reaction */




extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes();
extern s32 func_80099290();
extern s32 append_entity_display_text();
extern s32 has_pending_dungeon_activity();
extern s32 display_text_with_fullwidth_adjustment();
extern s32 generate_random_value(void);

const u8 D_80170854[20] = {129,64,130,146,130,143,130,129,130,146,130,133,130,132,129,68,0,0,0,0};
extern u8 D_80174B0C[];

/* Start the actor's hit reaction, then build and post the damage message for it. */
void start_bank_actor_hit_reaction(void *work, void *part_a, void *part_b, EntityRec *actor) {
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
        field_60 = place_actor_at_directional_neighbor(actor, ((Rec_D_80082E80 *)part_b)->unk_24, ((Rec_D_80082E80 *)part_b)->unk_25,
            (s16)((u16)actor->facing));
        table_base = D_80174B0C;
        actor->target = field_60;
        (((Rec_D_80082E80 *)part_b)->unk_2C.as_pu8) = table_base;
        select_sprite_entry(part_b, table_base[((s32)(g_game_work.view.viewAngle + (s16)((u16)actor->facing) + 0x100)
            >> 9) & 7], 0);
        actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
        g_dungeon_status.unk_0A = (u16)(((u16)g_dungeon_status.unk_0A) + 1);
        raw_result = get_unused_text_buffer();
        call_arg = actor;
        pass_result = raw_result;
        result = pass_result;
        raw_result = append_entity_display_text(call_arg, pass_result);
        func_80099290(expand_text_control_codes(&D_80170854, raw_result));
        display_text_with_fullwidth_adjustment(result);
    }
}

