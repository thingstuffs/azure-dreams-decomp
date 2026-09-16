#!/usr/bin/env python3
"""Unit tests for tools/xform/t29_addrsym.py - the round-34 openings, their refusals, the `Detail`
refusal counter and menu identity with every switch off.

No compiles: what is offered, what is refused and what the rewritten text looks like are all
decidable on synthetic texts.  Only vf accepts a candidate; these tests never claim one is exact.

    python3 -B tools/tests/test_t29_addrsym.py
"""
import hashlib
import os
import re
import sys
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of                           # noqa: E402
from xform import t29_addrsym as T29                      # noqa: E402

HEAD = """#include "common.h"

extern u8 D_800D0000[];
extern u8 D_800D0AFC[];
extern u8 D_80083160[];
extern u8 D_8040B1D0[];
extern u8 D_1F800000[];
extern s32 D_80130000;
extern void *D_800814A8;

"""


def wrap(body, decls=""):
    return HEAD + "void func_80010000(void)\n{\n" + decls + body + "}\n"


class Switches:
    """Set the openings for the duration of a `with` block and restore the environment after."""

    def __init__(self, **kw):
        self.kw = kw
        self.old = {}

    def __enter__(self):
        for k in T29.OPENINGS:
            self.old[k] = os.environ.get(k)
            os.environ[k] = "1" if self.kw.get(k) else "0"      # every switch explicit, never the default
        return self

    def __exit__(self, *a):
        for k, v in self.old.items():
            if v is None:
                os.environ.pop(k, None)
            else:
                os.environ[k] = v


def labels(text):
    cands, _ = T29.candidates(text)
    return [lab for lab, _ in cands]


def skipped(text):
    _, sk = T29.candidates(text)
    return sk


def detail(text):
    d = T29.Detail()
    T29.candidates(text, d)
    return d


# --------------------------------------------------------------------------- the Detail counter

class TestDetail(unittest.TestCase):
    def test_detail_records_the_variable_behind_each_refusal(self):
        t = wrap("""    page = (u8 *)0x800D0000;
    ASM_KEEP(page);
    page = other;
    use(page);
""", "    u8 *page;\n    u8 *other;\n")
        d = detail(t)
        self.assertTrue(d.detail, "the chain recorded nothing")
        for key, var in d.detail:
            self.assertIsInstance(key, str)
        self.assertIn("page", [v for _, v in d.detail])

    def test_detail_is_invisible_to_callers(self):
        t = wrap("""    page = (u8 *)0x800D0000;
    ASM_KEEP(page);
    x = *(s32 *)(page + 0x10);
""", "    u8 *page;\n    s32 x;\n")
        self.assertEqual(T29.candidates(t), T29.candidates(t, T29.Detail()))
        self.assertEqual(T29.addrvars(t), T29.addrvars(t, T29.Detail()))

    def test_a_load_from_a_symbol_is_not_a_symbol_address_definition(self):
        """`v = D_X[3];` reads memory; counting it as an address definition inflated the class by
        153 of its first 412 records."""
        t = wrap("""    value = D_80083160[3];
    ASM_KEEP(value);
    use(value);
""", "    s32 value;\n")
        keys = {k for k, _ in detail(t).detail}
        self.assertNotIn("symbol-page-def-only", keys)

    def test_an_ordinary_constant_is_not_a_non_ram_page(self):
        t = wrap("""    mask = 0xFFFC0000;
    ASM_KEEP(mask);
    use(mask);
""", "    u32 mask;\n")
        keys = {k for k, _ in detail(t).detail}
        self.assertNotIn("non-ram-page-literal", keys)


# --------------------------------------------------------------------------- T29_SYMDEF

SYMDEF_STMT = wrap("""    base = D_80083160;
    ASM_KEEP(base);
    use(*(s32 *)(base + 0x10));
""", "    u8 *base;\n")

SYMDEF_DECL = wrap("""    ASM_KEEP(base);
    use(*(s32 *)(base + 0x10));
""", "    u8 *base = (u8 *)&D_8040B1D0;\n")


