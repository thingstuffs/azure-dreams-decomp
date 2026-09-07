#include "common.h"

#include "common.h"

typedef struct Func80035C80Object Func80035C80Object;

struct Func80035C80Object {
    u8 pad00[0x44];
    u8 *field44;
    u8 pad48[2];
    s16 field4A;
    u8 pad4C[4];
    u8 field50;
    u8 pad51[0x17];
    void (*field68)(void);
    u8 pad6C[8];
    u8 *field74;
    u8 field78;
};

extern void func_8003C24C(void);
extern void func_80035ABC(void);

void func_80035C80(Func80035C80Object *arg0) {
    if (arg0->field78 != arg0->field74[1]) {
        u8 *base = arg0->field44;
        s16 offset = arg0->field4A;
        (base + offset)[0x50] = 1;
        func_8003C24C();
        arg0->field68 = func_80035ABC;
    }
}
