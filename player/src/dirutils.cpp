#include "dirutils.h"
#include <dirent.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <sstream>

using namespace std;

namespace UD {

int parse_dir(vector<string> &vec, const char *root_dir) {
    DIR *dir;
    struct dirent *ent;
    if (NULL == (dir = opendir(root_dir))) {
        cout << "could not open directory" << '\n';
        return EXIT_FAILURE;
    }
    
    while (NULL != (ent = readdir(dir))) {
        if (ent->d_type == DT_REG) {
            std::stringstream ss;
            ss << root_dir << '/' << ent->d_name;
            vec.push_back(ss.str().c_str());
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}

} // namespace UD
