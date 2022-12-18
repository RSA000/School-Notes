
SELECT name FROM
(
SELECT DISTINCT movies.id as movie_kevin FROM movies
    JOIN stars ON (stars.movie_id = movies.id)
    JOIN people ON (people.id = stars.person_id)
    WHERE people.name = 'Kevin Bacon' and people.birth = 1958
)
JOIN stars ON (stars.movie_id = movie_kevin)
JOIN people ON (people.id = stars.person_id)
WHERE name <> 'Kevin Bacon';