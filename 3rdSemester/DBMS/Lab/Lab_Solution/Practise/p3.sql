DROP TABLE Instructor_p3;
CREATE TABLE Instructor_p3 (
    id_p3 INT, 
    namex VARCHAR2(30), 
    dept_name VARCHAR2(10),
    salary NUMBER, 
    CONSTRAINT I_PK PRIMARY KEY(id_p3)
);

INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (101, 'Dr. Alice Thompson', 'CSE', 85000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (102, 'Prof. Robert Kim', 'EEE', 78000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (103, 'Dr. Emily Carter', 'MPE', 92000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (104, 'Prof. Michael Brown', 'CEE', 76000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (105, 'Dr. Susan Green', 'BTM', 83000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (106, 'Prof. James Lee', 'CSE', 87000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (107, 'Dr. Nancy Adams', 'EEE', 79000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (108, 'Prof. David Martin', 'MPE', 95000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (109, 'Dr. Olivia Wilson', 'CEE', 75000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (110, 'Prof. Daniel Clark', 'BTM', 81000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (111, 'Dr. Grace Miller', 'CSE', 89000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (112, 'Prof. Ethan Moore', 'EEE', 77000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (113, 'Dr. Isabella Taylor', 'MPE', 94000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (114, 'Prof. Benjamin Lee', 'CEE', 73000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (115, 'Dr. Mia Rodriguez', 'BTM', 85000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (116, 'Prof. William Anderson', 'CSE', 91000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (117, 'Dr. Sofia Scott', 'EEE', 80000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (118, 'Prof. Samuel Jackson', 'MPE', 96000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (119, 'Dr. Evelyn Martinez', 'CEE', 74000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (120, 'Prof. Lucas Hill', 'BTM', 82000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (121, 'Dr. Harper Adams', 'CSE', 86000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (122, 'Prof. Henry Phillips', 'EEE', 79500);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (123, 'Dr. Aria Gonzalez', 'MPE', 91000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (124, 'Prof. Jackson Evans', 'CEE', 76000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (125, 'Dr. Emily Brown', 'BTM', 83000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (126, 'Prof. Alexander White', 'CSE', 87000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (127, 'Dr. Amelia Collins', 'EEE', 81000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (128, 'Prof. Oliver Sanchez', 'MPE', 92500);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (129, 'Dr. Isla Ramirez', 'CEE', 78000);
INSERT INTO Instructor_p3 (id_p3, namex, dept_name, salary) VALUES (130, 'Prof. Mason Young', 'BTM', 84000);


SELECT * FROM Instructor_p3 WHERE salary < 85000;
SELECT * FROM Instructor_p3 WHERE salary = 81000; 
SELECT * FROM Instructor_p3 WHERE salary != 81000; 
SELECT * FROM Instructor_p3 WHERE salary BETWEEN 80000 AND 90000; 
SELECT * FROM Instructor_p3 WHERE salary > 85000 AND dept_name = 'CSE';
SELECT * FROM Instructor_p3 WHERE dept_name = 'CSE' OR dept_name = 'EEE';
SELECT * FROM Instructor_p3 WHERE salary NOT BETWEEN 80000 AND 90000; 

-- Instead of using multiple OR operations, you canuse IN 

SELECT * FROM Instructor_p3 WHERE dept_name IN ('CSE', 'EEE'); 

