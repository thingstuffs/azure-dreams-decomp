#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80092018_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x84];
    void * unk_124;
} S_80092018_0;   /* arg0 in func_80092018 */


typedef struct S_80092018_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_80092018_2;   /* arg3 in func_80092018 */

typedef struct S_80092018_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    s32 unk_14;
} S_80092018_3;   /* arg1 in func_80092018 */

typedef struct S_80092018_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80092018_4;   /* temp_v1_2 in func_80092018 */

typedef struct S_80092018_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_80092018_5;   /* temp_s4 in func_80092018 */

typedef struct S_80092018_6 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80092018_6;   /* rmw_base in func_80092018 */

typedef struct S_80092018_7 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
} S_80092018_7;   /* ((S_80092018_0 *)arg0)->unk_124 in func_80092018 */


struct D83460_VIEW { s16 pad[3]; s16 divisor[1]; };

extern void *D_800889C0[];
void func_80048A44();
s32 func_8009074C();
s32 func_80094EA4();
M2C_UNK func_80099F04();
M2C_UNK func_80099F70();
M2C_UNK func_800A2B04();
M2C_UNK func_800B653C();
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD018[];
extern u8 D_800DD020[];
extern u8 D_800DD028[];

/* Updates actor movement and animation through the action states. */
void func_80092018(void *actor, void *motion, void *sprite, void *model) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19 };
    s16 settle_frames;
    s16 move_frames_left;
    s32 heading_or_coord;
    u16 start_frames_left;
    u16 settle_frames_left;
    u16 anim_flags;
    u8 action_state;
    void *attachment;
    M2C_UNK *move_state;

    action_state = ((S_80092018_0 *)actor)->unk_9B;
    if (action_state >= 0x14U) {
        goto block_29;
    }
    (void)jt_keep; goto *D_800889C0[(u32)(action_state)];
jt_c0:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto block_5;
    }
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == D_800DD028) {
        goto block_27;
    }
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD028;
    func_80048A44(sprite, *((((s32) (D_80083228 + ((S_80092018_2 *)model)->unk_2A + 0x100) >> 9) & 7) + D_800DD028), 0, 1);
    return;
block_5:
    heading_or_coord = func_8009074C(((S_80092018_0 *)actor)->unk_9E, actor + 0xA2, model + 0x2A) << 0x10;
    if ((heading_or_coord >> 0x10) == 0xFFF) {
        goto block_29;
    }
    if ((((u16) ((S_80092018_2 *)model)->unk_2A >> 9) & 7) == ((heading_or_coord >> 0x19) & 7)) {
        goto block_29;
    }
    if ((func_80094EA4(heading_or_coord) << 0x10) == 0) {
        goto block_29;
    }
    goto block_28;
jt_c16:
    ((S_80092018_3 *)motion)->unk_0C.at02.v = (s16) (*((s16 *)(D_8006CCD8 + (((u16) ((S_80092018_2 *)model)->unk_2A >> 8) & 0xE))) * 8);
    ((S_80092018_3 *)motion)->unk_10.at02.v = (s16) (*((s16 *)(D_8006CCE8 + (((u16) ((S_80092018_2 *)model)->unk_2A >> 8) & 0xE))) * 8);
    start_frames_left = ((S_80092018_0 *)actor)->unk_96.s - 1;
    ((S_80092018_0 *)actor)->unk_96.s = start_frames_left;
    if ((start_frames_left << 0x10) > 0) {
        goto block_29;
    }
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD018;
    func_80048A44(sprite, *((((s32) (D_80083228 + ((S_80092018_2 *)model)->unk_2A + 0x100) >> 9) & 7) + D_800DD018), 0, 1);
    attachment = ((S_80092018_0 *)actor)->unk_124;
    ((S_80092018_4 *)attachment)->unk_1C = (s32) (((S_80092018_4 *)attachment)->unk_1C | 0x100);
    ((S_80092018_7 *)(((S_80092018_0 *)actor)->unk_124))->unk_6A = (u16) ((S_80092018_2 *)model)->unk_2A;
    ((S_80092018_7 *)(((S_80092018_0 *)actor)->unk_124))->unk_60 = model;
    ((S_80092018_0 *)actor)->unk_9B = (u8) (((S_80092018_0 *)actor)->unk_9B + 1);
    return;
jt_c17:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto block_13;
    }
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD020;
    func_80048A44(sprite, *((((s32) (D_80083228 + ((S_80092018_2 *)model)->unk_2A + 0x100) >> 9) & 7) + D_800DD020), 0, 1);
    ((S_80092018_0 *)actor)->unk_9B = (u8) (((S_80092018_0 *)actor)->unk_9B + 1);
