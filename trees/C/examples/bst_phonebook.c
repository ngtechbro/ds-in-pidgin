/**
* bst_phonebook.c 
*
* Example use case for binary search tree in C.
*
* WTD: We go make the phone book to save contacts, edit contacts, and delete contacts.
* auto complete feature dey added to the editing and deleting operation.
*
* Author: NULL
* Date: 10/04/2025 
* i finish this stuff today May 6 2025. omohh TIME na b***ard!!
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "linenoise.h"

// here we wan conditionally include libraries for different OS based on the type of OS.
#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <limits.h>
#else
#error "Unknown platform! This code can only run on Windows, Linux, or macOS."
#endif

#define MAX_SUGGESTIONS 5

static const char *FILENAME = "phonebook_db.txt";   // name of our db file.
static int noOfContacts = 0;  // total number of contacts inside the db file.

/**
  * This function na to get the path wey you compile this code from.
  * Na for this path i wan create the file wey we wan use store the contacts.
  *
  * @param char *buffer Pointer to the buffer we wan write the path to.
  * @param size_t size The size of the buffer.
  */
char *get_executable_path(char *buffer, size_t size) {
  #if defined(_WIN32)
    GetModuleFileNameA(NULL, buffer, size);
    return "\\";
  #elif defined(__linux__)
    ssize_t len = readlink("/proc/self/exe", buffer, size - 1);
    if (len != -1) buffer[len] = '\0';
    return "/";
  #elif defined(__APPLE__)
    uint32_t bufsize = (uint32_t)size;
    _NSGetExecutablePath(buffer, &bufsize);
    return "/";
  #else // we fit no ever reach this block, but just incase haha!
    strncpy(buffer, "Unknown OS", size);
    return NULL;
  #endif
}


/**
  * This function na to add contact data to our tree from line wey we don read from our db file.
  * the tree na wetin we wan use hold all our contact data.
  *
  * @param TreeNode *root The root node of our tree.
  * @param char *line The line we read from file wey contain a particular contact details.
  *
  * @return TreeNode* Pointer to our tree root node.
  */
TreeNode *addDataToPhoneBookTree(TreeNode *root, char *line) {
  // strip lines by delimeter we use(|), so we fit get each data(name, email, number)
  const char *delim = "|";
  char *tokens[3];
  char *token = strtok(line, delim);
  int i = 0;
  while (token != NULL && i < 3) {
    tokens[i] = token;
    token = strtok(NULL, delim);

    i ++;
  }

  // use the data we don get to build our Contact struct
  TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
  if(node == NULL) {
    printf("Memory alloc for new contact node no gree work.\n");
    return NULL;
  }

  node->name = (char *) malloc(strlen(tokens[0]) + 1);
  node->email = (char *) malloc(strlen(tokens[1]) + 1);
  node->number = (char *) malloc(strlen(tokens[2]) + 1);
  if(node->name == NULL || node->email == NULL || node->number == NULL) {
    free(node->name);
    free(node->email);
    free(node->number);
    free(node);

    printf("Memory alloc for contact details no gree work.\n");
    return NULL;
  }

  snprintf(node->name, strlen(tokens[0]) + 1, "%s", tokens[0]);
  snprintf(node->email, strlen(tokens[1]) + 1, "%s",  tokens[1]);
  snprintf(node->number, strlen(tokens[2]) + 1, "%s", tokens[2]);

  // add the contact to the tree node.
  return insertNode(root, node);
}


/**
  * This function na to get the absolute path to where our db file dey.
  * if the fname arg dey passed, e go get the absolute path to the file wey dey specified by fname.
  *
  * @param char *fname Name of specified file we wan get absolute path for.
  *
  * @return The path to the db file or the specified file(if arg dey passed).
  */
char *getDBFilePath(char *fname) {
  char path[5120];
  char *realpath = malloc(5120);
  if(realpath == NULL) {
    printf("Malloc for DB path building no gree work.\n");
    exit(1);
  }

  const char *delim = get_executable_path(path, sizeof(path));

  // strip filename from path.
  char prevStr[2048];
  realpath[0] = '\0';
  strcat(realpath, delim);
  char *token = strtok(path, delim);
  int i = 0;
  while (token != NULL) {
    if(i > 0)
      strcat(realpath, strcat(prevStr, delim));
      
    strcpy(prevStr, token);
    token = strtok(NULL, delim);
 
    i ++;
  }

  // append file name
  if(fname != NULL)
    strcat(realpath, fname);
  else 
    strcat(realpath, FILENAME);

  return realpath;
}


