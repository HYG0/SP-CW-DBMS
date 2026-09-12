CREATE DATABASE full_test;

USE full_test;


-- CREATE TABLE


CREATE TABLE users (
    id INT INDEXED,
    name STRING NOT_NULL DEFAULT "Unknown",
    age INT DEFAULT 18,
    city STRING DEFAULT "Moscow",
    active INT DEFAULT 1,
    note STRING DEFAULT NULL
);


-- INSERT


INSERT INTO users (id, name, age, city, active, note) VALUE
    (1, "Ann", 20, "Moscow", 1, "admin"),
    (2, "Bob", 25, "Berlin", 1, NULL),
    (3, "Alice", 30, "Amsterdam", 0, "guest"),
    (4, "Kate", NULL, "Kazan", 1, NULL);


-- INSERT с DEFAULT
INSERT INTO users (id, name) VALUE
    (5, "DefaultUser");


-- Проверка всех записей
SELECT * FROM users;



-- SELECT с отдельными столбцами


SELECT id, name FROM users;

SELECT name, age, city FROM users;


-- SELECT с AS
SELECT id AS user_id, name AS user_name, city AS user_city
FROM users;



-- WHERE и сравнения


SELECT * FROM users WHERE id == 2;

SELECT * FROM users WHERE id != 2;

SELECT * FROM users WHERE id <= 4;

SELECT * FROM users WHERE id > 2;

SELECT * FROM users WHERE id >= 3;



-- BETWEEN


SELECT id, name, age
FROM users
WHERE id BETWEEN 1 AND 4;

SELECT id, name, age
FROM users
WHERE id BETWEEN 2 AND 5;



-- LIKE


SELECT id, name
FROM users
WHERE name LIKE "A.*";


SELECT id, name, city
FROM users
WHERE city LIKE "M.*";



-- AND / OR


SELECT id, name, active
FROM users
WHERE active == 1 AND id >= 1;


SELECT id, name
FROM users
WHERE id == 1 OR id == 3;


SELECT id, name, active
FROM users
WHERE (id == 1 OR id == 3) AND active == 1;



-- NULL


SELECT id, name, age
FROM users
WHERE age == NULL;


SELECT id, name, age
FROM users
WHERE age != NULL;



-- UPDATE


UPDATE users
SET age = 40
WHERE id == 4;


SELECT * FROM users WHERE id == 4;


UPDATE users
SET city = "Paris"
WHERE id == 2;


SELECT * FROM users WHERE id == 2;


-- UPDATE нескольких столбцов
UPDATE users
SET city = "London", active = 0
WHERE id == 5;


SELECT * FROM users WHERE id == 5;



-- DELETE


DELETE FROM users
WHERE id == 3;


SELECT * FROM users;



-- INDEXED


CREATE TABLE products (
    sku STRING INDEXED,
    title STRING NOT_NULL,
    price INT DEFAULT 0
);


INSERT INTO products (sku, title, price) VALUE
    ("A001", "Keyboard", 100),
    ("B010", "Mouse", 50),
    ("C100", "Monitor", 300),
    ("D200", "Laptop", 1000);


-- Точное обращение по индексированному STRING
SELECT * FROM products
WHERE sku == "B010";


-- Диапазон по индексированному STRING
SELECT * FROM products
WHERE sku >= "B000";


SELECT * FROM products
WHERE sku BETWEEN "B000" AND "D000";



-- INTEGER INDEX


CREATE TABLE numbers (
    id INT INDEXED,
    value INT DEFAULT 0
);


INSERT INTO numbers (id, value) VALUE
    (1, -10),
    (2, -5),
    (3, 0),
    (4, 5),
    (5, 10);


SELECT * FROM numbers;

SELECT * FROM numbers
WHERE id == 3;


SELECT * FROM numbers
WHERE id >= 2;


SELECT * FROM numbers
WHERE id <= 4;


SELECT * FROM numbers
WHERE value < 0;


SELECT * FROM numbers
WHERE value >= 0;


SELECT * FROM numbers
WHERE value BETWEEN -5 AND 10;



-- UPDATE с отрицательным значением


UPDATE numbers
SET value = -20
WHERE id == 1;


SELECT * FROM numbers;



-- AGGREGATE FUNCTIONS


SELECT COUNT(*) AS total_users
FROM users;


SELECT COUNT(age) AS users_with_age
FROM users;


SELECT SUM(age) AS total_age
FROM users;


SELECT AVG(age) AS average_age
FROM users;


SELECT COUNT(age) AS users_with_age,
       SUM(age) AS total_age,
       AVG(age) AS average_age
FROM users;


-- Агрегаты с WHERE
SELECT COUNT(*) AS active_users
FROM users
WHERE active == 1;


SELECT SUM(age) AS active_age
FROM users
WHERE active == 1;


SELECT AVG(age) AS active_average_age
FROM users
WHERE active == 1;



-- Квалифицированное имя database.table


SELECT id, name
FROM full_test.users
WHERE id >= 1 AND id <= 5;



-- DEFAULT и NULL


CREATE TABLE defaults_test (
    id INT INDEXED,
    name STRING DEFAULT "default_name",
    age INT DEFAULT 18,
    comment STRING DEFAULT NULL
);


INSERT INTO defaults_test (id)
VALUE (1);


INSERT INTO defaults_test (id, name)
VALUE (2, "Custom");


SELECT * FROM defaults_test;



-- NOT_NULL


CREATE TABLE required_test (
    id INT INDEXED,
    name STRING NOT_NULL
);


INSERT INTO required_test (id, name)
VALUE (1, "Alice");


SELECT * FROM required_test;



-- Удаление таблицы


DROP TABLE defaults_test;



-- Проверка DELETE


DELETE FROM numbers
WHERE id == 5;


SELECT * FROM numbers;



-- Проверка DROP DATABASE


CREATE DATABASE database_to_drop;

USE database_to_drop;

CREATE TABLE temporary (
    id INT INDEXED,
    value STRING
);


INSERT INTO temporary (id, value)
VALUE (1, "temporary");


SELECT * FROM temporary;


DROP DATABASE database_to_drop;


-- Возвращаемся к основной БД
USE full_test;

SELECT * FROM users;