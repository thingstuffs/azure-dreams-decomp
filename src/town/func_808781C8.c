#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_80701DCE[];
extern TownPair D_80701DFC[];

extern s32 func_80702110(s32 index);
extern void func_80702180(s32 index, s32 arg1);
extern void func_8070224C(void) __attribute__((noreturn));
extern void func_80702260(void);
extern void func_80702670(u16 value);
extern void func_807026C0(s32 value);
extern s32 func_80702714(u16 value);

s32 func_807021C8(s32 index) {
    if (func_80702714(D_80701DCE[0]) == 0 &&
        func_80702714(0x1F9) != 0) {
        if (func_80702110(index) != 0) {
            func_80702670(D_80701DFC[index].field_0);
            func_807026C0(0x1F9);
            func_80702260();
            func_8070224C();
        }
        func_80702180(index, 0);
        return index;
    }
    func_80702180(index, 0);
    return index;
}
