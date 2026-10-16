#include "common.h"

typedef struct {
    u8 before_flags[0x1C];
    u32 flags;
} DungeonControl;
extern s32 D_800814A0;
extern u8 D_80080A86;
extern u16 D_80013714;
extern u8 D_80083160[];
extern DungeonControl *D_800814A8;
extern void func_80040190(void);
extern void func_800401FC(void);
extern void func_8004027C(void);
extern void func_8004D70C(void);
extern void func_800D13B8(void);
extern void func_800CF8E4(void);
extern void func_800897E4(void);
extern void func_80044B48(void);
extern void func_80089588(void);

void func_800894A0(void) {
    u8 *work = D_80083160;
    func_80040190();
    if (D_800814A0 & 0x8000) {
        func_800401FC();
    }
    D_800814A0 = 0;
    if (D_80080A86 == 0) {
        func_8004027C();
        if (D_80013714 & 2) {
            return;
        }
        if (*(s32 *)(work + 0x1DC) != 0) {
            func_8004D70C();
            func_800D13B8();
            if (!(D_800814A8->flags & 0x10)) {
                func_800CF8E4();
            }
        }
    }
    func_800897E4();
    func_80044B48();
    func_80089588();
}
