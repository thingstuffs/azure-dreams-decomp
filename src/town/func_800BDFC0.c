typedef signed int s32;
typedef unsigned char u8;

extern u8 D_800BB640[];
extern void func_800BB57C(void *, void *, void *);

void func_800BB720(void *arg0, void *arg1, void *arg2) {
    *(void **)((u8 *)arg0 - 0x10) = D_800BB640;
    func_800BB57C(arg0, arg1, arg2);
    do {
        ((s32 *)arg2)[2] = 14;
    } while (0);
}
