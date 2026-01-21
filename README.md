End goal is a DTP program. Broad gameplan:

+ Text rendering through SDL.
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

For rendering:
Get SDL3 going. Will also need SDL_TTF. Then refer to
https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2 to get
off the ground and take it from there.

For insertion:
So everytime you add or remove some text, add it to a separate buffer then
collapse that change into the strings on some kind of 'complete' action, if not
an escape then a timer of a few seconds from last typing keypress.

I will also want to stitch together a logging system and a separate system of
the loop.
