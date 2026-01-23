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

For insertion:
Change the 'complete' action on typing to be a timer? Especially since pressing
enter now makes no discernable impact whatsoever. Would also need to collapse
on any cursor motion.
See about that SDL_StartTextInput and whether is really is worthwhile. The SDL
wiki says that what I have done (reinventing the wheel) is really very foolish
because it won't support the input of every language ever. Fortunately, I don't
have plans _that_ grand, so I think letting it only support English for now is
quite reasonable. Getting it to support the input of more special characters
could be a nice idea, but I am not overly fussed.

Work out cursor motion!
Work out how to wrap text.      - How to work out width of a given character
for a given font and point size?
