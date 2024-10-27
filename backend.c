#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <microhttpd.h>

#define PORT 8080

enum MHD_Result send_response(struct MHD_Connection *connection, const char *data, int status_code) {
    struct MHD_Response *response;
    enum MHD_Result ret;

    response = MHD_create_response_from_buffer(strlen(data), (void*) data, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);
    return ret;
}

enum MHD_Result handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") == 0) {
        const char *name = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "name");
        const char *accountNumber = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "accountNumber");
        const char *balance = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "balance");

        char formattedString[1024];
        snprintf(formattedString, sizeof(formattedString), "Name:%s|AccountNumber:%s|Balance:%s", name, accountNumber, balance);
        
        // Send formatted string to COBOL (assuming a function sendToCOBOL exists)
        // sendToCOBOL(formattedString);

        return send_response(connection, formattedString, MHD_HTTP_OK);
    }
    return send_response(connection, "Invalid request", MHD_HTTP_BAD_REQUEST);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar(); // Keep the server running
    MHD_stop_daemon(daemon);
    return 0;
}
