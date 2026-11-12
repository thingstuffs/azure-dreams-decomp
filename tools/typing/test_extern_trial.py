"""Unit coverage for extern_trial.py (selection, reason classes, outcomes, receipt rows, lint blame).

    python3 -m unittest tools/typing/test_extern_trial.py
"""
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace as NS

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import extern_trial as T  # noqa: E402


def site(name, path, kind=''):
    s = NS(name=name, path=path, storage='extern', start=0, end=1)
    if kind:
        s.kind = kind
    return s


def row(name, path, header='include/x.h', kind='', status='header', definition=True, cls='identical', detail=''):
    d = NS(name=name, path='src/x/def.c', container='slus', header=header, status=status) if definition else None
    return NS(site=site(name, path, kind), definition=d, cls=cls, detail=detail, reason='', action='')


class FakePlan:
    def __init__(self, rows):
        self.sites = rows
        self.sites_by_path = {}
        for r in rows:
            self.sites_by_path.setdefault(r.site.path, []).append(r)

    def fn_for_def(self, d):
        return NS(header=d.header, status=d.status, reason='knr_definition' if d.status != 'header' else '')


class CategoryTests(unittest.TestCase):
    def test_brief_classes(self):
        c = T.category
        self.assertEqual(c('tu_hold:hand_written_header_differs:f'), 'type_disagreement')
        self.assertEqual(c('tu_hold:existing_header_return_dropped:ScaleMatrix'), 'type_disagreement')
        self.assertEqual(c('existing_header_other:consumer_conflict:g@src/a.c'), 'type_disagreement')
        self.assertEqual(c('proof_error:abc'), 'type_disagreement')
        self.assertEqual(c('proof_changed:abc'), 'byte_change')
        self.assertEqual(c('header_consumer_changed:f:src/a.c'), 'byte_change')
        self.assertEqual(c('lint_new_warning:Wint-conversion:f'), 'new_warning')
        self.assertEqual(c('retry:lint_compile_failure:x'), 'new_warning')
        self.assertEqual(c('header_not_writable'), 'missing_owner')
        self.assertEqual(c('function_held:knr_definition'), 'missing_owner')
        self.assertEqual(c('no_definition:cross_container'), 'foreign_import')
        self.assertEqual(c('cross_container'), 'foreign_import')
        self.assertEqual(c('data_views_differ'), 'type_disagreement')
        self.assertEqual(c('prototype_floor:f'), 'prototype_floor')
        self.assertEqual(c('tu_hold:annotated_declaration:f'), 'site_form')
        self.assertEqual(c('port_adaptation_anchor:s32 rsin'), 'port_anchor')
        self.assertEqual(c('debt_rise'), 'debt_rise')
        self.assertEqual(c('something_new'), 'other')
        self.assertTrue(set(T.CATEGORIES) >= {'type_disagreement', 'new_warning', 'byte_change', 'missing_owner'})


class SelectTests(unittest.TestCase):
    def plan(self):
        rows = [row('popular', 'src/a/%d.c' % i) for i in range(4)]
        rows += [row('D_80012345', 'src/a/%d.c' % i, kind='data') for i in range(5)]
        rows += [row('func_80012345', 'src/a/%d.c' % i) for i in range(6)]
        rows += [row('floored', 'src/a/%d.c' % i) for i in range(7)]
        rows += [row('ownerless', 'src/a/%d.c' % i, definition=False, cls='cross_container') for i in range(8)]
        rows += [row('held_def', 'src/a/%d.c' % i, status='hold') for i in range(9)]
        rows += [row('second', 'src/a/1.c'), row('second', 'src/a/1.c'), row('third', 'src/b/1.c')]
        rows += [row('header_only', 'include/a.h'), row('static_one', 'src/a/0.c')]
        rows[-1].site.storage = 'static'
        return FakePlan(rows)

    def test_top_ranks_by_files_and_skips_by_rule(self):
        got, skipped = T.select(self.plan(), {'floored'}, top=10, exclude={'third'})
        self.assertEqual(got, ['popular', 'second'])          # second: two sites in one file -> 1 file
        self.assertEqual(skipped['D_80012345'], 'd_address_name')
        self.assertEqual(skipped['func_80012345'], 'address_function_name')
        self.assertEqual(skipped['floored'], 'prototype_floor')
        self.assertEqual(skipped['ownerless'], 'no_owner:cross_container')
        self.assertEqual(skipped['held_def'], 'no_owner:knr_definition')
        self.assertEqual(skipped['third'], 'excluded')
        self.assertNotIn('header_only', got + list(skipped))
        self.assertNotIn('static_one', got + list(skipped))

    def test_owner_reason_class(self):
        self.assertEqual(T.owner_reason_class('function_held:private_header_type:T@include/a.h'), 'private_header_type')
        self.assertEqual(T.owner_reason_class('no_definition:data_views_differ'), 'data_views_differ')
        self.assertEqual(T.owner_reason_class('function_held:unbound'), 'unbound')

    def test_address_functions_opt_in_and_top_limit(self):
        got, _ = T.select(self.plan(), {'floored'}, top=2, address_functions=True)
        self.assertEqual(got, ['func_80012345', 'popular'])

    def test_explicit_names_keep_order_and_never_take_d_names(self):
        got, skipped = T.select(self.plan(), {'floored'}, names=['second', 'D_80012345', 'floored', 'popular',
                                                                  'second', 'missing'])
        self.assertEqual(got, ['second', 'popular'])
        self.assertEqual(skipped, {'D_80012345': 'd_address_name', 'floored': 'prototype_floor',
                                   'missing': 'no_local_declaration'})


