"""T112: dead-host detection and the host rewrite are textual; no screen, no `vf`."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t112_deadhost as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

SPAWN = '''#include "common.h"
void *spawn(void *arg0, s8 arg1, s16 arg3) {
    register s8 held ASM_REG("$21");
    void *created;

    held = arg1;
    created = func_8003FD64(0x112, D_80083498);
    if (created != 0) {
        *(u8 *)created = held;
        *(s16 *)created = arg3;
    }
    return created;
}
'''

PAGE = '''#include "common.h"
void init(void) {
    register u32 page ASM_REG("$2");
    s8 *record;
    s16 count;

    page = 0x800E0000;
    record = (s8 *)(page + 0x3DB0);
    ASM_CLOBBER("$2");
    count = 0;
    record[0] = count;
}
'''


class TestHosts(unittest.TestCase):
    def test_a_parameter_read_only_before_the_call_hosts_its_literal(self):
        st = [s for s in M.sites(SPAWN) if s["k"] == "0x112"][0]
        _p, b0, b1 = M._span(SPAWN, "spawn")
        names = [h[0] for h in M.hosts(SPAWN, _p, b0, b1, st["at"])]
        self.assertIn("arg1", names)
        self.assertNotIn("arg3", names)            # read after the call

    def test_a_dead_local_hosts_a_zero_init(self):
        st = [s for s in M.sites(PAGE) if s["kind"] == "assign" and s["k"] == "0"][0]
        _p, b0, b1 = M._span(PAGE, "init")
        self.assertEqual([h[0] for h in M.hosts(PAGE, _p, b0, b1, st["at"])], ["page"])


class TestRewrite(unittest.TestCase):
    def test_the_literal_goes_through_the_host_and_a_narrow_parameter_widens(self):
        c = dict(M.candidates(SPAWN))["arg@7:arg1<-0x112:s32:all"]
        self.assertIn("    arg1 = 0x112;\n    created = func_8003FD64(arg1, D_80083498);", c)
        self.assertIn("void *spawn(void *arg0, s32 arg1, s16 arg3)", c)
        self.assertEqual(sites_of(c), [])

    def test_the_zero_init_is_read_from_the_dead_local(self):
        c = dict(M.candidates(PAGE))["assign@10:page<-0:plain:window+hreg"]
        self.assertIn("    page = 0;\n    count = page;", c)
        self.assertEqual(len(sites_of(c)), 0)


if __name__ == "__main__":
    unittest.main()