class TestSymdef(unittest.TestCase):
    def test_refused_with_the_switch_off(self):
        with Switches():
            self.assertEqual(T29.addrvars(SYMDEF_STMT), [])
            self.assertEqual(labels(SYMDEF_STMT), [])
            self.assertIn("symbol-page-def-only", {k for k, _ in detail(SYMDEF_STMT).detail})

    def test_statement_form_offered_with_the_switch_on(self):
        with Switches(T29_SYMDEF=True):
            self.assertEqual(T29.addrvars(SYMDEF_STMT), ["base"])
            self.assertEqual(labels(SYMDEF_STMT), ["addrsym:base"])
            new, info = T29.rewrite_var(SYMDEF_STMT, "base")
            self.assertIsNotNone(new, info)
            self.assertNotIn("base", re.sub(r"D_[0-9A-F]{8}", "", new))
            self.assertEqual(len(sites_of(new)), 0)
            self.assertIn("D_80083170", new)              # 0x80083160 + 0x10, the same address

    def test_declaration_initialiser_form(self):
        with Switches():
            self.assertIn("symbol-decl-init-only", {k for k, _ in detail(SYMDEF_DECL).detail})
        with Switches(T29_SYMDEF=True):
            new, info = T29.rewrite_var(SYMDEF_DECL, "base")
            self.assertIsNotNone(new, info)
            self.assertEqual(len(sites_of(new)), 0)
            self.assertIn("D_8040B1E0", new)              # 0x8040B1D0 + 0x10

    def test_a_bare_scalar_global_is_a_load_not_an_address(self):
        """Review D2: `v = D_X;` is the symbol's ADDRESS only where D_X is an ARRAY (it decays).
        With `extern s32 D_80130000;` the same text LOADS the global's value, and rewriting the
        variable's uses as `D_80130004` stores an address where the source stored a value."""
        self.assertIsNone(T29.sym_value(HEAD, "D_80130000"))
        self.assertIsNone(T29.sym_value(HEAD, "(u8 *)D_80130000"))
        self.assertIsNone(T29.sym_value(HEAD, "D_80130000 + 4"))
        self.assertIsNone(T29.sym_value(HEAD, "D_800814A8"))          # `extern void *`: a pointer load
        self.assertIsNone(T29.sym_value(HEAD, "D_80140000"))          # declared nowhere: undecidable
        self.assertEqual(T29.sym_value(HEAD, "&D_80130000"), 0x80130000)     # `&` is always the address
        self.assertEqual(T29.sym_value(HEAD, "D_80083160"), 0x80083160)      # `extern u8 ...[]`: decays
        self.assertEqual(T29.sym_value(HEAD, "(u8 *)&D_80130000 + 0x10"), 0x80130010)

    def test_a_scalar_load_is_not_counted_in_the_refusal_table(self):
        t = wrap("""    page = D_80130000;
    ASM_KEEP(page);
    page += 0xB0;
    use(page);
""", "    s32 page;\n")
        keys = {k for k, _ in detail(t).detail}
        self.assertNotIn("symbol-page-def-only", keys)
        with Switches(T29_SYMDEF=True):
            self.assertEqual(T29.addrvars(t), [])
            self.assertEqual(labels(t), [])

    def test_a_pointer_global_load_is_not_an_address_definition(self):
        t = wrap("""    node = D_800814A8;
    ASM_KEEP(node);
    use(node);
""", "    void *node;\n")
        with Switches(T29_SYMDEF=True):
            self.assertEqual(T29.addrvars(t), [])

    def test_a_declaration_that_loads_from_a_symbol_still_refuses_decl_init(self):
        t = wrap("""    ASM_KEEP(v);
    use(v);
""", "    s32 v = D_80083160[2];\n")
        with Switches(T29_SYMDEF=True):
            new, info = T29.rewrite_var(t, "v")
            self.assertIsNone(new)
            self.assertEqual(info, "decl-init")


# --------------------------------------------------------------------------- T29_NONRAM

NONRAM = wrap("""    sp = (u8 *)0x1F800000;
    ASM_KEEP(sp);
    use(*(s32 *)(sp + 0x20));
""", "    u8 *sp;\n")


