typedef signed int s32;
typedef unsigned char u8;

extern u8 D_800BB6C4[];
extern void func_800BB57C(void *, void *, void *);

/* Set the object handler table, initialize its state, and set its counter to 14. */
void func_800BB75C(void *object, void *context, void *state) {
    *(void **)((u8 *)object - 0x10) = D_800BB6C4;
    func_800BB57C(object, context, state);
    do {
        ((s32 *)state)[2] = 14;
    } while (0);
}
