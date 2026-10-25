"""Unit tests for tools/headers (python3 -m unittest discover -s tools/headers -p 'test_*.py')."""
import os
import sys
import tempfile
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE)]

import cscan      # noqa: E402
import model as M  # noqa: E402
import plan as P   # noqa: E402
import rewrite as R  # noqa: E402

COMMON = '''#ifndef COMMON_H
#define COMMON_H
typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
#endif
'''
SHARED = '''#ifndef SHARED_T_H
#define SHARED_T_H
typedef struct EntityRec { s32 x; } EntityRec;
#endif
'''


def mkroot(files):
    td = tempfile.TemporaryDirectory()
    root = Path(td.name)
    for rel, text in files.items():
        p = root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text)
    return td, root


class ScanTests(unittest.TestCase):
    def test_mask_keeps_offsets(self):
        t = 'int a; /* x; */ "s;" \'c\' // y;\nint b;'
        m = cscan.mask(t)
        self.assertEqual(len(m), len(t))
        self.assertNotIn(';', m[7:30].replace(' ', '')[:0] + m[8:14])

    def test_items(self):
        t = ('#include "common.h"\n'
             'extern s32 f();\n'
             'extern void g(void);\n'
             'extern void (*fp)(s32);\n'
             'extern u8 D_1[];\n'
             'typedef s32 (*Fn)(void *);\n'
             'struct S { s32 a; };\n'
             's32 h(s32 a, u8 *b) { return f(a) + b[0]; }\n'
             'static void k(void) {}\n')
        sc = cscan.scan(t)
        kinds = [(i.kind, [d.name for d in i.decls]) for i in sc.items]
        self.assertIn(('decl', ['f']), kinds)
        self.assertIn(('def', ['h']), kinds)
        f = [i for i in sc.items if i.decls and i.decls[0].name == 'f'][0]
        self.assertIsNone(f.decls[0].params)              # '()' is unprototyped
        g = [i for i in sc.items if i.decls and i.decls[0].name == 'g'][0]
        self.assertEqual(g.decls[0].params, [['void']])
        fp = [i for i in sc.items if i.decls and i.decls[0].name == 'fp'][0]
        self.assertFalse(fp.decls[0].is_function)         # function pointer variable = data
        td = [i for i in sc.items if 'typedef' in i.storage][0]
        self.assertEqual(td.spec, ['s32'])                # 'T (*name)(...)' keeps T as the type
        self.assertEqual(td.decls[0].name, 'Fn')
        k = [i for i in sc.items if i.kind == 'def' and i.decls[0].name == 'k'][0]
        self.assertIn('static', k.storage)

    def test_conditional_depth(self):
        sc = cscan.scan('#ifdef X\nextern void a(void);\n#endif\nextern void b(void);\n')
        d = {i.decls[0].name: i.cond_depth for i in sc.items}
        self.assertEqual(d, {'a': 1, 'b': 0})

    def test_tagged_return_definition_does_not_consume_following_declaration(self):
        text = ('struct Item { int x; };\n'
                'struct Item *lookup(struct Item *p) { return p; }\n'
                'void next();\n')
        scan = cscan.scan(text)
        functions = [item for item in scan.items if item.kind == 'def']
        self.assertEqual([item.decls[0].name for item in functions], ['lookup'])
        self.assertEqual(functions[0].spec, ['struct', 'Item'])
        self.assertEqual(functions[0].decls[0].ptr, 1)
        self.assertIn(('decl', ['next']), [(item.kind, [d.name for d in item.decls]) for item in scan.items])

    def test_tagged_record_with_attribute_and_initializer_is_not_a_function(self):
        text = ('struct Item __attribute__((aligned(4))) { int x; };\n'
                'struct Item item = { 0 };\nvoid next();\n')
        scan = cscan.scan(text)
        self.assertFalse(any(item.kind == 'def' for item in scan.items))
        self.assertIn('next', [d.name for item in scan.items for d in item.decls])

    def test_knr_definition_keeps_following_functions_separate(self):
        text = ('int first(value)\nshort value;\n{ return value; }\n'
                'int second(int a, int b) { return a+b; }\nvoid next();\n')
        scan = cscan.scan(text)
        definitions = [item for item in scan.items if item.kind == 'def']
        self.assertEqual([item.decls[0].name for item in definitions], ['first', 'second'])
        self.assertEqual(definitions[0].decls[0].params, [['value']])
        self.assertIn('next', [d.name for item in scan.items for d in item.decls])


