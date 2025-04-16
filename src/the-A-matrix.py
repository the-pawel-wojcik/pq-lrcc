r"""
Calculate the matrix element of the following matrix:
   $$
   A _{\mu \nu} 
   =
   \mel{0}
   {
       \tau _{\mu} ^\dagger 
       [
           \bar{H _0},
           \tau _{\nu}
       ]
   }
   {0}
   $$
"""
import pdaggerq

pq = pdaggerq.pq_helper("fermi")

print('')
print(r'    < 0 | e(-T) tau _mu ^\dagger [H, t _nu] e(T) | 0> :')
print('')

# Singles part
pq.add_st_operator(1.0, ['e1(j,b)', 'f', 'e1(a,i)'], ['t1', 't2'])
pq.add_st_operator(1.0, ['e1(j,b)', 'v', 'e1(a,i)'], ['t1', 't2'])
pq.add_st_operator(-1.0, ['e1(j,b)', 'e1(a,i)', 'f'], ['t1', 't2'])
pq.add_st_operator(-1.0, ['e1(j,b)', 'e1(a,i)', 'v'], ['t1', 't2'])

pq.simplify()
terms = pq.strings()
for term in terms:
    print(term)
    
pq.clear()
