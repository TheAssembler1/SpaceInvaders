#include <headers.h>

#ifdef UNIX
FILE_HANDLE open_file_unix(const char* file_path) {

}

void read_file_bytes_unix(FILE_HANDLE h_file) {

}

#elif defined(WINDOWS)
FILE_HANDLE open_file_windows(const char* file_path) {
	FILE_HANDLE h_file = NULL;

	h_file = CreateFile(file_path, 
						 GENERIC_READ,
						 0,
						 NULL,
						 OPEN_EXISTING,
						 FILE_ATTRIBUTE_READONLY | FILE_FLAG_OVERLAPPED,
						 NULL);

	if (h_file == INVALID_HANDLE_VALUE)
		return 0;

	return h_file;
}

void read_file_bytes_windows(FILE_HANDLE h_file) {

}

#endif