class ClassifyTests(unittest.TestCase):
    def setUp(self):
        self.td, self.root = mkroot({
            'include/common.h': COMMON, 'include/shared/t.h': SHARED,
            'src/engine/a/def.c': '#include "common.h"\n#include "shared/t.h"\n'
                                  'void wide(s32 a, void *p) {}\n'
                                  'void narrow(s16 a) {}\n'
                                  's16 rets(void) { return 0; }\n'
                                  'void typed(EntityRec *e) {}\n',
            'src/engine/b/use.c': '#include "common.h"\n'
                                  'extern void wide();\n'
                                  'extern void narrow();\n'
                                  'extern s32 rets(void);\n'
                                  'extern void typed(void *);\n'
                                  'extern void wide2(int, void *);\n'
                                  'extern void narrow(s32, s32);\n',
        })
        self.corpus = M.Corpus(self.root)
        self.ti = M.TypeIndex(self.corpus)
        M._TINDEX[0] = self.ti
        self.defs, self.sites, _ = M.collect(self.corpus, self.ti)

    def tearDown(self):
        self.td.cleanup()

    def cls(self, name, i=0):
        s = [x for x in self.sites if x.name == name and x.path.endswith('use.c')][i]
        d, _ = M.bind(s.path, s.name, self.defs)
        return M.classify(s, d, self.ti)[0]

    def test_classes(self):
        self.assertEqual(self.cls('wide'), 'unprototyped')
        self.assertEqual(self.cls('narrow'), 'unprototyped_hazard')
        self.assertEqual(self.cls('narrow', 1), 'arity')
        self.assertEqual(self.cls('rets'), 'return_width')
        self.assertEqual(self.cls('typed'), 'void_ptr')
        self.assertEqual(M.risk('void_ptr'), 'safe')
        self.assertEqual(M.risk('param_width'), 'hazard')
        self.assertEqual(M.risk('arity'), 'never')

    def test_unbound(self):
        s = [x for x in self.sites if x.name == 'wide2'][0]
        self.assertEqual(M.bind(s.path, s.name, self.defs), (None, 'no_c_definition'))

    def test_unnamed_typedef_parameter_is_a_type(self):
        self.assertEqual(M.param_parts(['s32'])[:3], (('s32',), 0, ''))
        site=M.Site('wide','src/engine/b/use.c',1,0,1,'extern',('void',),0,
                    [['s32'],['void','*']],'',1,False,0)
        self.assertEqual(M.classify(site,self.defs['wide'][0],self.ti)[0],'identical')

    def test_containers(self):
        self.assertEqual(M.container_of('src/engine/x.c'), 'slus')
        self.assertEqual(M.container_of('src/frontend/card/x.c'), 'main')
        self.assertEqual(M.container_of('src/dungeon/x.c'), 'dungeon')


