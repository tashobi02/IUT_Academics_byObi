BEGIN
    DBMS_OUTPUT.PUT_LINE('Obidit Islam, ID: 220041154');
END;
/

CREATE OR REPLACE PROCEDURE multiply(x IN NUMBER, y IN NUMBER) IS 
    z NUMBER; 
BEGIN 
    z := x * y; 
    DBMS_OUTPUT.PUT_LINE('The result is: ' || z);
END; 
/

DECLARE 
    p NUMBER;
    q NUMBER;
BEGIN 
    p := &input_number;
    q := &input_number;
    multiply(p, q);
END;
/

DECLARE
    num NUMBER;
BEGIN
    num := &input_number;
    IF num = TRUNC(num) THEN
        DBMS_OUTPUT.PUT_LINE('The number ' || num || ' is a whole number.');
    ELSE
        DBMS_OUTPUT.PUT_LINE('The number ' || num || ' is a fraction.');
    END IF;
END;
/



