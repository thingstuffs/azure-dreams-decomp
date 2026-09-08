#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800A5FDC_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5FDC_0;   /* state in func_800A5FDC */

typedef struct S_800A5FDC_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xB4];
    union { s16 s; u16 u; } unk_C8;   /* accessed as both */
} S_800A5FDC_1;   /* globals in func_800A5FDC */


typedef struct S_800A5FDC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A5FDC_3;   /* coordinates in func_800A5FDC */


extern s32 func_800374F4();
extern s32 func_8003BD84();
extern void func_80053DA8();
extern s32 func_8008C180();
extern s16 func_80094BC8();
extern void func_80094C1C();
extern void func_80094F58();
extern void func_80095094();
extern void func_80095388();
extern void func_800954F4();
extern s16 func_80095978();
extern void func_80095A94();
extern void func_80095C80();
extern void func_80097844();
extern void func_800A55CC();
extern s32 func_800A5894();
extern s32 func_800C1D44();
extern int abs(int);

extern u8 D_80083160[];
extern u8 D_80083780[];
extern s32 D_800A58CC;
extern u8 D_800CFCEE[];
extern u8 D_800FE488[];
extern s32 D_80100E20[];


/* Updates town movement, terrain response, facing, and action state from input. */
void func_800A5FDC(u8 *state, u8 *table, void *action_context)
{
    u8 *context;
    u8 *globals;
    u8 *coordinates;
    s32 random_choice;
    s32 tile_id;
    s32 speed;
    s32 speed_delta;
    s32 sound_interval;
    s32 input_flags;
    s32 turn_angle;
    s16 direction;
    s16 ground_height;

    context = action_context;
    globals = D_80083160;
    func_80095C80(table);

    ((S_800A5FDC_0 *)state)->unk_0A.s--;
    if (((S_800A5FDC_0 *)state)->unk_0A.u <= 0) {
        ((S_800A5FDC_0 *)state)->unk_0A.s = func_800374F4(3) + 5;
        random_choice = func_800374F4(2);
        func_80097844(table, (u16)random_choice + 2);
    }

    input_flags = ((S_800A5FDC_1 *)globals)->unk_08;
    if (input_flags & 0xF000) {
        func_80094C1C(state);
        direction = func_80094BC8(((S_800A5FDC_1 *)globals)->unk_08,
                               ((S_800A5FDC_1 *)globals)->unk_C8.s);
        if (direction != -1) {
            func_80094F58(direction, D_80100E20[0], table);
        }
        random_choice = func_800374F4(1);
        func_80097844(table, (u16)random_choice);
        goto after_updates;
    }

    if (input_flags & 0x10) {
        func_80095094(table);
    }
    func_80095094(table);

after_updates:
    ground_height = func_80095978(table, D_800FE488);
    if (((Rec_D_800E3D7C *)table)->unk_08.at02_s16.v >= ground_height) {
        func_80095A94(table, ground_height, D_800FE488);
        coordinates = D_80083780;
        goto coordinates_ready;
    }

    if (D_800CFCEE[1] != 0) {
        ((Rec_D_800E3D7C *)table)->unk_14.as_s32 = 0;
        func_800954F4(table);
        coordinates = D_80083780;
        goto coordinates_ready;
    }

    func_80095388(table);
    coordinates = D_80083780;
coordinates_ready:
    tile_id = func_8008C180(((S_800A5FDC_3 *)coordinates)->unk_02,
                          ((S_800A5FDC_3 *)coordinates)->unk_06);
    if (func_800C1D44((u16)tile_id) != 0) {
        ((Rec_D_800E3D7C *)table)->unk_14.as_s32 -= func_800A5894(table);
    }

    speed = func_8003BD84(((Rec_D_800E3D7C *)table)->unk_0C.as_s32,
                          ((Rec_D_800E3D7C *)table)->unk_10.at00_s32.v);
    if (D_80100E20[0] != 0) {
        speed_delta = abs(D_80100E20[0] - speed);
        sound_interval = (s32)((u32)speed_delta * 7U) / D_80100E20[0];
        if ((((S_800A5FDC_1 *)globals)->unk_04 % (sound_interval + 2)) == 0) {
            func_80053DA8(0x60A);
        }
    }

    if (speed == 0) {
        ((S_800A5FDC_1 *)globals)->unk_C8.u =
            (((S_800A5FDC_1 *)globals)->unk_C8.u + 8) & 0xFFF0;
    }

    speed /= 0x10000;
    if (((S_800A5FDC_1 *)globals)->unk_08 & 4) {
        turn_angle = ((S_800A5FDC_1 *)globals)->unk_C8.u + 0x10;
        ((S_800A5FDC_1 *)globals)->unk_C8.u = turn_angle + speed;
    }
    if (((S_800A5FDC_1 *)globals)->unk_08 & 8) {
        turn_angle = ((S_800A5FDC_1 *)globals)->unk_C8.u - 0x10;
        ((S_800A5FDC_1 *)globals)->unk_C8.u = turn_angle - speed;
    }

    if ((((S_800A5FDC_1 *)globals)->unk_10 & 0x10) &&
        (D_800CFCEE[0] == 0)) {
        func_800A55CC(state, table, context);
        goto done;
    }

    if (((S_800A5FDC_1 *)globals)->unk_10 & 0x100) {
        ((S_800A5FDC_0 *)state)->unk_00 = (s32)&D_800A58CC;
        ((S_800A5FDC_0 *)state)->unk_0A.u = 8;
    }
done:
    return;
}
