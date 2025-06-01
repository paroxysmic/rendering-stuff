#include <stdio.h>
#include <string.h>
unsigned long hashcode = 0x21DD09EC;
unsigned long check_password(const char* p) {
    int* ip = (int*)p;
    int i;
    int res = 0;
    for (i = 0; i < 5; i++) {
        res += ip[i];
    }
    return res;
}
int main(){
  
}
// we want to find the value of p that's 20 bytes long, and returns the hashcode above.