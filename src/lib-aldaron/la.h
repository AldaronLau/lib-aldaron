/*
 * Lib Aldaron(c) Jeron A. Lau
*/

#ifndef LIB_ALDARON_H
#define LIB_ALDARON_H

#include <stdint.h>
#include "clump.h" // LibClump
#include "SDL_thread.h"

//Platform Declarations
#define JL_PLAT_COMPUTER 0 //PC/MAC
#define JL_PLAT_PHONE 1 //ANDROID/IPHONE
#define JL_PLAT_GAME 2 // 3DS
#if defined(__ANDROID__)
        #define JL_PLAT JL_PLAT_PHONE
	#define JL_PHONE
	#define JL_PHONE_ANDROID
#elif defined(__IPHONEOS__)
        #define JL_PLAT JL_PLAT_PHONE
	#define JL_PHONE
	#define JL_PHONE_APPLE
#else
        #define JL_PLAT JL_PLAT_COMPUTER
	#define JL_COMPUTER
#endif

//Determine Which OpenGL to use.

#define JL_GLTYPE_NO_SPRT 0 // No Support for OpenGL
// GLES version 2
#define JL_GLTYPE_SDL_GL2 1 // Include OpenGL with SDL
#define JL_GLTYPE_OPENGL2 2 // Include OpenGL with glut.
#define JL_GLTYPE_SDL_ES2 3 // Include OpenGLES 2 with SDL
#define JL_GLTYPE_OPENES2 4 // Include OpenGLES 2 standardly.
// Newer versions...

#define JL_GLTYPE JL_GLTYPE_NO_SPRT

// Platform Capabilities.
#if JL_PLAT == JL_PLAT_COMPUTER
	// All Linux Platforms
	#undef JL_GLTYPE
	#define JL_GLTYPE JL_GLTYPE_SDL_ES2
	// Windows
	// #define JL_GLTYPE JL_GLTYPE_SDL_GL2
#elif JL_PLAT == JL_PLAT_PHONE
	#undef JL_GLTYPE
	#define JL_GLTYPE JL_GLTYPE_SDL_ES2
#else
	#error "NO OpenGL support for this platform!"
#endif

//ERROR MESSAGES
typedef enum{
	JL_ERR_NERR, //NO ERROR
	JL_ERR_NONE, //Something requested is Non-existant
	JL_ERR_FIND, //Can not find the thing requested
	JL_ERR_NULL, //Something requested is empty/null
}jl_err_t;

typedef enum{
	JL_THREAD_PP_AA, // Push if acceptable
	JL_THREAD_PP_UA, // Push if acceptable, & make unacceptable until pull. 
	JL_THREAD_PP_FF, // Push forcefully.
	JL_THREAD_PP_UF, // Push forcefully, and make unacceptable until pull
}jl_thread_pp_t;

typedef struct{
	float x, y, z;
}jl_vec3_t;

typedef struct{
	float x, y, z, w;
}jl_vec4_t;

//4 bytes of information about the string are included
typedef struct{
	uint8_t* data; //Actual String
	uint32_t size; //Allocated Space In String
	uint32_t curs; //Cursor In String
}data_t;

typedef struct{
	/** Library Context **/
	void* jl;
	/** Mutex **/
	SDL_mutex* mutex;
#if JL_DEBUG
	/** Thread **/
	uint8_t thread_id;
#endif
}jl_mutex_t;

// Thread-Protected Variable
typedef struct{
	void* jl;
	jl_mutex_t lock;	/** The mutex lock on the "data" */
	void* data;		/** The data attached to the mutex */
	size_t size;		/** Size of "data" */
}jl_pvar_t;

// Thread-Wait Variable
typedef struct{
	SDL_atomic_t wait;
}jl_wait_t;

//Standard Mode Class
typedef struct {
	void* init;
	void* loop;
	void* kill;
}jl_mode_t;

// Thread-Specific context.
typedef struct{
	SDL_Thread* thread;
	SDL_threadID thread_id;

	struct {
		int8_t ofs2;
		char stack[50][30];
		uint8_t level;
	}print;

	void* temp_ptr;
}jl_ctx_t;

