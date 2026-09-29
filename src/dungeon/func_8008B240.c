#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef void (*StateFunc)(void *, void *, void *, void *);

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008ACDC(void *, void *, void *, void *);
extern s32 func_80094EA4(void);

extern s32 D_8008ACDC;
extern u8 D_800DD008[8];
extern u8 D_800DD010[8];
extern StateFunc D_800DD168[];

/* Advances the camera reset animation and resumes actor state handling. */
void to_camera_zero_00(void *actor, void *context, void *animation, void *transform)
{
    GameWork *camera = &gameWork;
    s32 phase;

    phase = *(u8 *)((u8 *)actor + 0x9B);
    switch (phase) {
    case 0:
        if (*(u16 *)((u8 *)animation + 0x14) & 0xE000) {
            *(u8 **)((u8 *)animation + 0x2C) = D_800DD008;
            func_80048A44(animation,
                D_800DD008[((camera->view.viewAngle +
                    *(s16 *)((u8 *)transform + 0x2A) + 0x100) >> 9) & 7], 0, 1);
            *(u8 *)((u8 *)actor + 0x9B) += 1;
        }
        break;
    case 1:
        if (*(u16 *)(&camera->buttons) != 0) {
            *(u8 **)((u8 *)animation + 0x2C) = D_800DD010;
            func_80048A44(animation,
                D_800DD010[((camera->view.viewAngle +
                    *(s16 *)((u8 *)transform + 0x2A) + 0x100) >> 9) & 7], 0, 1);
            *(u8 *)((u8 *)actor + 0x9B) += 1;

            dungeonStatus.flags &= 0xFEFF;
            if ((s16)func_80094EA4() != 0) {
                if (dungeonStatus.unk_0A != 0) {
                    dungeonStatus.flags |= 4;
                }
                func_8008ACDC(actor, context, animation, transform);
                if (*(u8 *)((u8 *)actor + 0x9A) != 0x17) {
                    D_800DD168[*(u8 *)((u8 *)actor + 0x9A)](actor, context, animation, transform);
                }
            }
        }
        break;
    case 2:
        if ((s16)func_80094EA4() != 0) {
            if (dungeonStatus.unk_0A != 0) {
                dungeonStatus.flags |= 4;
            }
            func_8008ACDC(actor, context, animation, transform);
            if (*(u8 *)((u8 *)actor + 0x9A) != 0x17) {
                D_800DD168[*(u8 *)((u8 *)actor + 0x9A)](actor, context, animation, transform);
                return;
            }
        }

        if (*(u16 *)((u8 *)animation + 0x14) & 0xE000) {
            *(u8 *)((u8 *)actor + 0x9A) = 0xE;
            *(s16 *)((u8 *)actor + 0xA4) = 0;
            *(s32 *)((u8 *)actor + 0x8C) = (s32)&D_8008ACDC;
        }
        break;
    }
}
