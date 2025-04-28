DROP TABLE TRANSACTIONS;
DROP TABLE ACCOUNT;

CREATE SEQUENCE transaction_seq START WITH 1 INCREMENT BY 1;
-- Create the ACCOUNT table
CREATE TABLE ACCOUNT (
    account_id NUMBER(10) PRIMARY KEY
);
-- Create the TRANSACTIONS table
CREATE TABLE TRANSACTIONS (
    transaction_id NUMBER(10) PRIMARY KEY,
    transaction_date DATE,
    account_id NUMBER(10),
    amount NUMBER(10,2),
    type NUMBER(1),
    CONSTRAINT fk_transactions_account FOREIGN KEY(account_id) REFERENCES ACCOUNT(account_id)
);
-- Insert 100 rows into the ACCOUNT table
INSERT INTO ACCOUNT (account_id)
SELECT LEVEL
FROM DUAL
CONNECT BY LEVEL <= 100;
-- Insert 1000 random transactions into the TRANSACTIONS table
DECLARE
    v_max_date DATE := SYSDATE;
BEGIN
    FOR i IN 1..1000 LOOP
    INSERT INTO TRANSACTIONS (transaction_id, transaction_date, account_id, amount, type)
    VALUES (
    transaction_seq.NEXTVAL, -- Use the sequence to generate unique ID
      v_max_date - FLOOR(DBMS_RANDOM.VALUE * 365),
      FLOOR(DBMS_RANDOM.VALUE * 100) + 1,
      FLOOR(DBMS_RANDOM.VALUE * 100000) + 1,
      FLOOR(DBMS_RANDOM.VALUE * 2)
    );
    END LOOP;
END;
/