/* Relink of matched dungeon/func_80A4BA70; every changed retail word is a paired relocation. */
#define advance_actor_transition_and_restore_child_angle func_8016F270
#define D_801758FC D_8016F8FC
#define D_80175904 D_8016F904
#define D_8017591C D_8016F91C
#define D_80175920 D_8016F920
#define D_80175921 D_8016F921
#define D_80175924 D_8016F924
#define D_80175928 D_8016F928
#define fade_effect_to_neutral_and_finish D_8016F114
#include "modules/dungeon_resource06_slot0.h"
extern s32 func_8016DE08(void *, s32, void *, s32);
extern void func_8016EE78(void *, void *, void *);
extern s32 func_80069EF8(void);

void func_8016F270(void *action, EntityRec *position, Rec_D_80082E80 *entity, void *actor)
{
    R06_80175270_S_80175270_2 *work = ((u8 *)(&g_game_work));
    u8 state;
    s32 effect_id;
    s32 direction;
    s32 raw_direction;
    u16 angle;

    state = ((R06_80175270_S_80175270_0 *)action)->unk_9B;
    if (state >= 9) {
        return;
    }
    switch (state) {
    case 0:
        ((R06_80175270_S_80175270_0 *)action)->unk_9B++;
        return;

    case 1:
        func_80041588(((u8 *)D_8016F8FC), ((u8 *)D_8016F920), 0);
        ((R06_80175270_S_80175270_0 *)action)->unk_BA = 0;
        ((R06_80175270_S_80175270_0 *)action)->unk_9B++;
        ((R06_80175270_S_80175270_1 *)actor)->unk_8A = ((R06_80175270_S_80175270_1 *)actor)->unk_2A.u;
        ((R06_80175270_S_80175270_1 *)actor)->unk_1C &= 0xFFFBFFFF;
        /* fallthrough */

    case 2:
        angle = ((R06_80175270_S_80175270_1 *)actor)->unk_2A.u;
        raw_direction = (g_game_work.view.viewAngle + ((R06_80175270_S_80175270_1 *)actor)->unk_2A.s + 0x100) >> 9;
        direction = raw_direction & 7;
        if ((((u8 *)((void * *)D_8016F924))[-4] == 0) || (direction != 2)) {
            if (direction == 2) {
                return;
            }
            ((R06_80175270_S_80175270_1 *)actor)->unk_2A.u = angle + 0x200;
            return;
        }
        func_80041588((u8 *)((s32 *)D_8016F904) - 8, (u8 *)((void * *)D_8016F924) - 4, 1);
        sound_set_cd_cue_parameters(0, ((s32 *)D_8006CD58)[0], 0x04000AD4, 0x05000CC4);
        effect_id = func_800445E0();
        Control_CD(0x15, effect_id, 0);
        ((u8 *)D_8016F921)[0] = 0;
        Control_CD(0xFF, ((s32 *)D_8003E140), ((u8 *)D_8016F921));
        select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, position, 8, 0x300);
        ((R06_80175270_S_80175270_0 *)action)->unk_96.s = 0x10;
        ((R06_80175270_S_80175270_0 *)action)->unk_9B++;
        /* fallthrough */

    case 3:
        {
            s32 frames_left;
            u8 *target_color;
            u8 effect_done;

            frames_left = ((R06_80175270_S_80175270_0 *)action)->unk_96.u;
            ((R06_80175270_S_80175270_0 *)action)->unk_96.u = frames_left - 1;
            if ((s16)(frames_left - 1) <= 0) {
                effect_done = ((u8 *)D_8016F921)[0];
                ((R06_80175270_S_80175270_0 *)action)->unk_96.u = frames_left;
                if (effect_done != 0) {
                    ((R06_80175270_S_80175270_0 *)action)->unk_9B++;
                    play_sound_if_enabled(0x300);
                    return;
                }
                return;
            }
            target_color = ((u8 * *)D_800DCEEC)[lookup_masked_byte_table(actor)];
            work->unk_A8 += (((R06_80175270_S_80175270_3 *)target_color)->unk_00 - work->unk_A8) / ((R06_80175270_S_80175270_0 *)action)->unk_96.s;
            work->unk_A9 += (((R06_80175270_S_80175270_3 *)target_color)->unk_01 - work->unk_A9) / ((R06_80175270_S_80175270_0 *)action)->unk_96.s;
            work->unk_AA += (((R06_80175270_S_80175270_3 *)target_color)->unk_02 - work->unk_AA) / ((R06_80175270_S_80175270_0 *)action)->unk_96.s;
            return;
        }

    case 4:
        {
            s16 asset_index;
            s32 *position_y_dst;
            s32 *position_z_dst;
            s32 position_y;
            s32 position_z;
            s32 color;

            work = func_8003FC64(0x12);
            if (work == 0) {
                return;
            }
            work->unk_10.p = ((u8 *)fade_effect_to_neutral_and_finish);
            func_8004491C(work, ((u8 *)func_8016DE08));
            color = 0x00808080;
            work->unk_08[0] = position->x.v;
            position_y_dst = work->unk_08;
            position_y = position->y.v;
            ((void * *)D_8016F924)[0] = work;
            position_y_dst[1] = position_y;
            position_z_dst = work->unk_08;
            position_z = position->z.v;
            ((s16 *)D_8016F91C)[0] = -12;
            position_z_dst[2] = position_z;
            work = work->unk_0C.p;
            work->unk_1E = 0x1000;
            work->unk_1C = 0x1000;
            work->unk_0C.i = color;
            asset_index = lookup_masked_byte_table(actor) - 1;
            if (asset_index < 0) {
                asset_index = func_80069EF8() % 3;
            }
            func_8003DB94(work, ((u8 *)D_8014A000) + ((s32 *)D_8016F904)[asset_index], 0);
            entity->unk_14.at00_u16.v |= 0x80;
            ((R06_80175270_S_80175270_0 *)action)->unk_96.s = 0;
            ((R06_80175270_S_80175270_0 *)action)->unk_9B++;
            func_8016EE78(action, position, entity);
            return;
        }

    case 5:
        {
            work = ((void * *)D_8016F924)[0];
            work = work->unk_0C.p;
            if (work->unk_14 & 0xE000) {
                ((R06_80175270_S_80175270_0 *)action)->unk_96.s = 0x10;
                ((R06_80175270_S_80175270_0 *)action)->unk_9B++;
                decrement_monster_entry_count(((R06_80175270_S_80175270_1 *)actor)->unk_13, 3);
                update_map_cell_flags_with_item_limit(entity->unk_24, entity->unk_25, 0x300);
                unlink_entity_node(actor);
                work = (u8 *)actor - 0x20;
                work->unk_10.i |= 0x80000000;
            }
        }

    case 6:
        {
            if (((R06_80175270_S_80175270_0 *)action)->unk_9B != 6) {
                return;
            }
            if (create_status_linked_render_effect(position, ((s32 *)D_8016F928)[0], (s16)((s16 *)D_8016F91C)[0], ((u8 *)D_800DCF5C)) == 0) {
                return;
            }
            ((R06_80175270_S_80175270_0 *)action)->unk_96.s = 0x10;
            ((R06_80175270_S_80175270_0 *)action)->unk_9B++;
            decrement_monster_entry_count(((R06_80175270_S_80175270_1 *)actor)->unk_13, 3);
            update_map_cell_flags_with_item_limit(entity->unk_24, entity->unk_25, 0x300);
            unlink_entity_node(actor);
            work = (u8 *)actor - 0x20;
            work->unk_10.i |= 0x80000000;
            return;
        }

    case 7:
        {
            void *child;
            R06_80175270_S_80175270_7 *child_obj;
            s16 direction;

            if ((((R06_80175270_S_80175270_1 *)actor)->unk_60 = advance_staged_entity_load(entity, actor)) == 0) {
                return;
            }
            ((R06_80175270_S_80175270_0 *)action)->unk_96.s = 0x10;
            ((R06_80175270_S_80175270_0 *)action)->unk_9B++;
            ((R06_80175270_S_80175270_9 *)(((R06_80175270_S_80175270_1 *)actor)->unk_60))->unk_2A = ((R06_80175270_S_80175270_1 *)actor)->unk_2A.u;
            child = ((R06_80175270_S_80175270_1 *)actor)->unk_60;
            child_obj = ((R06_80175270_S_80175270_6_pre *)child)[-1].unk_00;
            direction = (g_game_work.view.viewAngle + ((R06_80175270_S_80175270_6 *)child)->unk_2A + 0x100) >> 9;
            direction &= 7;
            select_indirect_table_entry(child_obj, ((R06_80175270_S_80175270_10 *)(child_obj->unk_2C + direction))->unk_00, child_obj->unk_04);
            child_obj->unk_14 &= 0xFFFE;
        }

    case 8:
        {

            ((R06_80175270_S_80175270_0 *)action)->unk_96.u--;
            if (((R06_80175270_S_80175270_0 *)action)->unk_96.s > 0) {
                return;
            }
            ((R06_80175270_S_80175270_9 *)(((R06_80175270_S_80175270_1 *)actor)->unk_60))->unk_2A = ((R06_80175270_S_80175270_1 *)actor)->unk_8A;
            ((R06_80175270_S_80175270_0_pre *)action)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
            g_dungeon_status.unk_0A--;
            ((R06_80175270_S_80175270_1 *)actor)->unk_6D = 0;
        }
        }
}
