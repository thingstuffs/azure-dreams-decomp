#include "common.h"
#include "frontend/card/menu_defaults.h"

typedef struct { s32 word[4]; } Primitive;
typedef struct { s32 word[3]; } Settings;
typedef struct { Primitive *primitive; Primitive *data; Settings *settings; s32 pad; } Item;
typedef struct { u8 pad[0xAEC]; Settings settings; u8 padAF8[0x10]; Primitive *pointers[21]; Item items[21]; Primitive primitives[21]; } Work;

typedef struct { s32 value; } DefaultWord;
extern DefaultWord D_8002D6A4, D_8002D6A8;
/* Links menu entries to their primitive storage and copies the default primitive and shared settings. */
void initialize_menu_primitive_entries(Work *work, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        work->pointers[i] = (Primitive *)&work->items[i];
        work->primitives[i].word[0] = menu_primitive_defaults[0];
        work->primitives[i].word[1] = menu_primitive_defaults[1];
        work->primitives[i].word[2] = menu_primitive_defaults[2];
        work->primitives[i].word[3] = menu_primitive_defaults[3];
        work->items[i].data = &work->primitives[i];
        work->items[i].settings = &work->settings;
    }
    work->settings.word[0] = menu_settings_defaults[0];
    work->settings.word[1] = D_8002D6A4.value;
    work->settings.word[2] = D_8002D6A8.value;
}
