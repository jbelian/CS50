# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Medical condition and the longest accepted word in the English language.

## According to its man page, what does `getrusage` do?

Returns resource usage measures for processes, like CPU time used.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Less memory used by pointing to the value instead of making a copy.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

For each character in the file until the end of the file, if that character is alphabetic or an apostrophe (that is not at the
beginning of a string), append that character to an array starting at an index of 0 and increment the index by 1 for each new
character appended. If the index is greater than the longest English word, meaning that the string is not a word in the dictionary,
consume the rest of the string and reset the index to 0 to iterate through a new string.

If a character is a number, consume the rest of the string and reset the index to 0 to iterate through a new string.

If the next character is not alphabetic, not an apostrophe, and not a number, and the index of iterating through the string is
greater than 0, then a word was found. Terminate the word at the current index with \0 and update the number of words found. Check
if the word is misspelled and note the time it took to perform the check. Add that time to the bank of time that's accumulated for
each check. If the word is misspelled, print that word to the terminal and update the number of misspellings. Reset the index to 0
to iterate through a new string.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

`fgetc` allows us to be very precise in the amount and type of characters we want read into memory. Using `fscanf` with format
string `"%s"` reads characters until a whitespace (blank, newline, or tab) is found. Because it reads all characters until a
whitespace into a string, it will accidentally include characters like punctuation marks into our "words". This will complicate the
code needed to correctly parse the words we want, so `fgetc` seems more intuitive. Also, if we do not specify a maximum width for
the number of characters to be read, an attacker that supplies a string without a whitespace could mess with us.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Basically to ensure that neither a string passed into `check` nor the dictionary loaded into `load` are modified while in use.