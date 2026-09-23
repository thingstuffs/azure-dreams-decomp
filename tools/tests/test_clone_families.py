"""clone_families: the pair finder and the union-find over the census prefilters (textual only;
the ledger writer, the lane-out glob and the scorer are not exercised)."""
import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "lanes"))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform"))
import clone_families as F  # noqa: E402
import clone_transfer as C  # noqa: E402
from test_clone_transfer import BASE, SIB  # noqa: E402

OTHER = '#include "common.h"\nvoid f(void) { s32 i; for (i = 0; i < 4; i++) g(i); }\n'


class Families(unittest.TestCase):
    def test_pairs_and_union(self):
        third = SIB.replace("8016A86C", "80EE5000").replace("D_8016AB64", "D_80EE5B64")
        docs = {"d/a": C.Doc("d/a", BASE), "d/b": C.Doc("d/b", SIB), "d/c": C.Doc("d/c", third),
                "d/x": C.Doc("d/x", OTHER)}
        pairs = F.clone_pairs(docs, threshold=0.9, jac=0.4, workers=2)
        got = {(a, b) for a, b, _ in pairs}
        self.assertIn(("d/a", "d/b"), got)
        self.assertFalse([p for p in got if "d/x" in p])
        fams = F.union_find(pairs)
        self.assertEqual(sorted(map(tuple, fams)), [("d/a", "d/b", "d/c")])

    def test_union_find_is_transitive(self):
        fams = F.union_find([("a", "b", 1), ("c", "d", 1), ("b", "c", 1), ("e", "f", 1)])
        self.assertEqual(sorted(map(tuple, fams)), [("a", "b", "c", "d"), ("e", "f")])

    def test_reason_phrases(self):
        t = ('    ASM_KEEP(x);   /* UNRESOLVED C shape (pin): removing it changes the address form '
             '(%hi/%lo vs base+offset); the source shape ... */')
        self.assertEqual([m.group(1) for m in F.REASON_RE.finditer(t)],
                         ["changes the address form (%hi/%lo vs base+offset)"])


if __name__ == "__main__":
    unittest.main()
