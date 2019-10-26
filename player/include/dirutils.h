#ifndef __DIRUTILS__
#define __DIRUTILS__

#include <dirent.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <sstream>

using namespace std;

namespace UD {

int parse_dir(vector<string> &vec, const char *root_dir);

} // namespace UD

#endif