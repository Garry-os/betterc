#include <betterc/format.h>
#include <betterc/print.h>
#include <stdio.h>

int main() {
    String test = format("{} {} {}!", "Hello World!", (void*)0xFFF, false);
    printf("%s\n", test.data);

    println("Hello World {}", 0.05f);

    return 0;
}
