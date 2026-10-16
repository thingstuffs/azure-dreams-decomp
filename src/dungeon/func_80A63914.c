/* Relink of matched dungeon/func_80A4B914; every changed retail word is a paired relocation. */
#define D_8017591C D_8015D91C
#define D_80175928 D_8015D928
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

extern void func_800478B8();
extern void func_80044A50();

extern u16 D_8015D91C[];
extern s32 D_8015D928[];

/* Updates an effect, then fades its colors to neutral and marks it finished. */
void func_8015D114(void *entity_data, void *unused, void *source_data)
{
    u8 *entity = entity_data;
    u8 *source = source_data;
    GameWork *colors = &gameWork;
    u16 frame_count;
    u16 fade_left;

    if (entity[0x9A] == 0) {
        D_8015D928[0] = *(s32 *)(source + 8);
        func_800478B8(source);

        if (*(u16 *)(source + 0x14) & 0xE000) {
            func_80044A50(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        frame_count = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = frame_count + 1;
        if ((frame_count & 3) == 1) {
            D_8015D91C[0]++;
            return;
        }
    } else {
        colors->view.unk_090 += (0x80 - colors->view.unk_090) / *(s16 *)(entity + 0x96);
        colors->view.unk_091 += (0x80 - colors->view.unk_091) / *(s16 *)(entity + 0x96);
        colors->view.unk_092 += (0x80 - colors->view.unk_092) / *(s16 *)(entity + 0x96);

        fade_left = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = fade_left;
        if ((fade_left << 16) <= 0) {
            *(u16 *)(entity - 2) |= 0x8000;
            *(s32 *)((u8 *)(&objectFlagBlock)) |= 0x8000;
        }
    }
}
