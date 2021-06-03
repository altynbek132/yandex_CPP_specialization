#pragma once

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)

// usage:
// #define UNIQ_ID GLUE(_var, __LINE__)
