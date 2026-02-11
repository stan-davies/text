#ifndef LOGW_H
#define LOGW_H

/*
 * Initialises the log file writer.
 */
int init_logw(
        void
);

/*
 * Logs the given message to the log file.
 */
void log_msg(
        char           *fmt     ,
        ...
);

/*
 * Logs the given error message to the log file.
 */
void log_err(
        char           *fmt     ,
        ...
);

/*
 * Logs the given warning message to the log file.
 */
void log_wrn(
        char           *fmt     ,
        ...
);

#endif
