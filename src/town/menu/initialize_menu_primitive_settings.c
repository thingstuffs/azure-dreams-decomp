#include "frontend/card/slot_details.h"
#include "common.h"
#include "frontend/card/menu_defaults.h"

typedef struct { s32 value; } DefaultWord;


extern DefaultWord D_8002D694;
extern DefaultWord D_8002D698;
extern DefaultWord D_8002D69C;

extern DefaultWord D_8002D6A4;
extern DefaultWord D_8002D6A8;
/* Copies default primitive settings and configures a 512-wide menu primitive at (-160, -120). */
void initialize_menu_primitive_settings(MenuDisplayNode *work, MenuDisplayBlock *primitive, DisplayPositionWords *settings) {
    s32 setting;
    primitive->words[0] = menu_primitive_defaults[0];
    setting = menu_settings_defaults[0];
    primitive->words[1] = D_8002D694.value;
    primitive->words[2] = D_8002D698.value;
    primitive->words[3] = D_8002D69C.value;
    settings->unk0 = setting;
    settings->unk4 = D_8002D6A4.value;
    settings->unk8 = D_8002D6A8.value;
    work->block = primitive;
    work->vector = settings;
    work->draw_commands = 0;
    work->block->fields.x = -160;
    work->block->fields.y = -120;
    work->block->fields.depth = 512;
    work->block->fields.mode = 4;
}
