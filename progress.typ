- Wanting to have a system for handling the two strings that make up the text.
  Asking to read them could provide a `const char *` and asking to write could
  give a `char *`. Sort of want to think about using `char *const`, presumably
  for the base pointer that hangs onto it all, though we will use realloc so
  that makes no sense!
- So everytime you add or remove some text, add it to a separate buffer then
  collapse that change into the strings on some kind of 'complete' action, if
  not an escape then a timer of a few seconds from last typing keypress.
