a tool i built in C to iterate through large text datasets and figure out what regex patterns show up before/after some data changes.

## how it works

- paste your before/after text data into an array
- iterate over the array, index by index
- each index gets broken up into individual words
- each word gets pushed into a rolling window array of 3
- every iteration: drop the first index, shift the other 2 left, then tack the new word onto the back
- that 3-word window gets stripped of trailing punctuation and concatenated back into a single string
- each individual word also gets checked against a set of regex patterns (emails, phone numbers, dates, timestamps, counters) and prints out whatever it matches

basically a sliding window over the text so you can see patterns in context instead of just word by word.

## why

wanted more reps with pointers and manual memory management in C — no `.join()`, no dynamic arrays, no built-in helpers. everything (string concat, array shifting, sizing buffers) is done by hand with `malloc`/`strcat`/`memmove`.

## heads up

memory management here is rough around the edges — this was more about learning pointers than writing clean C. also the 3-word merged string (`str_arr`) gets built every loop but isn't actually what gets checked against the regex patterns right now (that's still running on the single `word`) — window-building and regex-matching are two separate pieces that aren't wired together yet. treating this as a learning project, not production code.

## built with

C, `<regex.h>`, `<string.h>`, way too much `strdup`

Not really useful for anyone looking at this. Just something I made to automate my workflow and made my life much easier so I though I'd share.
