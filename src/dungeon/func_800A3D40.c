#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800A94A0_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x23];
    u8 unk_2B;
    u8 pad_2C[0x4C];
    void * unk_78;
    u8 pad_7C[0x24];
    s16 unk_A0;
} S_800A94A0_0;   /* arg0 in func_800A94A0; pointer addresses record offset 0x18 */


typedef struct S_800A94A0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    void * unk_20;
} S_800A94A0_2;   /* temp_v0 in func_800A94A0 */

typedef struct S_800A94A0_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
} S_800A94A0_3;   /* temp_v0_3 in func_800A94A0 */

typedef struct S_800A94A0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A94A0_4;   /* temp_s0 in func_800A94A0 */

typedef struct S_800A94A0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A94A0_5;   /* temp_v1 in func_800A94A0 */

typedef struct S_800A94A0_6 {
    s32 unk_00;
} S_800A94A0_6;   /* temp_v0_4 in func_800A94A0; pointer addresses record offset 0x14 */

typedef struct S_800A94A0_7 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800A94A0_7;   /* temp_s5 in func_800A94A0 */

typedef struct S_800A94A0_8 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800A94A0_8;   /* temp_t0 in func_800A94A0 */

typedef struct S_800A94A0_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800A94A0_9;   /* *D_800E3D7C in func_800A94A0 */


