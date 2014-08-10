#include "tests.h"

#include "sstring.h"
#include <string.h>
#include <ctype.h>

#include "stdio.h"


int
test_sstring_allocation(void)
{
	SString test = (SString){0,0,0};
	test = new_sstring(NULL,0);
	if(test.size != 0 || test.length != 0 || test.string != NULL)
		return -1;

	char* temp = "something";
	test = new_sstring(temp,0);
	if(test.size != strlen(temp)+1 || test.length != strlen(temp) || test.string == NULL || strcmp(test.string,temp))
		return -2;

	free_sstring(&test);
	if(test.size != 0 || test.length != 0 || test.string != NULL)
		return -3;

	test = new_sstring(NULL,2);
	if(test.size != 2 || test.length != 0 || test.string == NULL || test.string[0] != '\0')
		return -4;
	free_sstring(&test);

	char* temp2 = "another longer test string";
	test = new_sstring(temp2,10);
	if(test.size != 10 || test.length != 9 || test.string == NULL || strncmp(test.string,temp2,9))
		return -5;
	free_sstring(&test);

	return 0;
}

bool test_to_lower_sstring_helper(const char* input, const char* output)
{
	SString test = new_sstring(input,0);
	SString lowerstring = to_lower_sstring(&test);

	if(output != NULL) {
		if(strcmp(output,lowerstring.string))
			return true;
	} else {
		if(lowerstring.string != NULL)
			return true;
	}


	free_sstring(&test);
	free_sstring(&lowerstring);
	return false;
}

int test_to_lower_sstring()
{
	if(test_to_lower_sstring_helper("tEsTiNg","testing"))
		return -1;
	if(test_to_lower_sstring_helper("TESTING","testing"))
		return -2;
	if(test_to_lower_sstring_helper("testing","testing"))
		return -3;
	if(test_to_lower_sstring_helper(NULL,NULL))
		return -4;
	if(test_to_lower_sstring_helper("",""))
		return -5;
	return 0;
}

bool test_to_upper_sstring_helper(const char* input, const char* output)
{
	SString test = new_sstring(input,0);
	SString upperstring = to_upper_sstring(&test);

	if(output != NULL) {
		if(strcmp(output,upperstring.string))
			return true;
	} else {
		if(upperstring.string != NULL)
			return true;
	}

	free_sstring(&test);
	free_sstring(&upperstring);
	return false;
}

int test_to_upper_sstring()
{
	if(test_to_upper_sstring_helper("tEsTiNg","TESTING"))
		return -1;
	if(test_to_upper_sstring_helper("TESTING","TESTING"))
		return -2;
	if(test_to_upper_sstring_helper("testing","TESTING"))
		return -3;
	if(test_to_upper_sstring_helper(NULL,NULL))
		return -4;
	if(test_to_upper_sstring_helper("",""))
		return -5;
	return 0;
}

bool test_copy_sstring_helper(const char* string)
{
	SString output = (SString){0,0,0};
	SString input = new_sstring(string,0);
	if(copy_sstring(&output,&input) == -1)
		return true;
	if(strcmp(output.string,string))
		return true;
	free_sstring(&output);
	free_sstring(&input);
	return false;
}

int test_copy_sstring()
{
	SString temp;
	if(copy_sstring(NULL,NULL) != -1)
		return -1;
	if(copy_sstring(&temp, NULL) != -1)
		return -2;
	if(test_copy_sstring_helper(""))
		return -3;
	if(test_copy_sstring_helper("test"))
		return -4;
	temp = new_sstring(NULL,100);
	const char* inputStr = "some short string";
	SString input = new_sstring(inputStr,0);
	if(copy_sstring(&temp,&input) == -1 || strcmp(temp.string,inputStr) || temp.size != 100 || temp.length != strlen(inputStr))
		return -5;
	
	free_sstring(&temp);
	free_sstring(&input);		
	return 0;
}

bool test_all_sstring_functions()
{
	int allocation_failcode = test_sstring_allocation();
	if(allocation_failcode)
		printf("failed allocation test with: %i \n", allocation_failcode);
	else
		printf("allocation tests succeeded \n");

	int to_lower_failcode = test_to_lower_sstring();
	if(to_lower_failcode)
		printf("failed to_lower test with: %i \n", to_lower_failcode);
	else
		printf("to lower tests succeeded \n");

	int to_upper_failcode = test_to_upper_sstring();
	if(to_upper_failcode)
		printf("failed to_upper test with: %i \n", to_upper_failcode);
	else
		printf("to upper tests succeeded \n");

	int copy_failcode = test_copy_sstring();
	if(copy_failcode)
		printf("failed copy test with: %i \n", copy_failcode);
	else
		printf("copy test succeeded \n");

	return (!allocation_failcode && !to_lower_failcode && !to_upper_failcode && !copy_failcode);
}
