#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>



#define MAX_LEN_LINE    100
#define LEN_HOSTNAME	30


int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
    char pwd[1024];
    int i;




    while (true) {

      char hostname[LEN_HOSTNAME + 1];
      memset(hostname, 0x00, sizeof(hostname));
      gethostname(hostname, LEN_HOSTNAME);

      char *s;
      int len;

      /* ls를 치지 않았을때 작동되지 않도록 args[0]를 초기화 */
      args[0] = command;


      /* pwd 구현 */
      getcwd(pwd, sizeof(pwd));


      /* 글씨 색깔과 현재 디렉토리가 계속 나오도록 구현 */
      printf("\033[1;33m%s@%s:\033[0m\033[1;34m%s\033[0m$ ", getpwuid(getuid())->pw_name, hostname, pwd);


      s = fgets(command, MAX_LEN_LINE, stdin);
      if (s == NULL) {
          fprintf(stderr, "fgets failed\n");
          exit(1);
      }


      len = strlen(command);
      printf("%d\n", len);
      if (command[len - 1] == '\n') {
          command[len - 1] = '\0';
      }


      /* exit 구현 */
      if(strncmp(command, "exit", strlen(command)) == 0){
        break;
      }


      /* pwd 구현 */
      if(strncmp(command, "pwd", strlen(command)) == 0){
        printf("%s\n", pwd);
      }


      /* ls 구현 */
      if(strncmp(command, "ls", strlen(command)) == 0){
        args[0] = "/bin/ls";
      }
      

      printf("[%s]\n", command);


      /* cd 구현 */
      if(command[0]=='c' && command[1]=='d' && command[2]==' '){
        for(i=0; i<=len+3; i++){
          command[i] = command[i+3];
        }
        chdir(command);
      }

      pid = fork();
      if (pid < 0) {
          fprintf(stderr, "fork failed\n");
          exit(1);
      }
      if (pid != 0) {  /* parent */
          cpid = waitpid(pid, &status, 0);
          if (cpid != pid) {
              fprintf(stderr, "waitpid failed\n");
          }
          printf("Child process terminated\n");
          if (WIFEXITED(status)) {
              printf("Exit status is %d\n", WEXITSTATUS(status));
          }
      }
      else {  /* child */
          ret = execve(args[0], args, NULL);
          if (ret < 0) {
              fprintf(stderr, "execve failed\n");
              return 1;
            }
          }
        }
        return 0;
      }