class TestNonram(unittest.TestCase):
    def test_refused_with_the_switch_off(self):
        with Switches():
            self.assertEqual(T29.addrvars(NONRAM), [])
            self.assertIn("non-ram-page-literal", {k for k, _ in detail(NONRAM).detail})

    def test_offered_with_the_switch_on(self):
        with Switches(T29_NONRAM=True):
            self.assertEqual(T29.addrvars(NONRAM), ["sp"])
            new, info = T29.rewrite_var(NONRAM, "sp")
            self.assertIsNotNone(new, info)
            self.assertIn("D_1F800020", new)
            self.assertEqual(len(sites_of(new)), 0)

    def test_the_module_constant_LIT_never_moves(self):
        """tools/xform/t54_pagebase.py reads `A.LIT` by name: its menu must not change."""
        with Switches(T29_NONRAM=True):
            self.assertIsNone(re.search(r"1F8", T29.LIT))
            self.assertEqual(T29._lit(), T29.LIT_NONRAM)
        with Switches():
            self.assertEqual(T29._lit(), T29.LIT)


# --------------------------------------------------------------------------- T29_DEREF_USE

STORE = wrap("""    page = (u8 *)0x800D0000;
    ASM_KEEP(page);
    *(s32 *)(page + 0xAFC) = 16;
""", "    u8 *page;\n")

READ_UNDER_STAR = wrap("""    p = (s32 *)0x800D0000;
    ASM_KEEP(p);
    if (x == *p) {
        x = 1;
    }
""", "    s32 *p;\n    s32 x;\n")


class TestDerefUse(unittest.TestCase):
    def test_store_refused_with_the_switch_off(self):
        with Switches():
            new, info = T29.rewrite_var(STORE, "page")
            self.assertIsNone(new)
            self.assertEqual(info, "operand-context")

    def test_store_rewritten_with_the_switch_on(self):
        with Switches(T29_DEREF_USE=True):
            new, info = T29.rewrite_var(STORE, "page")
            self.assertIsNotNone(new, info)
            self.assertIn("*(s32 *)D_800D0AFC = 16;", new)
            self.assertEqual(len(sites_of(new)), 0)

    def test_read_under_a_star_refused_with_the_switch_off(self):
        with Switches():
            new, info = T29.rewrite_var(READ_UNDER_STAR, "p")
            self.assertIsNone(new)
            self.assertEqual(info, "not-operand")

    def test_read_under_a_star_rewritten_with_the_switch_on(self):
        with Switches(T29_DEREF_USE=True):
            new, info = T29.rewrite_var(READ_UNDER_STAR, "p")
            self.assertIsNotNone(new, info)
            self.assertEqual(len(sites_of(new)), 0)

    def test_a_comparison_is_not_a_store(self):
        """`== ` after a use must never be read as an assignment target."""
        t = wrap("""    page = (u8 *)0x800D0000;
    ASM_KEEP(page);
    if (*(s32 *)(page + 0xAFC) == 16) {
        y = 1;
    }
""", "    u8 *page;\n    s32 y;\n")
        with Switches(T29_DEREF_USE=True):
            new, info = T29.rewrite_var(t, "page")
            self.assertIsNotNone(new, info)
            self.assertIn("==", new)
            self.assertNotIn("D_800D0AFC ==", new.replace("*(s32 *)D_800D0AFC == 16", "OK"))

    def test_a_pointer_declarator_is_never_an_operand(self):
        """`u8 *page` puts the name in a declarator: `star_lead` must say no, or the rewrite would
        edit the declaration itself."""
        masked = "    u8 *page;\n"
        self.assertFalse(T29.star_lead(masked, masked.index("page")))
        masked2 = "    register const u8 *page;\n"
        self.assertFalse(T29.star_lead(masked2, masked2.index("page")))
        masked3 = "    x = *page;\n"
        self.assertTrue(T29.star_lead(masked3, masked3.index("page")))

    def test_a_multiplication_is_not_a_dereference(self):
        """Review D4: `n * page` is a factor, not a `*page`.  The local is an integer page and the
        symbol is an array, so the rewrite would emit `n * D_80110000` - an int times a pointer,
        which cannot build."""
        for m in ("    x = y * page;\n", "    x = f(y) * page;\n", "    x = t[i] * page;\n",
                  "    x = 4 * page;\n"):
            self.assertFalse(T29.star_lead(m, m.index("page")), m)
        for m in ("    return *page;\n", "    x = (y + 1) ? 0 : *page;\n", "    f(*page);\n"):
            self.assertTrue(T29.star_lead(m, m.index("page")), m)

    def test_a_multiplication_use_is_refused(self):
        t = wrap("""    page = (u8 *)0x800D0000;
    ASM_KEEP(page);
    x = n * page;
""", "    u8 *page;\n    s32 x;\n    s32 n;\n")
        for sw in (True, False):
            with Switches(T29_DEREF_USE=sw):
                new, info = T29.rewrite_var(t, "page")
                self.assertIsNone(new, "a multiplication was rewritten (switch %s)" % sw)
                self.assertEqual(info, "not-operand")


