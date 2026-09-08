#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x2D58];
    u32 increment;
    u32 total;
} CounterPage;

extern void func_80043458(void);
extern void func_8003B820(void);
extern void func_8003B714(void);

/* Runs runtime updates and adds the counter increment, capping the total at one billion. */
void func_8003B92C(void) {
    CounterPage *page;
    u32 total;

    func_80043458();
    func_8003B820();
    func_8003B714();

    page = (CounterPage *)0x80010000;
    total = page->total + page->increment;
    page->total = total;
    if (total > 1000000000U) {
        page->total = 1000000000U;
    }
}
