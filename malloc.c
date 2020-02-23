#include <unistd.h>
#include <dlfcn.h>
#include<stdbool.h>
static int alloc = 0;
char str[100];
/* A utility function to reverse a string */
void reverse(char str[], int length) 
{ 
	int start = 0;
        char tmp;	
	int end = length -1; 
	while (start < end) 
	{ 
		tmp=*(str+start);
	       	*(str+start)=*(str+end);
	        *(str+end)=tmp;	
		start++; 
		end--; 
	} 
} 

// Implementation of itoa() 
char* itoa(int num, char* str, int base) 
{ 
	int i = 0; 
	bool isNegative = false; 

	/* Handle 0 explicitely, otherwise empty string is printed for 0 */
	if (num == 0) 
	{ 
		str[i++] = '0'; 
		str[i] = '\0'; 
		return str; 
	} 

	// In standard itoa(), negative numbers are handled only with 
	// base 10. Otherwise numbers are considered unsigned. 
	if (num < 0 && base == 10) 
	{ 
		isNegative = true; 
		num = -num; 
	} 

	// Process individual digits 
	while (num != 0) 
	{ 
		int rem = num % base; 
		str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
		num = num/base; 
	} 

	// If number is negative, append '-' 
	if (isNegative) 
		str[i++] = '-'; 

	str[i] = '\0'; // Append string terminator 

	// Reverse the string 
	reverse(str, i); 

	return str; 
} 



void *malloc(size_t size)
{
    static void *(*fptr)(size_t) = NULL;
    /* look up of malloc, only the first time we are here */
    if (fptr == NULL)
    {
        fptr = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
        if (fptr == NULL)
        {
            write(1,"dlsym error\n",sizeof("dlsym error\n"));
            return NULL;
        }
    }
    alloc++;
    char *allocptr = itoa(alloc,str,10);
    write(1,"malloc() called:",sizeof("malloc() called:"));
    write(1,allocptr,sizeof(allocptr));
    write(1,"\n",sizeof("\n"));
    char * byte = itoa(size,str,10);
    write(1,"Allocated ",sizeof("Allocated "));
    write(1,byte,sizeof(byte));
    write(1,"byte(s) in heap memory.\n",sizeof("byte(s) in heap memory.\n"));
    return (*fptr)(size); // Calling original malloc
}

void free(void *ptr)
{
    static void (*fptr)(void *) = NULL;
    /* look up of free, only the first time we are here */
    if (fptr == NULL)
    {
        fptr = (void (*)(void *))dlsym(RTLD_NEXT, "free");
        if (fptr == NULL)
        {
            write(1,"dlsym error\n",sizeof("dlsym error\n"));
            return;
        }
    }
    write(1,"Our Free\n",sizeof("Our Free\n"));
    (*fptr)(ptr); // Calling original Free
    return;
}

