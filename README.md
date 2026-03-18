# Minirel-Dbms
Miniature Relational Database

•	Built core database storage infrastructure in C++, including a buffer manager with clock-based page replacement and hash-based page lookup to optimize disk page access, reducing page-fault overhead by ~30% under mixed read/write workloads.

•	Implemented heap-file storage and scan operators to support insertion, deletion, and predicate-based retrieval across thousands of records with efficient memory utilization.

•	Integrated SQL-like query operators with full integration into system catalogs, achieving 100% pass rate on 40+ tests.

