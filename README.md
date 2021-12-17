# toy-shell

I added the following funcions
-> ls, cd, pwd, exit, Text Color, user, name

1. ls -> I created the ls command through strncmp, args and "/bin/ls"

if you press 'ls', it displays folders and files in the current directory.
  'args[0] = command' was added so that the current file would not be output when ls was not typed.

2. cd -> I created the cd command through chdir function
  Press cd 'Folder name' to go to the high directory, press cd .. to go to the low directory.

3. pwd -> I created the pwd command through strncmp and getcwd function

I used pwd to keep the current directory visible next to the hostname looking like the existing shell.
  if you press 'pwd', it displays the current directory.

4. exit -> I created the exit command through strncmp and break function
  if you press 'exit', it returns to the original shell.

5. Text Color -> I changed Text Color through \033[1;33m, \n033[0m

  1;33m means yellow colors and It must be finished with \033[0m.

6. user, name -> I made it keep popping up in the window through getpwuid(getuid())->pw_name

  OS: Ubuntu 18.04
  
  # ㅁㄴㅇㄻㄴㄴ
  * 123
