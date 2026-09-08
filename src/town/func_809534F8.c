#include "common.h"

typedef struct {
    s16 unk0;       /* 0x00 */
    s16 pad2;       /* 0x02 */
    void *source;   /* 0x04 */
    s32 unused8;    /* 0x08 */
    void *buffer;   /* 0x0C */
    u32 color;      /* 0x10 */
    s16 x;          /* 0x14 */
    s16 y;          /* 0x16 */
    s16 type;       /* 0x18 */
    s16 vram;       /* 0x1A */
    s16 unk1C;      /* 0x1C */
    s16 pad1E;      /* 0x1E */
    u8 pad20[0x10]; /* 0x20 */
} TextParams;       /* 0x30 */

typedef struct {
    s16 unk0;       /* 0x00 */
    s16 pad2;       /* 0x02 */
    void *buffer;   /* 0x04 */
    u32 color;      /* 0x08 */
    u16 x;          /* 0x0C */
    s16 y;          /* 0x0E */
    s16 width;      /* 0x10 */
    s16 height;     /* 0x12 */
    s16 type;       /* 0x14 */
    s16 visible;    /* 0x16 */
    u8 pad18[0x10]; /* 0x18 */
} BoxParams;        /* 0x28 */

typedef struct {
    s32 words[4];
} WordBlock4;

typedef struct {
    s32 words[6];
} WordBlock6;

typedef struct {
    TextParams text;         /* 0x00 */
    BoxParams box;           /* 0x30 */
    WordBlock4 text_words;   /* 0x58 */
    WordBlock6 number_words; /* 0x68 */
} Screen;                    /* 0x80 */

extern WordBlock4 D_80020010;
extern WordBlock6 D_80020050;
extern u8 D_80020068[];
extern u8 D_800203D8[];
extern u8 D_80020468[];
extern u8 D_800204AC[];
extern u8 D_80020900[];
extern s16 D_80024308[];
extern s16 D_8002430A[];
extern u8 D_80083498[];

extern void func_800201C8();
extern void func_8002025C();
extern void *func_8003FD64();
extern void func_800537D0();
extern s32 strlen();

/* Draw a labeled grid with triangular entries of row and column products. */
void func_800204F8(void)
{
    Screen screen;
    Screen *header_screen;
    Screen *value_screen;
    void *allocation;
    void *buffer;
    s32 grid_index;
    s32 row_index;
    s32 value_index;
    s32 row_y;
    s16 column_x;
    s16 *column_factor;
    s16 *row_factor;
    register s16 *row_factors ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    buffer = 0;
    screen.text_words = D_80020010;
    screen.number_words = D_80020050;
    allocation = func_8003FD64(1, D_80083498);
    if (allocation != 0) {
        buffer = (u8 *)allocation + 0x20;
        *(void **)((u8 *)allocation + 0x10) = D_80020900;
    }

    screen.text.x = 0x14;
    screen.text.y = 0x14;
    screen.text.type = 3;
    screen.text.vram = 0x7C80;
    screen.text.unk1C = 0;
    screen.text.color = 0x00808080;
    screen.text.source = D_80020068;
    screen.text.unk0 = 0;
    screen.text.buffer = buffer;
    func_800201C8(D_800204AC, &screen.text);

    grid_index = 2;
    header_screen = &screen;
    do {
        screen.text.x = (grid_index * 0x28) + 0x48;
        screen.text.source = (void *)header_screen->text_words.words[grid_index];
        func_800201C8(D_800204AC, &header_screen->text);
        grid_index--;
    } while (grid_index >= 0);

    screen.text.x = 0x20;
    grid_index = 2;
    do {
        screen.text.y = (grid_index * 0x10) + 0x24;
        screen.text.source = (void *)screen.text_words.words[grid_index + 1];
        func_800201C8(D_800204AC, &screen.text);
        grid_index--;
    } while (grid_index >= 0);

    screen.box.x = 0x10;
    screen.box.y = 0x10;
    screen.box.width = 0xA0;
    screen.box.height = 0x40;
    screen.box.type = 2;
    screen.box.visible = 1;
    screen.box.color = 0x00606060;
    screen.box.unk0 = 0;
    screen.box.buffer = buffer;
    func_8002025C(D_800203D8, &screen.box);

    screen.box.y = 0x12;
    screen.box.width = 1;
    screen.box.height = 0x3C;
    screen.box.type = 0;
    screen.box.visible = 1;
    screen.box.color = 0x00808080;
    screen.box.unk0 = 0;
    screen.box.buffer = buffer;
    grid_index = 2;
    do {
        screen.box.x = (grid_index * 0x28) + 0x38;
        func_8002025C(D_80020468, &screen.box);
        grid_index--;
    } while (grid_index >= 0);

    screen.box.x = 0x12;
    screen.box.width = 0x9C;
    screen.box.height = 1;
    screen.box.type = 0;
    screen.box.visible = 1;
    screen.box.color = 0x00808080;
    screen.box.unk0 = 0;
    screen.box.buffer = buffer;
    grid_index = 2;
    do {
        screen.box.y = (grid_index * 0x10) + 0x20;
        func_8002025C(D_80020468, &screen.box);
        grid_index--;
    } while (grid_index >= 0);

    screen.box.x = 0x8C;
    screen.box.width = 0x20;
    screen.box.height = 1;
    screen.box.type = 0;
    screen.box.visible = 1;
    screen.box.color = 0x00C0C0C0;
    screen.box.unk0 = 0;
    screen.box.buffer = buffer;
    grid_index = 1;
    do {
        screen.box.y = (grid_index * 0x10) + 0x28;
        func_8002025C(D_80020468, &screen.box);
        grid_index--;
    } while (grid_index >= 0);

    screen.box.x -= 0x28;
    func_8002025C(D_80020468, &screen.box);
    value_index = 0;
    grid_index = 0;
    value_screen = &screen;

    column_factor = D_80024308;
    do {
        row_index = grid_index;
        if (grid_index < 3) {
            column_x = (grid_index * 0x28) + 0x3C;
            row_factors = D_8002430A;
            row_factor = row_factors + grid_index;
            row_y = (grid_index * 0x10) + 0x24;
            do {
                screen.text.x = column_x;
                screen.text.y = row_y;
                screen.text.source = (void *)value_screen->number_words.words[value_index];
                value_index++;
                row_y += 0x10;
                row_index++;
                func_800537D0(*column_factor * *row_factor,
                              strlen(screen.text.source), screen.text.source);
                row_factor++;
                func_800201C8(D_800204AC, value_screen);
            } while (row_index < 3);
        }
        column_factor++;
        grid_index++;
    } while (grid_index < 3);
}
