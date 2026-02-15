End goal is a DTP program. Broad gameplan:

+ Allow text to be edited.
+ Save file as plaintext.
+ Change font.
+ Add formatting to text and save as `.md`.
+ Add concept of page and compile to `.pdf`.
+ Add different paper sizes.
+ Create textboxes, can no longer save as single `.md` file. More likely
multiple that are linked by a file describing the location and size of each.
+ Add other media such as vector/bitmap graphics.
+ Add mathematical rendering to text - edit as latex-esque then place?

Some point throughout, tools such as creating grid, storing colours, ...


More specific points of what needs doing for now:
- Work out cursor motion - going to connect it with rendering (see odecd book).
- Sort out the slight bugginess of text wrapping.

Indeed, `strlen` returns a number which does _not_ include the null terminator
in the count.


---

Research notes (i.e. stuff I want to remember but won't be implementing in any
near future):

The SDL wiki says that what I have done for text input (reinventing the wheel)
is really very foolish because it won't support the input of every language
ever. I should have used SDL_StartTextInput. However, I don't have plans _that_
grand, so I think letting it only support English for now is quite reasonable.
Getting it to support the input of more special characters could be a nice
idea, but I am not overly fussed.