/**
  * This function na to write line to our db file or a specified path.
  * This line na contact details wey we don format so we fit store and retrieve effectively.
  *
  * @param char *line The line wey we wan write to the file.
  * @param char *optPath Optional file name we wan write the line to.
  *
  * @return int 0 if any error occur, 1 if we write successfully.
  */
int addLineToDBFile(char *line, char *optPath) {
  char *path = optPath == NULL ? getDBFilePath(NULL) : getDBFilePath(optPath);

  FILE *file = fopen(path, "a");
  if(file == NULL) {
    printf("DB file no gree open.\n");
    return 0;
  }

  if(fputs(line, file) == EOF) {
    printf("Writing to DB file no work.\n");
    fclose(file);
    return 0;
  }

  fclose(file);

  return 1;
}


/**
  * This function na to read line from our db file to a buffer.
  *
  * @param long *pos Pointer to the seek position of the file reader.
  * @param size_t *len Pointer to the length of the line we wan read from the file.
  * @param FILE *file Pointer to the file we wan read the line from.
  * @param char **buffer Pointer to the pointer of the buffer we wan read to.
  * @1para size_t *buffer_size Pointer to the size of the buffer.
  * @param int contactLoad This na to help us know if we dey read to load contact or we dey read to delete contact.
  *
  * @return int 1 if reading from the file no work, 2 if size of buffer dey less than the size of the line to read.
  */
int readFileLine(long *pos, size_t *len, FILE *file, char **buffer, size_t *buffer_size, int contactLoad) {
  *pos = ftell(file);

  // try read line from the file.
  if(fgets(*buffer, *buffer_size, file) == NULL) {
    if(!feof(file))
      printf("Attempt to read the database file no work.\n");
    else if(contactLoad == 1 && feof(file) && noOfContacts >= 0)
      printf("Loaded %d %s.\n", noOfContacts, noOfContacts > 1 ? "Contacts" : "Contact");
    else if(contactLoad == 1)
      printf("DB file empty.\n");

    return 1;
  }

  *len = strlen(*buffer);
  if((*buffer)[*len - 1] != '\n' && !feof(file)) {
    *buffer_size *= 2;
    char *tmp = (char *) realloc(*buffer, *buffer_size);
    if(tmp == NULL) {
      printf("Memory realloc no gree work for buffer.\n");
      fclose(file);
      free(*buffer);
      exit(1);
    }

    *buffer = tmp;
    (*buffer)[0] = '\0';   // clear partial data wey dey the buffer

    // jump back to prev pos for re reading
    fseek(file, *pos, SEEK_SET);

    return 2;
  }

  return 0;
}


/**
  * This function na to load contact from file to our tree.
  *
  * @param TreeNode *root Pointer to the root node of the tree.
  *
  * @return TreeNode* Pointer to the root node of the tree.
  */
TreeNode *loadContacts(TreeNode *root) {
  char *path = getDBFilePath(NULL);

  FILE *file = fopen(path, "r");
  if(file == NULL) {
    printf("No phone book database file found, creating...\n");
    file = fopen(path, "w");
    if(file == NULL) {
      printf("I try create the database file, but e no work.\n");
      exit(1);
    }
    
    printf("Phone book database file created.\n");

    fclose(file);

    return root;
  }

  // read already saved contacts.
  size_t buffer_size = 100;
  char *buffer = (char *) malloc(buffer_size);
  if(buffer == NULL) {
    printf("Memory alloc no gree work for buffer.\n");
    fclose(file);
    exit(1);
  }

  size_t len = 0;
  long pos;
  while(1) {
    int readLineStatus = readFileLine(&pos, &len, file, &buffer, &buffer_size, 1);
    if(readLineStatus == 1)
      break;
    else if(readLineStatus == 2)
      continue;

    noOfContacts ++;

    root = addDataToPhoneBookTree(root, buffer);

    len = 0;
    buffer[0] = '\0';
  }

  fclose(file);
  free(buffer);

  return root;
}


/**
  * This function na to edit or delete contact from our tree node, and our file.
  *
  * @param TreeNode *root The root node of our tree wey hold the contacts.
  * @param char *name The name of the contact we wan delete.
  * @param char *editLine If e no dey null, the func go know say na for edit. Else, na for delete.
  */
