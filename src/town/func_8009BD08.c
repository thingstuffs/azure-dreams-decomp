#include "common.h"

typedef struct {
    unsigned char pad04[0];
} Unknown;

extern void func_80094984(void *, void *);
extern void func_80099754(void *);
extern signed char D_80082668;
extern int D_80098764;
extern int D_800D01B8[];

/* Initializes an object from the supplied data and sets its handler and state. */
void func_80099468(void *object, void *initializationData) {
    unsigned short secondaryValue;

    func_80094984(D_800D01B8, object);
    D_80082668 = 0;
    *(unsigned short *)((unsigned char *)object + 0x30) =
        *(unsigned short *)((unsigned char *)initializationData + 2);
    secondaryValue = *(unsigned short *)((unsigned char *)initializationData + 6);
    *(short *)((unsigned char *)object + 0xA) = 8;
    *(int **)((unsigned char *)object + 4) = &D_80098764;
    *(unsigned short *)((unsigned char *)object + 0x32) = secondaryValue;
    func_80099754(initializationData);
}
