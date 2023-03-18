#ifndef ADAPTARRAY_H
#define ADAPTARRAY_H
typedef struct AdptArray_* PAdptArray;
typedef enum  {FAIL = 0, SUCCESS=1} Result;
typedef void* PElement;

typedef void(*DEL_FUNC)(PElement);
typedef PElement(*COPY_FUNC)(PElement);
typedef void(*PRINT_FUNC)(PElement);

PAdptArray CreateAdptArray(COPY_FUNC, DEL_FUNC,PRINT_FUNC);
void DeleteAdptArray(PAdptArray head);
Result SetAdptArrayAt(PAdptArray head, int index, PElement element);
PElement GetAdptArrayAt(PAdptArray, int);
int GetAdptArraySize(PAdptArray head);
void PrintDB(PAdptArray head);
#endif