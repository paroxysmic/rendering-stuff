#include <iostream>
#include <string.h>
#include "mlib.h"
int main(){
    vec2 v0 = vec2(1, 0);
    vec2 v1 = vec2(0, 1);
    v0.desc();
    (v0+v1).desc();
    (v0-v1).desc();
    (v0 * 4.0).desc();
    (v0 / 4.0).desc();
    (v1.norm()).desc();
    return 0;
}
