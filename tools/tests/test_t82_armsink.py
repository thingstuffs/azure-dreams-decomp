"""T82: chain parsing, sink/hoist site finding and the rewrite are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t82_armsink as M  # noqa: E402

SINK_CALL = '''#include "common.h"
void f(void *state) {
    func_8004DCE0(2);
    {
        register void *message ASM_REG("$4"); /* MATCH: the retail argument register. */

        if (S16_AT(state, 0x120) == 0) {
            if (D_80012D6D == 0) {
                message = &D_80088904;
            } else {
                message = &D_80088934;
            }
        } else {
            message = &D_80088970;
        }
        func_8004DD2C(message);
    }
}
'''

SINK_STORE = '''#include "common.h"
void g(void *motion) {
    s32 target_delta;
    s32 z_accel;

    target_delta = S16_AT(motion, 0x5a);
    if (target_delta >= 17) {
        ASM_SCHED_BARRIER();
        z_accel = 0x10000;
    } else {
        z_accel = 0x1000;
    }
    S32_AT(motion, 0x54) = z_accel;
}
'''

HOIST = '''#include "common.h"
void h(s32 c, u8 *p, s32 *q) {
    s32 t;
    if (c & 1) {
        t = p[0];
        p[1] = 1;
        q[0] = t;
    } else {
        t = p[0];
        p[2] = 2;
        q[0] = t;
    }
}
'''


def src(body, decls="    s32 v;\n"):
    return '#include "common.h"\nvoid r(void *m, s32 c) {\n%s%s}\n' % (decls, body)


class Parsing(unittest.TestCase):
    def test_close_walks_past_a_brace_neutral_else(self):
        ml = M.mask(SINK_CALL).split("\n")
        i = next(k for k, l in enumerate(ml) if "S16_AT(state" in l)
        c = M._close(ml, i, len(ml) - 1)
        self.assertIsNotNone(c)                              # a per-line net count never returns to zero:
        self.assertEqual(ml[c].strip(), "} else {")          # the nested `} else {` is brace-neutral
        self.assertEqual(c - i, 6)
        ch = M.chain_at(ml, i, len(ml) - 1)
        self.assertEqual(len(ch["arms"]), 2)

    def test_chain_needs_braced_arms_and_a_final_else(self):
        for body in ("    if (c) v = 1; else v = 2;\n",
                     "    if (c) {\n        v = 1;\n    }\n",
                     "    if (c) {\n        v = 1;\n    } else\n    {\n        v = 2;\n    }\n"):
            ml = M.mask(src(body)).split("\n")
            i = next(k for k, l in enumerate(ml) if l.strip().startswith("if (c)"))
            self.assertIsNone(M.chain_at(ml, i, len(ml) - 1), body)

    def test_top_stmts(self):
        ml = M.mask(SINK_CALL).split("\n")
        b0 = next(k for k, l in enumerate(ml) if "S16_AT(state" in l)
        self.assertEqual(len(M.top_stmts(ml, b0, b0 + 8)), 1)                   # the whole nested chain is one

    def test_consumer_forms(self):
        self.assertEqual(M.top_eq("S32_AT(a, 1) = b"), 13)
        self.assertIsNone(M.top_eq("a == b"))
        self.assertIsNone(M.top_eq("a += b"))
        self.assertIsNone(M.top_eq("f(a, b)"))
        self.assertEqual([t for _, t in M.split_args("a, f(b, c), d")], ["a", " f(b, c)", " d"])
        store = M.consumers("    S32_AT(motion, 0x54) = z_accel;")
        self.assertEqual([c[0] for c in store], ["z_accel"])
        call = M.consumers("    func_8004DD2C(message);")
        self.assertEqual([c[0] for c in call], ["message"])
        self.assertEqual(M.substitute(store[0], "0x1000"), "    S32_AT(motion, 0x54) = 0x1000;")
        self.assertEqual(M.substitute(call[0], "&D_80088904", "  "), "  func_8004DD2C(&D_80088904);")
        cast = M.consumers("    p->x = (u8 *)m;")
        self.assertEqual(M.substitute(cast[0], "a + b"), "    p->x = (u8 *)(a + b);")   # precedence kept
        self.assertEqual(M.substitute(cast[0], "q"), "    p->x = (u8 *)q;")

    def test_consumer_refuses_a_second_call(self):
        self.assertEqual(M.consumers("    func_a(func_b(), m);"), [])
        self.assertEqual(M.consumers("    q->n = deref(m);"), [])
        self.assertEqual([c[0] for c in M.consumers("    S32_AT(m, 0x4) = v;")], ["v"])  # ALL-CAPS is a macro


class Sites(unittest.TestCase):
    def test_sink_call_consumer(self):
        s = M.sites_in(SINK_CALL)
        self.assertEqual([(x["kind"], x.get("m")) for x in s], [("sink", "message")])
        self.assertEqual(len(s[0]["leaves"]), 3)                                 # the nested chain's arms too
        self.assertTrue(s[0]["decl_single"])

    def test_sink_store_consumer(self):
        s = [x for x in M.sites_in(SINK_STORE) if x["kind"] == "sink"]
        self.assertEqual([x["m"] for x in s], ["z_accel"])
        self.assertEqual(len(s[0]["leaves"]), 2)

    def test_hoist_both_ends(self):
        s = M.sites_in(HOIST)
        self.assertEqual({(x["where"], x["stmt"]) for x in s}, {("lead", "t = p[0];"), ("tail", "q[0] = t;")})
        self.assertTrue(all(len(x["copies"]) == 2 for x in s))

    def test_refusals(self):
        def sinks(text):
            return [x for x in M.sites_in(text) if x["kind"] == "sink"]
        chain = "    if (c) {\n        v = 1;\n    } else {\n        v = 2;\n    }\n"
        self.assertTrue(sinks(src(chain + "    S32_AT(m, 0x4) = v;\n")))         # the shape itself is a site
        self.assertFalse(sinks(src(chain + "    S32_AT(m, 0x4) = v;\n    v = 3;\n")))    # mentioned twice below
        self.assertFalse(sinks(src(chain + "    func_a(&v);\n")))                        # address-taken
        self.assertFalse(sinks(src(chain + "    S32_AT(m, v) = v;\n")))                  # two mentions in one
        self.assertFalse(sinks(src("    if (c) {\n        v = 1;\n    }\n    S32_AT(m, 0x4) = v;\n")))
        self.assertTrue(sinks(src("    if (c) {\n        if (c & 2) {\n            return;\n        }\n"
                                  "        v = 1;\n    } else {\n        v = 2;\n    }\n"
                                  "    S32_AT(m, 0x4) = v;\n")))             # a jump OUT of an arm is fine
        self.assertFalse(sinks(src("    if (c) {\n        v = 1;\n    } else {\n        v = 2;\n    }\n"
                                   "out:\n    S32_AT(m, 0x4) = v;\n")))       # a label: something can jump in
        self.assertFalse(sinks(src("    if (c) {\n        v = f(1,\n            2);\n    } else {\n"
                                   "        v = 2;\n    }\n    S32_AT(m, 0x4) = v;\n")))  # multi-line leaf
        self.assertFalse(sinks(src(chain + "    S32_AT(m, 0x4) = v;\n", decls="")))       # v is not a local

    def test_preprocessor_span_refused(self):
        text = src("    if (c) {\n#ifdef NON_MATCHING\n        v = 9;\n#endif\n        v = 1;\n    } else {\n"
                   "        v = 2;\n    }\n    S32_AT(m, 0x4) = v;\n")
        self.assertFalse([x for x in M.sites_in(text) if x["kind"] == "sink"])


class Rewrite(unittest.TestCase):
    def test_sink_call_unwraps_the_block(self):
        site = M.sites_in(SINK_CALL)[0]
        new, win, touched = M.build(SINK_CALL, site)
        self.assertNotIn("message", new)
        self.assertNotIn("        {\n", new)                                     # the bare block is gone
        for arg in ("&D_80088904", "&D_80088934", "&D_80088970"):
            self.assertIn("func_8004DD2C(%s);" % arg, new)
        self.assertEqual(new.count("func_8004DD2C"), 3)
        self.assertIn("\n    if (S16_AT(state, 0x120) == 0) {", new)            # re-indented by one level
        self.assertTrue(win[0] <= min(i for i, l in enumerate(new.split("\n")) if "func_8004DD2C" in l))

    def test_sink_store_keeps_the_fence_for_the_erase_step(self):
        site = [x for x in M.sites_in(SINK_STORE) if x["kind"] == "sink"][0]
        new, _, _ = M.build(SINK_STORE, site)
        self.assertNotIn("z_accel", new)                                         # decl, arms and consumer
        self.assertIn("        S32_AT(motion, 0x54) = 0x10000;", new)
        self.assertIn("        S32_AT(motion, 0x54) = 0x1000;", new)
        self.assertIn("ASM_SCHED_BARRIER();", new)                               # erased later, not by the move
        self.assertIn("    s32 target_delta;", new)                              # the other local stays

    def test_hoist_moves_one_copy_out(self):
        lead = [x for x in M.sites_in(HOIST) if x["where"] == "lead"][0]
        new, _, _ = M.build(HOIST, lead)
        self.assertEqual(new.count("t = p[0];"), 1)
        self.assertIn("    t = p[0];\n    if (c & 1) {", new)
        tail = [x for x in M.sites_in(HOIST) if x["where"] == "tail"][0]
        new, _, _ = M.build(HOIST, tail)
        self.assertEqual(new.count("q[0] = t;"), 1)
        self.assertIn("    }\n    q[0] = t;", new)

    def test_hoist_lead_refused_when_the_condition_reads_the_target(self):
        text = src("    if (v & 1) {\n        v = 1;\n        p[1] = 1;\n    } else {\n        v = 1;\n"
                   "        p[2] = 2;\n    }\n", decls="    s32 v;\n    u8 *p;\n")
        # the lead is refused (the condition reads what it assigns); the same statement may still go after
        self.assertEqual([x["where"] for x in M.sites_in(text)], ["tail"])


if __name__ == "__main__":
    unittest.main()
