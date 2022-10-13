#include <fstream>
#include <libproc.h>
#include <pwd.h>
#include <unistd.h>

// g++ -fPIC -dynamiclib -arch arm64 dylib.cpp -o dummydylib_arm64.dylib
// g++ -fPIC -dynamiclib -arch x86_64 dylib.cpp -o dummydylib_x64.dylib
void initialize()
{
    std::ofstream fStream;

    pid_t pid; int ret;
    char fullpath[PROC_PIDPATHINFO_MAXSIZE];    

    pid = getpid();
    ret = proc_pidpath(pid, fullpath, sizeof(fullpath));
    uid_t euid = getuid();
    struct passwd *pw = getpwuid(euid);

    fStream.open("/tmp/dylib.log", std::ios_base::app);
    fStream << "Path:" << fullpath << std::endl;
    fStream << "User:" << pw->pw_name << std::endl;
    fStream << "PID:" << pid << std::endl;
    fStream << "UID:" << getuid() << std::endl;
    fStream << "EUID:" << geteuid() << std::endl;
    fStream << "GID:" << getgid() << std::endl;
    fStream.close();
}

extern "C" __attribute__ ((visibility("default"))) void* exec(void *data)
{
    initialize();
    return 0;
}

__attribute__ ((constructor)) void run()
{
    pthread_attr_t  attr;
    pthread_t       posixThreadID;
    int             returnVal;
    
    returnVal = pthread_attr_init(&attr);
    assert(!returnVal);
    returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    assert(!returnVal);
    
    pthread_create(&posixThreadID, &attr, &exec, NULL);
}
