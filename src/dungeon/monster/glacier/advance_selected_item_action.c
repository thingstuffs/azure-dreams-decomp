#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x1C];
    u32 field_1C;
    u8 pad_20[0xA];
    union {
        s16 s16;
        u16 u16;
    } field_2A;
    u8 pad_2C[0x1A];
    u16 field_46;
    u8 pad_48[0x18];
    void *field_60;
    u8 pad_64[0x9];
    u8 field_6D;
    u8 pad_6E[0x4];
    union {
        s8 s8;
        u8 u8;
    } field_72;
    union {
        s8 s8;
        u8 u8;
    } field_73;
} ActorFieldView_810318E4;

typedef struct {
    u8 pad_00[0xA6];
    u16 field_A6;
} ActiveFieldView_810318E4;

typedef struct Copy48 {
    u32 words[12];
} Copy48;

extern s32 resolve_record_orientation_or_fallback(void *, void *, u16 *, s32);
extern s32 get_cd_command_queue_depth(void);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, u8, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, void *);

extern u8 D_801708D4;
extern u8 D_801714B8;
extern u8 D_8017609C[];
extern u8 D_801760FC[];

typedef struct S_801730E4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801730E4_0;   /* arg0 in advance_selected_item_action_2 */

typedef struct S_801730E4_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801730E4_1_pre;   /* the 0x14 bytes before active in advance_selected_item_action_2, addressed as active[-1] */

typedef struct S_801730E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801730E4_2;   /* linked in advance_selected_item_action_2 */

