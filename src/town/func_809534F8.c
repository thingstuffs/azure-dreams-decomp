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

void func_800204F8(void)
{
    Screen s;
    Screen *p;
    Screen *q;
    void *allocated;
    void *buffer;
    s32 i;
    s32 j;
    s32 word_index;
    s32 column_y;
    s16 row_x;
    s16 *row_scale;
    s16 *column_scale;
    register s16 *cbase ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    buffer = 0;
    s.text_words = D_80020010;
    s.number_words = D_80020050;
    allocated = func_8003FD64(1, D_80083498);
    if (allocated != 0) {
        buffer = (u8 *)allocated + 0x20;
        *(void **)((u8 *)allocated + 0x10) = D_80020900;
    }

    s.text.x = 0x14;
    s.text.y = 0x14;
    s.text.type = 3;
    s.text.vram = 0x7C80;
    s.text.unk1C = 0;
    s.text.color = 0x00808080;
    s.text.source = D_80020068;
    s.text.unk0 = 0;
    s.text.buffer = buffer;
    func_800201C8(D_800204AC, &s.text);

    i = 2;
    p = &s;
    do {
        s.text.x = (i * 0x28) + 0x48;
        s.text.source = (void *)p->text_words.words[i];
        func_800201C8(D_800204AC, &p->text);
        i--;
    } while (i >= 0);

    s.text.x = 0x20;
    i = 2;
    do {
        s.text.y = (i * 0x10) + 0x24;
        s.text.source = (void *)s.text_words.words[i + 1];
        func_800201C8(D_800204AC, &s.text);
        i--;
    } while (i >= 0);

    s.box.x = 0x10;
    s.box.y = 0x10;
    s.box.width = 0xA0;
    s.box.height = 0x40;
    s.box.type = 2;
    s.box.visible = 1;
    s.box.color = 0x00606060;
    s.box.unk0 = 0;
    s.box.buffer = buffer;
    func_8002025C(D_800203D8, &s.box);

    s.box.y = 0x12;
    s.box.width = 1;
    s.box.height = 0x3C;
    s.box.type = 0;
    s.box.visible = 1;
    s.box.color = 0x00808080;
    s.box.unk0 = 0;
    s.box.buffer = buffer;
    i = 2;
    do {
        s.box.x = (i * 0x28) + 0x38;
        func_8002025C(D_80020468, &s.box);
        i--;
    } while (i >= 0);

    s.box.x = 0x12;
    s.box.width = 0x9C;
    s.box.height = 1;
    s.box.type = 0;
    s.box.visible = 1;
    s.box.color = 0x00808080;
    s.box.unk0 = 0;
    s.box.buffer = buffer;
    i = 2;
    do {
        s.box.y = (i * 0x10) + 0x20;
        func_8002025C(D_80020468, &s.box);
        i--;
    } while (i >= 0);

    s.box.x = 0x8C;
    s.box.width = 0x20;
    s.box.height = 1;
    s.box.type = 0;
    s.box.visible = 1;
    s.box.color = 0x00C0C0C0;
    s.box.unk0 = 0;
    s.box.buffer = buffer;
    i = 1;
    do {
        s.box.y = (i * 0x10) + 0x28;
        func_8002025C(D_80020468, &s.box);
        i--;
    } while (i >= 0);

    s.box.x -= 0x28;
    func_8002025C(D_80020468, &s.box);
    word_index = 0;
    i = 0;
    q = &s;

    row_scale = D_80024308;
    do {
        j = i;
        if (i < 3) {
            row_x = (i * 0x28) + 0x3C;
            cbase = D_8002430A;
            column_scale = cbase + i;
            column_y = (i * 0x10) + 0x24;
            do {
                s.text.x = row_x;
                s.text.y = column_y;
                s.text.source = (void *)q->number_words.words[word_index];
                word_index++;
                column_y += 0x10;
                j++;
                func_800537D0(*row_scale * *column_scale,
                              strlen(s.text.source), s.text.source);
                column_scale++;
                func_800201C8(D_800204AC, q);
            } while (j < 3);
        }
        row_scale++;
        i++;
    } while (i < 3);
}
