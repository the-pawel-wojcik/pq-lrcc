import pdaggerq

pq = pdaggerq.pq_helper("fermi")

print('')
print('    < 0 | e(-T) H e(T) | 0> :')
print('')

# one-electron part: 

# f
pq.add_operator_product(1.0,['f'])

# [f, T1]
pq.add_commutator(1.0,['f'],['t1'])

# [f, T2]
pq.add_commutator(1.0,['f'],['t2'])

# two-electron part: 

# v
pq.add_operator_product(1.0,['v'])

# [v, T1]
pq.add_commutator(1.0,['v'],['t1'])

# [v, T2]
pq.add_commutator(1.0,['v'],['t2(a,b,i,j)'])

# [[v, T1], T1]]
pq.add_double_commutator(0.5, ['v'],['t1'],['t1'])

pq.simplify()
terms = pq.strings()
for term in terms:
    print(term)
pq.clear()
