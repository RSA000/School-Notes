-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND year = 2021;

 - Clues
    * Withing ten minutes of the theft, thief got into car. 10:15 - 10:25
    * Thief withdrew money money on Legget Street earlier in the morning
    * Thief called someone and talked for less then a minute. Asking to take earliest flight out of Fiftyville on the next day
    * FiftyVille airport id = 8, abr = CSF



SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 and minute > 15 AND minute < 25;
    * Gives us all the licence plates that left between 10:16 and 10:25



SELECT * FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw';
    * Shows all widthdrawels on Leggett that day. Amounts may be indicative of something

SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw')


SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
    * Shows all calls that occurred on that day that was less then a minute



SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour;
   * Find flights departing FiftyVille on day after. earliest 8:20am to destination - New York City, airport id = 4



SELECT passport_number FROM passengers WHERE flight_id = 36;
    * Shows passengers who where on flight 36


 SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
    * Finds people information based on the passport numbers of the people on flight 36


SELECT * FROM people WHERE passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id = 36)
    AND phone_number IN
    (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
    AND license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 and minute > 15 AND minute < 25)
    AND id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = "Leggett Street" AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw'));

    * Finding Theif


(375) 555-8161 - number theif called

SELECT * FROM people WHERE phone_number = (375) 555-8161;