class FakeBulk:
    def __init__(self, tus, accepted, holds=(), restored=None):
        self.plan = NS(tus=tus)
        self._acc = accepted
        self.holds = list(holds)
        self.restored = dict(restored or {})

    def accepted(self):
        return {rel: hs for rel, hs in self._acc.items() if rel not in self.restored}

    def restore_tu(self, rel, why):
        if rel in self._acc and rel not in self.restored:
            self.restored[rel] = why


class OutcomeTests(unittest.TestCase):
    def test_kept_held_static_and_override(self):
        r1, r2, r3 = row('f', 'src/a.c'), row('f', 'src/b.c'), row('g', 'src/a.c', header='include/y.h')
        r4 = row('f', 'src/c.c')
        plan = FakePlan([r1, r2, r3, r4])
        sites = T.local_sites(plan)
        static = {('src/c.c', 'f'): 'tu_hold:annotated_declaration:f'}
        tus = {'src/a.c': NS(remove=[r1, r3]), 'src/b.c': NS(remove=[r2])}
        bulk = FakeBulk(tus, {'src/a.c': ['include/x.h', 'include/y.h'], 'src/b.c': ['include/x.h']},
                        holds=[('src/a.c', 'include/y.h', 'proof_changed:rid')])
        outs = T.outcomes(plan, sites, ['f', 'g'], static, [(bulk, {'f', 'g'})])
        self.assertEqual(outs[('src/a.c', 'f')], ('kept', ''))
        self.assertEqual(outs[('src/a.c', 'g')], ('held', 'proof_changed:rid'))
        self.assertEqual(outs[('src/b.c', 'f')], ('kept', ''))
        self.assertEqual(outs[('src/c.c', 'f')], ('held', 'tu_hold:annotated_declaration:f'))
        # a TU restored in the batch and kept by a later single-name retry
        bulk.restored['src/a.c'] = 'proof_error:rid'
        retry = FakeBulk({'src/a.c': NS(remove=[r1])}, {'src/a.c': ['include/x.h']})
        outs = T.outcomes(plan, sites, ['f', 'g'], static, [(bulk, {'f', 'g'}), (retry, {'f'})])
        self.assertEqual(outs[('src/a.c', 'f')], ('kept', ''))
        self.assertEqual(outs[('src/a.c', 'g')], ('held', 'proof_error:rid'))
        rows = {r['name']: r for r in T.receipt_rows(['f', 'g'], {'f': 'function'}, outs)}
        self.assertEqual((rows['f']['status'], rows['f']['kept'], rows['f']['held']), ('partial', 2, 1))
        self.assertEqual(rows['f']['held_by_reason'], {'site_form': 1})
        self.assertEqual(rows['g']['status'], 'held')
        self.assertEqual(rows['g']['held_files']['src/a.c']['reason'], 'type_disagreement')