extern u8 D_80083498[];
extern s32 D_800814A0[3];
extern volatile s16 D_80013714[8];
extern u8 D_80082E80[];
extern u8 D_800E3CC8[];
extern u8 *D_800E3D7C[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
struct S_8006DE24_Entry;
typedef struct S_8006DE24_Entry S_8006DE24_Entry;
struct S_8006DE24_Entry {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    u8 padC[8];
};
extern S_8006DE24_Entry D_8006DE24[];

void *func_8003FD64();
M2C_UNK func_80069EF8();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099734();
M2C_UNK func_8009FD40();
M2C_UNK func_800A5720();
s16 func_800A9400();
s32 func_800A982C();
M2C_UNK func_800C77D0();
M2C_UNK func_800C78A0();
M2C_UNK func_800C7A3C();
void func_800AD594();
extern M2C_UNK D_80089080;
extern u8 D_800DD880[];
extern u8 D_800DD8B4[];
extern M2C_UNK D_800E1C58;
extern u8 D_800E3D68;

/* Creates an effect for an actor, sets its position and scale, and builds its message. */
void *func_800A94A0(void *actor, Rec_D_800E3D7C *effect_record, s16 mode, void *context) {
    s32 message;
    s32 name_text;
    s32 effect_data;
    register s32 text_context ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 new_text_context;
    M2C_UNK direction_offset;
    s16 name_index;
    s32 effect_mode;
    u16 effect_flags;
    s32 global_flags;
    s32 effect_scale;
    register void *actor_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 variant;
    register s16 effect_id ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    S_800A94A0_4 *effect_position;
    S_800A94A0_7 *actor_state;
    void *effect;
    S_800A94A0_3 *effect_state;
    void *linked_object;
    S_800A94A0_5 *actor_position;
    u8 *map_state;

    actor_state = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_04;
    effect = func_8003FD64(0x12, D_80083498);
    if (effect != NULL) {
        effect_mode = ((s32) mode << 0x10) >> 0x10;
        {
            register s32 mode_arg ASM_REG("$5") = effect_mode;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            u8 entry_variant;
            effect_id = effect_record->unk_00.at00_u8.v;
            entry_variant = effect_record->unk_00.at01_u8.v;
            D_800E3D68 = entry_variant;
            effect_data = func_800A982C((u8) effect_id, mode_arg, ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_2B);
        }
        ASM_KEEP_NV(effect_id);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        if (effect_data == 0) {
            effect_flags = ((S_800A94A0_2 *)effect)->unk_1E | 0x8000;
            global_flags = D_800814A0[0] | 0x8000;
            ((S_800A94A0_2 *)effect)->unk_1E = effect_flags;
            D_800814A0[0] = global_flags;
            return NULL;
        }
        ((S_800A94A0_2 *)effect)->unk_10 = effect_data;
        effect_state = effect + 0x20;
        ((S_800A94A0_2 *)effect)->unk_20 = actor;
        effect_state->unk_04 = context;
        effect_state->unk_08 = effect_id;
        D_800E3CC8[0] = effect_id;
        variant = effect_record->unk_00.at01_u8.v;
        effect_state->unk_09 = variant;
        D_800E3CC8[1] = variant;
        if (mode == 0) {
            actor_position = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_00;
            effect_position = ((S_800A94A0_2 *)effect)->unk_08;
            effect_position->unk_02 = (u16) actor_position->unk_02;
            effect_position->unk_06 = (u16) actor_position->unk_06;
            effect_position->unk_0A = (u16) actor_position->unk_0A;
            text_context = func_80069EF8();
            if (!((u16) *D_80013714 & 1)) {
                linked_object = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_78;
                if (linked_object != NULL) {
                    func_8009FD40(((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_04, ((S_800A94A0_6 *)((u8 *)linked_object - 0x14))->unk_00);
                }
            }
            func_800C77D0(effect, effect_position, 8, 0x300);
            ASM_KEEP(text_context);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            goto set_effect_scale;
        }
        map_state = D_80082E80;
        if (!(actor_state->unk_14 & 0x8000)) {
            if (!(((S_800A94A0_8 *)map_state)->unk_14 & 0x8000)) {
                func_800C7A3C(map_state, actor_state, ((S_800A94A0_9 *)(*D_800E3D7C))->unk_88, ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_A0, 8, 0x300);
                goto set_effect_scale;
            }
        }
        direction_offset = ((u16) ((S_800A94A0_9 *)(*D_800E3D7C))->unk_2A >> 8) & 0xE;
        func_800C78A0(actor - 0x20, (((S_800A94A0_8 *)map_state)->unk_24 << 6) + ((s32) (*(u16 *)((u8 *)D_800DCEAC + direction_offset) << 0x10) >> 0x11) + 0x20, (((S_800A94A0_8 *)map_state)->unk_25 << 6) + ((s32) (*(u16 *)((u8 *)D_800DCEBC + direction_offset) << 0x10) >> 0x11) + 0x20, ((S_800A94A0_9 *)(*D_800E3D7C))->unk_88, 8, 0x300);
set_effect_scale:
        if ((mode << 0x10) != 0) {
            register s32 lookup_index ASM_REG("$2") = effect_id;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            effect_scale = D_800DD8B4[lookup_index];
            actor_arg = actor;
            effect_scale <<= 6;
        } else {
            register s32 lookup_index ASM_REG("$2") = effect_id;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            effect_scale = D_800DD880[lookup_index];
            actor_arg = actor;
            effect_scale <<= 8;
        }
        func_800AD594(actor_arg, effect_scale);
        if ((effect != NULL) && ((s8) ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_2B > 0)) {
            new_text_context = func_800990FC();
            actor_arg = actor;
            text_context = new_text_context;
            message = func_80099194(&D_800E1C58, func_80099734(actor_arg, text_context));
            if (((u32)(u16)mode << 0x10) != 0) {
                name_index = func_800A9400(((s32)effect_id << 0x10) >> 0x10);
                name_text = D_8006DE24[name_index].unk8;
            } else {
                register s32 effect_index ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                S_8006DE24_Entry *name_table;
                effect_index = (s32)effect_id << 0x10;
                name_table = D_8006DE24;
                effect_index >>= 0x10;
                name_text = name_table[effect_index].unk0;
            }
            message = func_80099194(name_text, message);
            func_80099290(func_80099194(&D_80089080, message));
            ASM_KEEP(message);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_800A5720(text_context);
            goto return_effect;
        }
        return effect;
    }
return_effect:
    return effect;
}
