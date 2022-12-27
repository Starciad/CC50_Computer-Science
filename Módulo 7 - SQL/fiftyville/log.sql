-- Keep a log of any SQL queries you execute as you solve the mystery.

-- ver todas as tabelas
.tables
.schema

-- Veja o registro do crime do dia
SELECT *
  FROM crime_scene_reports
 WHERE year = 2020
   AND month = 6
   AND day = 28
   AND street = "Chamberlin Street";

-- Veja os registros da entrevista de três testemunhas sobre o ladrão naquele dia
SELECT *
  FROM interviews
 WHERE year = 2020
   AND month = 6
   AND day = 28
   AND transcript LIKE "%thief%";

-- pista 1. Pouco depois de dez minutos do roubo, vi o ladrão entrar em um carro no estacionamento da padaria e ir embora.
-- Se você tiver imagens de segurança do estacionamento da padaria, talvez queira procurar carros que saíram do estacionamento nesse período.
-- Pessoas saindo do estacionamento
-- | Barry   |
-- | Bruce   |
-- | Diana   |
-- | Iman    |
-- | Kelsey  |
-- | Luca    |
-- | Sofia   |
-- | Vanessa |
SELECT name
  FROM people
 WHERE license_plate IN
        (SELECT license_plate
           FROM bakery_security_logs
          WHERE year = 2022
            AND month = 6
            AND day = 28
            AND hour = 10
            AND minute > 15
            AND minute <= 25
            AND activity = "exit")
 ORDER BY name;

-- pista 2. Não sei o nome do ladrão, mas era alguém que reconheci. No início desta manhã, antes de chegar à padaria de Emma,
-- Eu estava passando pelo caixa eletrônico na Leggett Street e vi o ladrão lá sacando algum dinheiro.
-- No dia, Leggett Street, pessoa que saca dinheiro
-- | Bruce   |
-- | Diana   |
-- | Iman    |
-- | Luca    |
SELECT name
  FROM people, bank_accounts
 WHERE people.id = bank_accounts.person_id
   AND account_number IN
       (SELECT account_number
          FROM atm_transactions
         WHERE year = 2022
           AND month = 6
           AND day = 28
           AND atm_location = "Leggett Street"
           AND transaction_type = "withdraw")
 ORDER BY name;


-- pista 3. Quando o ladrão estava saindo da padaria, eles ligaram para alguém que falou com eles por menos de um minuto. Na chamada, ouvi o ladrão
-- diga que eles estavam planejando pegar o primeiro vôo de Fiftyville amanhã. O ladrão então pediu à pessoa do outro lado do telefone para comprar a passagem aérea.
-- A pessoa que comprou o primeiro ingresso de amanhã
-- | Bruce  |
-- | Luca   |
SELECT name
  FROM people
 WHERE passport_number IN
        (SELECT passport_number
           FROM passengers
          WHERE flight_id IN
                (SELECT id
                   FROM flights
                  WHERE year = 2022
                    AND month = 6
                    AND day = 29
                    AND origin_airport_id IN
                        (SELECT id
                           FROM airports
                          WHERE city = "Fiftyville")
                  ORDER BY hour
                  LIMIT 1))
 ORDER BY name;

-- Pessoas que fizeram menos de um minuto de telefonemas naquele dia
-- | Bruce   |
SELECT name
  FROM people
 WHERE phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE year = 2022
           AND month = 6
           AND day = 28
           AND duration < 60)
 ORDER BY name;

-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- 当天打给了 (375) 555-8161
-- | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
-- 飞往 New York City