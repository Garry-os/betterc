#include <betterc/format.h>
#include <stdio.h>

int main() {
    String test = format("Hello World {}!", 0.5f);
    printf("%s\n", test.data);

    return 0;
}
