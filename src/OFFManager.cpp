#include "OFFManager.h"

bool OFFFileHandler::read(std::string& filename, Mesh& mesh) {
    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return false;
    }

    if (!CGAL::IO::read_OFF(input, mesh)) {
        std::cerr << "Error: invalid OFF file" << std::endl;
        return false;
    }

    return true;
}

//bool OFFFileHandler::write(const std::string& filename, const Mesh& mesh) {
//    std::ofstream output(filename);
//    if (!output) {
//        std::cerr << "Error: cannot open file " << filename << std::endl;
//        return false;
//    }
//
//    if (!CGAL::IO::write_OFF(output, mesh)) {
//        std::cerr << "Error: cannot write OFF file" << std::endl;
//        return false;
//    }
//
//    return true;
//}
