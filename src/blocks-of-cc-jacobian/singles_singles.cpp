
/////////////////// PQ GRAPH ///////////////////

Options:
--------
    print_level: 0  // verbosity level:
                    // 0: no printing of optimization steps (default)
                    // 1: print optimization steps without fusion or merging
                    // 2: print optimization steps with fusion and merging
    permute_eri: true  // whether to permute two-electron integrals to common order (default: true)
    no_scalars: false  // whether to skip the scalar terms in the final equations (default: false)
    use_trial_index: false  // whether to store trial vectors as an additional index/dimension for tensors in a sigma-vector build (default: false)
    separate_sigma: false  // whether to separate reusable intermediates for sigma-vector build (default: false)
    opt_level: 6  // optimization level:
                  // 0: no optimization
                  // 1: single-term optimization only (reordering)
                  // 2: reordering and subexpression elimination (substitution)
                  // 3: reordering, substitution, and separation of reusable intermediates (for sigma vectors)
                  // 4: reordering, substitution, and separation; unused intermediates are removed (pruning)
                  // 5: reordering, substitution, separation, pruning, and merging of equivalent terms
                  // 6: reordering, substitution, separation, pruning, merging, and fusion of intermediates (default)
    batched: false  // candidate substitutions are applied in batches rather than one at a time. (default: false)
                   // Generally faster, but may not yield optimal results compared to single substitutions.
    batch_size: 10  // size of the batch for batched substitution (default: 10; -1 for no limit)
    max_temps: -1  // maximum number of intermediates to find (default: -1 for no limit)
    max_depth: -1  // maximum depth for chain of contractions (default: -1 for no limit)
    max_shape: o255v255 // a map of maximum sizes for each line type in an intermediate (default: {o: 255, v: 255}, for no limit.): 
    low_memory: false  // whether to recompute or save all possible permutations of each term in memory (default: false)
                       // if true, permutations are recomputed on the fly. Recommended if memory runs out.
    nthreads: 1  // number of threads to use (default: OMP_NUM_THREADS | available: 24)

Using custom label order: a b i j 
Formatting equations for c++

/////////////////// PQ GRAPH Output ///////////////////

///// Declarations /////

// initialize -> Id["oo"];
// initialize -> Id["vv"];
// initialize -> cc_jacobian;
// initialize -> eri["oovo"];
// initialize -> eri["oovv"];
// initialize -> eri["vovo"];
// initialize -> eri["vovv"];
// initialize -> f["oo"];
// initialize -> f["ov"];
// initialize -> f["vv"];
// initialize -> perm_tmps;
// initialize -> t1;
// initialize -> t2;
// initialize -> tmps;

/////////////////// Evaluate Equations ///////////////////

    
    // cc_jacobian  = +1.00 <i,b||a,j> 
    cc_jacobian("a,b,i,j")  = -1.00 * eri["vovo"]("b,i,a,j");
    
    // cc_jacobian += +1.00 d(j,i) f(b,a) 
    // flops: o2v2 += o2v2
    //  mems: o2v2 += o2v2
    cc_jacobian("a,b,i,j") += Id["oo"]("j,i") * f["vv"]("b,a");
    
    // cc_jacobian += -1.00 d(b,a) f(i,j) 
    // flops: o2v2 += o2v2
    //  mems: o2v2 += o2v2
    cc_jacobian("a,b,i,j") -= Id["vv"]("b,a") * f["oo"]("i,j");
    
    // cc_jacobian += +1.00 f(i,a) t1(b,j) 
    // flops: o2v2 += o2v2
    //  mems: o2v2 += o2v2
    cc_jacobian("a,b,i,j") += f["ov"]("i,a") * t1("b,j");
    
    // cc_jacobian += -1.00 d(b,a) <k,i||c,j> t1(c,k) 
    //             += -1.00 d(b,a) f(i,c) t1(c,j) 
    // flops: o2v2 += o3v1 o2v1 o2v0 o2v2
    //  mems: o2v2 += o2v0 o2v0 o2v0 o2v2
    cc_jacobian("a,b,i,j") += (eri["oovo"]("i,k,c,j") * t1("c,k") + -1.00 * f["ov"]("i,c") * t1("c,j")) * Id["vv"]("b,a");
    
    // cc_jacobian += +1.00 <k,i||a,j> t1(b,k) 
    // flops: o2v2 += o3v2
    //  mems: o2v2 += o2v2
    cc_jacobian("a,b,i,j") -= eri["oovo"]("i,k,a,j") * t1("b,k");
    
    // cc_jacobian += +1.00 <i,b||a,c> t1(c,j) 
    // flops: o2v2 += o2v3
    //  mems: o2v2 += o2v2
    cc_jacobian("a,b,i,j") -= eri["vovv"]("b,i,a,c") * t1("c,j");
    
    // cc_jacobian += +1.00 <k,i||a,c> t2(c,b,j,k) 
    // flops: o2v2 += o3v3
    //  mems: o2v2 += o2v2
    cc_jacobian("a,b,i,j") -= eri["oovv"]("i,k,a,c") * t2("c,b,j,k");
    
    // cc_jacobian += -1.00 d(j,i) f(k,a) t1(b,k) 
    // flops: o2v2 += o1v2 o2v2
    //  mems: o2v2 += o0v2 o2v2
    cc_jacobian("a,b,i,j") -= f["ov"]("k,a") * t1("b,k") * Id["oo"]("j,i");
    
    // cc_jacobian += -1.00 <k,i||a,c> t1(b,j) t1(c,k) 
    // flops: o2v2 += o2v2 o2v2
    //  mems: o2v2 += o1v1 o2v2
    cc_jacobian("a,b,i,j") += eri["oovv"]("i,k,a,c") * t1("c,k") * t1("b,j");
    
    // cc_jacobian += -1.00 d(j,i) <k,b||a,c> t1(c,k) 
    // flops: o2v2 += o1v3 o2v2
    //  mems: o2v2 += o0v2 o2v2
    cc_jacobian("a,b,i,j") += eri["vovv"]("b,k,a,c") * t1("c,k") * Id["oo"]("j,i");
    
    // cc_jacobian += +0.50 d(b,a) <k,i||c,d> t2(c,d,j,k) 
    // flops: o2v2 += o3v2 o2v2
    //  mems: o2v2 += o2v0 o2v2
    cc_jacobian("a,b,i,j") -= 0.50 * eri["oovv"]("i,k,c,d") * t2("c,d,j,k") * Id["vv"]("b,a");
    
    // cc_jacobian += +0.50 d(j,i) <l,k||a,c> t2(c,b,l,k) 
    // flops: o2v2 += o2v3 o2v2
    //  mems: o2v2 += o0v2 o2v2
    cc_jacobian("a,b,i,j") -= 0.50 * eri["oovv"]("k,l,a,c") * t2("c,b,l,k") * Id["oo"]("j,i");
    
    // cc_jacobian += -1.00 d(j,i) <l,k||a,c> t1(b,l) t1(c,k) 
    // flops: o2v2 += o2v2 o1v2 o2v2
    //  mems: o2v2 += o1v1 o0v2 o2v2
    cc_jacobian("a,b,i,j") += eri["oovv"]("k,l,a,c") * t1("c,k") * t1("b,l") * Id["oo"]("j,i");
    
    // flops: o3v1  = o3v2
    //  mems: o3v1  = o3v1
    tmps_["1_oovo"]("i,j,a,k")  = eri["oovv"]("i,j,a,b") * t1("b,k");
    
    // cc_jacobian += +1.00 <k,i||a,c> t1(b,k) t1(c,j) 
    // flops: o2v2 += o3v2
    //  mems: o2v2 += o2v2
    cc_jacobian("a,b,i,j") -= t1("b,k") * tmps_["1_oovo"]("i,k,a,j");
    
    // cc_jacobian += -1.00 d(b,a) <k,i||c,d> t1(c,k) t1(d,j) 
    // flops: o2v2 += o3v1 o2v2
    //  mems: o2v2 += o2v0 o2v2
    cc_jacobian("a,b,i,j") += t1("c,k") * tmps_["1_oovo"]("i,k,c,j") * Id["vv"]("b,a");
    tmps_["1_oovo"].~TArrayD();

