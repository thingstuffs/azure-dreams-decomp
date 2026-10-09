#include "modules/dungeon_native_abi.h"
#include "shared/game_work.h"
#include "shared/slus_callbacks.h"

extern s32 rand(void);
extern void func_80024B00(void *, s16 *);
extern u8 D_80027484[12];
extern s32 func_800C95C0(void *, void *, s16 *);
/* Spawn two pairs of effects at random offsets around the source. */
void func_80024C38(void *source, s16 effect_param, s32 render_param)
{
    s32 remaining;
    void *effect;
    void *effect_data;
    void *render_data;
    remaining = 2;
    do {
        effect = func_8003FD64(0x212, source);
        if (effect != 0) {
            *((void **) (((u8 *) effect) + 0x10)) = func_80024B00;
            func_8004491C(effect, (s32)func_80045340);
            effect_data = ((u8 *) effect) + 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 2)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 6)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 0xA)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA))) + (rand() & 0x3F)) - 0x20;
            render_data = *((void **) (((u8 *) effect) + 0xC));
            *((void **) (((u8 *) render_data) + 8)) = D_80027484;
            *((s16 *) (((u8 *) render_data) + 0x1E)) = 0x1000;
            *((s16 *) (((u8 *) render_data) + 0x1C)) = 0x1000;
            *((s32 *) (((u8 *) render_data) + 0xC)) = render_param;
            *((s16 *) (((u8 *) render_data) + 6)) = 8;
            *((s16 *) (((u8 *) effect_data) + 0x36)) = effect_param;
            *((s16 *) (((u8 *) effect_data) + 0x30)) = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
    remaining = 2;
    do {
        effect = func_8003FD64(0x212, source);
        if (effect != 0) {
            *((void **) (((u8 *) effect) + 0x10)) = func_80024B00;
            func_8004491C(effect, (s32)func_800C95C0);
            effect_data = ((u8 *) effect) + 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 2)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 6)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 0xA)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) effect) + 0x20)) = 0x20;
            *((s16 *) (((u8 *) effect_data) + 2)) = 0x20;
            *((s16 *) (((u8 *) effect_data) + 4)) = 1;
            *((s16 *) (((u8 *) effect_data) + 6)) = 0;
            *((s16 *) (((u8 *) effect_data) + 0x36)) = effect_param;
            *((s16 *) (((u8 *) effect_data) + 0x30)) = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
}
