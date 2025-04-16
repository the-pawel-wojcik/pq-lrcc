import pdaggerq

pq = pdaggerq.pq_helper("fermi")

print('')
print('    < 0 | e(-T) H e(T) | 0> :')
print('')

pq.add_st_operator(1.0, ['f'], ['t1','t2'])
pq.add_st_operator(1.0, ['v'], ['t1','t2'])

pq.simplify()
terms = pq.strings()
for term in terms:
    print(term)
    
pq.clear()
