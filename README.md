# Cache Simulator

Implemented in C++, an LRU (Least Recently Used) cache simulator

Tools : C++, Operating Systems concepts




Compilation:

	g++ src/lru_cache.cpp -o src/lru_cache
	./src/lru_cache


Explanation of Output:


| Step | Operation                             | Expected Output | Explanation                                                                  |
|------|---------------------------------------|-----------------|------------------------------------------------------------------------------|
| 1    | put(1,100), put(2,200), put(3,300)    | N/A             | Cache is now {1:100, 2:200, 3:300}                                           |
| 2    | get(1)                                | 100             | Accessing key 1 makes it Most Recently Used (MRU)                            |
| 3    | put(4,400)                            | N/A             | Evicts key 2 (Least Recently Used - LRU). Cache is now {1:100, 3:300, 4:400} |
| 4    | get(2)                                | -1              | Key 2 was evicted, so it’s not in the cache                                  |
| 5    | get(3)                                | 300             | Key 3 is present in the cache                                                |
| 6    | get(4)                                | 400             | Key 4 is present in the cache                                                |
| 7    | put(5,500)                            | N/A             | Evicts key 1 (Least Recently Used - LRU). Cache is now {3:300, 4:400, 5:500} |
| 8    | get(1)                                | -1              | Key 1 was evicted                                                            |
| 9    | get(5)                                | 500             | Key 5 is present in the cache                                                |

