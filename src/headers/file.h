#ifndef FILE_H
#define FILE_H

#ifdef UNIX
#define open_file open_file_unix
#define read_file read_file_bytes_unix
#elif defined(WINDOWS)
#define open_file open_file_windows
#define read_file read_file_bytes_windows
#endif


FILE_HANDLE open_file_unix(const char* file_path);
FILE_HANDLE open_file_windows(const char* file_path);

void read_file_bytes_unix(FILE_HANDLE h_file);
void read_file_bytes_windows(FILE_HANDLE h_file);

#endif //FILE_H