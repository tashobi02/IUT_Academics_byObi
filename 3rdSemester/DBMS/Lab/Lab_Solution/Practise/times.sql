SELECT 
    TO_CHAR(SYSDATE, 'YYYY') AS "Year (4 digits)",
    TO_CHAR(SYSDATE, 'YY') AS "Year (2 digits)",
    TO_CHAR(SYSDATE, 'MONTH') AS "Month Name",
    TO_CHAR(SYSDATE, 'MM') AS "Month (Number)",
    TO_CHAR(SYSDATE, 'DD') AS "Day (Number)",
    TO_CHAR(SYSDATE, 'DY') AS "Abbreviated Day",
    TO_CHAR(SYSDATE, 'Day') AS "Full Day Name",
    TO_CHAR(SYSDATE, 'HH24') AS "Hour (24-hour)",
    TO_CHAR(SYSDATE, 'HH12') AS "Hour (12-hour)",
    TO_CHAR(SYSDATE, 'MI') AS "Minutes",
    TO_CHAR(SYSDATE, 'SS') AS "Seconds"
FROM dual; 

