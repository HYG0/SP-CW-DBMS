# SP-CW-DBMS
This repository contains an implementation of a DBMS developed as part of a coursework for the Systems Programming course in MAI.


## Build

```bash
cmake -B build
cmake --build build
```

## Run

Interactive mode: 

```bash
./build/dbms
```

From a file:

```bash
./build/dbms tests/full_dbms_test.sql
```

All SQL commands must end with `;`.

## Example

```sql
CREATE DATABASE shop;
USE shop;

CREATE TABLE users (
    id INT INDEXED,
    name STRING NOT_NULL
);

INSERT INTO users (id, name) VALUE
    (1, "Alice");

SELECT * FROM users;

SELECT * FROM users WHERE id == 1;
```


## Implemented features
- B+ tree
- File-based table storage
- CREATE DATABASE / DROP DATABASE / USE
- CREATE TABLE / DROP TABLE
- INSERT / SELECT / UPDATE / DELETE
- INT / STRING
- NOT_NULL
- INDEXED
- DEFAULT
- WHERE with == != < > <= >=
- WHERE BETWEEN
- WHERE LIKE
- WHERE AND / OR
- SELECT aliases with AS
- SUM / COUNT / AVG
- JSON output for SELECT


## Full test

The implemented functionality can be checked using:

```bash
./build/dbms tests/full_dbms_test.sql
```