#include <linux/types.h>
#include <linux/wireless.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

enum {
  SUCCESS,
  ERROR_ARGS,
  ERROR_SOCKET,
  ERROR_IOCTL,
  ERROR__COUNT
};

enum {
  ARGS_EXEC,
  ARGS_INTERFACE,
  ARGS__COUNT
};

int main (int argc, char** argv) {
  // Determine if all required arguments have been provided. Without
  // the wireless interface, this program cannot set the interface
  // name for the ioctl function call.
  if (argc < ARGS__COUNT)
  {
    return ERROR_ARGS;
  }

  // There seems to be a race condition between this and iwd. This
  // must execute after iwd has configured the wireless interface.
  // This seems to give iwd enough time to complete.
  sleep(2);

  int fd = socket(AF_INET, SOCK_DGRAM, 0);

  if (fd == -1)
  {
    return ERROR_SOCKET;
  }

  struct iwreq wrq = { 0 };

  // assign interface name
  strncpy(wrq.ifr_name, argv[ARGS_INTERFACE], IFNAMSIZ);

  // assign power-savings
  wrq.u.power.disabled = 1;

  // Send an ioctl request to configure the wireless interface. If
  // the interface name passed via the command-line arguments does
  // not match a valid wireless interface, this will fail. This
  // ioctl request also requires root privileges.
  if (ioctl(fd, SIOCSIWPOWER,  &wrq) == -1)
  {
    return ERROR_IOCTL;
  }

  close(fd);

  return SUCCESS;
}