class ClosureConflictTests(unittest.TestCase):
    def plan(self, other_cls):
        def hsite(name, path, cls, text):
            r = row(name, path, cls=cls)
            r.site.text = text
            return r
        rows = [hsite('shared', 'include/old.h', 'identical', 'extern s32 shared(s32 x);'),
                hsite('shared', 'include/inner.h', other_cls, 'extern void shared(s32 x);'),
                hsite('moved', 'include/new.h', 'identical', 'void moved(void);')]
        plan = FakePlan(rows)
        closure = {'src/a.c': ['src/a.c', 'include/old.h'], 'include/new.h': ['include/new.h', 'include/inner.h'],
                   'include/seen.h': ['include/seen.h', 'include/old.h']}
        plan.corpus = NS(closure=lambda f: closure[f])
        plan.data_by_path = {}
        return plan

    def test_newly_visible_header_declaring_another_type_holds(self):
        why = T.closure_conflict(self.plan('return_dropped'), 'src/a.c', 'include/new.h')
        self.assertEqual(why, 'existing_header_closure:shared@include/inner.h~include/old.h')
        self.assertEqual(T.category(why), 'type_disagreement')

    def test_agreeing_or_already_visible_headers_pass(self):
        self.assertEqual(T.closure_conflict(self.plan('spelling'), 'src/a.c', 'include/new.h'), '')
        self.assertEqual(T.closure_conflict(self.plan('return_dropped'), 'src/a.c', 'include/seen.h'), '')

    def test_the_moved_names_own_local_declaration_does_not_count(self):
        plan = self.plan('spelling')
        local = row('moved', 'src/a.c', cls='return_dropped')
        local.site.text = 'extern s32 moved(void);'
        plan.sites_by_path['src/a.c'] = [local]
        self.assertEqual(T.closure_conflict(plan, 'src/a.c', 'include/new.h', 'moved'), '')
        self.assertTrue(T.closure_conflict(plan, 'src/a.c', 'include/new.h').startswith('existing_header_closure:moved'))


class LintTests(unittest.TestCase):
    def test_increases_and_new_failures(self):
        result = dict(plan=dict(renames={}),
                      base_findings=[dict(file='src/a.c', function='f', warning='W', sites='src/a.c:1:1', count=1,
                                          messages='m')],
                      head_findings=[dict(file='src/a.c', function='f', warning='W', sites='src/a.c:1:1;src/a.c:2:1',
                                          count=2, messages='m'),
                                     dict(file='include/h.h', function='', warning='V', sites='include/h.h:3:1',
                                          count=1, messages='m')],
                      base_failures=[dict(tu='src/old.c', mode='m32', phase='flow')],
                      head_failures=[dict(tu='src/old.c', mode='m32', phase='flow'),
                                     dict(tu='src/b.c', mode='m32', phase='flow', first_error='e')])
        rising, failures = T.lint_increases(result)
        self.assertEqual([(r['file'], r['warning']) for r in rising], [('include/h.h', 'V'), ('src/a.c', 'W')])
        self.assertEqual([f['tu'] for f in failures], ['src/b.c'])

    def test_blame_restores_named_tu_and_header_includers(self):
        bulk = FakeBulk({}, {'src/a.c': ['include/x.h'], 'src/b.c': ['include/y.h'], 'src/c.c': ['include/z.h'],
                             'src/d.c': ['include/x.h']})
        rising = [dict(file='src/a.c', function='f', warning='W'), dict(file='include/inner.h', function='', warning='V')]
        failures = [dict(tu='src/c.c', first_error='boom')]
        closure = {'include/x.h': {'include/x.h'}, 'include/y.h': {'include/y.h', 'include/inner.h'},
                   'include/z.h': {'include/z.h'}}
        got = T.lint_blame(bulk, rising, failures, lambda h: closure[h])
        self.assertEqual(got, ['src/a.c', 'src/b.c', 'src/c.c'])
        self.assertTrue(bulk.restored['src/a.c'].startswith('lint_new_warning:W'))
        self.assertTrue(bulk.restored['src/c.c'].startswith('lint_compile_failure'))
        self.assertNotIn('src/d.c', bulk.restored)
        self.assertEqual(T.lint_blame(bulk, [dict(file='src/zz.c', function='', warning='W')], [],
                                      lambda h: closure[h]), [])


if __name__ == '__main__':
    unittest.main()
