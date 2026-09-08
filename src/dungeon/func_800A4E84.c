#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"





extern s32 func_8009A3D0();
extern s8 func_8009FB34();
extern s32 func_800A4E2C();
extern s32 func_800AA53C();
typedef struct {
    u8 pad[10];
    u16 counter;
} DungeonState;

extern DungeonState D_80083460;


void func_800AA5E4(Rec_func_800A9E70_arg0 *arg0, void *arg1, void *arg2, Rec_D_800E3D7C *arg3) {
    s32 var_a2;
    s32 temp_v0;
    s32 x;
    s32 y;
    void *var_a0;
    DungeonState *state;

    arg0->unk_9A.as_s8 = 4;
    arg0->unk_9B.as_s8 = 0;
    arg0->unk_8C = 0;
    arg0->unk_96.as_s16 = 0x10;
    arg0->unk_98 = arg0->unk_98 | 8;
    temp_v0 = arg3->unk_1C.as_s32 | 0x10000;
    arg3->unk_1C.as_s32 = temp_v0;
    x = ((Rec_D_80082E80 *)arg2)->unk_24;
    y = ((Rec_D_80082E80 *)arg2)->unk_25;
    var_a2 = 0x3000;
    if (temp_v0 & 0x2000) {
        var_a2 = 0x300;
    }
    func_8009A3D0(x, y, var_a2);
    var_a0 = (u8 *)arg2 + 0x24;
loop:
    if ((s16)func_800A4E2C(var_a0, (u8 *)arg2 + 0x25) < 0) {
        var_a0 = (u8 *)arg2 + 0x24;
        goto loop;
    }
    ((Rec_D_80082E80 *)arg2)->unk_26.as_s8 = func_8009FB34(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AA53C(arg3);
    state = &D_80083460;
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    state->counter = state->counter + 1;
}