/////////////////////////////////////////////////////////


/////////////////// PQ GRAPH Analysis ///////////////////

Net time: 36.798 ms

Total Number of Terms: 17
Total Contractions: (last) 45 -> (new) 44

Total FLOP scaling: 
------------------
 Scaling :   I   |   R   |   F   ||  F-I  |  F-R 
-------- : ----- | ----- | ----- || ----- |  ----
    o3v4 :     1 |     0 |     0 ||    -1 |     0 
    o4v3 :     2 |     0 |     0 ||    -2 |     0 
-------- : ----- | ----- | ----- || ----- |  ----
    o2v4 :     3 |     0 |     0 ||    -3 |     0 
    o3v3 :     8 |     1 |     1 ||    -7 |     0 
    o4v2 :     2 |     0 |     0 ||    -2 |     0 
-------- : ----- | ----- | ----- || ----- |  ----
    o2v3 :     5 |     2 |     2 ||    -3 |     0 
    o3v2 :     2 |     4 |     4 ||     2 |     0 
-------- : ----- | ----- | ----- || ----- |  ----
    o1v3 :     1 |     1 |     1 ||     0 |     0 
    o2v2 :    20 |    32 |    29 ||     9 |    -3 
    o3v1 :     1 |     1 |     3 ||     2 |     2 
-------- : ----- | ----- | ----- || ----- |  ----
    o1v2 :     0 |     2 |     2 ||     2 |     0 
    o2v1 :     0 |     2 |     1 ||     1 |    -1 
-------- : ----- | ----- | ----- || ----- |  ----
    o2v0 :     0 |     0 |     1 ||     1 |     1 
-------- : ----- | ----- | ----- || ----- |  ----
   Total :    45 |    45 |    44 ||    -1 |    -1 

Total MEM scaling: 
------------------
 Scaling :   I   |   R   |   F   ||  F-I  |  F-R 
-------- : ----- | ----- | ----- || ----- |  ----
    o2v4 :     2 |     0 |     0 ||    -2 |     0 
    o3v3 :     4 |     0 |     0 ||    -4 |     0 
    o4v2 :     2 |     0 |     0 ||    -2 |     0 
-------- : ----- | ----- | ----- || ----- |  ----
    o1v3 :     3 |     0 |     0 ||    -3 |     0 
    o2v2 :    33 |    33 |    31 ||    -2 |    -2 
    o3v1 :     1 |     1 |     2 ||     1 |     1 
-------- : ----- | ----- | ----- || ----- |  ----
    o0v2 :     0 |     4 |     4 ||     4 |     0 
    o1v1 :     0 |     3 |     2 ||     2 |    -1 
    o2v0 :     0 |     4 |     5 ||     5 |     1 
-------- : ----- | ----- | ----- || ----- |  ----
   Total :    45 |    45 |    44 ||    -1 |    -1 


/////////////////////////////////////////////////////////

