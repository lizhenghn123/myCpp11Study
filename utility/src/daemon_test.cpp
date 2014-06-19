#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Server
{
public:
	void Start() { printf("Server Start\n"); }
	void Stop()  { printf("Server Stop\n"); }
};
Server *server = new Server;

#ifdef WIN32
#include <Windows.h>

#define WIN_SERVICE_NAME "WinServerDaemon"

static SERVICE_STATUS_HANDLE win_service_status_handle = NULL;
static SERVICE_STATUS win_service_status;

static const char *svcname = NULL;

/** Display error message with Windows error code and description */
static void winerror(const char *file, int line, const char *msg)
{
	char buf[128];
	DWORD err = GetLastError();
	int ret = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buf, sizeof(buf), NULL);
	printf("%s: %lu %.*s\n", msg, err, ret, buf);
}

/** SCM state change handler */
static void WINAPI win_service_handler(DWORD control)
{
	printf("Service Handler %d", control);
	switch (control)
	{
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_SHUTDOWN:
	case SERVICE_CONTROL_STOP:
		if (server)
		{
			win_service_status.dwCurrentState = SERVICE_STOP_PENDING;
			if (!SetServiceStatus(win_service_status_handle, &win_service_status))
			{
				winerror(__FILE__, __LINE__, "Failed to Set Service Status");
			}

			/* shutdown server */
			server->Stop();
		}
		win_service_status.dwCurrentState = SERVICE_STOPPED;
		win_service_status.dwCheckPoint = 0;
		win_service_status.dwWaitHint = 0;
		break;
	}

	if (!SetServiceStatus(win_service_status_handle, &win_service_status))
	{
		winerror(__FILE__, __LINE__, "Failed to Set Service Status");
		printf("Failed to Set Service Status\n");
	}
}

static void WINAPI win_service_main(DWORD argc, LPTSTR *argv)
{
	printf("Service Main\n");
	win_service_status.dwServiceType = SERVICE_WIN32;
	win_service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	win_service_status.dwWin32ExitCode = 0;
	win_service_status.dwServiceSpecificExitCode = 0;
	win_service_status.dwCheckPoint = 0;
	win_service_status.dwWaitHint = 0;

	win_service_status_handle = RegisterServiceCtrlHandler(svcname, win_service_handler);
	if (win_service_status_handle == (SERVICE_STATUS_HANDLE)0)
	{
		winerror(__FILE__, __LINE__, "Failed to Register Service Control Handler");
		return;
	}

	win_service_status.dwCurrentState = SERVICE_START_PENDING;
	if (!SetServiceStatus(win_service_status_handle, &win_service_status))
	{
		winerror(__FILE__, __LINE__, "Failed to Set Service Status");
	}

	/* start server */
	server->Start();
	printf("Run as Daemon Success\n");

	while (true)  Sleep(10000000);

	win_service_status.dwCurrentState = server ? SERVICE_RUNNING : SERVICE_STOPPED;
	if (!SetServiceStatus(win_service_status_handle, &win_service_status))
	{
		winerror(__FILE__, __LINE__, "Failed to Set Service Status");
	}
}

/** Run SCM service */
void WindowsServiceDaemon(const char *name)
{
	SERVICE_TABLE_ENTRY win_service_table[2];
	svcname = name ? name : WIN_SERVICE_NAME;
	memset(&win_service_table, 0, sizeof(win_service_table));
	win_service_table->lpServiceName = (LPSTR)svcname;
	win_service_table->lpServiceProc = win_service_main;

	printf("Run as Service Daemon : %s\n", svcname);
	if (!StartServiceCtrlDispatcher(win_service_table))
	{
		winerror(__FILE__, __LINE__, "Failed to Connect to SCM");
	}
}

#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define ERR_EXIT(m) do \
					{  \
					perror(m);  \
					exit(EXIT_FAILURE);  \
					}  \
										while (0);  

void LinuxServerDaemon()
{
	printf("Run as Daemon\n");

	time_t t;
	int fd;

	// 将当前进程变成守护进程
	if (daemon(1, 0) == -1) {
		perror("daomon error");
		exit(EXIT_FAILURE);
	}

	server->Start();
	printf("Run as Daemon Success\n");

	while (true)  sleep(10000000);
}
#endif

void RunServer(bool foreground)
{
	if (foreground == true)
	{
		printf("Run as foreground\n");
		server->Start();
	}
	else
	{
#ifdef WIN32
		/* run as windows service */
		WindowsServiceDaemon("MyTestDaemon");
#else
		/* run as daemon */
		LinuxServerDaemon();
#endif
	}
}

int main(int argc, char *argv[])
{
	RunServer(false);

	getchar();
	return 0;
}
