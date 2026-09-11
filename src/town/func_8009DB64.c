#include "common.h"
#include "records/Rec_D_800CFCB4.h"


typedef struct {
    u8 pad_00[0x10];
    void *field_10;
    u8 pad_14[4];
    s32 index;
    void *owner;
    u8 pad_20[0x1A];
    u8 state;
    u8 state_3B;
} TownControl;

typedef struct {
    void (*func0)(void);
    void *pad_04[5];
    void (*func18)(void);
} TownVtable;

typedef struct {
    u8 pad_00[0x58];
    TownVtable *vtable;
} TownObject;

extern void func_8009C120(TownObject *arg0, void *arg1, void *arg2);
extern void func_8009C148(TownObject *arg0, void *arg1, void *arg2);

extern s32 D_800834B8;
extern u8 D_80091F64[];
extern u8 D_8009204C[];
extern u8 D_800920F4[];
extern u8 D_800924EC[];
extern u8 D_80092698[];
extern u8 D_800927EC[];
extern TownControl D_800CFCB4;
extern s32 D_800CFCCC;
extern s32 D_800CFDD8[];


typedef struct S_8009B2C4_0 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_8009B2C4_0;   /* (u8 *)arg1 + D_800CFDD8[index] in func_8009B2C4 */

typedef struct S_8009B2C4_1 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_8009B2C4_1;   /* entry in func_8009B2C4 */


/* Dispatches town object actions for the active script and owner state. */
s32 func_8009B2C4(TownObject *object, void *owner, void *context) {
    register TownControl *control ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register TownControl *initial_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    TownControl *control_page;
    TownControl *owner_control;
    register u8 *entry ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 active_script;

    initial_page = (TownControl *)0x800D0000;
    ASM_KEEP_NV(initial_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    control = (TownControl *)((u8 *)initial_page - 0x34C);

    if (control->field_10 == owner) {
        register s32 index ASM_REG("$8") = control->index;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        if (((S_8009B2C4_0 *)((u8 *)owner + D_800CFDD8[index]))->unk_3A != 0) {
            entry = (u8 *)(index + (s32)control);
            if (((S_8009B2C4_1 *)entry)->unk_3A == 1) {
                if (D_800834B8 == (s32)&D_800924EC) {
                    object->vtable->func0();
                    return 1;
                }
            }
            if (D_800834B8 == (s32)&D_80092698) {
                func_8009C120(object, owner, context);
                return 1;
            }
            if (D_800834B8 == (s32)&D_800927EC) {
                if (D_800CFCCC == 0) {
                    func_8009C148(object, owner, context);
                    return 1;
                }
            }
        }
        control_page = (TownControl *)0x800D0000;
    } else {
        control_page = (TownControl *)0x800D0000;
    }
    owner_control = (TownControl *)((u8 *)control_page - 0x34C);
    if (((owner_control->state != 0) && (owner_control->owner == owner)) ||
        ((((Rec_D_800CFCB4 *)owner)->unk_3B != 0) &&
         (((Rec_D_800CFCB4 *)owner)->unk_20 == owner_control))) {
        active_script = D_800834B8;
        if ((active_script == (s32)&D_80091F64) ||
            (active_script == (s32)&D_800920F4) ||
            (active_script == (s32)&D_8009204C)) {
            object->vtable->func18();
        }
    }
    return 0;
}
