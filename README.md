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
* Complete `page`.
- Save text to a file - detect cmd+s then collapse all then copy down fresh.
- Show save icon - a coloured square in the corner that is red when there are
  unsaved changes and green the rest of the time. Use a system like the
  flashing cursor where `input` is passed and then savedness is toggled
  accordingly.
- Allow file contents to be loaded - load into a string and then do a kind of
  `backpend` to the text so that the whole lot goes into `aft` and so the
  cursor begins at the start of the text (or not focussed?).
- Add some kind of interface for choosing files.
- Add ability to highlight words and set text effects.
- Really need a better system than '|' for setting the cursor position ---
  might want to type that.

For `page`, I want to render lines to it, and then do some magic or something.
No idea what the plan is really.

---

Notes:

The SDL wiki says that what I have done for text input (reinventing the wheel)
is really very foolish because it won't support the input of every language
ever. I should have used SDL_StartTextInput. However, I don't have plans _that_
grand, so I think letting it only support English for now is quite reasonable.
Getting it to support the input of more special characters could be a nice
idea, but I am not overly fussed.

The function `strlen` returns a number which does _not_ include the null
terminator in the count.

Currently when rendering the lines of text, spaces aren't moved directly into
the output word (but rather when word is pushed to line), so if there are
multiple subsequent spaces then only the first is included and the rest are
ignored. This will presumably be useful for justified lines but currently feels
a bit odd.

Had a crash one time when the second line was filled with a single word that
wrapped to the next but then I couldn't reproduce this error ever so hopefully
it's fine. The crash was during rendering, but that's just trickle down I
imagine.

Whole thing would be a lot better if the entire text got converted to some kind
of 'W W\nW' symbol form of words and control characters, though how that would
be interacted with I do not know.
