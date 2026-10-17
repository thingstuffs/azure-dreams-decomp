/* Relink of matched dungeon/func_802835B8; every changed retail word is a paired relocation. */
#include "modules/dungeon_dungeon_setup.h"

void dungeonInitializeDungeonActor(void) {
    u8 pos_x;
    u8 pos_y;
    u16 flags;
    void *allocation;
    u8 *actor_storage;
    u8 *actor;
    u8 *call_target;
    u8 *state;
    u8 *obj;
    u8 *entity;
    u8 *room;
    u8 first_height;
    s16 height;
    s16 *delta_x;
    u8 *delta_page;
    s16 *delta_y;
    s32 height_diff;
    s32 entry_index;
    s32 offset_index;
    s32 sample_x;
    s32 sample_y;
    s32 state_config;
    GameWork *table_base;
    u8 tile;
    u8 actor_x;
    u8 actor_y;
    u16 display_setting;
    s32 lift_height;
    u8 *display_state;
    s32 bind_count;
    u8 *bind_state;
    u8 *bind_angle;
    u8 *defaults_page;
    u16 init_flags;
    s32 neutral_color;
    s32 object_color;
    s32 entity_mask;
    s32 copy_tail;
    u16 final_flags;

    table_base = &gameWork;
    D_800DCF5A = 1;
    allocation = initializeSceneObjectInBuffer(0, ((u8 *)(&D_80083498)), 0x53);
    ((dungeon_setup_802835B8_S_800165B8_0 *)allocation)->unk_10 = D_80089AA0;
    func_8004491C(allocation, func_80045340);
    actor_storage = ((u8 *)(&D_80083780.x.v));
    ((dungeon_setup_802835B8_S_800165B8_0 *)allocation)->unk_08 = actor_storage;
    actor = actor_storage;
    zeroWords(actor, 6);
    state = ((u8 *)(&D_80082E80));
    ((dungeon_setup_802835B8_S_800165B8_0 *)allocation)->unk_0C = state;
    zeroWords(state, 0xC);
    D_800814A8 = obj = (u8 *)allocation + 0x20;
    D_800E3D7C = obj;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_13 = 0;
    entity = obj;
    room = (u8 *)&D_80082E60;

    if (!(((dungeon_setup_802835B8_S_800165B8_2 *)room)->unk_16 & 1)) {
retry_position:
        do {
        } while (selectDungeonSpawnTile(&pos_x, &pos_y) < 0);
        if (D_80012090 != 0 || func_80033BC0(0x1389) != 0) {
            goto position_selected;
        }
        call_target = actor;
        if (D_8008146C != 0x1F) {
            goto initialize_position;
        }
        bind_state = (u8 *)(-0x400);
        first_height = func_800BCB04((pos_x << 6) | 0x20,
                                     (pos_y << 6) | 0x20, (s32)bind_state);
        entry_index = -1;
        delta_x = dirStepX;
        delta_y = dirStepY;
        do {
        getOffsetMapCellValueAndFlags(pos_x, pos_y, (s16)entry_index, &flags);
        bind_state = (u8 *)(-0x400);
        if (flags & 0x8000) {
            goto retry_position;
        }
        offset_index = entry_index & 7;
        {
            u8 sample_tile_y;
            s32 sample_y_sum;

            sample_tile_y = pos_y;
            sample_x = (pos_x << 6) + 0x20;
            sample_x += delta_x[offset_index] << 6;
            sample_x &= 0xFFE0;
            sample_y = ((s32)sample_tile_y << 6) + 0x20;
            sample_y_sum = sample_y + (delta_y[offset_index] << 6);
            sample_y = sample_y_sum & 0xFFE0;
        }
        height = func_800BCB04(sample_x, sample_y, (s32)bind_state);
        height_diff = (height & 0xFF) - (first_height & 0xFF);
        if (height_diff < 0) {
            height_diff = -height_diff;
        }
        entry_index++;
        if (height_diff >= 0x21) {
            goto retry_position;
        }
        } while (entry_index < 2);
    } else {
        pos_x = ((dungeon_setup_802835B8_S_800165B8_2 *)room)->unk_10;
        pos_y = ((dungeon_setup_802835B8_S_800165B8_2 *)room)->unk_12;
    }
position_selected:
    call_target = actor;
initialize_position:
    entry_index = 7;
    {
        u8 setup_x;
        u8 setup_y;

        setup_x = pos_x;
        setup_y = pos_y;
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_24 = setup_x;
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_25 = setup_y;
        dungeonSetRecordIntegerTileCenter(call_target, setup_x, setup_y);
    }
    func_8009A21C(pos_x, pos_y, 0x300);
    height = func_800BCB04(((dungeon_setup_802835B8_S_800165B8_4 *)actor)->unk_02, ((dungeon_setup_802835B8_S_800165B8_4 *)actor)->dungeon_setup_802835B8_unk_06, -0x400);
    actor_x = pos_x;
    actor_y = pos_y;
    ((dungeon_setup_802835B8_S_800165B8_4 *)actor)->unk_0A = height;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_88 = height;
    (*(s16 *)((u8 *)entity + 0x8A)) = height;
    delta_page = (u8 *)(((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2);
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_0C = 0x2C808080;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2 = (s32)delta_page | 0x10;
    state_config = D_80080A80;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_5C = allocation;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_58 = allocation;
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_1E = 0x1000;
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_1C = 0x1000;
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_28 = state_config;
    dungeonRestoreInventoryAndFamiliars(obj, entity, actor_x, actor_y);

    entity_mask = 0xFFEFFFFF;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_14 &= entity_mask;
    do {
        textureHandleInstallsSelectedAnimationFrameSecondaryPointerUpdatesAnimationFlags(state, (&D_800DD078)[entry_index], 0, 0);
        D_800E3D80[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        textureHandleInstallsSelectedAnimationFrameSecondaryPointerUpdatesAnimationFlags(state, (&D_800DD0A8)[entry_index], 0, 0);
        D_800E3CF8[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        textureHandleInstallsSelectedAnimationFrameSecondaryPointerUpdatesAnimationFlags(state, (&D_800DD090)[entry_index], 0, 0);
        D_800E3D48[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        entry_index--;
    } while (entry_index >= 0);
    D_800E3D18 = D_800E3CF8;

    if ((func_80042900(entity, 0xA) << 16) != 0) {
        (*(void * *)((u8 *)state + 0x2C)) = D_800DD274;
        func_8003DB94(state,
            *(void **)((u8 *)D_800DD274 +
                (((gameWork.view.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 7) & 0x1C)),
            0);
    } else {
        textureHandleInstallsSelectedAnimationFrameSecondaryPointerUpdatesAnimationFlags(state, 0xB0, 0, 1);
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_2C = D_800DCFB0;
    }
    bind_count = 1;
    bind_angle = obj + 0x2A;
    (*(s16 *)((u8 *)obj + 0x94)) = -1;
    (*(s16 *)((u8 *)obj + 0x118)) = 0;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_2A = 0x400 - (((u16)gameWork.view.viewAngle + 0x100) & 0xE00);
    dungeonCreateTrackedEffect((u8 *)&D_80083498, bind_count, state + 0x2C, bind_angle);
    {
        s32 clear_flag_mask;

        clear_flag_mask = 0xFFEFFFFF;
        ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_9A = 0xFF;
        ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_1C &= clear_flag_mask;
    }
    dungeonRestorePlayerControlCallback(obj, entity);
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_14 |= 0x8000;
    defaults_page = (u8 *)0x80010000;
    for (entry_index = 0; entry_index < 2; entry_index++) {
        tile = defaults_page[entry_index + 0x2D6C];
        ((dungeon_setup_802835B8_S_800165B8_6 *)(obj + entry_index))->unk_FA = tile;
        if (tile == 2) {
            ((dungeon_setup_802835B8_S_800165B8_6 *)(obj + entry_index))->unk_FA = 1;
        }
    }

    object_color = 0x2C808080;
    entry_index = (s32)0x80010000;
    delta_page = (u8 *)(((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2);
    delta_page = (u8 *)(((s32)delta_page) | (0x10));
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2 = (s32)delta_page;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_14 |= 0x4000;
    bind_state = (u8 *)(0x8001020C);
    *(dungeon_setup_802835B8_Copy13 *)(entity + 0x34) = *(dungeon_setup_802835B8_Copy13 *)(u32)bind_state;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_42 = 0;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_41 = 0;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_DC = object_color;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_E0 = object_color;

    {
        u32 tile_y;
        s32 display_index;
        u16 height_index;
        u16 display_value;

        u16 *display_table = D_800DD264;
        call_target = (u8 *)(u32)((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_24;
        display_index = *(u16 *)((u8 *)entry_index + 0x20A2);
        tile_y = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_25;
        display_setting = *(u16 *)((u8 *)display_table + (s16)display_index * 2);
        bind_state = (u8 *)&dungeonStatus;
        table_base->view.unk_0AC = display_setting;
        height_index = *(u16 *)((u8 *)entry_index + 0x20A0);
        *(u16 *)D_800DCE60 = display_setting;
        lift_height = *(u16 *)((u8 *)D_800DD26C + (s16)height_index * 2);
        display_value = ((u16)table_base->view.unk_0AE);
        display_state = D_800DCE60;
        ((dungeon_setup_802835B8_S_800165B8_8 *)display_state)->unk_04 = 0;
        (*(u16 *)((u8 *)display_state + 2)) = display_value;
        D_800E4938[0] = 0;
        final_flags = ((DungeonGlobalStatus *)bind_state)->flags;
        *(void **)&D_800E4938[1] = allocation;
        D_800E4938[2] = 0;
        final_flags |= 2;
        ((DungeonGlobalStatus *)bind_state)->flags = final_flags;
        ((dungeon_setup_802835B8_S_800165B8_8 *)display_state)->dungeon_setup_802835B8_unk_06.s = lift_height;
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_26 =
            func_8009FB34((s32)call_target, tile_y, bind_state, lift_height);
    }
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_9C = -2;
    dungeonProcessGlobalBufferAndSubmit();
    {
        s32 actor_lift;

        call_target = actor;
        actor_lift = ((dungeon_setup_802835B8_S_800165B8_8 *)display_state)->dungeon_setup_802835B8_unk_06.u;
        D_800E3540 = 0;
        D_80081484 = 0;
        D_80081470 = 0;
        dungeonInitializeRandomEffectPosition(call_target, actor_lift);
    }
    init_flags = ((dungeon_setup_802835B8_S_800165B8_10 *)(u8 *)entry_index)->unk_3714;
    D_80082A3B = -0x24;
    if (init_flags & 4) {
        func_800A6C00();
    }
}