typedef struct S_801730E4_5 {
    u8 pad_00[0x94];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_801730E4_5;   /* part in advance_selected_item_action_2 */

typedef struct S_801730E4_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_801730E4_6;   /* object in advance_selected_item_action_2 */

typedef struct S_801730E4_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_801730E4_7;   /* target in advance_selected_item_action_2 */

typedef struct S_801730E4_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_801730E4_8;   /* held_base in advance_selected_item_action_2 */

typedef struct S_801730E4_9 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801730E4_9;   /* source in advance_selected_item_action_2 */

/* Advances the selected item's action, visual effect, and cleanup states. */
void advance_selected_item_action_2(void *action, ObjectPosition *position, void *sprite, void *actor)
{
    u16 position_delta[3];
    s16 is_special;
    void *active;
    u32 linked;
    u8 linked_x;
    u8 linked_y;
    u8 *selection;
    u8 *owner_object;
    u8 state;

    is_special = 0;
    owner_object = (u8 *)action - 0x20;
    state = ((S_801730E4_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((((ActorFieldView_810318E4 *)actor)->field_1C) & 0x2000) {
            switch ((((ActorFieldView_810318E4 *)actor)->field_46) & 0x3FFF) {
            case 7:
                is_special = 1;
                /* fallthrough */
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fallthrough */
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fallthrough */
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        } else {
            switch ((((ActorFieldView_810318E4 *)actor)->field_46) & 0x3FFF) {
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        }

        if (*selection != 0) {
            ((S_801730E4_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 use_special = is_special;

                if (use_special != 0) {
                    active = primary_actor_record;
                    (((ActorFieldView_810318E4 *)actor)->field_60) = active;
                    linked = (u32)((S_801730E4_1_pre *)active)[-1].unk_00;
                    (((ActorFieldView_810318E4 *)actor)->field_72.u8) = ((S_801730E4_2 *)linked)->unk_24;
                    (((ActorFieldView_810318E4 *)actor)->field_73.u8) = ((S_801730E4_2 *)linked)->unk_25;
                } else {
                    linked = item_action_definitions[*selection].kind;
                    if (linked == 2) {
                        active = (((ActorFieldView_810318E4 *)actor)->field_60);
                        if (active != 0) {
                            linked = (u32)((S_801730E4_1_pre *)active)[-1].unk_00;
                            (((ActorFieldView_810318E4 *)actor)->field_72.u8) = ((S_801730E4_2 *)linked)->unk_24;
                            (((ActorFieldView_810318E4 *)actor)->field_73.u8) = ((S_801730E4_2 *)linked)->unk_25;
                        }
                    } else {
                        {
                            s32 target_x;
                            s32 target_y;

                            target_x = (s32)scan_monster_along_heading(
                                actor, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                                (((ActorFieldView_810318E4 *)actor)->field_2A.s16), 0x10);
                            (*(void * volatile *)((u8 *)actor + 0x60)) = (void *)target_x;
                            target_x = (((ActorFieldView_810318E4 *)actor)->field_72.s8);
                            target_y = (((ActorFieldView_810318E4 *)actor)->field_73.s8);
                            if (target_x < 0) {
                                target_x = -target_x;
                            }
                            if (target_y < 0) {
                                target_y = -target_y;
                            }
                            (((ActorFieldView_810318E4 *)actor)->field_72.u8) = target_x;
                            (((ActorFieldView_810318E4 *)actor)->field_73.u8) = target_y;
                        }
                    }
                }
            }

            if (create_actor_spell_effect(actor, selection, is_special, (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_801730E4_0 *)action)->unk_96 = 10;
            ((S_801730E4_0 *)action)->unk_9B++;
            play_sound_if_enabled(0x703);
            return;
        }
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        {
            void *active;

            active = primary_actor_record;
            g_dungeon_status.active_actor = 0;
            (((ActiveFieldView_810318E4 *)active)->field_A6)--;
        }
        advance_status_timers(actor);
        (((ActorFieldView_810318E4 *)actor)->field_6D)--;
        ((S_801730E4_0 *)action)->unk_8C = &D_801714B8;
        (((ActorFieldView_810318E4 *)actor)->field_73.u8) = 0;
        (((ActorFieldView_810318E4 *)actor)->field_72.u8) = 0;
        (((ActorFieldView_810318E4 *)actor)->field_46) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((S_801730E4_0 *)action)->unk_96 = 10;
        ((S_801730E4_0 *)action)->unk_9B++;
        {
            u8 *effect_object;

            effect_object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
            if (effect_object != 0) {
                u8 *effect_state;
                u8 *effect_data;
                void *owner_sprite;
                u8 animation_id;

                effect_state = effect_object + 0x20;
                ((S_801730E4_5 *)effect_state)->unk_96 = 0xF;
                ((S_801730E4_6 *)effect_object)->unk_10 = &D_801708D4;
                ((S_801730E4_5 *)effect_state)->unk_A8 = position;
                ((S_801730E4_5 *)effect_state)->unk_94 = (((ActorFieldView_810318E4 *)actor)->field_2A.u16);
                effect_data = ((S_801730E4_6 *)effect_object)->unk_0C;
                *(Copy48 *)effect_data = *(Copy48 *)sprite;
                ((S_801730E4_7 *)effect_data)->unk_1E = 0x1000;
                ((S_801730E4_7 *)effect_data)->unk_1C = 0x1000;
                ((S_801730E4_7 *)effect_data)->unk_0E = 0x80;
                ((S_801730E4_7 *)effect_data)->unk_0D = 0x80;
                ((S_801730E4_7 *)effect_data)->unk_0C = 0x80;
                register_node(effect_object, project_sprite_chain);
                animation_id = D_801760FC[0];
                ((S_801730E4_7 *)effect_data)->unk_2C = D_801760FC;
                select_sprite_entry(effect_data, animation_id, 0);
                ((S_801730E4_7 *)effect_data)->unk_10 = 0x20;
                ((S_801730E4_7 *)effect_data)->unk_12 = 0xFF80;
                ((S_801730E4_7 *)effect_data)->unk_14 |= 0xC;

                owner_sprite = ((S_801730E4_8 *)owner_object)->unk_0C;
                effect_data = ((S_801730E4_6 *)effect_object)->unk_08;
                if (resolve_record_orientation_or_fallback(((S_801730E4_9 *)owner_sprite)->unk_08, owner_sprite, position_delta, 0) != 0) {
                    ((S_801730E4_7 *)effect_data)->unk_02 = ((u16)position->x.w.i);
                    ((S_801730E4_7 *)effect_data)->unk_06 = ((u16)position->y.w.i);
                    ((S_801730E4_7 *)effect_data)->unk_0A = ((u16)position->z.w.i);
                    ((S_801730E4_7 *)effect_data)->unk_02 += position_delta[0];
                    ((S_801730E4_7 *)effect_data)->unk_06 += position_delta[1];
                    ((S_801730E4_7 *)effect_data)->unk_0A += position_delta[2];
                }
            }
        }

    case 2:
        {
            u16 timer;

            timer = ((S_801730E4_0 *)action)->unk_96 - 1;
            ((S_801730E4_0 *)action)->unk_96 = timer;
            if ((s16)timer > 0 && !(((SpriteFrameState *)sprite)->flags & 0xE000)) {
                return;
            }
        }
        ((S_801730E4_0 *)action)->unk_98 |= 0x80;
        ((S_801730E4_0 *)action)->unk_9B++;
        return;

    case 3:
        if ((((SpriteFrameState *)sprite)->unk_04 == 2 &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            ((S_801730E4_0 *)action)->unk_96 = 0x14;
        }
        {
            u16 timer;

            if (((s32)g_dungeon_status.active_actor) == 0) {
                ((S_801730E4_0 *)action)->unk_96 = 0;
            }
            timer = ((S_801730E4_0 *)action)->unk_96 - 1;
            ((S_801730E4_0 *)action)->unk_96 = timer;
            if ((s16)timer <= 0) {
                ((S_801730E4_0 *)action)->unk_96 = 0;
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            }
            if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
                return;
            }

            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != D_8017609C) {
                s32 direction_index;

                ((SpriteFrameState *)sprite)->frameTable = D_8017609C;
                direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + (((ActorFieldView_810318E4 *)actor)->field_2A.s16) + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, D_8017609C[direction_index], 0);
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            }
            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((S_801730E4_0 *)action)->unk_8C = &D_801714B8;
        advance_status_timers(actor);
        (((ActorFieldView_810318E4 *)actor)->field_73.u8) = 0;
        (((ActorFieldView_810318E4 *)actor)->field_72.u8) = 0;
        (((ActorFieldView_810318E4 *)actor)->field_6D)--;
        (((ActorFieldView_810318E4 *)actor)->field_46) &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        return;
    default:
        return;
    }
}
