"""T87: pair finding and the four rewrites are textual; the listing screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t87_lifetimemerge as M  # noqa: E402

ITEM = '''#include "common.h"
void f(void *object, void *actor) {
    static void *const table[3] = {
        &&a, &&b, &&c
    };
    void *node;
    s32 seen;

    seen = 0;
    node = D_800814A8;
    if (seen) {
        s32 x;
        s32 y;

        node = func_800A05A4(object, actor, 0x10);
        (*(void * volatile *)((u8 *)object + 0x60)) = node;
        ASM_KEEP(node);   /* UNRESOLVED C shape (pin) */
        x = (*(s8 *)((u8 *)object + 0x72));
        y = (*(s8 *)((u8 *)object + 0x73));
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        (*(s8 *)((u8 *)object + 0x72)) = x;
        (*(s8 *)((u8 *)object + 0x73)) = y;
    }
a:
b:
c:
    return;
}
'''

REVERSE = '''#include "common.h"
void r(void *sprite, void *motion) {
    {
        s32 tile_coord;
        s32 target_coord;
        s32 current_coord;

        tile_coord = sprite->unk_24;
        current_coord = motion->unk_02.u;
        target_coord = tile_coord << 6;
        ASM_USE_NV(target_coord);   /* UNRESOLVED C shape (pin) */
        current_coord -= 0x20;
        motion->unk_0C.s = (target_coord - current_coord) << 14;
    }
}
'''

SPLIT = '''#include "common.h"
void g(void *object, void *actor) {
    s32 target_x;
    s32 target_y;

    ((S_1 *)object)->unk_60 = func_800A05A4(
        object, actor, 0x10);
    ASM_KEEP(object);   /* UNRESOLVED C shape (pin) */
    target_x = ((S_1 *)object)->unk_72.s;
    target_y = ((S_1 *)object)->unk_73.s;
    if (target_x < 0) {
        target_x = -target_x;
    }
    ((S_1 *)object)->unk_72.s = target_x;
    ((S_1 *)object)->unk_73.s = target_y;
}
'''

HOIST = '''#include "common.h"
void q(void *actor, void *sprite) {
    *(void * volatile *)((u8 *)actor + 0x60) =
        func_800A05A4(actor, sprite, 0x10);
    ASM_KEEP(use_player);   /* UNRESOLVED C shape (pin) */
    {
        s32 x = ((S_1 *)actor)->unk_72.u;
        s32 y = ((S_1 *)actor)->unk_73.u;

        if (x < 0) {
            x = -x;
        }
        ((S_1 *)actor)->unk_72.s = x;
        ((S_1 *)actor)->unk_73.s = y;
    }
}
'''

NARROW = '''#include "common.h"
void h(void *object_arg) {
    s32 height;
    s32 height_adjust;
    register u32 raw_height ASM_REG("$3");   /* UNRESOLVED C shape (pin) */
    u16 part_flags;

    part_flags = ((S_1 *)object_arg)->unk_14;
    if (!(part_flags & 0x8000)) {
        height = *(s16 *)((u8 *)object_arg + 0x92);
        raw_height = *(volatile u16 *)((u8 *)object_arg + 0x92);
        if (height_adjust < height) {
            height_adjust = raw_height - 8;
        }
    }
}
'''

NOMERGE = '''#include "common.h"
void k(void *object) {
    void *node;
    s32 x;
    s32 y;

    node = func_800A05A4(object, 0x10);
    (*(void * volatile *)((u8 *)object + 0x60)) = node;
    ASM_KEEP(node);   /* UNRESOLVED C shape (pin) */
    y = (*(s8 *)((u8 *)object + 0x73));
    x = (*(s8 *)((u8 *)object + 0x72));
    (*(s8 *)((u8 *)object + 0x72)) = x + y;
    node = D_800814A8;
    (*(void * volatile *)((u8 *)object + 0x64)) = node;
}
'''


def labels(text):
    return [c[0] for c in M.candidates(text)]


def form(text, name):
    return next(c for c in M.candidates(text) if c[0].startswith(name))[1]


class Scope(unittest.TestCase):
    def test_declaration_rescan(self):
        """natural's block reader stops at the computed-goto table; the rescan still finds `node`."""
        import natural as N
        t = N._T(ITEM)
        fn = list(N._functions(t))[0]
        names = {d["name"] for d in M.scope_decls(fn)}
        self.assertTrue({"node", "seen", "x", "y"} <= names)

    def test_no_declaration_from_an_assignment(self):
        """`dx = -dx;` must not read as a declaration of `x` with base type `d`."""
        self.assertIsNone(M.DECL_RE.match("        dx = -dx;"))
        self.assertIsNone(M.DECL_RE.match("        dx = (*(s8 *)((u8 *)object + 0x72));"))
        self.assertIsNotNone(M.DECL_RE.match("    void *node;"))
        self.assertIsNotNone(M.DECL_RE.match('    register u32 raw_height ASM_REG("$3");'))


