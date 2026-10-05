#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173C20_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_80173C20_0;   /* action_record in func_80173C20 */

typedef struct S_80173C20_1 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0x18];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80173C20_1;   /* entity_data in func_80173C20 */


typedef struct S_80173C20_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173C20_3;   /* motion_data in func_80173C20 */


extern void func_80047784(void *, s32, s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_80099734(void *record, u8 *out);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A4ACC(void *);
extern void func_800A5720(s8 *text);
extern void func_800AD594(void *, s32);

extern void *D_800E3DE8;
extern u8 D_80170854[];
extern u8 D_80170874[];
extern u8 D_80170EA8;
extern u8 D_80174090[];
extern u8 D_80174098[];
extern u8 D_801740A0[];

void func_80173C20(void *action_record, void *motion_data, void *status_record, void *entity_data)
{
    s32 state;
    s32 saved;
    s32 value;
    s32 index;
    u16 timer;

    state = ((S_80173C20_0 *)action_record)->unk_9B;
    switch (state) {
    case 0:
        saved = func_800990FC();
        if ((((S_80173C20_1 *)entity_data)->unk_2A.s >> 9) & 1) {
            func_80099290(func_80099194(
                D_80170854, func_80099734(entity_data, saved)));
        } else {
            func_80099290(func_80099194(
                D_80170874, func_80099734(entity_data, saved)));
        }
        func_800A5720(saved);

        if (((Rec_D_80082E80 *)status_record)->unk_14.at00_u16.v & 0x8000) {
            ((S_80173C20_0 *)action_record)->unk_9B = 3;
            ((S_80173C20_0 *)action_record)->unk_96 = 0;
            ((Rec_D_80082E80 *)status_record)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(entity_data, status_record, ((S_80173C20_1 *)entity_data)->unk_2A.u, 1);
            break;
        }
        (*(void * *)((u8 *)status_record + 0x2C)) = D_80174090;
        index = (gameWork.view.viewAngle + ((S_80173C20_1 *)entity_data)->unk_2A.u + 0x100) >> 9;
        func_80047784(status_record, D_80174090[index & 7], 0);
        ((S_80173C20_0 *)action_record)->unk_90 = 0;
        ((S_80173C20_0 *)action_record)->unk_98 |= 8;
        ((S_80173C20_3 *)motion_data)->unk_14 = 0xFFF00000;
        ((S_80173C20_0 *)action_record)->unk_9B++;
        break;
    case 1:
        value = ((S_80173C20_3 *)motion_data)->unk_14 + 0x20000;
        ((S_80173C20_3 *)motion_data)->unk_14 = value;
        ((S_80173C20_0 *)action_record)->unk_90 += value;
        if (!(((Rec_D_80082E80 *)status_record)->unk_14.at00_u16.v & 0xE000)) {
            break;
        }
        (*(void * *)((u8 *)status_record + 0x2C)) = D_80174098;
        index = (gameWork.view.viewAngle + ((S_80173C20_1 *)entity_data)->unk_2A.u + 0x100) >> 9;
        func_80047784(status_record, D_80174098[index & 7], 0);
        ((S_80173C20_0 *)action_record)->unk_96 = 8;
        ((S_80173C20_0 *)action_record)->unk_98 &= 0xFFF7;
        ((S_80173C20_0 *)action_record)->unk_9B++;
        break;
    case 2:
        timer = ((S_80173C20_0 *)action_record)->unk_96 - 1;
        ((S_80173C20_0 *)action_record)->unk_96 = timer;
        if (((timer << 16) == 0) || (((Rec_D_80082E80 *)status_record)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(entity_data, status_record, ((S_80173C20_1 *)entity_data)->unk_2A.u, 1);
        }
        if (!(((Rec_D_80082E80 *)status_record)->unk_14.at00_u16.v & 0xE000)) {
            break;
        }
        (*(void * *)((u8 *)status_record + 0x2C)) = D_801740A0;
        index = (gameWork.view.viewAngle + ((S_80173C20_1 *)entity_data)->unk_2A.u + 0x100) >> 9;
        func_80047784(status_record, D_801740A0[index & 7], 0);

        ((S_80173C20_0 *)action_record)->unk_9B++;
        break;
    case 3:
        if (((Rec_D_80082E80 *)status_record)->unk_14.at00_u16.v & 0xE000) {
            ((S_80173C20_3 *)motion_data)->unk_10 = 0;
            ((S_80173C20_3 *)motion_data)->unk_0C = 0;
            func_800AD594(entity_data, 0x1000);
            ((S_80173C20_0 *)action_record)->unk_8C = &D_80170EA8;
            dungeonStatus.unk_0C = 0;
            func_800A4ACC(entity_data);

            if (((S_80173C20_0 *)action_record)->unk_98 & 0x4000) {
                ((S_80173C20_1 *)entity_data)->unk_1C |= 0x1000;
            } else {
                ((S_80173C20_1 *)entity_data)->unk_1C &= ~0x1000;
            }
            ((S_80173C20_1 *)entity_data)->unk_03 = ((S_80173C20_0 *)action_record)->unk_AC;
            if (((S_80173C20_1 *)entity_data)->unk_6D == 0) {
                ((S_80173C20_1 *)entity_data)->unk_46 &= 0x7FFF;
            } else {
                D_800E3DE8 = (u8 *)entity_data - 0x20;
            }
        }
        break;
    }
}
