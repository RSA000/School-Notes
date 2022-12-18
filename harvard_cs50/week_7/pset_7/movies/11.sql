SELECT title FROM movies
    JOIN stars ON (stars.movie_id = movies.id)
    JOIN ratings ON (movies.id = ratings.movie_id)
    JOIN people ON (stars.person_id = people.id)
    WHERE people.name = 'Chadwick Boseman'
    ORDER BY (rating) DESC
    LIMIT(5);