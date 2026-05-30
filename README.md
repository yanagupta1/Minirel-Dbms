# MiniRel Database Management System

A relational database management system (DBMS) built from the ground up in C++, implementing core database internals including storage management, buffer management, query execution, catalog management, and optimized join algorithms.

## Overview

MiniRel recreates many of the fundamental components found in modern database systems. The project provides hands-on experience with how databases manage persistent storage, cache pages in memory, execute relational operations, and process queries efficiently.

The system supports disk-backed storage, heap files, page-level management, SQL-style operations, and hash-based join optimization.

---

## Features

### Storage Engine
- Heap-file record storage
- Page-level data organization
- Persistent database creation and destruction
- Record insertion and deletion

### Buffer Manager
- In-memory page caching
- Clock replacement policy
- Hash-based page lookup
- Dirty-page tracking
- Page pinning and unpinning

### Catalog Manager
- Relation metadata management
- Schema storage
- System catalog support

### Query Processing
- CREATE TABLE
- INSERT
- DELETE
- LOAD
- JOIN

### Join Algorithms
- Nested-loop joins
- Hash joins
- Optimized hash-table probing

### Testing
- Unit-tested storage layer
- Buffer manager validation
- Query execution testing
- Dataset-driven benchmarking

---

## Architecture

```text
                 User Queries
                        │
                        ▼
                 Query Processor
                        │
       ┌────────────────┼────────────────┐
       ▼                                 ▼
 Catalog Manager                  Join Engine
                                          │
                                          ▼
                                  Hash Join Module
                                          │
                                          ▼
                                  Buffer Manager
                                          │
                                          ▼
                                Heap File Storage
                                          │
                                          ▼
                                  Database Files
```

---

## Project Structure

```text
src/
├── buffer/      # Buffer pool and page caching
├── storage/     # Database files, pages, heap files
├── catalog/     # Metadata and schema management
├── parser/      # SQL parser and lexer
├── query/       # Query operators
└── core/        # Entry point and utilities

tests/           # Unit tests
data/            # Sample datasets
tools/           # Dataset generation utilities
```

---

## Key Components

### Buffer Manager

Implements a clock-based page replacement strategy to efficiently manage memory usage and reduce disk I/O.

Features:
- Page pinning
- Dirty page handling
- Hash-based lookup
- Cache eviction

### Heap File Manager

Provides persistent storage for database records using page-based heap files.

Features:
- Record insertion
- Record deletion
- Sequential scans
- Disk-backed storage

### Query Engine

Executes relational operations and coordinates storage, buffer, and catalog components.

Supported operations:
- Create relations
- Insert tuples
- Delete tuples
- Load datasets
- Execute joins

### Hash Join

Implements an optimized hash join algorithm for efficient relational joins on large datasets.

---

## Technologies

- C++
- Flex
- Bison/Yacc
- File Systems
- Hash Tables
- Memory Management
- Relational Database Systems

---

## Example Query

```sql
CREATE TABLE Students (
    id INTEGER,
    name STRING,
    gpa FLOAT
);

INSERT INTO Students VALUES (1, 'Alice', 3.8);

DELETE FROM Students WHERE id = 1;
```

Join example:

```sql
SELECT *
FROM Students
JOIN Courses
ON Students.id = Courses.student_id;
```

---

## Learning Outcomes

This project provided practical experience with:

- Database architecture
- Storage engines
- Buffer management
- Query execution
- SQL parsing
- Join optimization
- Systems programming
- Performance engineering

---

## Author

Yana Gupta

B.S. Computer Engineering, Machine Learning & Data Science
University of Wisconsin–Madison