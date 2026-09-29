#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"

typedef struct S_800A5FDC_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5FDC_0;   /* state in func_800A5FDC */



extern s32 func_800374F4();
extern s32 func_8003BD84();
extern void SD_Call();
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

extern s32 D_800A58CC;
extern u8 D_800CFCEE[];
extern u8 D_800FE488[];
extern s32 D_80100E20[];


/* Updates town movement, terrain response, facing, and action state from input. */
void func_800A5FDC(u8 *state, EntityRec *table, void *action_context)
{
    u8 *context;
    GameWork *globals;
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
    globals = &gameWork;
    func_80095C80(table);

    ((S_800A5FDC_0 *)state)->unk_0A.s--;
    if (((S_800A5FDC_0 *)state)->unk_0A.u <= 0) {
        ((S_800A5FDC_0 *)state)->unk_0A.s = func_800374F4(3) + 5;
        random_choice = func_800374F4(2);
        func_80097844(table, (u16)random_choice + 2);
    }

    input_flags = globals->buttons;
    if (input_flags & 0xF000) {
        func_80094C1C(state);
        direction = func_80094BC8(globals->buttons,
                               globals->view.viewAngle);
        if (direction != -1) {
            func_80094F58(direction, D_80100E20[0], table);
        }
        random_choice = func_800374F4(1);
        func_80097844(table, (u16)random_choice);
    } else {
        if (input_flags & 0x10) {
            func_80095094(table);
        }
        func_80095094(table);
    }

    ground_height = func_80095978(table, D_800FE488);
    if (table->z.w.i >= ground_height) {
        func_80095A94(table, ground_height, D_800FE488);
    } else if (D_800CFCEE[1] != 0) {
        table->flags14 = 0;
        func_800954F4(table);
    } else {
        func_80095388(table);
    }
    tile_id = func_8008C180(D_80083780.x.w.i,
                          D_80083780.y.w.i);
    if (func_800C1D44((u16)tile_id) != 0) {
        table->flags14 -= func_800A5894(table);
    }

    speed = func_8003BD84(table->unk_0C,
                          table->unk_10);
    if (D_80100E20[0] != 0) {
        speed_delta = abs(D_80100E20[0] - speed);
        sound_interval = (s32)((u32)speed_delta * 7U) / D_80100E20[0];
        if ((globals->unk_004 % (sound_interval + 2)) == 0) {
            SD_Call(0x60A);
        }
    }

    if (speed == 0) {
        globals->view.viewAngle =
            (((u16)globals->view.viewAngle) + 8) & 0xFFF0;
    }

    speed /= 0x10000;
    if (globals->buttons & 4) {
        turn_angle = ((u16)globals->view.viewAngle) + 0x10;
        globals->view.viewAngle = turn_angle + speed;
    }
    if (globals->buttons & 8) {
        turn_angle = ((u16)globals->view.viewAngle) - 0x10;
        globals->view.viewAngle = turn_angle - speed;
    }

    if ((((s32)globals->unk_010) & 0x10) &&
        (D_800CFCEE[0] == 0)) {
        func_800A55CC(state, table, context);
        return;
    }

    if (((s32)globals->unk_010) & 0x100) {
        ((S_800A5FDC_0 *)state)->unk_00 = (s32)&D_800A58CC;
        ((S_800A5FDC_0 *)state)->unk_0A.u = 8;
    }
    return;
}
