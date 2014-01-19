#ifndef SULCATA_RIO_H
#define SULCATA_RIO_H

#define RIO_BUFSIZE 8192

namespace sulcata{
  
  typedef struct {
    int rio_fd; /* Descriptor for this internal buf */
    int rio_cnt; /* Unread bytes in internal buf */
    char *rio_bufptr; /* Next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE]; /* Internal buffer */
  } rio_t;
  
  void rio_readinitb(rio_t *rp, int fd);
  
  static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);
  
  ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
  
  ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
  
  ssize_t rio_writen(rio_t *rp, const void* usrbuf, size_t n);

}//namespace ends

#endif
