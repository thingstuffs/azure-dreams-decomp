#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


extern void *D_80170858[];
extern s32 D_8003E140[];
extern s32 D_8006CD58[];
extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 *D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[200000];
extern u8 D_80173E08[];
extern u8 D_80175114[];
extern u8 D_801758FC[];
extern s32 D_80175904[];
extern s16 D_8017591C[];
extern u8 D_80175920[];
extern u8 D_80175921[16];
extern void *D_80175924[];
extern s32 D_80175928[];

extern void func_8003DB94();
extern s32 Control_CD();
extern void func_8003F540();
extern void *func_8003FC64();
extern void func_80041588();
extern s32 func_800445E0();
extern void func_8004491C();
extern void func_80047738();
extern s32 func_800498A0();
extern s32 func_80069EF8();
extern void func_8009A028();
extern void func_8009A3D0();
extern void func_800A18E8();
extern void *func_800A504C();
extern void func_800A56E0();
extern s32 func_800ADC4C();
extern void func_800C77D0();
extern void func_80174E78();


typedef struct S_80175270_0_pre {
    u16 unk_00;
} S_80175270_0_pre;   /* the 0x2 bytes before arg0 in func_80175270, addressed as arg0[-1] */

typedef struct S_80175270_0 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x1E];
    s16 unk_BA;
} S_80175270_0;   /* arg0 in func_80175270 */

typedef struct S_80175270_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80175270_1;   /* arg3 in func_80175270 */

typedef struct S_80175270_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    union { void * p; s32 i; } unk_0C;   /* accessed as both */
    union { void * p; s32 i; } unk_10;   /* accessed as both */
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x88];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80175270_2;   /* work in func_80175270 */

typedef struct S_80175270_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80175270_3;   /* vec in func_80175270 */



typedef struct S_80175270_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80175270_6_pre;   /* the 0x14 bytes before child in func_80175270, addressed as child[-1] */

typedef struct S_80175270_6 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80175270_6;   /* child in func_80175270 */

typedef struct S_80175270_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_80175270_7;   /* obj in func_80175270 */

typedef struct S_80175270_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80175270_8;   /* countp in func_80175270 */

typedef struct S_80175270_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175270_9;   /* ((S_80175270_1 *)arg3)->unk_60 in func_80175270 */

typedef struct S_80175270_10 {
    u8 unk_00;
} S_80175270_10;   /* ((S_80175270_7 *)obj)->unk_2C + index in func_80175270 */

/* Advances an actor's transition sequence, updating effects and restoring its child's angle. */
void func_80175270(void *action, Rec_D_800E3D7C *position, Rec_D_80082E80 *entity, void *actor)
{
    static void *const state_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_4, &&case_4, &&case_7, &&case_8
    };
    S_80175270_2 *work = D_80083160;
    u8 state;

    state = ((S_80175270_0 *)action)->unk_9B;
    if (state >= 9) {
        return;
    }
    (void)state_labels;
    goto *D_80170858[state];

case_0:
    ((S_80175270_0 *)action)->unk_9B++;
    return;

case_1:
  {
    s32 effect_id;
    s32 direction;
    s32 raw_direction;
    u16 angle;

    func_80041588(D_801758FC, D_80175920, 0);
    ((S_80175270_0 *)action)->unk_BA = 0;
    ((S_80175270_0 *)action)->unk_9B++;
    ((S_80175270_1 *)actor)->unk_8A = ((S_80175270_1 *)actor)->unk_2A.u;
    ((S_80175270_1 *)actor)->unk_1C &= 0xFFFBFFFF;
    do { angle = ((S_80175270_1 *)actor)->unk_2A.u; } while (0);
    raw_direction = (D_80083228 + ((S_80175270_1 *)actor)->unk_2A.s + 0x100) >> 9;
    direction = raw_direction & 7;
    if ((((u8 *)D_80175924)[-4] == 0) || (direction != 2)) {
        if (direction == 2) {
            return;
        }
        ((S_80175270_1 *)actor)->unk_2A.u = angle + 0x200;
        return;
    }
    func_80041588((u8 *)D_80175904 - 8, (u8 *)D_80175924 - 4, 1);
    func_8003F540(0, D_8006CD58[0], 0x04000AD4, 0x05000CC4);
    effect_id = func_800445E0();
    Control_CD(0x15, effect_id, 0);
    D_80175921[0] = 0;
    Control_CD(0xFF, D_8003E140, D_80175921);
    func_800C77D0((u8 *)actor - 0x20, position, 8, 0x300);
    ((S_80175270_0 *)action)->unk_96.s = 0x10;
    ((S_80175270_0 *)action)->unk_9B++;
  }

