DROP TABLE students;
CREATE TABLE students (
    id INT, 
    namex VARCHAR2(30),
    semester VARCHAR2(30),
    PRIMARY KEY (id)
); 
-- Will show nothing 
SELECT * FROM students; 

-- Sample Inserts for the students table
INSERT INTO students (id, namex, semester) VALUES (1, 'Alice', 'Spring 2024');
INSERT INTO students (id, namex, semester) VALUES (2, 'Bob', 'Fall 2023');
INSERT INTO students (id, namex, semester) VALUES (3, 'Charlie', 'Summer 2024');
INSERT INTO students (id, namex, semester) VALUES (4, 'Dave', 'Spring 2024');
INSERT INTO students (id, namex, semester) VALUES (5, 'Eve', 'Fall 2023');
INSERT INTO students (id, namex, semester) VALUES (6, 'Frank', 'Spring 2024');
INSERT INTO students (id, namex, semester) VALUES (7, 'Grace', 'Winter 2023');
INSERT INTO students (id, namex, semester) VALUES (8, 'Hannah', 'Summer 2024');
INSERT INTO students (id, namex, semester) VALUES (9, 'Ivy', 'Fall 2024');
INSERT INTO students (id, namex, semester) VALUES (10, 'Jack', 'Winter 2023');

-- Will show them all 
SELECT * FROM students; 
-- Will show only the names 
SELECT namex FROM students;