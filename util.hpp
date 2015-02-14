#pragma once

#include <assert.h>
#include <bits/unique_ptr.h>
#include <error.h>
#include <iostream>
#include <stdint.h>
#include <sys/un.h>

#define var auto
#define val const var
#define loop for(;;)

template<typename T>
void zero(T &s) {
    memset(&s, 0, sizeof s);
}
