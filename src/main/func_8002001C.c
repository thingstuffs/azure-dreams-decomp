#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    void (*unk10)(void);
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
} StructA_8002001C;

extern StructA_8002001C *func_8003C480(s32 arg0);
extern void func_80402214(void);
extern void func_804023C4(void);
extern s32 func_80404C84(StructA_8002001C *arg0, s32 arg1);
extern s32 func_804057F0(StructA_8002001C *arg0, s32 arg1);
extern void func_80406F14(void *arg0, s32 arg1);
extern s32 func_80407C10(StructA_8002001C *arg0);
extern void func_80406F70(void);

/* Allocates and initializes an object and installs its callback. */
StructA_8002001C *func_8002001C(s32 init_value, s32 config_value) {
    StructA_8002001C *object;

    object = func_8003C480(0);
    if (object != NULL) {
        object->unk44 = config_value;
        func_80406F14((void *) ((s32) object + 0x20), init_value);
        func_804023C4();
        func_80402214();
        object->unk20 = func_80404C84(object, 0);
        object->unk24 = func_804057F0(object, object->unk4C);
        object->unk28 = func_80407C10(object);
        object->unk48 = 0;
        object->unk10 = func_80406F70;
    }
    return object;
}
