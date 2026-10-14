#include "shared/object_node.h"
#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"














extern s32 D_800E2178;
s32 rand(void);
extern s32 D_800253BC;
/* Spawns a primary effect and eight randomly offset particles from the supplied data. */
void func_80024A44(s32 source, B22_81893244_Func81893244Data *initial_data, s16 status_param) {
    B22_81893244_Func81893244Sub *sprite;
    B22_81893244_Func81893244Data *payload;
    B22_81893244_Func81893244Object *effect;
    B22_81893244_Func81893244Status *status;
    s32 brightness;
    s32 particle_index;
    effect = (B22_81893244_Func81893244Object *)func_8003FC64(0x212);
    if (effect != NULL) {
        status = &effect->status;
        effect->field10 = func_800248F8;
        status->field20 = source;
        status->field24 = 0;
        status->field26 = status_param;
        sprite = effect->fieldC;
        sprite->uC.bytesC.fieldE = 0x80;
        sprite->uC.bytesC.fieldD = 0x80;
        sprite->uC.bytesC.fieldC = 0x80;
        func_8003DB94(sprite, &D_800E2178, 0);
        sprite->field1E = 0x1800;
        sprite->field1C = 0x1800;
        func_8004491C(effect, func_80045340);
        payload = effect->field8;
        *payload = *initial_data;
        func_80024824(source, payload, 8, -0x40);
    }
    particle_index = 0;
    do {
        effect = (B22_81893244_Func81893244Object *)func_8003FC64(0x212);
        status = &effect->status;
        if (effect != NULL) {
            effect->field10 = func_800249B8;
            brightness = 0x80;
            status->field20 = source;
            status->field24 = 0;
            status->field26 = status_param;
            sprite = effect->fieldC;
            sprite->uC.bytesC.fieldE = brightness;
            sprite->uC.bytesC.fieldD = brightness;
            sprite->uC.bytesC.fieldC = brightness;
            func_8003DB94(sprite, &D_800253BC, 0);
            sprite->field1E = 0x800;
            sprite->field1C = 0x800;
            sprite->field14 = (u16) (sprite->field14 | 0xC);
            sprite->field10 = (u16) (sprite->field10 | 0x60);
            func_8004491C(effect, func_80045340);
            payload = effect->field8;
            *payload = *initial_data;
            payload->u0.halves0.field2 = (u16) (payload->u0.halves0.field2 + ((s32) (func_800644B8(rand()) * 2) >> 8));
            payload->u4.halves4.field6 = (u16) (payload->u4.halves4.field6 + ((s32) (func_80064584(rand()) * 2) >> 8));
        }
        particle_index += 1;
    } while (particle_index < 8);
}