void editOrDeleteContact(TreeNode *root, char *name, char *editLine) {
  // delete record from file
  FILE *file = fopen(getDBFilePath(NULL), "r");
  if(file == NULL) {
    printf("I try open the database file, but e no work.\n");
    exit(1);
  }

  // read already saved contacts.
  size_t buffer_size = 100;
  char *buffer = (char *) malloc(buffer_size);
  if(buffer == NULL) {
    printf("Memory alloc no gree work for buffer.\n");
    fclose(file);
    exit(1);
  }

  size_t len = 0;
  long pos;
  while(1) {
    int readLineStatus = readFileLine(&pos, &len, file, &buffer, &buffer_size, 0);
    if(readLineStatus == 1)
      break;
    else if(readLineStatus == 2)
      continue;

    char *tmp = (char *) malloc(buffer_size);
    if(tmp == NULL) {
      printf("Memory alloc no gree work for temp.\n");
      fclose(file);
      free(buffer);
      exit(1);
    }

    strcpy(tmp, buffer);
    char *token = strtok(tmp, "|");
    char *dbName = malloc(strlen(token) + 1);
    snprintf(dbName, strlen(token) + 1, "%s", token);
    
    free(tmp);

    if(strcmp(dbName, name) != 0)
      addLineToDBFile(buffer, "tmp_db.txt");
    else if(strcmp(dbName, name) == 0 && editLine != NULL)
      addLineToDBFile(editLine, "tmp_db.txt");

    len = 0;
    buffer[0] = '\0';
  }

  remove(getDBFilePath(NULL));
  rename(getDBFilePath("tmp_db.txt"), getDBFilePath(NULL));

  // delete record from tree node
  if(editLine == NULL) {
    deleteNode(root, name);
    noOfContacts --;

    printf("Contact deleted!\n");
  }

  fclose(file);
  free(buffer);
}


/**
  * This function nat to print out all contacts wey dey our tree.
  *
  * @param TreeNode *root Pointer to the root node of tree where the contacts dey saved.
  */
void printContacts(TreeNode *root) {
  if(root == NULL) {
    printf("Sorry boss! contact no dey to show\n");
    return;
  }

  if(root->left != NULL)
    printContacts(root->left);

  if(root->email != NULL && root->number != NULL)
    printf("| %-14s | %-20s | %-13s |\n", root->name, root->email, root->number);

  if(root->right != NULL)
    printContacts(root->right);
}


/**
  * This function na to free all contact data and nodes wey dey our tree.
  *
  * @param TreeNode *root Pointer to the root node of the tree.
  */
void freeTree(TreeNode *root) {
  if (root == NULL)
    return;

  // we go first free left and right subtrees
  freeTree(root->left);
  freeTree(root->right);

  // Then we go free the node itself and all mem contents.
  free(root->name);
  free(root->email);
  free(root->number);
  free(root);
}


/**
  * This function na to clear the terminal.
  * e no dey necessarily clear am, but e dey clear am. (find out wetin i mean by yourself lol).
  */
void clearTerminal() {
  printf("\033[2J\033[H");
  fflush(stdout);
}

/**
* These variables here na global variables, and na wetin we go use wire up our auto completion feature.
* @param int operationId - This phone book get many operations. we get add, delete, edit, etc. But no be for all these operations we need autocompletion,
*                           so this variable go dey set to 3 from within any scope to show say we need autocompletion feature turned on.
*                           No ask why i choose 3, i no know why i choose 3, i for choose 7(no ask why), but i just choose 3.
* @param int suggestionCount - This var na to show how many suggestions we don get so far. We limit our phonebook app to just 5 suggestions, so we need a way to track.
* @param TreeNode *autocompleteNode - This pointer na to hold address of any root node wey fall inside any scope we need the autocomplete feature.
*                                     We need this pointer inside global scope because the lib i dey use for auto complete dey use callback func wey dey global scope.
* @param char **acSuggestions - This na where we dey store all suggestions, remember say we limit am to just 5.
*/
static int operationId = 0, suggestionCount = 0;
TreeNode *autocompleteNode = NULL;
char **acSuggestions;


/**
  * This function na to carry our auto complete suggestion array pointer (@param **acSuggestions), and all the containing(remember say na 5) suggestions pointer allocate memory to them.
  *
  * @param char ***acSuggestions Pointer to our array of suggestions.
  */
