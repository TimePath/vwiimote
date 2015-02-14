#pragma once

#include <assert.h>
#include <error.h>
#include <iostream>
#include <stdint.h>

#define var auto
#define val const var
#define loop for(;;)

#define zero(struct) memset(&struct, 0, sizeof struct)
