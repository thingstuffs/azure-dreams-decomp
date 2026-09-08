typedef signed int s32;
typedef unsigned char u8;

extern u8 D_800BB6C4[];
extern void func_800BB57C(void *, void *, void *);

/* Initializes the object with D_800BB6C4 and sets the state counter to 30. */
void func_800BB6E4(void *object, void *init_data, void *state) {
    *(void **)((u8 *)object - 0x10) = D_800BB6C4;
    func_800BB57C(object, init_data, state);
    do {
        ((s32 *)state)[2] = 30;
    } while (0);
}