void initAutoCompletions(char ***acSuggestions) {
  *acSuggestions = malloc(MAX_SUGGESTIONS * sizeof(char *));   // we need 5 suggestions.
  if(*acSuggestions == NULL) {
    printf("Memory alloc no gree work for suggestions");

    exit(1);
  }

  for(int i = 0; i < MAX_SUGGESTIONS; i ++) {
    (*acSuggestions)[i] = malloc(1);  // allocate for each of them.

    // if any allocation fail, clear all previously allocated.
    if((*acSuggestions)[i] == NULL) {
      printf("Memory alloc no gree work for suggestion item\n");

      if(i > 0)
        for(int j = i - 1; j >= 0; j --) {
          free((*acSuggestions)[j]);
        }

      free(*acSuggestions);
      exit(1);
    }
  }
}


/**
  * This function na to traverse from our root node, dey check for all child node wey the name start with our prefix.
  * If we get any one, we dey add am to the array wey dey hold all suggestions.
  *
  * @param char ***s pointer to our array of suggestions.
  * @param TreeNode **root Pointer to root node we wan start dey traverse from.
  * @1param char *prefix Our prefix.
  */
void fillSuggestions(char ***s, TreeNode **root, const char *prefix) {
  if (*root == NULL) {
    return;
  }

  // collect suggestions if e match our prefix.
  if(strncmp((*root)->name, prefix, strlen(prefix)) == 0) {

    // we must respect our limit for suggestions.
    if(suggestionCount < MAX_SUGGESTIONS) {
      snprintf((*s)[suggestionCount], strlen((*root)->name) + 1, "%s", (*root)->name);
      suggestionCount ++;
    }
  }

  fillSuggestions(s, &(*root)->left, prefix);  // Go left
  fillSuggestions(s, &(*root)->right, prefix); // Go right
}


/**
  * This function na the callback we go use implement all our autocomplete thing.
  * i dey use linenoise lib:
  * @see https://github.com/antirez/linenoise
  */
void completion(const char *buf, linenoiseCompletions *lc) {
  // if our operation id na 3, we need the autocomplete feature.
  if(operationId == 3) {
    initAutoCompletions(&acSuggestions);

    fillSuggestions(&acSuggestions, &autocompleteNode, buf);

    if(suggestionCount > 0) {
      for(int i = 0; i < suggestionCount; i ++) {
        linenoiseAddCompletion(lc, acSuggestions[i]);
      }
    }

    suggestionCount = 0;
  }
}


/**
  * This func na to display our hint, so users go know say them go get auto complete feature if them click tab.
  * na still part of the linenoise thing.
  * @see https://github.com/antirez/linenoise
  */
char *hints(const char *buf, int *color, int *bold) {
  if (operationId == 3 && strlen(buf) % 3 == 0) {
    *color = 35;
    *bold = 0;
    return " dey press tab make you fit see autocomplete suggestions.";
  }

  return NULL;
}


/**
  * This function na to use linenoise get input from user.
  * 
  * @param char **line Pointer to the buffer we wan use get input.
  * @param char *prompt Point wey we wan show at left side before cursor input.
  * @param int allowEmpty Wether we wan allow user to submit empty input or not(0 for no, 1 for yes).
  *
  * @return int -1 if the user dey terminate this input. ie: if them click CTRL + C or so.
  *             0 if we no get any input.
  *             1 if our setup get the input dey okay.
  */
int inputLine(char **line, char *prompt, int allowEmpty) {
  *line = linenoise(prompt);

  if(*line == NULL)
    return -1;

  if(strlen(*line) <= 0 && allowEmpty == 0) {
    printf("This input no valid.\n");

    return 0;
  }

  return 1;
}


