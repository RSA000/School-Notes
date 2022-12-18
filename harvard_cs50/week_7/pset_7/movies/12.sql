SELECT title FROM
(
SELECT title, COUNT(title) AS 'counts' FROM movies
    JOIN stars ON (movies.id = stars.movie_id)
    JOIN people ON (stars.person_id = people.id)
    WHERE people.name = 'Johnny Depp' OR people.name = 'Helena Bonham Carter'
    GROUP BY title
)
WHERE counts > 1;