#include "common.h"

typedef struct { s32 value; } DefaultWord;

extern DefaultWord D_8002D690;
extern DefaultWord D_8002D694;
extern DefaultWord D_8002D698;
extern DefaultWord D_8002D69C;
extern DefaultWord D_8002D6A0;
extern DefaultWord D_8002D6A4;
extern DefaultWord D_8002D6A8;
typedef struct { u8 pad[8]; s16 x, y, width; u8 padE; u8 kind; } Primitive;
typedef struct { s32 active; Primitive *primitive; s32 *settings; } Work;
void initialize_menu_primitive_settings(Work *work, s32 *primitive, s32 *settings) {
    s32 setting;
    primitive[0] = D_8002D690.value;
    setting = D_8002D6A0.value;
    primitive[1] = D_8002D694.value;
    primitive[2] = D_8002D698.value;
    primitive[3] = D_8002D69C.value;
    settings[0] = setting;
    settings[1] = D_8002D6A4.value;
    settings[2] = D_8002D6A8.value;
    work->primitive = (Primitive *)primitive;
    work->settings = settings;
    work->active = 0;
    work->primitive->x = -160;
    work->primitive->y = -120;
    work->primitive->width = 512;
    work->primitive->kind = 4;
}
