//---------------------------------------------------------------------------
//	Arenadata logging for research purposes
//
//	@filename:
//		adlog.h
//
//	@doc:
//		Simple logging function to write arbitrary strings into hardcoded log_file
//---------------------------------------------------------------------------
#ifndef ARENADATA_ADLOG
#define ARENADATA_ADLOG

#include <stdio.h>
#include <stdarg.h>
#include <time.h>


const char* LOG_FILE = "/tmp/ad_orca.log";
const char* LOG_FILE_MODE = "a";
const int TIME_STRING_LENGTH = 64;


// Same as printf(), but also prints time and outputs data to log log_file
// The given string should will be null-terminated automatically
void adlog(const char* format, ...) {
    // Parse arguments
    va_list arglist;
    va_start(arglist, format);

    // Open log file
    FILE* log_file = fopen(LOG_FILE, LOG_FILE_MODE);
    if (log_file == NULL)
        return;

    // Make time_string
    char time_string[TIME_STRING_LENGTH];
    const time_t timestamp = time(NULL);
    strftime(time_string, TIME_STRING_LENGTH, "[%F %T] ", localtime(&timestamp));

    // Print
    fprintf(log_file, "%s", time_string);
    vfprintf(log_file, format, arglist);
    fprintf(log_file, "\n");

    fclose(log_file);

    va_end(arglist);
}


#endif // ARENADATA_ADLOG