class PlanTests(unittest.TestCase):
    FILES = {
        'include/common.h': COMMON, 'include/shared/t.h': SHARED,
        'src/engine/a/one.c': '#include "common.h"\n#include "shared/t.h"\n\n'
                              'typedef struct Local { s32 v; } Local;\n'
                              'typedef struct { s32 v; } Anon;\n\n'
                              '/* Adds. */\ns32 add(s32 a, s32 b) { return a + b; }\n'
                              'void touch(EntityRec *e) { e->x = 0; }\n'
                              'void loc(Local *l) { l->v = 1; }\n'
                              'void anon(Anon *a) { a->v = 1; }\n',
        'src/dungeon/b/two.c': '#include "common.h"\n\n'
                               'extern s32 add(s32, s32);\n'
                               'extern void touch(void *);\n'
                               'extern void loc();\n'
                               'extern void anon(void *);\n'
                               'extern u8 D_8000[];\n\n'
                               'void caller(void) { touch(0); loc(0); anon(0); D_8000[0] = add(1, 2); }\n',
        'src/dungeon/b/three.c': '#include "common.h"\n\n'
                                 'extern s32 add(s32);\n\n'
                                 'void caller3(void) { add(1); }\n',
    }

    def setUp(self):
        self.td, self.root = mkroot(self.FILES)

    def tearDown(self):
        self.td.cleanup()

    def test_layout_and_holds(self):
        pl = P.build(self.root, scope=['src'])
        self.assertEqual(P.header_for('src/engine/a/one.c'), 'include/engine/a.h')
        self.assertEqual(P.header_for('src/town/x.c'), 'include/town.h')
        f = pl.functions
        self.assertEqual(f['add'].status, 'header')
        self.assertEqual(f['touch'].type_headers, ('include/shared/t.h',))
        self.assertEqual(f['loc'].proto, 'void loc(struct Local *l)')     # tagged local type -> struct tag
        self.assertEqual(f['anon'].status, 'hold')
        self.assertTrue(f['anon'].reason.startswith('local_type_anonymous'))
        two = pl.tus['src/dungeon/b/two.c']
        self.assertEqual(two.add, ['include/dungeon/b.h', 'include/engine/a.h'])   # own header + callee's
        self.assertEqual(sorted(r.site.name for r in two.remove), ['add', 'loc', 'touch'])
        three = pl.tus['src/dungeon/b/three.c']
        self.assertIn('include/engine/a.h', three.holds)               # arity conflict keeps its local
        self.assertTrue(three.holds['include/engine/a.h'].startswith('site_arity'))

    def test_header_text_and_edit(self):
        pl = P.build(self.root, scope=['src'])
        h = R.header_text(pl, 'include/engine/a.h')
        self.assertIn('#include "shared/t.h"', h)
        self.assertIn('struct Local;', h)
        self.assertIn('s32 add(s32 a, s32 b);', h)
        self.assertNotIn('anon', h)
        self.assertTrue(h.startswith('#ifndef ENGINE_A_H\n#define ENGINE_A_H\n'))
        tp = pl.tus['src/dungeon/b/two.c']
        e = R.tu_edit(tp, lambda r: pl.fn_for_def(r.definition).header)
        new = R.edit_tu(pl.corpus.text(tp.path), e)
        self.assertEqual(new, '#include "common.h"\n#include "dungeon/b.h"\n#include "engine/a.h"\n\n'
                              'extern void anon(void *);\n'
                              'extern u8 D_8000[];\n\n'
                              'void caller(void) { touch(0); loc(0); anon(0); D_8000[0] = add(1, 2); }\n')

    def test_rerun_is_idempotent(self):
        pl = P.build(self.root, scope=['src'])
        hof = lambda r: pl.fn_for_def(r.definition).header  # noqa: E731
        for rel, tp in pl.tus.items():
            if tp.add:
                p = self.root / rel
                p.write_text(R.edit_tu(p.read_text(), R.tu_edit(tp, hof)))
        for h in pl.headers:
            (self.root / h).parent.mkdir(parents=True, exist_ok=True)
            (self.root / h).write_text(R.header_text(pl, h))
        before = {rel: (self.root / rel).read_text() for rel in pl.tus}
        pl2 = P.build(self.root, scope=['src'])
        hof2 = lambda r: pl2.fn_for_def(r.definition).header  # noqa: E731
        for rel, tp in pl2.tus.items():
            new = R.edit_tu(before[rel], R.tu_edit(tp, hof2))
            self.assertEqual(new, before[rel], rel)
        for h in pl2.headers:
            self.assertEqual(R.header_text(pl2, h), (self.root / h).read_text())

    def test_moved_definition_repoints_include(self):
        pl = P.build(self.root, scope=['src'])
        hof = lambda r: pl.fn_for_def(r.definition).header  # noqa: E731
        for rel, tp in pl.tus.items():
            p = self.root / rel
            p.write_text(R.edit_tu(p.read_text(), R.tu_edit(tp, hof)))
        for h in pl.headers:
            (self.root / h).parent.mkdir(parents=True, exist_ok=True)
            (self.root / h).write_text(R.header_text(pl, h))
        # a newer HEAD moves one.c into engine/c/ (a merge/move by another lane)
        (self.root / 'src/engine/c').mkdir()
        os.rename(self.root / 'src/engine/a/one.c', self.root / 'src/engine/c/one.c')
        pl2 = P.build(self.root, scope=['src'])
        two = pl2.tus['src/dungeon/b/two.c']
        self.assertIn('include/engine/c.h', two.add)
        self.assertEqual(two.stale, ['include/engine/a.h'])
        new = R.edit_tu((self.root / two.path).read_text(),
                        R.tu_edit(two, lambda r: pl2.fn_for_def(r.definition).header))
        self.assertIn('#include "engine/c.h"', new)
        self.assertNotIn('engine/a.h', new)


class RewriteTests(unittest.TestCase):
    def test_line_span_and_collapse(self):
        text = '#include "common.h"\n\nextern void a(void);\nextern void b(void); /* extern */\n\nint x;\n'
        sc = cscan.scan(text)
        items = [i for i in sc.items if i.decls and i.decls[0].name in ('a', 'b')]
        edit = {'add': ['include/z.h'], 'remove': [('include/z.h', i.start, i.end) for i in items]}
        self.assertEqual(R.edit_tu(text, edit), '#include "common.h"\n#include "z.h"\n\nint x;\n')

    def test_keeps_annotated(self):
        text = 'extern void a(void); /* retail reads no args */\n'
        sc = cscan.scan(text)
        s = M.Site('a', 'x.c', 1, sc.items[0].start, sc.items[0].end, 'extern', ('void',), 0, [], text, 1, False, 0)
        self.assertTrue(P._annotated(sc, s))


if __name__ == '__main__':
    unittest.main()
