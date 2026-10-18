#include "common.h"

typedef struct { s32 word[4]; } Primitive;
typedef struct { s32 word[3]; } Settings;
typedef struct { Primitive *primitive; Primitive *data; Settings *settings; s32 pad; } Item;
typedef struct { u8 pad[0xAEC]; Settings settings; u8 padAF8[0x10]; Primitive *pointers[21]; Item items[21]; Primitive primitives[21]; } Work;
extern Primitive D_8002D690;
typedef struct { s32 value; } DefaultWord;
extern DefaultWord D_8002D6A0, D_8002D6A4, D_8002D6A8;
void initialize_menu_primitive_entries(Work *work, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        work->pointers[i] = (Primitive *)&work->items[i];
        work->primitives[i].word[0] = D_8002D690.word[0];
        work->primitives[i].word[1] = D_8002D690.word[1];
        work->primitives[i].word[2] = D_8002D690.word[2];
        work->primitives[i].word[3] = D_8002D690.word[3];
        work->items[i].data = &work->primitives[i];
        work->items[i].settings = &work->settings;
    }
    work->settings.word[0] = D_8002D6A0.value;
    work->settings.word[1] = D_8002D6A4.value;
    work->settings.word[2] = D_8002D6A8.value;
}
