#define ERROR_TEXT_COLOR "\x1b[31m"
#define ERROR_WARNING_COLOR "\x1b[33m"
#define ERROR_INFO_COLOR "\x1b[34m"
#define ERROR_RESET_COLOR "\x1b[m"

typedef enum {
  QUEUE_EMPTY
} Queue_errors;

void Queue_print_error (char* type, char* message, char* solution) {
  printf(ERROR_TEXT_COLOR "%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}


void Queue_print_warning (char* type, char* message, char* solution) {
  printf(ERROR_WARNING_COLOR "%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}


void Queue_print_info (char* type, char* message, char* solution) {
  printf(ERROR_INFO_COLOR "%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}

void Queue_error (Queue_errors error_code) {
  switch (error_code) {
    case QUEUE_EMPTY:
      Queue_print_warning("Logical Error", "The queue is empty. You cannot get/set an element in an empty list.", "Try adding an element to the queue before trying to get/set an element.");
      break;
}
}