#ifndef WRITER_H
#define WRITER_H

void init_writer(
        char           *_txt            ,
        int             chars_per_line
);

void dest_writer(
        void
);

int writer_getline(
        char          **ln
);

#endif
