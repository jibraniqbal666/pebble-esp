int _close_r(void *reent, int fd) { return -1; }
int _write_r(void *reent, int fd, const void *buf, unsigned int cnt) { return -1; }
int _read_r(void *reent, int fd, void *buf, unsigned int cnt) { return -1; }
int _lseek_r(void *reent, int fd, int ptr, int dir) { return -1; }
int _fstat_r(void *reent, int fd, void *st) { return 0; }
int _isatty_r(void *reent, int fd) { return 1; }
void *__getreent(void) { return 0; }
void *_sbrk_r(void *reent, int incr) { return 0; }
