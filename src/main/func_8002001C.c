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

extern StructA_8002001C *func_8003C480(s32 value);
extern void func_80402214(void);
extern void run_slot_operation_code_five(void);
extern s32 init_card_background_object(StructA_8002001C *init_value, s32 config_value);
extern s32 init_card_info_object(StructA_8002001C *init_option, s32 info_value);
extern void func_80406F14(void *object, s32 value);
extern s32 init_card_sme_object(StructA_8002001C *init_option);
extern void func_80406F70(void);

/* Allocates and initializes an object and installs its callback. */
StructA_8002001C *func_8002001C(s32 init_value, s32 config_value) {
    StructA_8002001C *object;

    object = func_8003C480(0);
    if (object != NULL) {
        object->unk44 = config_value;
        func_80406F14((void *) ((s32) object + 0x20), init_value);
        run_slot_operation_code_five();
        func_80402214();
        object->unk20 = init_card_background_object(object, 0);
        object->unk24 = init_card_info_object(object, object->unk4C);
        object->unk28 = init_card_sme_object(object);
        object->unk48 = 0;
        object->unk10 = func_80406F70;
    }
    return object;
}
