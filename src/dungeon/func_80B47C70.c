#include "modules/dungeon_resource12_slot0.h"

void func_80175470(void *sequence, void *position, Rec_D_80082E80 *record, void *actor) {
    GameWork *scene_color = &gameWork;
    R12_80175470_S_80175470_2 *node;
    R12_80175470_S_80175470_3 *model;
    void *child;
    u8 *target_color;
    s32 direction;
    s32 color_index;
    s32 effect_choice;
    u32 model_color;
    u32 state;
    u8 cd_ready;
    u16 timer;
    u16 next_timer;
    s32 next_state;
    s16 effect_index;

    state = ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n;
    switch (state) {

    case 0:
        next_state = ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.v + 1;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n = next_state;
        return;

    case 1:
        func_80041588(((u8 *)D_80175B0C), ((u8 *)D_80175B24), 0);
        ((R12_80175470_S_80175470_0 *)sequence)->unk_AC = 0;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
        ((R12_80175470_S_80175470_1 *)actor)->unk_8A = ((R12_80175470_S_80175470_1 *)actor)->unk_2A.u;
        return;

    case 2:
        direction = ((gameWork.view.viewAngle + ((R12_80175470_S_80175470_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        if ((*(u8 *)D_80175B24) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((R12_80175470_S_80175470_1 *)actor)->unk_2A.u += 0x200;
            return;
        }

        func_80041588(((u8 *)D_80175B0C), ((u8 *)D_80175B24), 1);
        func_8003F540(0, ((s32 *)D_8006CD58)[0], 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), 0);
        (*(u8 *)D_80175B25) = 0;
        Control_CD(0xFF, ((s32 *)D_8003E140), ((u8 *)D_80175B25));
        func_800C77D0((u8 *)actor - 0x20, position, 8, 0x300);
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0x10;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
        func_80175180(sequence, position, record);

    case 3:
        timer = ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u;
        next_timer = timer - 1;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = next_timer;
        if ((s16)next_timer <= 0) {
            cd_ready = (*(u8 *)D_80175B25);
            ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = timer;
            if (cd_ready == 0) {
                return;
            }
            ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
            func_800A56E0(0x300);
            return;
        }
        color_index = func_800498A0(actor);
        target_color = ((u8 * *)D_800DCEEC)[color_index];
        scene_color->view.unk_090 += ((s32)target_color[0]
            - scene_color->view.unk_090) / ((R12_80175470_S_80175470_0 *)sequence)->unk_96.s;
        scene_color->view.unk_091 += ((s32)target_color[1]
            - scene_color->view.unk_091) / ((R12_80175470_S_80175470_0 *)sequence)->unk_96.s;
        scene_color->view.unk_092 += ((s32)target_color[2]
            - scene_color->view.unk_092) / ((R12_80175470_S_80175470_0 *)sequence)->unk_96.s;
        return;

    case 4:
        node = func_8003FC64(0x12);
        if (node == 0) {
            return;
        }
        node->unk_10.p = ((u8 *)func_80175318);
        func_8004491C(node, ((u8 *)func_8017458C));
        ((R12_80175470_S_80175470_0 *)sequence)->unk_A8 = node;
        model_color = 0x00808080;
        *(s32 *)node->unk_08 = ((s32 *)position)[0];
        ((s32 *)node->unk_08)[1] = ((s32 *)position)[1];
        ((s32 *)node->unk_08)[2] = ((s32 *)position)[2];
        (*(s16 *)D_80175B20) = -12;
        model = node->unk_0C;
        model->unk_1E = 0x1000;
        model->unk_1C = 0x1000;
        model->unk_0C = model_color;
        effect_choice = func_800498A0(actor) - 1;
        effect_index = effect_choice;
        if ((s16)effect_choice < 0) {
            effect_index = func_80069EF8() % 3;
        }
        func_8003DB94(model, ((u8 *)D_8014A000) + ((s32 *)D_80175B14)[(s16)effect_index], 0);
        record->unk_14.at00_u16.v |= 0x80;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0;
        next_state = ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n + 1;
store_next_state:
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n = next_state;
        return;

    case 5:
        node = ((R12_80175470_S_80175470_0 *)sequence)->unk_A8;
        model = node->unk_0C;
        if (model->unk_14 & 0xE000) {
            ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0x10;
            ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
            func_800A18E8(((R12_80175470_S_80175470_1 *)actor)->unk_13, 3);
            func_8009A3D0(record->unk_24, record->unk_25, 0x300);
            func_8009A028(actor);
            node = (u8 *)actor - 0x20;
            node->unk_10.i |= 0x80000000;
        }

    case 6:
        if (((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n != 6) {
            return;
        }
        if (!func_800ADC4C(position, (*(void * *)D_80175B28), (*(s16 *)D_80175B20), ((s32 *)D_800DCF5C))) {
            return;
        }
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0x10;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
        func_800A18E8(((R12_80175470_S_80175470_1 *)actor)->unk_13, 3);
        func_8009A3D0(record->unk_24, record->unk_25, 0x300);
        func_8009A028(actor);
        node = (u8 *)actor - 0x20;
        node->unk_10.i |= 0x80000000;
        return;

    case 7:
        ((R12_80175470_S_80175470_1 *)actor)->unk_60 = func_800A504C(record, actor);
        if (((R12_80175470_S_80175470_1 *)actor)->unk_60 == 0) {
            return;
        }
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0x10;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
        ((R12_80175470_S_80175470_5 *)(((R12_80175470_S_80175470_1 *)actor)->unk_60))->unk_2A = ((R12_80175470_S_80175470_1 *)actor)->unk_2A.u;
        model = ((R12_80175470_S_80175470_5_pre *)(((R12_80175470_S_80175470_1 *)actor)->unk_60))[-1].unk_00;
        node = ((R12_80175470_S_80175470_1 *)actor)->unk_60;
        func_80047738(model, ((u8 *)model->unk_2C)[
                      ((gameWork.view.viewAngle + node->unk_2A + 0x100) >> 9) & 7],
                      model->unk_04);
        model->unk_14 &= 0xFFFE;

    case 8:
        next_timer = ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u - 1;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = next_timer;
        if ((s16)next_timer > 0) {
            return;
        }
        ((R12_80175470_S_80175470_5 *)(((R12_80175470_S_80175470_1 *)actor)->unk_60))->unk_2A = ((R12_80175470_S_80175470_1 *)actor)->unk_8A;
        ((R12_80175470_S_80175470_0_pre *)sequence)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        dungeonStatus.unk_0A--;
        ((R12_80175470_S_80175470_1 *)actor)->unk_6D = 0;
    default:
        return;
    }
}
