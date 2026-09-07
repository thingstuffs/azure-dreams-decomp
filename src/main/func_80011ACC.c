#include "common.h"

typedef struct {
    u8 pad[8];
    s16 w;
    s16 h;
} WinSub;

typedef struct {
    void *field0;
    WinSub *field4;
} WinObj;

extern void func_800242D8(void *arg0, s32 arg1, s32 arg2);
extern s32 D_80079054;
extern s32 D_800790B4;
extern s32 D_80079114;

void func_80024ACC(u8 *arg0) {
    void *temp_s1;
    WinObj *obj;

    temp_s1 = arg0 + 4;
    func_800242D8(temp_s1, 0xF8, 0x48);

    obj = *(WinObj **)(arg0 + 0xB48);
    obj->field4->w = 0xA0;
    obj->field4->h = 0xB0;
    obj->field0 = temp_s1;

    obj = *(WinObj **)(arg0 + 0xB3C);
    obj->field4->w = 0x60;
    obj->field4->h = 0x88;
    obj->field0 = &D_80079054;

    obj = *(WinObj **)(arg0 + 0xB40);
    obj->field4->w = 0xD0;
    obj->field4->h = 0x88;
    obj->field0 = &D_800790B4;

    obj = *(WinObj **)(arg0 + 0xB44);
    obj->field4->w = 0x20;
    obj->field4->h = 0x88;
    obj->field0 = &D_80079114;
}
