#include <crtdbg.h>
#include <stdio.h>
#include <windows.h>

#ifdef PXWC_MEMORY_PROFILER

static int __debug_crt_indicator__ = 0;

/* Some grey theory ;o): the only thing, thats called *before* main
 * and *after* runtime initialization are the constructors of globals.
 * this means, that in the constructor of a global object one can set
 * runtime features, theoretically ;o) */

class __pxwc_set_memory_debug_class {
public:
	__pxwc_set_memory_debug_class();
	~__pxwc_set_memory_debug_class();
	void __Statistics();
	void __StatisticsLast();
	void __DetectLeak();
private:
	_CrtMemState _StartState;
	_CrtMemState _LastState;
	char * _ModuleName;
};

__pxwc_set_memory_debug_class::__pxwc_set_memory_debug_class() {
	_ModuleName = (char*)_malloc_dbg(sizeof(char)*1024, _IGNORE_BLOCK, __FILE__, __LINE__);
	GetModuleFileName(GetModuleHandle(NULL), _ModuleName, 1024);

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath( _ModuleName, drive, dir, fname, ext );
	sprintf(_ModuleName, "%s%s", fname, ext);

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);

	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

	int DebugFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	DebugFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	_CrtSetDbgFlag(DebugFlags);

	fprintf(stderr, "\n=========================================================\n");
    fprintf(stderr, "PXWC: memory state before execution for %s:\n", _ModuleName);
	fprintf(stderr, "=========================================================\n");

	_CrtMemCheckpoint(&_StartState);
	_CrtMemCheckpoint(&_LastState);
	_CrtMemDumpStatistics(&_StartState);
}

void __pxwc_set_memory_debug_class::__Statistics() {
	fprintf(stderr, "\nPXWC: memory state between start and now for %s:\n", _ModuleName);

	_CrtMemCheckpoint(&_LastState);
	
	_CrtMemState DiffState;
	_CrtMemDifference(&DiffState, &_StartState, &_LastState);
	_CrtMemDumpStatistics(&DiffState);
}

void __pxwc_set_memory_debug_class::__StatisticsLast() {
	fprintf(stderr, "\nPXWC: memory state between last dump and now for %s:\n", _ModuleName);

	_CrtMemState DiffState;
	_CrtMemState NowState;

	_CrtMemCheckpoint(&NowState);
	_CrtMemDifference(&DiffState, &_LastState, &NowState);
	_CrtMemDumpStatistics(&DiffState);

	_CrtMemCheckpoint(&_LastState);
}

void __pxwc_set_memory_debug_class::__DetectLeak() {
	fprintf(stderr, "\nPXWC: current leak situation for %s:\n", _ModuleName);

	if(!_CrtDumpMemoryLeaks())
		fprintf(stderr, "No memory leaks found!\n");
}

__pxwc_set_memory_debug_class::~__pxwc_set_memory_debug_class()
{
	fprintf(stderr, "\n=========================================================\n");
    fprintf(stderr, "PXWC: memory state after execution for %s:\n", _ModuleName);
	fprintf(stderr, "=========================================================\n");

	_CrtMemCheckpoint(&_LastState);
	_CrtMemDumpStatistics(&_LastState);

	_CrtMemState DiffState;
	fprintf(stderr, "\nPXWC: memory difference from start to end for %s:\n", _ModuleName);
	_CrtMemDifference(&DiffState, &_StartState, &_LastState);
	_CrtMemDumpStatistics(&DiffState);
	
	__DetectLeak();
}

static __pxwc_set_memory_debug_class __pxwc_set_memory_debug_object;

extern "C" void __internal_pxwc_memory_dump() {
	__pxwc_set_memory_debug_object.__Statistics();
}

extern "C" void __internal_pxwc_memory_dump_positional() {
	__pxwc_set_memory_debug_object.__StatisticsLast();
}

extern "C" void __internal_pxwc_memory_leak() {
	__pxwc_set_memory_debug_object.__DetectLeak();
}

#endif

/* reference dummy */
extern "C" int __pxwc_set_memory_debug_class_reference_dummy() {
	return 0;	
}
