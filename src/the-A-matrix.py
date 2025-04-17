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
import argparse
from collections.abc import Callable

import pdaggerq


def print_banner():
    print('')
    print(r'    < 0 | e(-T) tau _mu ^\dagger [H, t _nu] e(T) | 0> :')
    print('')


def verbose_print(terms: list[str]):
    for term in terms:
        print(term)


def numpy_print(terms: list[str]):
    from pdaggerq.parser import contracted_strings_to_tensor_terms
    tensor_terms = contracted_strings_to_tensor_terms(terms)
    for my_term in tensor_terms:
        einsum_terms = my_term.einsum_string(
            output_variables=('a', 'i'),
            update_val='r1_aa',
        )
        print(f"{einsum_terms}")


def build_singles_singles() -> list[str]:
    pq = pdaggerq.pq_helper("fermi")
    pq.add_st_operator(1.0, ['e1(j,b)', 'f', 'e1(a,i)'], ['t1', 't2'])
    pq.add_st_operator(1.0, ['e1(j,b)', 'v', 'e1(a,i)'], ['t1', 't2'])
    pq.add_st_operator(-1.0, ['e1(j,b)', 'e1(a,i)', 'f'], ['t1', 't2'])
    pq.add_st_operator(-1.0, ['e1(j,b)', 'e1(a,i)', 'v'], ['t1', 't2'])
    pq.simplify()
    terms = pq.strings()
    return terms


def build_doubles_singles() -> list[str]:
    pq = pdaggerq.pq_helper("fermi")
    pq.add_st_operator(1.0, ['e2(j,k,b,c)', 'f', 'e1(a,i)'], ['t1', 't2'])
    pq.add_st_operator(1.0, ['e2(j,k,b,c)', 'v', 'e1(a,i)'], ['t1', 't2'])
    pq.add_st_operator(-1.0, ['e2(j,k,b,c)', 'e1(a,i)', 'f'], ['t1', 't2'])
    pq.add_st_operator(-1.0, ['e2(j,k,b,c)', 'e1(a,i)', 'v'], ['t1', 't2'])
    return pq


def build_singles_doubles() -> list[str]:
    pq = pdaggerq.pq_helper("fermi")
    pq.add_st_operator(1.0, ['e1(j,b)', 'f', 'e2(a,c,i,k)'], ['t1', 't2'])
    pq.add_st_operator(1.0, ['e1(j,b)', 'v', 'e2(a,c,i,k)'], ['t1', 't2'])
    pq.add_st_operator(-1.0, ['e1(j,b)', 'e2(a,c,i,k)', 'f'], ['t1', 't2'])
    pq.add_st_operator(-1.0, ['e1(j,b)', 'e2(a,c,i,k)', 'v'], ['t1', 't2'])
    pq.simplify()
    terms = pq.strings()
    return terms


def build_doubles_doubles() -> list[str]:
    pq = pdaggerq.pq_helper("fermi")
    pq.add_st_operator(1.0, ['e2(k,l,c,d)', 'f', 'e2(a,b,i,j)'], ['t1', 't2'])
    pq.add_st_operator(1.0, ['e2(k,l,c,d)', 'v', 'e2(a,b,i,j)'], ['t1', 't2'])
    pq.add_st_operator(-1.0, ['e2(k,l,c,d)', 'e2(a,b,i,j)', 'f'], ['t1', 't2'])
    pq.add_st_operator(-1.0, ['e2(k,l,c,d)', 'e2(a,b,i,j)', 'v'], ['t1', 't2'])
    pq.simplify()
    terms = pq.strings()
    return terms


def cli() -> argparse.Namespace: 
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--block',
        choices=['ss', 'sd', 'ds', 'dd',],
        default='ss',
        help='Chose the block of the matrix: s stands for singles and d for'
        ' doubles.',
    )
    print_options = parser.add_mutually_exclusive_group()
    print_options.add_argument('--np', default=False, action='store_true')
    print_options.add_argument('--verbose', default=False, action='store_true')
    args = parser.parse_args()
    return args


def main():
    args = cli()
    print_np = args.np
    print_np = True
    
    if args.verbose is True:
        print_banner()

    build_functions: dict[str, Callable[[], list[str]]] = {
        'ss': build_singles_singles,
        'ds': build_doubles_singles,
        'sd': build_singles_doubles,
        'dd': build_doubles_doubles,
    }
    builder = build_functions[args.block]
    strings = builder()

    if args.verbose:
        verbose_print(strings)

    elif print_np is True:
        numpy_print(strings)


if __name__ == "__main__":
    main()
