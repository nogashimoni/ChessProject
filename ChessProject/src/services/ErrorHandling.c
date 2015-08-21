#include "ErrorHandling.h"

void notifyFunctionFailure(char* failedFunction) {
	/* Prints an error message saying faildFunction has failed. failesFunction name should not exceed 74 chars.*/
	char error_msg[100];
	sprintf(error_msg, "ERROR: standard function %s has failed. Exiting.",
			failedFunction);
	perror(error_msg);
}
