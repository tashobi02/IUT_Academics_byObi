CREATE OR REPLACE PROCEDURE n_movies_with_highest_rating (v_movies IN NUMBER) IS
    v_count NUMBER; 
BEGIN 
    SELECT COUNT(*)
    INTO v_count
    FROM MOVIE m
    JOIN RATING qr ON m.MOV_ID = qr.MOV_ID
    WHERE qr.REV_STARS = (SELECT MAX(REV_STARS) FROM RATING);
    DBMS_OUTPUT.PUT_LINE('Number of movies with highest rating: ' || v_count);
END;
/

DECLARE
    v_count NUMBER;
BEGIN
    v_count := &input_number;
    n_movies_with_highest_rating(v_count);
END;
/

CREATE OR REPLACE FUNCTION get_movie_status(p_movie_title VARCHAR2) 
RETURN VARCHAR2 IS
    v_actor_count NUMBER;
    v_status VARCHAR2(10);

BEGIN
    SELECT COUNT(*)
    INTO v_actor_count
    FROM CASTS c
    JOIN MOVIE m ON c.MOV_ID = m.MOV_ID
    WHERE m.MOV_TITLE = p_movie_title;
    IF v_actor_count = 1 THEN
        v_status := 'Solo';
    ELSE
        v_status := 'Ensemble';
    END IF;
    RETURN v_status;
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE(get_movie_status('Titanic'));
    DBMS_OUTPUT.PUT_LINE(get_movie_status('Beyond The Sea'));
END;
/

CREATE OR REPLACE PROCEDURE find_oscar_nominees IS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Eligible Directors for Oscars:');
    FOR director_rec IN (
        SELECT DISTINCT d.DIR_ID, d.DIR_FIRSTNAME, d.DIR_LASTNAME
        FROM DIRECTOR d
        JOIN DIRECTION dir ON d.DIR_ID = dir.DIR_ID
        JOIN MOVIE m ON dir.MOV_ID = m.MOV_ID
        JOIN RATING qr ON m.MOV_ID = qr.MOV_ID
        GROUP BY d.DIR_ID, d.DIR_FIRSTNAME, d.DIR_LASTNAME, m.MOV_ID
        HAVING AVG(qr.REV_STARS) >= 7 AND COUNT(qr.REV_ID) > 10  
    ) 
    LOOP
        DBMS_OUTPUT.PUT_LINE('Director: ' || director_rec.DIR_FIRSTNAME || ' ' || director_rec.DIR_LASTNAME);
    END LOOP;
END;
/

EXEC find_oscar_nominees;