int main() {
  TreeNode *root = NULL;
  root = loadContacts(root);

  linenoiseSetHintsCallback(hints); // call callback func to set hint.
  linenoiseSetCompletionCallback(completion); // call callback func to setup the auto completion.

  while(1) {
    printf("\n\n");
    printf("*******************************************************************************\n");
    printf("*             Tuale Boss!! See available options wey dey:                     *\n");
    printf("*******************************************************************************\n");
    printf("* 1. Create new contact\n");
    printf("* 2. Edit contact.\n");
    printf("* 3. Delete contact.\n");
    printf("* 4. Print all contacts.\n");
    printf("* 0. Exit.\n");
    printf("*******************************************************************************\n");
    printf("* Total contacts: %d\n", noOfContacts);
    printf("*******************************************************************************\n");

    printf("\nEnter your option: \n");

    char *line;
    int inputStatus = inputLine(&line, "PB >> ", 0);
    if (inputStatus == -1) break;
    else if(inputStatus == 0) continue;
    else {
      char *end;
      int option = (int) strtol(line, &end, 10);
      switch (option) {
        int nStatus, eStatus, noStatus;
        char *name, *email, *number;
        TreeNode *searchedNode;

        case 0:
          printf("Exiting program...\n");

          if(line)  free(line);
          if(acSuggestions) free(acSuggestions);
          if(root)  freeTree(root);

          return 0;
        case 1:
          // get name
          nStatus = inputLine(&name, "Enter contact full name >> ", 0);
          if(nStatus <= 0) break;

          // get email
          eStatus = inputLine(&email, "Enter contact email >> ", 0);
          if(eStatus <=0) break;
 
          // get number
          noStatus = inputLine(&number, "Enter contact number >> ", 0);
          if(noStatus <= 0) break;

          char line[250];
          line[0] = '\0';

          // write name, email and number
          snprintf(line, sizeof(line), "%s|%s|%s|\n", name, email, number);

          int wStatus = addLineToDBFile(line, NULL);

          if(wStatus == 0)
            printf("Writing to DB file no gree work.\n");

          root = addDataToPhoneBookTree(root, line);
          noOfContacts ++;

          clearTerminal();
          printf("\n Contact don dey added successfully!\n");

          // free linenoise pointers.
          free(name);
          free(email);
          free(number);
          break;
        case 2:
          operationId = 3;  // update operation id number.
          autocompleteNode = root;

          // get name
          nStatus = inputLine(&name, "Enter name of contact you wan edit >> ", 0);
          if(nStatus <= 0) break;

          searchedNode = search(root, name);
          if(searchedNode == NULL) {
            printf("Contact name no dey found.");
          }
          else {
            char *editedName; // to store edited name
            // collect new name
            nStatus = inputLine(&editedName, "New name(press enter make you retain the old value) >> ", 1);
            if(nStatus < 0)  break;

            // collect new email
            eStatus = inputLine(&email, "New email(press enter make you retain the old value) >> ", 1);
            if(eStatus < 0)  break;

            // collect new phone number
            noStatus = inputLine(&number, "New number(press enter make you retain the old value) >> ", 1);
            if(noStatus < 0)  break;

            if(strlen(editedName) > 0)
              snprintf(searchedNode->name, strlen(editedName) + 1, "%s", editedName);
            if(strlen(email) > 0)
              snprintf(searchedNode->email, strlen(email) + 1, "%s", email);
            if(strlen(number) > 0)
              snprintf(searchedNode->number, strlen(number) + 1, "%s", number);

            // build file line
            char editedLine[250];
            editedLine[0] = '\0';

            // write name, email and number
            snprintf(editedLine, sizeof(editedLine), "%s|%s|%s|\n", searchedNode->name, searchedNode->email, searchedNode->number);

            editOrDeleteContact(NULL, name, editedLine);

            // updated!!
            printf("Contact don dey edited.\n");

            free(editedName);
          }

          operationId = 0;  // reset operation id number.

          free(name);
          free(email);
          free(number);
          break;
        case 3:
          operationId = 3;  // delete operation id number.
          autocompleteNode = root;

          // get name
          int deleteNameStatus = inputLine(&name, "Enter name of contact you wan delete >> ", 0);

          if(deleteNameStatus <= 0) break;

          searchedNode = search(root, name);
          if(searchedNode != NULL)
            editOrDeleteContact(root, name, NULL);
          else
            printf("no contact to delete\n");

          operationId = 0;  // reset operation id number.

          free(name);
          break;
        case 4:
          clearTerminal();

          // Table top border
          printf("+----------------+----------------------+---------------+\n");
          printf("| Name           | Email                | Phone         |\n");
          printf("+----------------+----------------------+---------------+\n");

          // Table rows
          printContacts(root);

          // Table Bottom border
          printf("+----------------+----------------------+---------------+\n");

          break;
        default:
          printf("\n\nThe option wey you enter no dey make sense boss.\n\n");
          break;
      }
    }
    
    free(line);
  }

  free(acSuggestions);
  freeTree(root);

  return 0;
}
