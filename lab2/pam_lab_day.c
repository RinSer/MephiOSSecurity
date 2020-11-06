#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

/* expected hook, necessary to get module known */
PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
	return PAM_SUCCESS;
}

/* expected hook, lets authenticate only if the current weekday is included in parameter array */
PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags, int argc, const char **argv ) {

        if (argc < 1) 
        {
		printf("Weekdays numbered from 0 to 6 must be concatenated with | and passed as module parameter");
		return PAM_AUTH_ERR;
        }

	time_t t = time(NULL);
	struct tm *now = localtime(&t);

        // check all received weekdays
        char buff[256];
        strcpy(buff, argv[0]);
	char* token = strtok(buff, "|");
	while( token != NULL ) {
		if (atoi(token) == now->tm_wday)
                {
			printf("Have found weekday %d in configuration parameter!\n", now->tm_wday);
			return PAM_SUCCESS;
		}
		token = strtok(NULL, "|");
	}

	printf("Weekday %d is not included to authenticate!\n", now->tm_wday);

	return PAM_AUTH_ERR;
}
