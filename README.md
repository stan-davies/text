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
- Work out how to wrap words as wholes rather than character specific (again,
  see odecd book).      - It is getting super confused sometimes.
- Draw text block as lines to a texture then store that texture. If no keyboard
  input since last frame, redraw the same texture.
- Draw cursor as a rectangle or something.
- Implement delete - maybe a clear currently editing to main text then pluck
  characters off the end of there. Alternatively: remove from editing string
  until empty, then pop from main text.

Current problem is an annoying bit of heap corruption in creating a texture
from the surface. Typing 'how ' (for 'how is this looking') causes the error,
though precisely four frames of the full text are rendered before the heap
corruption occurs. Very confused. It also seems that, if instead four
characters ending in a letter, rather than a space, are entered, then the error
instead crops us when trying to free the texture. If it is a linefeed, then it
is the actuall rendering call that crashes. In all cases, however, heap
corruption, and always after four frames of the fourth character.



Research notes (i.e. stuff I want to remember but won't be implementing in any
near future):

The SDL wiki says that what I have done for text input (reinventing the wheel)
is really very foolish because it won't support the input of every language
ever. I should have used SDL_StartTextInput. However, I don't have plans _that_
grand, so I think letting it only support English for now is quite reasonable.
Getting it to support the input of more special characters could be a nice
idea, but I am not overly fussed.
