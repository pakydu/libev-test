
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckSymbolExists)

# Check for header files
check_include_file("dlfcn.h"      HAVE_DLFCN_H)
check_include_file("inttypes.h"    HAVE_INTTYPES_H)
check_include_file("memory.h"      HAVE_MEMORY_H)
check_include_file("poll.h"        HAVE_POLL_H)
check_include_file("port.h"        HAVE_PORT_H)
check_include_file("stdint.h"      HAVE_STDINT_H)
check_include_file("stdlib.h"      HAVE_STDLIB_H)
check_include_file("strings.h"     HAVE_STRINGS_H)
check_include_file("string.h"      HAVE_STRING_H)
check_include_file("sys/epoll.h"   HAVE_SYS_EPOLL_H)
check_include_file("sys/eventfd.h" HAVE_SYS_EVENTFD_H)
check_include_file("sys/event.h"   HAVE_SYS_EVENT_H)
check_include_file("sys/inotify.h" HAVE_SYS_INOTIFY_H)
check_include_file("sys/select.h"  HAVE_SYS_SELECT_H)
check_include_file("sys/signalfd.h" HAVE_SYS_SIGNALFD_H)
check_include_file("sys/stat.h"    HAVE_SYS_STAT_H)
check_include_file("sys/timerfd.h" HAVE_SYS_TIMERFD_H)
check_include_file("sys/types.h"   HAVE_SYS_TYPES_H)
check_include_file("unistd.h"      HAVE_UNISTD_H)
check_include_file("linux/aio_abi.h" HAVE_LINUX_AIO_ABI_H)
check_include_file("linux/fs.h"    HAVE_LINUX_FS_H)

# Check for functions
check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)
check_function_exists(epoll_ctl    HAVE_EPOLL_CTL)
check_function_exists(eventfd      HAVE_EVENTFD)
list(APPEND CMAKE_REQUIRED_LIBRARIES m)
check_function_exists(floor        HAVE_FLOOR)
check_function_exists(inotify_init HAVE_INOTIFY_INIT)
check_function_exists(kqueue       HAVE_KQUEUE)
check_function_exists(nanosleep    HAVE_NANOSLEEP)
check_function_exists(poll         HAVE_POLL)
check_function_exists(port_create  HAVE_PORT_CREATE)
check_function_exists(select       HAVE_SELECT)
check_function_exists(signalfd     HAVE_SIGNALFD)

# Check for clock_syscall
include(CheckCSourceCompiles)
check_c_source_compiles("
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
int main() {
    struct timespec ts;
    syscall(SYS_clock_gettime, CLOCK_REALTIME, &ts);
    return 0;
}
" HAVE_CLOCK_SYSCALL)

# Check for kernel_rwf_t
check_c_source_compiles("
#include <linux/fs.h>
int main() {
    kernel_rwf_t rwf;
    return 0;
}
" HAVE_KERNEL_RWF_T)

#find_library(EV_MULTIPLICITY pthread)
# Check for libraries
#find_library(HAVE_LIBRT rt)

# Package information
set(PACKAGE "libev")
set(PACKAGE_NAME "libev")
set(PACKAGE_VERSION "${PROJECT_VERSION}")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}")
set(PACKAGE_URL "http://software.schmorp.de/pkg/libev.html")
set(PACKAGE_BUGREPORT "")
set(VERSION "${PROJECT_VERSION}")

# Check for standard C headers
include(CheckIncludeFiles)
CHECK_INCLUDE_FILES("stdlib.h;stdarg.h;string.h;float.h" STDC_HEADERS)

# Additional system-specific settings
if(UNIX AND NOT STDC_HEADERS)
  set(STDC_HEADERS 1)
endif()