jt_c18:
block_13:
    move_state = &D_80083460;
    if (((S_80092018_5 *)move_state)->unk_04 == 0) {
        goto block_15;
    }
    heading_or_coord = ((S_80092018_3 *)motion)->unk_02;
    {
        s32 delta;
        s32 direction_offset;
        delta = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        direction_offset = *((s16 *)(D_8006CCD8 + (((u16) ((S_80092018_2 *)model)->unk_2A >> 8) & 0xE))) * 0x10;
        direction_offset += 0x20;
        delta += direction_offset;
        delta -= heading_or_coord;
        ((S_80092018_3 *)motion)->unk_0C.at00.v = (s32) ((delta << 0x10) / (s16) ((S_80092018_5 *)move_state)->unk_04);
    }
    heading_or_coord = ((S_80092018_3 *)motion)->unk_06;
    {
        s32 delta;
        s32 direction_offset;
        delta = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        direction_offset = *((s16 *)(D_8006CCE8 + (((u16) ((S_80092018_2 *)model)->unk_2A >> 8) & 0xE))) * 0x10;
        direction_offset += 0x20;
        delta += direction_offset;
        delta -= heading_or_coord;
        ((S_80092018_3 *)motion)->unk_10.at00.v = (s32) ((delta << 0x10) / ((struct D83460_VIEW *) move_state)->divisor[-1]);
    }
block_15:
    if ((u16) ((S_80092018_5 *)move_state)->unk_04 & 3) {
        goto block_17;
    }
    func_800B653C(motion, ((S_80092018_2 *)model)->unk_2A);
block_17:
    move_frames_left = (u16) ((S_80092018_5 *)move_state)->unk_04 - 1;
    ((S_80092018_5 *)move_state)->unk_04 = move_frames_left;
    if ((move_frames_left << 0x10) > 0) {
        goto block_29;
    }
    ((S_80092018_5 *)move_state)->unk_04 = 0;
    ((S_80092018_3 *)motion)->unk_14 = 0;
    ((S_80092018_3 *)motion)->unk_10.at00.v = 0;
    ((S_80092018_3 *)motion)->unk_0C.at00.v = 0;
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_800DD028;
    func_80048A44(sprite, *((((s32) (D_80083228 + ((S_80092018_2 *)model)->unk_2A + 0x100) >> 9) & 7) + D_800DD028), 0, 1);
    ((S_80092018_0 *)actor)->unk_96.s = 2U;
    ((S_80092018_0 *)actor)->unk_9B = 0x13U;
    return;
jt_c19:
    settle_frames = (s16) ((S_80092018_0 *)actor)->unk_96.s;
    if (settle_frames == 0) {
        goto block_23;
    }
    {
        s32 delta;
        s32 origin;
        delta = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        origin = ((S_80092018_3 *)motion)->unk_02;
        origin -= 0x20;
        delta -= origin;
        ((S_80092018_3 *)motion)->unk_0C.at00.v = (s32) ((delta << 0x10) / settle_frames);
    }
    {
        s32 delta;
        s32 origin;
        origin = ((S_80092018_3 *)motion)->unk_06;
        origin -= 0x20;
        delta = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
        delta -= origin;
        ((S_80092018_3 *)motion)->unk_10.at00.v = (s32) ((delta << 0x10) / (s16) ((S_80092018_0 *)actor)->unk_96.s);
    }
    if (((S_80092018_0 *)actor)->unk_96.u == 0) {
        goto block_23;
    }
    settle_frames_left = ((S_80092018_0 *)actor)->unk_96.s - 1;
    ((S_80092018_0 *)actor)->unk_96.s = settle_frames_left;
    if ((settle_frames_left << 0x10) != 0) {
        goto block_23;
    }
    ((S_80092018_3 *)motion)->unk_10.at00.v = 0;
    ((S_80092018_3 *)motion)->unk_0C.at00.v = 0;
block_23:
    anim_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
    if (anim_flags & 0x8000) {
        goto block_26;
    }
    if (!(anim_flags & 0x6000)) {
        goto block_29;
    }
    if (((S_80092018_0 *)actor)->unk_96.u != 0) {
        goto block_29;
    }
block_26:
    ((S_80092018_3 *)motion)->unk_14 = 0;
    ((S_80092018_3 *)motion)->unk_10.at00.v = 0;
    ((S_80092018_3 *)motion)->unk_0C.at00.v = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_80099F70(((S_80092018_2 *)model)->unk_5C);
    func_80099F04(((S_80092018_2 *)model)->unk_5C);
    {
        void *action_status = &D_80083460;
        register u16 action_flags ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        action_flags = ((S_80092018_6 *)action_status)->unk_02;
        action_flags = (u16) (action_flags | 0x812);
        ((S_80092018_6 *)action_status)->unk_02 = action_flags;
    }
block_27:
block_28:
    ((S_80092018_0 *)actor)->unk_8C = &D_8008ACDC;
block_29:
    return;
}