case_2:
  {
    s32 frames_left;
    u8 *target_color;
    u8 effect_done;

    frames_left = ((S_80175270_0 *)action)->unk_96.u;
    ((S_80175270_0 *)action)->unk_96.u = frames_left - 1;
    if ((s16)(frames_left - 1) <= 0) {
        effect_done = D_80175921[0];
        ((S_80175270_0 *)action)->unk_96.u = frames_left;
        if (effect_done != 0) {
            ((S_80175270_0 *)action)->unk_9B++;
            func_800A56E0(0x300);
            return;
        }
        return;
    }
    target_color = D_800DCEEC[func_800498A0(actor)];
    work->unk_A8 += (((S_80175270_3 *)target_color)->unk_00 - work->unk_A8) / ((S_80175270_0 *)action)->unk_96.s;
    work->unk_A9 += (((S_80175270_3 *)target_color)->unk_01 - work->unk_A9) / ((S_80175270_0 *)action)->unk_96.s;
    work->unk_AA += (((S_80175270_3 *)target_color)->unk_02 - work->unk_AA) / ((S_80175270_0 *)action)->unk_96.s;
    return;
  }

case_3:
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
    work->unk_10.p = D_80175114;
    func_8004491C(work, D_80173E08);
    color = 0x00808080;
    work->unk_08[0] = position->unk_00.at00_s32.v;
    position_y_dst = work->unk_08;
    position_y = position->unk_04.at00_s32.v;
    D_80175924[0] = work;
    position_y_dst[1] = position_y;
    position_z_dst = work->unk_08;
    position_z = position->unk_08.at00_s32.v;
    D_8017591C[0] = -12;
    position_z_dst[2] = position_z;
    work = work->unk_0C.p;
    work->unk_1E = 0x1000;
    work->unk_1C = 0x1000;
    work->unk_0C.i = color;
    asset_index = func_800498A0(actor) - 1;
    if (asset_index < 0) {
        asset_index = func_80069EF8() % 3;
    }
    func_8003DB94(work, D_8014A000 + D_80175904[asset_index], 0);
    entity->unk_14.at00_u16.v |= 0x80;
    ((S_80175270_0 *)action)->unk_96.s = 0;
    ((S_80175270_0 *)action)->unk_9B++;
    func_80174E78(action, position, entity);
    return;
  }

case_4:
  {
    work = D_80175924[0];
    work = work->unk_0C.p;
    if (work->unk_14 & 0xE000) {
        ((S_80175270_0 *)action)->unk_96.s = 0x10;
        ((S_80175270_0 *)action)->unk_9B++;
        func_800A18E8(((S_80175270_1 *)actor)->unk_13, 3);
        func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
        func_8009A028(actor);
        work = (u8 *)actor - 0x20;
        work->unk_10.i |= 0x80000000;
    }
    if (((S_80175270_0 *)action)->unk_9B != 6) {
        return;
    }
  }

case_6:
  {
    if (func_800ADC4C(position, D_80175928[0], (s16)D_8017591C[0], D_800DCF5C) == 0) {
        return;
    }
    ((S_80175270_0 *)action)->unk_96.s = 0x10;
    ((S_80175270_0 *)action)->unk_9B++;
    func_800A18E8(((S_80175270_1 *)actor)->unk_13, 3);
    func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
    func_8009A028(actor);
    work = (u8 *)actor - 0x20;
    work->unk_10.i |= 0x80000000;
    return;
  }

case_7:
  {
    void *child;
    S_80175270_7 *child_obj;
    s32 direction;

    if ((((S_80175270_1 *)actor)->unk_60 = func_800A504C(entity, actor)) == 0) {
        return;
    }
    ((S_80175270_0 *)action)->unk_96.s = 0x10;
    ((S_80175270_0 *)action)->unk_9B++;
    ((S_80175270_9 *)(((S_80175270_1 *)actor)->unk_60))->unk_2A = ((S_80175270_1 *)actor)->unk_2A.u;
    child = ((S_80175270_1 *)actor)->unk_60;
    child_obj = ((S_80175270_6_pre *)child)[-1].unk_00;
    ASM_KEEP_NV(child);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    direction = (D_80083228 + ((S_80175270_6 *)child)->unk_2A + 0x100) >> 9;
    direction &= 7;
    func_80047738(child_obj, ((S_80175270_10 *)(child_obj->unk_2C + direction))->unk_00, child_obj->unk_04);
    child_obj->unk_14 &= 0xFFFE;
  }

case_8:
  {
    u8 *counter_base;

    ((S_80175270_0 *)action)->unk_96.u--;
    if (((S_80175270_0 *)action)->unk_96.s > 0) {
        return;
    }
    ((S_80175270_9 *)(((S_80175270_1 *)actor)->unk_60))->unk_2A = ((S_80175270_1 *)actor)->unk_8A;
    ((S_80175270_0_pre *)action)[-1].unk_00 |= 0x8000;
    D_800814A0 |= 0x8000;
    counter_base = (u8 *)&D_80083460;
    ((S_80175270_8 *)counter_base)->unk_0A--;
    ((S_80175270_1 *)actor)->unk_6D = 0;
  }
}