typedef struct{
	struct {
		uint8_t graphics; //graphics are enabled
		uint8_t fileviewer; //Fileviewer is enabled
		uint8_t filesys; // Filesystem is enabled.
		uint8_t input; // Input is enabled.
		uint8_t quickloop; // Quickloop is enabled
	}has;
	struct{
		void* printfn; // Function for printing
		uint8_t bkspc; // Backspace.
		jl_mutex_t mutex; // Mutex for printing to terminal
	}print;
	struct{
		double psec; // Seconds since last frame.
		double timer; // Time 1 frame ago started
	}time;
	struct {
		jl_mode_t *mdes; // Array Sizof Number Of Modes
		jl_mode_t prev; // Previous Mode Data
		jl_mode_t mode; // Current Mode Data
		uint16_t which;
		uint16_t count;
		uint8_t changed;
	}mode;
	struct {
		struct{
			char* root; // The root directory "-- JL_Lib/"
			char* cprg; // The current program "-- JL_Lib/program"
			char* errf; // The error file "-- JL_Lib/errf.txt"
		}paths; // Paths to different files.

		data_t separator;
	}fl;
	void* loop; // The main loop.
	char* name; // The name of the program.
	uint32_t info; // @startup:# images loaded from media.zip.Set by others.
	jl_err_t errf; // Set if error
	//
	uint8_t mode_switch_skip;
	//
	jl_ctx_t jl_ctx[16];
	jl_wait_t wait;
	// Program's context.
	void* prg_context;
	// Built-in library pointers.
	void* jlgr;
	void* jlau;
}jl_t;

typedef void(*jl_fnct)(jl_t* jl);
typedef void(*jl_data_fnct)(jl_t* jl, void* data);
typedef void(*jl_print_fnt)(jl_t* jl, const char * print);

void la_panic(jl_t* jl, const char* format, ...);
void la_dont(jl_t* jl);
void* la_context(jl_t* jl);
int32_t la_start(jl_fnct fnc_init, jl_fnct fnc_kill, const char* name,
	size_t ctx_size);

// "JLmem.c"
void *jl_mem(jl_t* jl, void *a, uint32_t size);
void *jl_memi(jl_t* jl, uint32_t size);
void *jl_mem_copy(jl_t* jl, const void *src, uint64_t size);
uint64_t jl_mem_tbiu(void);
void jl_mem_leak_init(jl_t* jl);
void jl_mem_leak_fail(jl_t* jl, const char* fn_name);
void jl_mem_clr(void* mem, uint64_t size);
void jl_mem_copyto(const void* src, void* dst, uint64_t size);
void jl_mem_format(char* rtn, const char* format, ... );
void jl_mem_format2(char* rtn, const char* format, ...);
uint32_t jl_mem_random_int(uint32_t a);
void *jl_mem_temp(jl_t* jl, void *mem);
double jl_mem_addwrange(double v1, double v2);
double jl_mem_difwrange(double v1, double v2);
void jl_mem_vec_add(jl_vec3_t* v1, const jl_vec3_t* v2);
void jl_mem_vec_sub(jl_vec3_t* v1, const jl_vec3_t v2);
uint32_t jl_mem_string_upto(const char* string, char chr);

// "JLdata_t.c"
void jl_data_clear(jl_t* jl, data_t* pa);
void jl_data_init(jl_t* jl, data_t* a, uint32_t size);
void jl_data_free(data_t* pstr);
void jl_data_mkfrom_str(data_t* a, const char* string);
void jl_data_mkfrom_data(jl_t* jl, data_t* a, uint32_t size, const void *data);
void jl_data_data(jl_t *jl, data_t* a, const data_t* b, uint64_t bytes);
void jl_data_merg(jl_t *jl, data_t* a, const data_t* b);
void jl_data_trunc(jl_t *jl, data_t* a, uint32_t size);
uint8_t jl_data_byte(data_t* pstr);
void jl_data_loadto(data_t* pstr, uint32_t varsize, void* var);
void jl_data_saveto(data_t* pstr, uint32_t varsize, const void* var);
void jl_data_add_byte(data_t* pstr, uint8_t pvalue);
void jl_data_delete_byte(jl_t *jl, data_t* pstr);
void jl_data_resize(jl_t *jl, data_t* pstr, uint32_t newsize);
void jl_data_insert_byte(jl_t *jl, data_t* pstr, uint8_t pvalue);
void jl_data_insert_data(jl_t *jl, data_t* pstr, const void* data, uint32_t size);
char* jl_data_tostring(jl_t* jl, data_t* a);
uint8_t jl_data_test_next(data_t* script, const char* particle);
void jl_data_read_upto(jl_t* jl, data_t* compiled, data_t* script, uint8_t end,
	uint32_t psize);

