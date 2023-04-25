#define ERROR_TEXT_COLOR "\x1b[31m"
#define ERROR_WARNING_COLOR "\x1b[33m"
#define ERROR_INFO_COLOR "\x1b[34m"
#define ERROR_RESET_COLOR "\x1b[m"

typedef enum {
  MEM_ALLOC_ERROR, OUT_OF_BOUNDS, LIST_EMPTY, LIST_DESTROYED, PRINT_EMPTY_LIST
} LL_errors;

void LL_print_error (char* type, char* message, char* solution) {
  printf(ERROR_TEXT_COLOR "\n%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}


void LL_print_warning (char* type, char* message, char* solution) {
  printf(ERROR_WARNING_COLOR "\n%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}


void LL_print_info (char* type, char* message, char* solution) {
  printf(ERROR_INFO_COLOR "\n%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}

void LL_error (LL_errors error_code) {
  switch (error_code) {
    case MEM_ALLOC_ERROR:
      LL_print_error("Runtime Error", "Memory allocation using malloc failed.", "Try freeing up some memory.");
      break;
    case OUT_OF_BOUNDS:
      LL_print_warning("Logical Error", "Index out of bounds. You tried accessing an element past the end of the list or before the beginning of the list.", "Try checking the index that you are accessing.");
      break;
    case LIST_EMPTY:
      LL_print_warning("Logical Error", "The list is empty. You cannot get/set an element in an empty list.", "Try adding an element to the list (push, insert, etc.) before trying to get/set an element.");
      break;
    case LIST_DESTROYED:
      LL_print_error("Logical Error", "You tried access the list after it has been destroyed.", "Try creating a new list or check for unintended LL_destroy calls.");
      break;
    
    case PRINT_EMPTY_LIST:
      LL_print_info("You tried to print an empty list", "This message was printed to avoid unintended operations.", "Try adding an element to the list using push/unshift/insert or check for unintended calls to pop/shift/delete.");
      break;
    
}
}