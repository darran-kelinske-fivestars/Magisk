#include <magisk.h>
#include <selinux.h>

constexpr char magiskrc[] =
"\n"

"on post-fs-data\n"
"    start logd\n"
"    load_persist_props\n"
"    rm " UNBLOCKFILE "\n"
"    start %s\n"
"    wait " UNBLOCKFILE " 10\n"
"    rm " UNBLOCKFILE "\n"
"\n"

"service %s /sbin/magisk --post-fs-data\n"
"    user root\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"service %s /sbin/magisk --service\n"
"    class late_start\n"
"    user root\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"on property:sys.boot_completed=1\n"
"    start %s\n"
"\n"

"service %s /sbin/magisk --boot-complete\n"
"    user root\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n\n"
"#Check if chargermode and start autoreboot service.\n"
"on property:ro.bootmode=charger\n"
"    touch /data/wegothere\n"
"    start autoreboot\n"
"\n"
"service autoreboot /system/bin/reboot\n"
"    user root\n"
"    oneshot"

"\n"
;