// "cl.c"
void jl_cl_list_alphabetize(struct cl_list *list);
void jl_clump_list_iterate(jl_t* jl, struct cl_list *list, jl_data_fnct fn);

// "JLmode.c"
void jl_mode_set(jl_t* jl, uint16_t mode, jl_mode_t loops);
void jl_mode_override(jl_t* jl, jl_mode_t loops);
void jl_mode_reset(jl_t* jl);
void jl_mode_switch(jl_t* jl, uint16_t mode);
void jl_mode_exit(jl_t* jl);

// "JLprint.c"
void jl_print_set(jl_t* jl, jl_print_fnt fn_);
void jl_print(jl_t* jl, const char* format, ... );
void jl_print_rewrite(jl_t* jl, const char* format, ... );
void jl_print_function(jl_t* jl, const char* fn_name);
void jl_print_return(jl_t* jl, const char* fn_name);
void jl_print_stacktrace(jl_t* jl);
#ifdef JL_DEBUG
	#define JL_PRINT_DEBUG(jl, ...) jl_print(jl, __VA_ARGS__)
#else
	#define JL_PRINT_DEBUG(jl, ...)
#endif

// "JLfile.c"
void jl_file_print(jl_t* jl, const char* fname, const char* msg);
uint8_t jl_file_exist(jl_t* jl, const char* path);
void jl_file_rm(jl_t* jl, const char* filename);
void jl_file_save(jl_t* jl, const void *file, const char *name, uint32_t bytes);
void jl_file_load(jl_t* jl, data_t* load, const char* file_name);
char jl_file_pk_save(jl_t* jl, const char* packageFileName,
	const char* fileName, void *data, uint64_t dataSize);
char* jl_file_pk_compress(jl_t* jl, const char* folderName);
void jl_file_pk_load_fdata(jl_t* jl, data_t* rtn, data_t* data,
	const char* file_name);
void jl_file_pk_load(jl_t* jl, data_t* rtn, const char *packageFileName,
	const char *filename);
uint8_t jl_file_dir_mk(jl_t* jl, const char* path);
struct cl_list * jl_file_dir_ls(jl_t* jl,const char* dirname,uint8_t recursive);
char* jl_file_get_resloc(jl_t* jl, const char* prg_folder, const char* fname);

// "JLthread.c"
uint8_t jl_thread_new(jl_t *jl, const char* name, SDL_ThreadFunction fn);
uint8_t jl_thread_current(jl_t *jl);
int32_t jl_thread_old(jl_t *jl, uint8_t threadnum);
void jl_thread_mutex_new(jl_t *jl, jl_mutex_t* mutex);
void jl_thread_mutex_lock(jl_mutex_t* mutex);
void jl_thread_mutex_unlock(jl_mutex_t* mutex);
void jl_thread_mutex_cpy(jl_t *jl, jl_mutex_t* mutex, void* src,
	void* dst, uint32_t size);
void jl_thread_pvar_init(jl_t* jl, jl_pvar_t* pvar, void* data, uint64_t size);
void* jl_thread_pvar_edit(jl_pvar_t* pvar);
void jl_thread_pvar_drop(jl_pvar_t* pvar, void** data);
void jl_thread_pvar_free(jl_pvar_t* pvar);
void jl_thread_wait(jl_t* jl, jl_wait_t* wait);
void jl_thread_wait_init(jl_t* jl, jl_wait_t* wait);
void jl_thread_wait_stop(jl_t* jl, jl_wait_t* wait);

// "JLsdl.c"
double jl_time_get(jl_t* jl);
double jl_sdl_timer(jl_t* jl, double* timer);
double jl_time_regulatefps(jl_t* jl, double* timer, uint8_t* on_time);

#endif