# --------------------------------------------------------------------------- menu identity

class TestMenuIdentity(unittest.TestCase):
    """With every switch off the module offers exactly what it offered before round 34: shapes the
    openings do not apply to must be byte-identical either way."""

    ROWS = [
        # an ordinary t29 row: a pinned integer page with a plain offset use
        wrap("""    page = (u8 *)0x800D0000;
    ASM_KEEP(page);
    use(*(s32 *)(page + 0x10));
""", "    u8 *page;\n"),
        # a row with no address variable at all
        wrap("""    ASM_KEEP(x);
    x = y + 1;
""", "    s32 x;\n    s32 y;\n"),
        # a row whose page is modified in a way that does not fold
        wrap("""    page = (u8 *)0x800D0000;
    ASM_KEEP(page);
    page += n;
    use(page);
""", "    u8 *page;\n    s32 n;\n"),
        SYMDEF_STMT, SYMDEF_DECL, NONRAM, STORE, READ_UNDER_STAR,
    ]

    def test_every_switch_off_is_the_baseline(self):
        with Switches():
            base = [(T29.addrvars(t), labels(t), sorted(skipped(t).items())) for t in self.ROWS]
        for sw in T29.OPENINGS:
            with Switches(**{sw: True}):
                now = [(T29.addrvars(t), labels(t), sorted(skipped(t).items())) for t in self.ROWS]
            # the first three rows carry none of the openings' shapes: they must not move
            for i in range(3):
                self.assertEqual(base[i], now[i], "%s moved a row it does not apply to" % sw)

    # three pages, two of them rewritable before round 34 and the third only under T29_DEREF_USE:
    # the JOINT candidate `addrsym:*pa+pb` is rewritten to `*pa+pb+pc` when the third is admitted,
    # so the text HEAD would have tried first disappears unless the baseline menu is appended
    # (review D3).
    JOINT = wrap("""    pa = (u8 *)0x800D0000;
    ASM_KEEP(pa);
    x = *(s32 *)(pa + 0x10);
    pb = (u8 *)0x800D0000;
    ASM_KEEP(pb);
    y = *(s32 *)(pb + 0x20);
    pc = (u8 *)0x800D0000;
    ASM_KEEP(pc);
    *(s32 *)(pc + 0xAFC) = 16;
""", "    u8 *pa;\n    u8 *pb;\n    u8 *pc;\n    s32 x;\n    s32 y;\n")

    # a candidate that is exact and frees NO pin: the pin stands before the page literal, so the
    # rewrite is CONFINED and leaves it.  HEAD offers it; the openings' pin-count filter must not
    # take it away (review D1).
    PINFREE = wrap("""    page = other;
    ASM_KEEP(page);
    use(page);
    page = (u8 *)0x800D0000;
    q = (s32 *)(page + 0x10);
""", "    u8 *page;\n    u8 *other;\n    s32 *q;\n")

    def test_an_opening_never_removes_a_candidate(self):
        """Compared by candidate TEXT, not by label: a joint candidate keeps its label while its
        text changes underneath it."""
        rows = self.ROWS + [self.JOINT, self.PINFREE]
        with Switches():
            base = [{t for _, t in T29.candidates(r)[0]} for r in rows]
        for kw in ({"T29_SYMDEF": True}, {"T29_NONRAM": True}, {"T29_DEREF_USE": True},
                   {"T29_SYMDEF": True, "T29_NONRAM": True, "T29_DEREF_USE": True}):
            with Switches(**kw):
                now = [{t for _, t in T29.candidates(r)[0]} for r in rows]
            for i, (b, n) in enumerate(zip(base, now)):
                self.assertTrue(b <= n, "%s lost a candidate TEXT on row %d" % (sorted(kw), i))

    def test_the_joint_candidate_of_the_baseline_survives(self):
        with Switches():
            base = dict((lab, t) for lab, t in T29.candidates(self.JOINT)[0])
        self.assertIn("addrsym:*pa+pb", base)
        with Switches(T29_DEREF_USE=True):
            now = dict((lab, t) for lab, t in T29.candidates(self.JOINT)[0])
        self.assertIn("addrsym:*pa+pb+pc", now)                     # the wider joint is offered
        self.assertIn(base["addrsym:*pa+pb"], set(now.values()))    # and the narrower one survives

    def test_apply_verified_puts_the_same_texts_to_vf_on_a_row_no_opening_touches(self):
        """Review D1: the identity that matters is the sequence `sweep.py` actually sees, which is
        `apply_verified`'s, not `candidates`'.  A stub vf records what it was offered."""
        row = {"cfg": "2.7.2", "id": "test/func_80010000"}
        def seq(text):
            seen = []
            def vf(t, cfg=None):
                seen.append((cfg, hashlib.sha256(t.encode()).hexdigest()[:16]))
                return {"exact": False}
            out, info = T29.T.apply_verified(text, row, None, vf)
            return seen, out, info
        for text in self.ROWS[:3] + [self.PINFREE]:
            with Switches():
                base = seq(text)
            with Switches(T29_DEREF_USE=True):                      # the shipped default
                now = seq(text)
            self.assertEqual(base, now, "the shipped default moved a row it does not apply to")

    def test_the_baseline_menu_is_not_visible_to_other_threads(self):
        """`lane_eval`, `sweep.py` and the lane's screens run this module on a ThreadPoolExecutor.
        The baseline menu must therefore never switch the openings off through `os.environ`, or one
        row's baseline computation silently disables the openings under every row in flight."""
        import threading
        rows = [self.JOINT] * 8
        with Switches(T29_DEREF_USE=True):
            want = len(T29.candidates(self.JOINT)[0])
            self.assertGreater(want, 1)
            stop = threading.Event()

            def churn():                                   # a second thread taking baselines
                while not stop.is_set():
                    T29._baseline_candidates(self.JOINT)
            th = threading.Thread(target=churn)
            th.start()
            try:
                got = [len(T29.candidates(r)[0]) for r in rows for _ in range(4)]
            finally:
                stop.set()
                th.join()
        self.assertEqual(set(got), {want}, "a concurrent baseline changed another thread's menu")

    def test_the_baseline_helper_restores_the_environment(self):
        with Switches(T29_DEREF_USE=True, T29_SYMDEF=True):
            T29._baseline_candidates(self.PINFREE)
            self.assertTrue(T29._on("T29_DEREF_USE"))
            self.assertTrue(T29._on("T29_SYMDEF"))
            self.assertFalse(T29._on("T29_NONRAM"))


class TestDefaults(unittest.TestCase):
    def test_only_the_opening_that_paid_defaults_on(self):
        self.assertEqual(T29.DEFAULTS, {"T29_SYMDEF": "0", "T29_NONRAM": "0", "T29_DEREF_USE": "1"})
        for k in T29.OPENINGS:
            os.environ.pop(k, None)
        self.assertTrue(T29._on("T29_DEREF_USE"))
        self.assertFalse(T29._on("T29_SYMDEF"))
        self.assertFalse(T29._on("T29_NONRAM"))

    def test_the_environment_still_overrides_the_default(self):
        with Switches(T29_DEREF_USE=False):
            self.assertFalse(T29._on("T29_DEREF_USE"))
            new, info = T29.rewrite_var(STORE, "page")
            self.assertIsNone(new)
            self.assertEqual(info, "operand-context")


if __name__ == "__main__":
    unittest.main(verbosity=2)
