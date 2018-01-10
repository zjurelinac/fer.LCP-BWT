# Code optimizations

## Functions of interest

(percentage only approximate)
- `get_intervals` -> **18%** of time spent in it                                -> probably unoptimizable by much
- `build_lcp` -> **14%** of time spent in it (excluding children)               -> probably unoptimizable by much
- `output_results` -> **2%** of time spent in it                                -> use fastIO if neccessary

- `deque` (from `build_lcp` or `get_intervals`) -> **9%** of time spent in it   -> replace with stack / implement custom bare stack     [In progress]
- `vector` (from `deque`) -> **7%** of time spent in it                         -> -v-

- `saisxx` -> **18%** of time spent in it                                       -> cannot optimize, potentialy replace with divsufsort

- `node_rank` -> **18%** of time spent in it                                    -> improve by switching to 64b bv store [DONE]
- `fast_bitvector.push_back` -> **3%** of time spent in it                      -> think of a better implementation     [DONE]
- `alphabet constructor` -> **2%** of time spent in it                          -> use fixed arrays (ASCII <-> INT)     [DONE]

## Various simple things
- use custom structs for search states (instead of pairs and tuples)