SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE person_id = (SELECT id from people WHERE name = "Helena Bonham Carter")
INTERSECT
SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
AND person_id = (SELECT id from people WHERE name = "Johnny Depp");