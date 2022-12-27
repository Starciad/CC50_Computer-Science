SELECT distinct(name) FROM ratings, directors, people
WHERE directors.movie_id = ratings.movie_id
  AND people.id = directors.person_id
  AND rating >= 9.0;