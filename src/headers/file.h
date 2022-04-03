#ifndef FILE_H
#define FILE_H

#ifdef UNIX
#define open_file open_file_unix
#elif defined(WINDOWS)
#define open_file open_file_winodws
#endif


FILE_HANDLE open_file_unix(const char* file_path);
FILE_HANDLE open_file_windows(const char* file_path);

#endif //FILE_H