class Pairs(unittest.TestCase):
    def test_item_family_pair(self):
        ps = M.pairs(ITEM)
        self.assertEqual([(p[2]["name"], p[3]["name"], p[9]) for p in ps],
                         [("node", "x", ["cast", "union"])])          # `y` is not the next statement

    def test_cast_rewrite(self):
        cand = form(ITEM, "cast")
        self.assertIn("        x = (s32)func_800A05A4(object, actor, 0x10);", cand)
        self.assertIn("(*(void * volatile *)((u8 *)object + 0x60)) = (void *)x;", cand)
        self.assertIn("        ASM_KEEP(node);", cand)                # the pin is left for the eraser
        self.assertIn("        s32 x;", cand)                         # B's declaration is untouched
        self.assertIn("    void *node;", cand)                        # A is still used before its tail

    def test_union_rewrite(self):
        cand = form(ITEM, "union")
        self.assertIn("        union { void * pointer; s32 value; } x;", cand)
        self.assertIn("        x.pointer = func_800A05A4(object, actor, 0x10);", cand)
        self.assertIn("        if (x.value < 0) {", cand)
        self.assertIn("            y = -y;", cand)                    # the sibling is untouched

    def test_refusals(self):
        self.assertEqual(labels(NOMERGE), [])                         # A is written again afterwards
        self.assertEqual(labels(ITEM.replace("x = (*(s8 *)", "x = node;\n        x = (*(s8 *)")), [])
        self.assertEqual(labels(ITEM.replace("        s32 x;", "        s32 x = 0;")), [])
        self.assertEqual(labels(ITEM.replace("= x;", "= *&x;").replace("if (x < 0)", "if (*&x < 0)")), [])


class Reverse(unittest.TestCase):
    def test_source_hosts_the_value(self):
        """`B = f(A);` on A's last line: B is renamed away onto its own source."""
        self.assertEqual(labels(REVERSE), ["rename:target_coord->tile_coord@10"])
        cand = form(REVERSE, "rename")
        self.assertIn("        tile_coord = tile_coord << 6;", cand)
        self.assertIn("        motion->unk_0C.s = (tile_coord - current_coord) << 14;", cand)
        self.assertNotIn("        s32 target_coord;", cand)
        self.assertIn("        ASM_USE_NV(target_coord);", cand)     # left for the eraser

    def test_refused_when_the_source_lives_on(self):
        self.assertEqual(labels(REVERSE.replace("current_coord -= 0x20;",
                                                "current_coord -= tile_coord;")), [])


class Split(unittest.TestCase):
    def test_store_reading(self):
        import natural as N
        fn = list(N._functions(N._T(SPLIT)))[0]
        st = M._stores(fn)
        self.assertEqual(len(st), 1)
        self.assertTrue(st[0][2].strip().startswith("((S_1 *)object)->unk_60"))

    def test_split_rewrite(self):
        self.assertEqual(labels(SPLIT), ["split:target_x@6-cast", "split:target_x@6"])
        cand = form(SPLIT, "split:target_x@6-cast")
        self.assertIn("    target_x = (s32)func_800A05A4(\n        object, actor, 0x10);", cand)
        self.assertIn("    ((S_1 *)object)->unk_60 = (void *)target_x;", cand)
        self.assertIn("    ASM_KEEP(object);", cand)

    def test_top_level_equals(self):
        self.assertIsNone(M._top_eq("if (a == b) {"))
        self.assertIsNone(M._top_eq("f(a, b);"))
        self.assertEqual(M._top_eq("p->x = g(1);"), 5)


class Hoist(unittest.TestCase):
    def test_block_hoist(self):
        """The coordinates are the block's initialisers: the call moves in, the store follows it."""
        self.assertEqual(labels(HOIST), ["hoist:x@3-cast", "hoist:x@3"])
        cand = form(HOIST, "hoist:x@3-cast")
        self.assertIn("        s32 x = (s32)func_800A05A4(actor, sprite, 0x10);", cand)
        self.assertIn("        s32 y;", cand)
        self.assertIn("        *(void * volatile *)((u8 *)actor + 0x60) = (void *)x;", cand)
        self.assertIn("        x = ((S_1 *)actor)->unk_72.u;", cand)
        self.assertIn("        y = ((S_1 *)actor)->unk_73.u;", cand)
        self.assertEqual(cand.count("func_800A05A4"), 1)

    def test_refused_when_an_initialiser_calls(self):
        self.assertEqual([l for l in labels(HOIST.replace("->unk_73.u;", "->unk_73.u + g(1);"))
                          if l.startswith("hoist")], [])


class Narrow(unittest.TestCase):
    def test_narrow_host(self):
        self.assertEqual(labels(NARROW), ["narrow:raw_height->part_flags"])
        cand = form(NARROW, "narrow")
        self.assertNotIn("raw_height", cand)                          # declaration, pin and uses gone
        self.assertIn("        part_flags = *(volatile u16 *)((u8 *)object_arg + 0x92);", cand)
        self.assertIn("            height_adjust = part_flags - 8;", cand)

    def test_width_must_match(self):
        self.assertEqual(labels(NARROW.replace("u16 part_flags;", "u8 part_flags;")), [])


class Plans(unittest.TestCase):
    def test_required_pins(self):
        from pin_census import sites_of
        cand = form(ITEM, "cast")
        rs = sites_of(cand)
        plans = M._plans(sites_of(ITEM), rs, (16, 19))
        self.assertTrue(all(g for g in plans))                        # nothing was dropped by the rewrite
        self.assertIn([0], plans)                                     # the keep alone


if __name__ == "__main__":
    unittest.main()
