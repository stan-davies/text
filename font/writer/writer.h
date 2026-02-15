#ifndef WRITER_H
#define WRITER_H

/*
 * Initialise the writer, called per rendering of text.
 */
void init_writer(
        char           *_txt            ,
        int             chars_per_line
);

/*
 * Destroy the writer.
 */
void dest_writer(
        void
);

/*
 * Returns the next line of the given text to draw.
 */
int writer_getline(
        char          **ln      ,       // Line to draw.
        int            *cursx           // Char index of cursor (potentially).
);

#endif
